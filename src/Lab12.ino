#include "env.h"
#include "oled-wing-adafruit.h"
#include <blynk.h>

SYSTEM_THREAD(ENABLED);

OledWingAdafruit display;

#include "MQTT.h"

void callback(char *topic, byte *payload, unsigned int length);

MQTT client("lab.thewcl.com", 1883, callback);

void setup()
{
  Serial.begin(9600);
  Blynk.begin(AUTH);

  display.setup();
  display.clearDisplay();
  display.display();
}

void loop()
{
  Blynk.run();
  display.loop();

  if (client.isConnected())
  {
    client.loop();
  }
  else
  {
    client.connect(System.deviceID());
  }
}

void callback(char *topic, byte *payload, unsigned int length)
{
  // write my code here
}