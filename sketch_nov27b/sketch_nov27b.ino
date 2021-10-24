#include <Servo.h>

Servo servo;
void setup() {
  servo.attach(9);
}

void loop() {
  int val = analogRead(1);
  int angle = map(val, 0, 1023, 0, 179);

  servo.write(angle);
  delay(10);
}
