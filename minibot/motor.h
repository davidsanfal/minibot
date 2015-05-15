#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

//Motor Rigth
int encoderRPinA = 2;
int encoderRPinB = 3;
int valRNew = 0;
int valROld = 0;
volatile int encoderRPos = 0;
volatile int mR = LOW;

void CountRB()
{
  if (mR == LOW) {
    encoderRPos--;
  }
  else {
    encoderRPos++;
  }
}
void StateRA()
{
  mR = digitalRead(encoderRPinA);
}

//Motor Left
int encoderLPinA = 4;
int encoderLPinB = 5;
int valLNew = 0;
int valLOld = 0;
volatile int encoderLPos = 0;
volatile int mL = LOW;

void CountLB()
{
  if (mL == LOW) {
    encoderLPos--;
  }
  else {
    encoderLPos++;
  }
}
void StateLA()
{
  mL = digitalRead(encoderLPinA);
}

void setup_motors() {
  attachInterrupt(encoderRPinB, CountRB, RISING);
  attachInterrupt(encoderRPinA, StateRA, CHANGE);

  attachInterrupt(encoderLPinB, CountLB, RISING);
  attachInterrupt(encoderLPinA, StateLA, CHANGE);
}
