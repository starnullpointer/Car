#include <SPI.h>
#include "Game/game.h"
Game car;
//0 Auto, 1 Manual
int mode = 1;

void setup()
{
  Serial.begin(9600);
  delay(2000);
  Serial.println("=====Test Car Moving=====");
  Wire.begin();
  car.Init();
}

void loop()
{
  car.Update();
}

