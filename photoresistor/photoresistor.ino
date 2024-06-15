#define pin_photo A5
#define pin_led A1
#define pin_buzz A0

void setup() {
  Serial.begin(9600);
  pinMode(pin_photo, INPUT_PULLUP);
  pinMode(pin_led, OUTPUT);
  pinMode(pin_buzz, OUTPUT);
}

void loop() {
  int light = analogRead(pin_photo);
  Serial.println(light);
  if (light < 320) {
    digitalWrite(pin_led, HIGH);
    tone(pin_buzz, 1000);
  } else {
    digitalWrite(pin_led, LOW);
    tone(pin_buzz, 50);
  }
}
