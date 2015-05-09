#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

int encoderRPinA = 2;
int encoderRPinB = 3;
int valRNew = 0;
int valROld = 0;
volatile int encoderRPos = 0;
volatile int mR = LOW;

//Motor L
int encoderLPinA = 4;
int encoderLPinB = 5;
int valLNew = 0;
int valLOld = 0;
volatile int encoderLPos = 0;
volatile int mL = LOW;

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
  pinMode (encoderRPinA, INPUT);
  pinMode (encoderRPinB, INPUT);
  attachInterrupt(1, CountRB, CHANGE);
  attachInterrupt(0, StateRA, RISING);

  pinMode (encoderLPinA, INPUT);
  pinMode (encoderLPinB, INPUT);
  attachInterrupt(1, CountLB, CHANGE);
  attachInterrupt(0, StateLA, RISING);
}
