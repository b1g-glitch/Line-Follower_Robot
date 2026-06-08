#include <AFMotor.h>

//Sensor pins
#define LEFT_SENSOR A0
#define RIGHT_SENSOR A1

//Create motor objects for 4WD (using 4 motors)
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

int speed_val = 150; //Motor speed (0 to 255)

void setup() {
  Serial.begin(9600);
  pinMode(LEFT_SENSOR, INPUT);
  pinMode(RIGHT_SENSOR, INPUT);
}

void loop() {
  int left_val = digitalRead(LEFT_SENSOR);
  int right_val = digitalRead(RIGHT_SENSOR);

  //0 = White (Reflective), 1 = Black (Line).
  // You might need to swap logic based on your sensor's output.

  if (left_val == 0 && right_val == 0) {
    // Both sensors on white: Move Forward
    moveForward();
  } 
  else if (left_val == 1 && right_val == 0) {
    // Left sensor on line: Turn Left
    turnLeft();
  } 
  else if (left_val == 0 && right_val == 1) {
    // Right sensor on line: Turn Right
    turnRight();
  } 
  else {
    //Both sensors on line or error: Stop
    stopRobot();
  }
}

void moveForward() {
  motor1.run(FORWARD); motor2.run(FORWARD);
  motor3.run(FORWARD); motor4.run(FORWARD);
  setSpeed(speed_val);
}

void turnLeft() {
  //For a true turn, run left side backward, right side forward.
  motor1.run(BACKWARD); motor2.run(FORWARD);
  motor3.run(BACKWARD); motor4.run(FORWARD);
  setSpeed(speed_val);
}

void turnRight() {
  motor1.run(FORWARD); motor2.run(BACKWARD);
  motor3.run(FORWARD); motor4.run(BACKWARD);
  setSpeed(speed_val);
}

void stopRobot() {
  motor1.run(RELEASE); motor2.run(RELEASE);
  motor3.run(RELEASE); motor4.run(RELEASE);
}

void setSpeed(int sp) {
  motor1.setSpeed(sp); motor2.setSpeed(sp);
  motor3.setSpeed(sp); motor4.setSpeed(sp);
}