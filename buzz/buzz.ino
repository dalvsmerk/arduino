#define pin_buzz A0
#define pin_handle A1

void setup() {
  pinMode(pin_buzz, OUTPUT);
  // pinMode(pin_handle, INPUT);
}

void loop() {
  int reading = analogRead(pin_handle);
  Serial.println(reading);

  int tone_hz = map(reading, 0, 1023, 50, 1000);
  tone(pin_buzz, tone_hz);
}
