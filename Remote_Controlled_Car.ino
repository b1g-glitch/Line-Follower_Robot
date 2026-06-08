#include <AFMotor.h>

AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

int speedVal = 150;

void setup() {
  Serial.begin(9600);
  Serial.println("WASD control ready");
  Serial.println("W = forward");
  Serial.println("S = backward");
  Serial.println("A = left");
  Serial.println("D = right");
  Serial.println("X = stop");
  Serial.println("1 = slow, 2 = medium, 3 = fast");
}

void setAllSpeeds(int spd) {
  motor1.setSpeed(spd);
  motor2.setSpeed(spd);
  motor3.setSpeed(spd);
  motor4.setSpeed(spd);
}

void forward() {
  setAllSpeeds(speedVal);
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
}

void backward() {
  setAllSpeeds(speedVal);
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
}

void left() {
  setAllSpeeds(speedVal);
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void right() {
  setAllSpeeds(speedVal);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void stopRobot() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void loop() {
  if (Serial.available() > 0) {
    char cmd = tolower(Serial.read());

    if (cmd == 'w') {
      forward();
      Serial.println("Forward");
    }
    else if (cmd == 's') {
      backward();
      Serial.println("Backward");
    }
    else if (cmd == 'a') {
      left();
      Serial.println("Left");
    }
    else if (cmd == 'd') {
      right();
      Serial.println("Right");
    }
    else if (cmd == 'x') {
      stopRobot();
      Serial.println("Stop");
    }
    else if (cmd == '1') {
      speedVal = 100;
      Serial.println("Speed = 100");
    }
    else if (cmd == '2') {
      speedVal = 150;
      Serial.println("Speed = 150");
    }
    else if (cmd == '3') {
      speedVal = 255;
      Serial.println("Speed = 255");
    }
  }
}