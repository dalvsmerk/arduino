#define LED_DIGITAL_PIN 12
#define LED_ANALOG_PIN 11

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_DIGITAL_PIN, OUTPUT);
  pinMode(LED_ANALOG_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);

  if (sensorValue > 500) {
    digitalWrite(LED_DIGITAL_PIN, HIGH);
  } else {
    digitalWrite(LED_DIGITAL_PIN, LOW);
  }

  int intensity = map(sensorValue, 0, 1023, 0, 255);

  analogWrite(LED_ANALOG_PIN, intensity);

  // for (int i = 0; i <= 255; i++) {
  //   analogWrite(LED_ANALOG_PIN, i);
  //   delay(2);
  // }

  // for (int i = 255; i >= 0; i--) {
  //   analogWrite(LED_ANALOG_PIN, i);
  //   delay(2);
  // }

  delay(1);
}
