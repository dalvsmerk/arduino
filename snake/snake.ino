#define OP_NOOP       0x0
#define OP_DIGIT0     0x1
#define OP_DIGIT1     0x2
#define OP_DIGIT2     0x3
#define OP_DIGIT3     0x4
#define OP_DIGIT4     0x5
#define OP_DIGIT5     0x6
#define OP_DIGIT6     0x7
#define OP_DIGIT7     0x8
#define OP_DECODE     0x9
#define OP_INTENSITY  0xA
#define OP_SCAN_LIMIT 0xB
#define OP_SHUTDOWN   0xC
#define OP_TEST       0xF

class Display8x8
{
private:
  int pinData;
  int pinClock;
  int pinLoad;

public:
  Display8x8(int pinData, int pinClock, int pinLoad) {
    pinData = pinData;
    pinClock = pinClock;
    pinLoad = pinLoad;

    pinMode(pinData, OUTPUT);
    pinMode(pinClock, OUTPUT);
    pinMode(pinLoad, OUTPUT);

    digitalWrite(pinLoad, HIGH);
  }

  void init() {
    // unsigned int res = sendBytes(OP_SHUTDOWN, 1);
    // Serial.println(res, BIN);

    sendBytes(OP_TEST, 0x0);
    sendBytes(OP_SCAN_LIMIT, 0x7);
    sendBytes(OP_DECODE, 0x0);

    for (int i = 0; i < 8; i++) {
      // Clear each row
      unsigned int res = sendBytes(i+1, 0x0);
      // Serial.println(res, BIN);
    }

    sendBytes(OP_SHUTDOWN, 0);
  }

  void clear() {
    // for (int i = 0; i < 8; i++) {
    //   for (int j = 0; i < 8; i++) {
    //     state[i][j] = LOW;
    //   }
    // }
  }

  unsigned short sendBytes(byte op, byte data) {
    unsigned short dataByte = 0x00 | data;
    unsigned short packet = (op << 8) | dataByte;

    Serial.print("OP 0x");
    Serial.print(op, HEX);
    Serial.print(": ");
    Serial.print("0b");
    Serial.println(packet, BIN);

    digitalWrite(pinLoad, LOW);
    shiftOut(pinData, pinClock, MSBFIRST, packet);
    digitalWrite(pinLoad, HIGH);

    return packet;
  }
};

int pinData = 4;
int pinClock = 3;
int pinLoad = 2;

Display8x8 disp(pinData, pinClock, pinLoad);

void setup() {
  Serial.begin(9600);
  disp.init();
}

void loop() {
  // int val = digitalRead(8);
  // Serial.println(val);
}
