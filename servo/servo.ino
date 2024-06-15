int serialPin = 4;
int latchPin = 3;
int clockPin = 2;
int yPin = A5;

/**
  a
f   b
  g
e   c
  d

a B10000000
b B01000000
c B00100000
d B00010000
e B00001000
f B00000100
g B00000010
. B00000001 - not connected currently
*/

byte numbers[10] = {
  B11111100,  // 0
  B01100000,  // 1
  B11011010,  // 2
  B11110010,  // 3
  B01100110,  // 4
  B10110110,  // 5
  B10111110,  // 6
  B11100000,  // 7
  B11111110,  // 8
  B11110110,  // 9
};

int yMid = 512;
byte display = numbers[0];
size_t i = 0;
int lastMs = 0;
int debounce = 250;

void setup() {
  Serial.begin(9600);

  pinMode(serialPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(yPin, INPUT);

  lastMs = millis();

  updateShiftRegister();
}

void loop() {
  // delay(500);
  // display = numbers[8]; // debugging of LED segments
  // display = numbers[i];

  int y = analogRead(yPin);
  if (y < 1013) {
    y += 10;
  }
  // Serial.println(y);

  int passedSinceLastUpdate = millis() - lastMs;
  int passedDebounceTime = passedSinceLastUpdate > debounce;

  if (passedDebounceTime) {
    if (y > yMid + 256) {
      if (i == 9) {
        i = 0;
      } else {
        i++;
      }
    } else if (y < yMid - 256) {
      if (i == 0) {
        i = 9;
      } else {
        i--;
      }
    }

    Serial.println(i);

    display = numbers[i];
    lastMs = millis();
  }

  updateShiftRegister();
}

void updateShiftRegister() {
  digitalWrite(latchPin, LOW);
  shiftOut(serialPin, clockPin, LSBFIRST, display);
  digitalWrite(latchPin, HIGH);
}
