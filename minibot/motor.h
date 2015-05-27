#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

//Motor Rigth
const int encoderRPinA = 2;
const int encoderRPinB = 3;
const int dirRPinA = 23;
const int dirRPinB = 25;
const int speedRPin = 6;

int valRNew = 0;
int valROld = 0;
volatile int encoderRPos = 0;
volatile int mR = LOW;


void CountRB()
{
  if (mR == LOW) {
    encoderRPos++;
  }
  else {
    encoderRPos--;
  }
}
void StateRA()
{
  mR = digitalRead(encoderRPinA);
}

//Motor Left
const int encoderLPinA = 4;
const int encoderLPinB = 5;
const int dirLPinA = 27;
const int dirLPinB = 29;
const int speedLPin = 7;
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
  pinMode(dirRPinA, OUTPUT);
  pinMode(dirRPinB, OUTPUT);
  pinMode(speedRPin, OUTPUT);

  attachInterrupt(encoderLPinB, CountLB, RISING);
  attachInterrupt(encoderLPinA, StateLA, CHANGE);
  pinMode(dirLPinA, OUTPUT);
  pinMode(dirLPinB, OUTPUT);
  pinMode(speedLPin, OUTPUT);
}
