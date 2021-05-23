//Dziuba Aleksandr
#include <Arduino.h>
#include <DHT.h>

void PrintTempAndHum(const float &t1, const float &t2, const float &h1, const float &h2);

void WorkMode(const int &but_state, float &t1, float &t2, float &h1, float &h2, DHT &dht, const int *const leds, const int &n_leds);
