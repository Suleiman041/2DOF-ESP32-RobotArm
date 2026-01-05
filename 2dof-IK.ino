#include <ESP32Servo.h>

float x = 4.0;
float y = 5.0;

float l1 = 7.7;
float l2 = 8.5;

Servo servo1;
Servo servo2;

void smoothMoveTogether(Servo &s1, int target1, Servo &s2, int target2, int durationMs) {
  int start1 = s1.read();
  int start2 = s2.read();

  int diff1 = target1 - start1;
  int diff2 = target2 - start2;

  int steps = 60;  // number of increments (increase for smoother motion)

  for (int i = 0; i <= steps; i++) {
    float t = (float)i / steps;

    // linear interpolation
    int pos1 = start1 + diff1 * t;
    int pos2 = start2 + diff2 * t;

    s1.write(pos1);
    s2.write(pos2);

    delay(durationMs / steps);
  }
}


void setup() {
  Serial.begin(115200);

  servo1.attach(32);
  servo2.attach(33);

  // Neutral / center = pointing forward
  servo1.write(90);
  servo2.write(90);

  delay(1000);
}

void loop() {

  // Read X Y if both are available
  if (Serial.available() > 0) {
    float newX = Serial.parseFloat();
    float newY = Serial.parseFloat();

    if (!isnan(newX) && !isnan(newY)) {
      x = newX;
      y = newY;
    }
  }

  double r = sqrt(x*x + y*y);

  if (r < 0.01) return;

  if (r > (l1 + l2) || r < fabs(l1 - l2)) {
    Serial.println("Target out of reach.");
    return;
  }

  double phi1 = acos(((l1*l1)+(r*r)-(l2*l2)) / (2*l1*r));
  double phi2 = atan2(y, x);
  double phi3 = acos(((l1*l1)+(l2*l2)-(r*r)) / (2*l1*l2));

  double th1 = (phi2 - phi1) * RAD_TO_DEG;
  double th2 = (PI - phi3) * RAD_TO_DEG;

  if (isnan(th1) || isnan(th2)) return;

  // Correct mapping:
  int servo1_angle = map(th1, -90, 90, 0, 180);
  int servo2_angle = map(th2, -90, 90, 0, 180);

  smoothMoveTogether(servo1, servo1_angle, servo2, servo2_angle, 500);  // 300 ms move



  Serial.print("Theta 1: "); Serial.println(th1);
  Serial.print("Theta 2: "); Serial.println(th2);
  Serial.print("Servo1: "); Serial.println(servo1_angle);
  Serial.print("Servo2: "); Serial.println(servo2_angle);
  Serial.println();

  delay(50);
}
