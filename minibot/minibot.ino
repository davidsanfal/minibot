#include"robot.h"
#include"motor.h"
#include "DeadReckoning.h"

const int encoder_steps = 1600;
const float wheel_diameter = 80.0;
const float wheelbase = 211.0;

//Step steps[256];

DeadReckoning navegation(wheel_diameter, wheelbase, 1600);
/*
Robot robot(wheelbase, wheel_diameter, encoder_steps,
            1.0, 0.0, 0.0, -100.0, 100,
            1.0, 0.0, 0.0, -100.0, 100);
*/
int preR = 0;
int preL = 0;
int num_steps = 0;
float length_step = 80;
int speedL = 150, speedR = 150;
int dirA = LOW, dirB = HIGH;
bool dirG = true;

int actualLPos = 0;
int actualRPos = 0;
int prevLPos = 0;
int prevRPos = 0;

int steps = 0;

void setup()
{
  Serial.begin (9600);
  setup_motors();
  Serial.println("Inint ...");
  navegation.setObjetivo(1000.0f, 0.0f);
}

void loop()
{
  actualLPos = encoderLPos;
  actualRPos = encoderRPos;
  speedL = 180;
  speedR = 180;
  navegation.calculaDesplazamiento(actualLPos - prevLPos, actualRPos - prevRPos);
  if (!navegation.isFinal()) { // ¿ha llegado al objetivo?
    float real_angle = navegation.getOrientacionObjetivo() - navegation.getActualTheta();
    float angle = (real_angle / (2 * M_PI)) * 360;
    int vueltas = angle / 360;
    angle -= vueltas * 360;
    if (angle > 180) angle = 360 - angle;
    speedL += angle;
    speedR -=  angle;
    if (angle > 45) {
      speedL = -180;
      speedR = 180;
    }
    if (angle < -45) {
      speedL = 180;
      speedR = -180;
    }
    Serial.print(speedL);
    Serial.print(" ; ");
    Serial.print(speedR);
    Serial.print(" ; ");
    Serial.print(navegation.getActualX());
    Serial.print(" ; ");
    Serial.print(navegation.getActualY());
    Serial.print(" ; ");
    Serial.println((real_angle / (2 * M_PI)) * 360);
  }
  else { // objetivo alcanzado, se detienen motores y se desabilitan los timers
    navegation.setObjetivo(1000.0f, 1000.0f);
    steps++;
    speedL = 0;
    speedR = 0;
  }
  if (speedR > 255) speedR = 255;
  if (speedL > 255) speedL = 255;
  if (speedR < -255) speedR = -255;
  if (speedL < -255) speedL = -255;
  analogWrite(speedLPin, abs(speedR));
  analogWrite(speedRPin, abs(speedL));
  if (speedR > 0) {
    digitalWrite(dirRPinB, HIGH);
    digitalWrite(dirRPinA, LOW);
  }
  else {
    digitalWrite(dirRPinB, LOW);
    digitalWrite(dirRPinA, HIGH);
  }
  if (speedL > 0) {
    digitalWrite(dirLPinB, HIGH);
    digitalWrite(dirLPinA, LOW);
  }
  else {
    digitalWrite(dirLPinB, LOW);
    digitalWrite(dirLPinA, HIGH);
  }
  prevLPos = actualLPos;
  prevRPos = actualRPos;
  if(steps > 1) while(1){;}
}

/*void add_step(float angle) {
  Step _step(angle, length_step);
  steps[num_steps] = _step;
  num_steps++;
}
*/

