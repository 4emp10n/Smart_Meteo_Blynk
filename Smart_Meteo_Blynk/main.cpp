//Dziuba Aleksandr
// The second annex should form an external monitoring and
// control the status of light bulbs using a mobile device and
// Blynk system capabilities (including Blynk cloud environment) and
// Wi-Fi mode features ESP8266. Remote status visualization
// temperature, humidity, condition of 3 light bulbs and remote control
// is performed using the widgets of the mobile application Blynk.
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include "Funcs.h"

DHT dht(D7, DHT11);

const int n_leds = 3;
const int led1 = D1;
const int led2 = D2;
const int led3 = D3;
const int leds[n_leds] = {led1, led2, led3};

float prev = millis();

char auth[] = "RBriTm0zV1YEI2fuEXo1rDGNbCtUwLMD";

char ssid[] = "373";
char pass[] = "2899117fifc";

// BLYNK_CONNECTED()
// {
//   Blynk.syncVirtual(V1);
// }

float t1 = dht.readTemperature(), t2 = dht.readTemperature();
float h1 = dht.readHumidity(), h2 = dht.readHumidity();
bool but_state = 0;
BLYNK_WRITE(V1)
{
  if (param.asInt() == HIGH && but_state == 0)
  {
    Serial.println("ON");
    but_state = 1;
  }
  else if (param.asInt() == HIGH && but_state == 1)
  {
    Serial.println("OFF");
    but_state = 0;
  }
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  for (int i = 0; i < n_leds; i++)
  {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }

  Blynk.begin(auth, ssid, pass);
  dht.begin();
}

void loop()
{
  do
  {
    Blynk.run();
  } while (millis() - prev < 30000);
  prev = millis();
  WorkMode(but_state, t1, t2, h1, h2, dht, leds, n_leds);
}

// Error
// ON
// t1: 23.40
// t2: 23.90
// h1: 32.00
// h2: 31.00
// t1: 23.30
// t2: 23.90
// h1: 32.00
// h2: 32.00
// OFF
// t1: 23.30
// t2: 23.90
// h1: 32.00
// h2: 32.00
// t1: 23.40
// t2: 23.90
// h1: 32.00
// h2: 32.00
// t1: 23.40
// t2: 23.90
// h1: 31.00
// h2: 32.00