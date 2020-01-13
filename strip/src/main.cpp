
#include <Arduino.h>
#include "colors.h"
#include "strip.h"

ColorPin pins[] = {3, 5, 6, 9};

RGBWStrip strip(pins);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  strip.show();
  delay(10);
}