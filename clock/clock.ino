#include <DS18B20.h>

// #include <DHT11.h>

#include <Ds1302.h>

#define SERIAL_PIN 7
#define LATCH_PIN 6
#define CLOCK_PIN 5

#define D1_PIN 11
#define D2_PIN 10
#define D3_PIN 9
#define D4_PIN 8

#define CLK_PIN A3
#define DAT_PIN A4
#define RST_PIN A5

#define BTN_PIN 2

#define TEMP_PIN 12

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

byte degree = B11000110;
byte c_letter = B10011100;

uint32_t prev_now = 0;
uint32_t time_prev = 0;

Ds1302 rtc(RST_PIN, CLK_PIN, DAT_PIN);

byte value = numbers[2];
byte digit = 1;
// byte digit_number_map[4] = {3, 2, 1, 0};
byte symbol_map[4] = { numbers[3], numbers[2], degree, c_letter };

uint32_t delay_ms = 1;
uint32_t time_ms = 1000;

struct mmss_t {
  uint8_t mm;
  uint8_t ss;
};

mmss_t current;

struct parts_t {
  uint8_t first;
  uint8_t second;
};

parts_t part(uint8_t num);

parts_t part(uint8_t num) {
  parts_t parts;
  parts.first = (num - num % 10) / 10;
  parts.second = num % 10;
  return parts;
}

volatile enum Mode {
  TIME,
  TEMP
} mode;

// DHT11 dht11(TEMP_PIN);
int temp = 0;
uint32_t temp_time;

DS18B20 ds(TEMP_PIN);

void setup() {
  Serial.begin(9600);

  rtc.init();

  if (rtc.isHalted()) {
    Serial.println("RTC is halted. Setting time...");

    Ds1302::DateTime dt = {
      .year = 24,
      .month = Ds1302::MONTH_MAY,
      .day = 14,
      .hour = 18,
      .minute = 1,
      .second = 59,
      .dow = Ds1302::DOW_TUE
    };

    rtc.setDateTime(&dt);
  }

  // put your setup code here, to run once:
  pinMode(SERIAL_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);

  pinMode(D1_PIN, OUTPUT);
  pinMode(D2_PIN, OUTPUT);
  pinMode(D3_PIN, OUTPUT);
  pinMode(D4_PIN, OUTPUT);

  pinMode(BTN_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(BTN_PIN), next_mode_interupt, RISING);

  prev_now = millis();
  time_prev = millis();

  select_digit(1);
  updateShiftRegister(numbers[3]);

  select_digit(2);
  updateShiftRegister(numbers[2]);

  mode = TEMP;

  temp_time = millis();
  ds.setResolution(9);
  temp = ds.getTempC();
}

void loop() {
  uint32_t now = millis();

  if (digit == 5) {
    digit = 1;
  }

  if ((now - prev_now) < delay_ms) return;
  prev_now = now;

  // byte number_to_display = digit_number_map[digit - 1];

  // clear();
  display_digit(digit, symbol_map[digit - 1]);

  digit++;

  now = millis();

  if (mode == TIME) {
    if ((now - time_prev) >= time_ms) {
      Ds1302::DateTime time_now;

      rtc.getDateTime(&time_now);

      current.mm = time_now.minute;
      current.ss = time_now.second;

      parts_t parts_mm = part(current.mm);
      parts_t parts_ss = part(current.ss);

      symbol_map[0] = numbers[parts_mm.first];
      symbol_map[1] = numbers[parts_mm.second];
      symbol_map[2] = numbers[parts_ss.first];
      symbol_map[3] = numbers[parts_ss.second];

      Serial.print(time_now.hour);
      Serial.print(':');
      Serial.print(time_now.minute);
      Serial.print(':');
      Serial.print(time_now.second);
      Serial.println();

      time_prev = now;
    }
  } else {
    if ((millis() - temp_time) > 60000) {
      temp = static_cast<int>(ds.getTempC());
      temp_time = millis();
    }

    parts_t digits = part(temp);

    symbol_map[0] = numbers[digits.first];
    symbol_map[1] = numbers[digits.second];
    symbol_map[2] = degree;
    symbol_map[3] = c_letter;
  }
}

uint32_t last_intr = millis();
uint32_t debounce = 500;

void next_mode_interupt() {
  uint32_t now = millis();

  if ((now - last_intr) < debounce) return;

  if (mode == TIME) {
    mode = TEMP;
  } else {
    mode = TIME;
  }
}

void display_digit(byte digit, byte symbol) {
  updateShiftRegister(0);
  select_digit(digit);
  updateShiftRegister(symbol);
}

void updateShiftRegister(byte serial) {
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(SERIAL_PIN, CLOCK_PIN, LSBFIRST, serial);
  digitalWrite(LATCH_PIN, HIGH);
}

byte select_digit(byte digit) {
  if (digit > 4) {
    return 1;
  }

  switch (digit) {
    case 1:
      digitalWrite(D1_PIN, LOW);
      digitalWrite(D2_PIN, HIGH);
      digitalWrite(D3_PIN, HIGH);
      digitalWrite(D4_PIN, HIGH);
      break;
    case 2:
      digitalWrite(D1_PIN, HIGH);
      digitalWrite(D2_PIN, LOW);
      digitalWrite(D3_PIN, HIGH);
      digitalWrite(D4_PIN, HIGH);
      break;
    case 3:
      digitalWrite(D1_PIN, HIGH);
      digitalWrite(D2_PIN, HIGH);
      digitalWrite(D3_PIN, LOW);
      digitalWrite(D4_PIN, HIGH);
      break;
    case 4:
      digitalWrite(D1_PIN, HIGH);
      digitalWrite(D2_PIN, HIGH);
      digitalWrite(D3_PIN, HIGH);
      digitalWrite(D4_PIN, LOW);
      break;
    default: break;
  }

  return 0;
}

void clear() {
  digitalWrite(D1_PIN, HIGH);
  digitalWrite(D2_PIN, HIGH);
  digitalWrite(D3_PIN, HIGH);
  digitalWrite(D4_PIN, HIGH);
}
