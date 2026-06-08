#include <AFMotor.h>
#include <SoftwareSerial.h>

SoftwareSerial BT(2, 3);

AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

int speedVal = 150;

void setup() {
  Serial.begin(9600);
  BT.begin(9600);
  Serial.println("Bluetooth ready");
}

bool m1_invert = false;
bool m2_invert = true;
bool m3_invert = true;
bool m4_invert = false;

void runMotor(AF_DCMotor &m, int dir, bool invert) {
  if (invert) {
    if (dir == FORWARD) dir = BACKWARD;
    else if (dir == BACKWARD) dir = FORWARD;
  }
  m.run(dir);
}

void setAllSpeeds(int spd) {
  motor1.setSpeed(spd);
  motor2.setSpeed(spd);
  motor3.setSpeed(spd);
  motor4.setSpeed(spd);
}

void forward() {
  setAllSpeeds(speedVal);

  runMotor(motor1, FORWARD, m1_invert);
  runMotor(motor2, FORWARD, m2_invert);
  runMotor(motor3, FORWARD, m3_invert);
  runMotor(motor4, FORWARD, m4_invert);
}

void backward() {
  setAllSpeeds(speedVal);

  runMotor(motor1, BACKWARD, m1_invert);
  runMotor(motor2, BACKWARD, m2_invert);
  runMotor(motor3, BACKWARD, m3_invert);
  runMotor(motor4, BACKWARD, m4_invert);
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
  if (BT.available()) {
    char cmd = tolower(BT.read());
    Serial.println(cmd);

    if (cmd == 'w') forward();
    else if (cmd == 's') backward();
    else if (cmd == 'a') left();
    else if (cmd == 'd') right();
    else if (cmd == 'x') stopRobot();
  }
}