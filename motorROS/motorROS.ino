#define USE_SOFTWARE_SERIAL 1

#include <AFMotor.h>
#include <Servo.h>

AF_DCMotor motorFR(4);
AF_DCMotor motorFL(1);
AF_DCMotor motorBL(2);
AF_DCMotor motorBR(3);

Servo servoFL;
Servo servoFR;
Servo servoBL;
Servo servoBR;

void setup() {
  Serial2.begin(9600);

  servoFL.attach(A0);  // верхний левый
  servoFR.attach(A2);  // верхний правый
  servoBL.attach(A1);  // нижний левый
  servoBR.attach(A3);  // нижний правый

  motorFR.setSpeed(255);
  motorFL.setSpeed(255);
  motorBL.setSpeed(255);
  motorBR.setSpeed(255);

  motorFR.run(RELEASE);
  motorFL.run(RELEASE);
  motorBL.run(RELEASE);
  motorBR.run(RELEASE);
}

void loop() {
  if (Serial2.available()) {
    int command = Serial2.read();
    if (command == 5) {  // все сервы в 45 градусов
      servoFL.write(90);
      servoFR.write(90);
      servoBL.write(90);
      servoBR.write(90);
    }
    if (command == 4) {  //положение серв для переноса
      servoFL.write(45);
      servoFR.write(135);
      servoBL.write(135);
      servoBR.write(45);
    }
    if (command == 0) {  // едем вперед
      servoFL.write(45);
      servoFR.write(135);
      servoBL.write(135);
      servoBR.write(45);
      forward();
    } else if (command == 1) {  // едем назад
      servoFL.write(45);
      servoFR.write(135);
      servoBL.write(135);
      servoBR.write(45);
      backward();
    } else if (command == 2) {  // едем направо
      servoFL.write(135);
      servoFR.write(45);
      servoBL.write(45);
      servoBR.write(135);
      right();
    } else if (command == 3) {  // едем налево
      servoFL.write(135);
      servoFR.write(45);
      servoBL.write(45);
      servoBR.write(135);
      left();
    } else if (command == 6) {
      servoFL.write(90);
      servoFR.write(90);
      servoBL.write(90);
      servoBR.write(90);
      leftP();
    } else if (command == 7) {
      servoFL.write(90);
      servoFR.write(90);
      servoBL.write(90);
      servoBR.write(90);
      rightP();
    } else if (command == 10) {
      stop();
    } else {
      stop();
    }
  }
}

void forward() {
  motorFL.run(FORWARD);
  motorFR.run(FORWARD);
  motorBL.run(FORWARD);
  motorBR.run(FORWARD);

  motorFL.setSpeed(255);
  motorFR.setSpeed(255);
  motorBL.setSpeed(255);
  motorBR.setSpeed(255);
}

void backward() {
  motorFL.run(BACKWARD);
  motorFR.run(BACKWARD);
  motorBL.run(BACKWARD);
  motorBR.run(BACKWARD);

  motorFL.setSpeed(255);
  motorFR.setSpeed(255);
  motorBL.setSpeed(255);
  motorBR.setSpeed(255);
}

void right() {
  motorFL.run(FORWARD);
  motorFR.run(BACKWARD);
  motorBL.run(BACKWARD);
  motorBR.run(FORWARD);

  motorFL.setSpeed(255);
  motorFR.setSpeed(255);
  motorBL.setSpeed(255);
  motorBR.setSpeed(255);
}

void left() {
  motorFL.run(BACKWARD);
  motorFR.run(FORWARD);
  motorBL.run(FORWARD);
  motorBR.run(BACKWARD);

  motorFL.setSpeed(255);
  motorFR.setSpeed(255);
  motorBL.setSpeed(255);
  motorBR.setSpeed(255);
}

void leftP() {
  motorFL.run(FORWARD);
  motorFR.run(BACKWARD);
  motorBL.run(FORWARD);
  motorBR.run(BACKWARD);

  motorFL.setSpeed(255);
  motorFR.setSpeed(255);
  motorBL.setSpeed(255);
  motorBR.setSpeed(255);
}

void rightP() {
  motorFL.run(BACKWARD);
  motorFR.run(FORWARD);
  motorBL.run(BACKWARD);
  motorBR.run(FORWARD);

  motorFL.setSpeed(255);
  motorFR.setSpeed(255);
  motorBL.setSpeed(255);
  motorBR.setSpeed(255);
}

void stop() {
  motorFL.setSpeed(0);
  motorFR.setSpeed(0);
  motorBL.setSpeed(0);
  motorBR.setSpeed(0);
}