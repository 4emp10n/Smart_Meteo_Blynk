//Dziuba Aleksandr
#include "Funcs.h"

void PrintTempAndHum(const float &t1, const float &t2, const float &h1, const float &h2)
{
    Serial.print("t1: ");
    Serial.println(t1);
    Serial.print("t2: ");
    Serial.println(t2);
    Serial.print("h1: ");
    Serial.println(h1);
    Serial.print("h2: ");
    Serial.println(h2);
}

void WorkMode(const int &but_state, float &t1, float &t2, float &h1, float &h2, DHT &dht, const int *const leds, const int &n_leds)
{
    t1 = dht.readTemperature();
    h1 = dht.readHumidity();

    if (isnan(t1) || isnan(t2) || isnan(h1) || isnan(h2))
    {
        t2 = t1;
        h2 = h1;
        Serial.println("Error");
    }
    else
    {
        PrintTempAndHum(t1, t2, h1, h2);

        for (int i = 0; i < n_leds; i++)
        {
            digitalWrite(leds[i], but_state);
        }

        if (abs(t1 - t2) >= 1 && abs(h1 - h2) >= 1)
        {
            for (int i = 0; i < n_leds; i++)
            {
                digitalWrite(leds[i], !but_state);
            }
            t2 = t1;
            h2 = h1;
        }
        else if (abs(t1 - t2) >= 1)
        {
            digitalWrite(leds[0], !but_state);
            digitalWrite(leds[1], but_state);
            digitalWrite(leds[2], but_state);
            t2 = t1;
        }
        else if (abs(h1 - h2) >= 1)
        {
            digitalWrite(leds[0], but_state);
            digitalWrite(leds[1], !but_state);
            digitalWrite(leds[2], but_state);
            h2 = h1;
        }
        else
        {
            for (int i = 0; i < n_leds; i++)
            {
                digitalWrite(leds[i], but_state);
            }
        }
    }
}
