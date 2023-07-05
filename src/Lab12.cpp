/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#line 1 "/Users/ashleylibasci/IoTFolderLabs/Lab12/src/Lab12.ino"
#include "env.h"
#include "oled-wing-adafruit.h"
#include <blynk.h>
#include "Particle.h"


void setup();
void loop();
#line 7 "/Users/ashleylibasci/IoTFolderLabs/Lab12/src/Lab12.ino"
SYSTEM_THREAD(ENABLED);

OledWingAdafruit display;

#include "MQTT.h"

void callback(char *topic, byte *payload, unsigned int length);

MQTT client("lab.thewcl.com", 1883, callback);

void setup()
{
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN);

  display.setup();
  display.clearDisplay();
  display.display();

  client.subscribe("Lab12Topic/message");
  client.publish("Lab12Topic/name", "test message");
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
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  Serial.printf("%s", p);
  Serial.println();

  if (String(p).equals("high"))
  {
    digitalWrite(D7, HIGH);
  }
  else if (String(p).equals("low"))
  {
    digitalWrite(D7, LOW);
  }
  else
  {
    Serial.println(p);
  }
}