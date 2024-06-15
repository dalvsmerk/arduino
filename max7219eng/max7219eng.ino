#define u16 unsigned short
#define u8 unsigned char

enum RegisterEnum
{
  NO_OP = 0x0,
  D0 = 0x1,
  D1 = 0x2,
  D2 = 0x3,
  D3 = 0x4,
  D4 = 0x5,
  D5 = 0x6,
  D6 = 0x7,
  D7 = 0x8,
  DECODE = 0x9,
  INTENSITY = 0xA,
  SCAN = 0xB,
  SHUTDOWN = 0xC,
  TEST = 0xF
};

enum DecodeModeEnum
{
  NO_DECODE = 0x0,
  DECODE_D0 = 0x1,
  DECODE_D0_D3 = 0xF,
  DECODE_D0_D7 = 0xFF
};

class DecodeMode
{
public:
  static DecodeModeEnum noDecode() { return NO_DECODE; }
  static DecodeModeEnum decodeD0() { return DECODE_D0; }
  static DecodeModeEnum decodeD0D3() { return DECODE_D0_D3; }
  static DecodeModeEnum decodeD0D7() { return DECODE_D0_D7; }
};

static const u8 DIGITS[10] = {
    0b01111110, // 0
    0b00110000, // 1
    0b01101101, // 2
    0b01111001, // 3
    0b00110010, // 4
    0b01011011, // 5
    0b01011111, // 6
    0b01110000, // 7
    0b01111111, // 8
    0b01111011, // 9
};

class Max7219Eng
{
public:
  Max7219Eng(int pinDin, int pinClk, int pinLoad, short digits) : pinDin(pinDin),
                                                                  pinClk(pinClk),
                                                                  pinLoad(pinLoad),
                                                                  digits(digits)
  {
    if (digits > 8)
    {
      digits = 8;
    }
  }

  void init()
  {
    digitalWrite(pinLoad, LOW);

    transfer(SHUTDOWN, 0);
    transfer(SCAN, digits - 1);
    transfer(DECODE, 0x0F);
    transfer(SHUTDOWN, 1);
  }

  void setDecodeMode(DecodeModeEnum mode)
  {
    transfer(SHUTDOWN, 0);
    transfer(DECODE, mode);
    transfer(SHUTDOWN, 1);
  }

  /**
   * @param percent Will clamp to [0; 100] if outside of the range
   */
  void setIntensity(u8 percent)
  {
    if (percent > 100)
    {
      percent = 100;
    }

    u8 intensity = map(percent, 0, 100, 0, 15);

    transfer(SHUTDOWN, 0);
    transfer(INTENSITY, intensity);
    transfer(SHUTDOWN, 1);
  }

  void fromOneToFour()
  {
    transfer(D0, 0x01);
    transfer(D1, 0x02);
    transfer(D2, 0x03);
    transfer(D3, 0x04);
  }

  void zeros()
  {
    transfer(D0, 0x00);
    transfer(D1, 0x00);
    transfer(D2, 0x00);
    transfer(D3, 0x00);
  }

  /**
   * @param degreesC Will clamp to [0; 99] if out of range
   */
  void temperature(u8 degreesC)
  {
    if (degreesC > 99)
    {
      degreesC = 99;
    }

    u8 first = (degreesC - degreesC % 10) / 10;
    u8 second = degreesC % 10;

    transfer(D0, DIGITS[first]);
    transfer(D1, DIGITS[second]);
    transfer(D2, 0b01100011);
    transfer(D3, 0b01001110);
  }

  void blink(int delayMs)
  {
    transfer(SHUTDOWN, 0);
    delay(delayMs);
    transfer(SHUTDOWN, 1);
    delay(delayMs);
    transfer(SHUTDOWN, 0);
    delay(delayMs);
    transfer(SHUTDOWN, 1);
    delay(delayMs);
    transfer(SHUTDOWN, 0);
    delay(delayMs);
    transfer(SHUTDOWN, 1);
  }

private:
  int pinDin;
  int pinClk;
  int pinLoad;
  short digits;

  void transfer(u8 addr, u8 data)
  {
    // LOAD has to be LOW the whole time during transmission
    digitalWrite(pinLoad, LOW);

    // Why this doesn't work?
    // u16 packet = addr << 8 | data;
    // shiftOut(pinDin, pinClk, MSBFIRST, packet);

    // But this works:
    shiftOut(pinDin, pinClk, MSBFIRST, addr);
    shiftOut(pinDin, pinClk, MSBFIRST, data);

    // Latch 16-bit DIN from shift register on LOAD rise
    digitalWrite(pinLoad, HIGH);
    digitalWrite(pinLoad, LOW);
  }
};

#define DIN 4
#define CLK 3
#define LOAD 2
#define DIGITS 4

Max7219Eng dsp(DIN, CLK, LOAD, DIGITS);

void setup()
{
  Serial.begin(9600);
  Serial.println("hello");

  pinMode(DIN, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(LOAD, OUTPUT);

  dsp.init();
  dsp.setIntensity(100);

  // dsp.setDecodeMode(DecodeMode::decodeD0D3());
  // dsp.fromOneToFour();

  // dsp.blink(200);

  dsp.setDecodeMode(DecodeMode::noDecode());
  dsp.temperature(35);
}

void loop()
{
  // dsp.zeros();
  // dsp.update();
}
