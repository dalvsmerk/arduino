#define u16 unsigned short
#define u8 unsigned char

enum Max7219EngRegister
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

class Max7219Eng
{
public:
  Max7219Eng(int pinDin, int pinClk, int pinLoad, short digits)
      : pinDin(pinDin), pinClk(pinClk), pinLoad(pinLoad), digits(digits)
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

  void update()
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

private:
  int pinDin;
  int pinClk;
  int pinLoad;
  short digits;

  void transfer(u8 addr, u8 data)
  {

    digitalWrite(pinLoad, LOW);

    // Why this doesn't work?
    // u16 packet = addr << 8 | data;
    // shiftOut(pinDin, pinClk, MSBFIRST, packet);

    // But this works:
    shiftOut(pinDin, pinClk, MSBFIRST, addr);
    shiftOut(pinDin, pinClk, MSBFIRST, data);
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
  dsp.update();
}

void loop()
{
  // dsp.zeros();
  // dsp.update();
}
