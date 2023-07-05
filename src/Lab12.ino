#include "oled-wing-adafruit.h"
#include "Particle.h"

SYSTEM_THREAD(ENABLED);

OledWingAdafruit display;

#include "MQTT.h"

void callback(char *topic, byte *payload, unsigned int length);

MQTT client("lab.thewcl.com", 1883, callback);

void setup()
{
  Serial.begin(9600);

  display.setup();
  display.clearDisplay();
  display.display();

  pinMode(D7, OUTPUT);
}

void loop()
{
  display.loop();

  if (client.isConnected())
  {
    client.loop();
  }
  else
  {
    client.connect(System.deviceID());
    client.subscribe("Lab12");
    client.publish("Lab12", "welcome!!");
  }

  if (display.pressedA())
  {
    client.publish("Lab12", "button A pressed");
  }
  if (display.pressedB())
  {
    client.publish("Lab12", "button B pressed");
  }
  if (display.pressedC())
  {
    client.publish("Lab12", "button C pressed");
  }
}

void callback(char *topic, byte *payload, unsigned int length)
{
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  Serial.printf("%s", p);
  Serial.println();

  if (String(p).equals("1"))
  {
    Serial.println("1");
    digitalWrite(D7, HIGH);
  }
  else if (String(p).equals("0"))
  {
    digitalWrite(D7, LOW);
  }
  else
  {
    Serial.println(p);
  }
}