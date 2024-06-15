#define TOP_PIN 10
#define LEFT_PIN 11
#define RIGHT_PIN 6
#define BOTTOM_PIN 9

int lights[4] = { TOP_PIN, LEFT_PIN, RIGHT_PIN, BOTTOM_PIN };

#define X_PIN A0
#define Y_PIN A1

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(lights[i], OUTPUT);
    analogWrite(lights[i], 2);
  }
  pinMode(X_PIN, INPUT);
  pinMode(Y_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  // for (int i = 0; i < 4; i++) {
  //   digitalWrite(lights[i], HIGH);
  // }

  int x_value = analogRead(X_PIN); // from 0 to 1023
  int y_value = analogRead(Y_PIN); // from 0 to 1023

  x_value += 9;
  if (x_value > 1023) {
    x_value = 1023;
  }

  y_value += 15;
  if (y_value > 1023) {
    y_value = 1023;
  }

  int x_norm = map(x_value, 0, 1023, -512, 512);
  int y_norm = map(y_value, 0, 1023, -512, 512);

  Serial.println(x_norm);
  Serial.println(y_norm);
  // delay(400);

  if (x_norm < 0) {
    int intensity = map(x_norm, -512, 0, 255, 0);
    analogWrite(LEFT_PIN, intensity);
  } else {
    int intensity = map(x_norm, 0, 512, 0, 255);
    analogWrite(RIGHT_PIN, intensity);
  }

  if (y_norm < 0) {
    int intensity = map(y_norm, -512, 0, 255, 0);
    analogWrite(TOP_PIN, intensity);
  } else {
    int intensity = map(y_norm, 0, 512, 0, 255);
    analogWrite(BOTTOM_PIN, intensity);
  }
}
