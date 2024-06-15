#define BTN_PIN 2
#define LED_PIN 4

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(BTN_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = digitalRead(BTN_PIN);
  Serial.println(value);

  digitalWrite(LED_BUILTIN, value);
  digitalWrite(LED_PIN, value);

  delay(1);
}
