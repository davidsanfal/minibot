#include"robot.h"
#include"motor.h"

Robot robot(211,
            1.0, 0.0, 0.0, -100.0, 100,
            1.0, 0.0, 0.0, -100.0, 100);


void setup()
{
  Serial.begin (9600);
  setup_motors();
}

void loop()
{
  //  valNew = encoder0Pos;
  //  if (valNew != valOld) {
  //    Serial.print (encoder0Pos, DEC);
  //    Serial.print ("/");
  //    valOld = valNew;
  //  }
  ;
}


