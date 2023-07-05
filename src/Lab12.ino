#include "env.h"
#include "oled-wing-adafruit.h"
#include <blynk.h>

SYSTEM_THREAD(ENABLED);

OledWingAdafruit display;

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth);
}

void loop()
{
}