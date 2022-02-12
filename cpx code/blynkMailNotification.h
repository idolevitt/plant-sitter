/*
 * This file is responsible for triggering the integromat flow using the blynk webhook
 */
// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "XXXXXXXXX" // fill in your blynk template id
#define BLYNK_DEVICE_NAME "XXXXXXXXX" // fill in your bkynk device name
#define BLYNK_AUTH_TOKEN "XXXXXXXXX" // fill in your authentication token

// Comment this out to disable prints and save space
#define BLYNK_PRINT SerialUSB

#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Hardware Serial on Mega, Leonardo, Micro...
#define EspSerial Serial1

// Your ESP8266 baud rate:
#define ESP8266_BAUD 115200

char ssid[] = "XXXXXXXXX"; // fill in your wifi name
char pass[] = "XXXXXXXXX"; // fill in your wifi password

ESP8266 wifi(&EspSerial);

void setupBlynk(){
  Blynk.begin(auth, wifi, ssid, pass);
  Blynk.run();
}

/*
 * send mail if flower needs water/light
 */
void startBlynkFlow(float fhumidity, float flight) {
  Serial.println("blynk flow started");
  if (fhumidity < 15 || flight < 10) {
    Blynk.virtualWrite(V5, 5);
    Serial.println("mail is sent");
  }
}
