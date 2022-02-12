#define TINY_GSM_MODEM_ESP8266
#include <PubSubClient.h>
#include <TinyGsmClient.h>

#include <algorithm>

#define SerialMon Serial
#define SerialAT Serial1
//
TinyGsm modem(SerialAT);
TinyGsmClient client(modem);
