/*
  Sketch finalProject
  This project allows better care to home flowers.
  Using our Plant-Saver you can take care of your plant better:
  - Get notified by mail in real time when there is not enough light for the flower, or the soil is too dry. 
  - See how the flower is feeling in an animated web application.
  - See all stats on the flower and even activate SOS button for the flower when needed.
  - While watering it, get light indication on how much water is needed.
  
  
  The circuit:
    Electric circuit
    Mini speaker
    LEDS
    Light sensor
    Temperature sensor
    ESP8266
  
  Created By:
  Omer_Erman
  Yuval_Spinzi
  Ido_Levitt
*/





#include <Adafruit_CircuitPlayground.h>
#include "defines_and_inclusions.h"
#include "connectToWifi.h"
#include "needWaterSound.h"
#include "MQTTHandler.h"
#include "waterAmountNeeded.h"
#include "webDashboardUpdater.h"
#include "blynkMailNotification.h"
#include "stats_calculator.h"

//define time units
const int SEC = 1000; // 1000ms = 1sec
const int MIN = 60000; // 60000ms = 1min

// used for asynchronous multitasking: making the flower say "water me"
long previousMillisTalk = 0;
long timeIntervalTalk = 15 * MIN;

// used for asynchronous multitasking: showing the amount of water the flower has with blue led lights
long previousMillisWaterAmount = 0;
long timeIntervalWaterAmount = 10 * SEC;

// used for asynchronous multitasking: updating the html web page on the local server
long previousMillisUpdatedWebDashboard = 0;
long timeIntervalUpdatedWebDashboard = 1 * MIN;

// used for asynchronous multitasking: starting BLYNK flow
long previousMillisBlynkFlow = 0;
long timeIntervalBlynkFlow = 60 * MIN;

// used for asynchronous multitasking: starting MQTT flow
long previousMillisMQTTFlow = 0;
long timeIntervalMQTTFlow = 30 * SEC;

// used for asynchronous multitasking: update stats
long previousMillisStatsUpdateFlow = 0;
long timeIntervalStatsUpdateFlow = 5 * SEC;

// initialize stats
float ftemperature = 10.0f;
float flight = 10.0f;
float fhumidity = 10.0f;
float fhealth = 10.0f;

void setup() {
  Serial.begin(115200);
  CircuitPlayground.begin();

  SerialMon.begin(115200);
  delay(1000);
  // connect to Wi-fi
  connectToWifi();
  // connect to MQTT broker
  MQTTBrokerSetup();
  // connect to MQTT
  connectToMQTT();
  // connect to Blynk
  setupBlynk();
}

void loop() {
  unsigned long currentMillis = millis();

  // update stats
  if (currentMillis - previousMillisStatsUpdateFlow > timeIntervalStatsUpdateFlow) {
    previousMillisStatsUpdateFlow = currentMillis;
    update_stats();
  }

  //SOS message - blink red lights and make the flower say "water me"
  if (currentMillis - previousMillisTalk > timeIntervalTalk && fhumidity < 10.0f) {
    previousMillisTalk = currentMillis;
    sosMessage();
  }

  //show the amount of water the flower has with blue led lights
  if (currentMillis - previousMillisWaterAmount > timeIntervalWaterAmount) {
    previousMillisWaterAmount = currentMillis;
    updateWaterStatus(fhumidity / 10);
  }

  //update the html web page on the local server
  if (currentMillis - previousMillisUpdatedWebDashboard > timeIntervalUpdatedWebDashboard) {
    previousMillisUpdatedWebDashboard = currentMillis;
    updateWebDashboard(fhumidity, ftemperature);
  }

  //start blynk flow
  if (currentMillis - previousMillisBlynkFlow > timeIntervalBlynkFlow) {
    previousMillisBlynkFlow = currentMillis;
    startBlynkFlow(fhumidity, flight);
  }

  //start MQTT flow
  if (currentMillis - previousMillisMQTTFlow > timeIntervalMQTTFlow) {
    previousMillisMQTTFlow = currentMillis;
    startMQTTFlow(ftemperature, fhumidity, flight, fhealth);
  }
}

/*
 * update stats and calculate current health
 */
void update_stats() {
  ftemperature = get_temperature();
  flight = get_light();
  fhumidity = get_humidity();
  fhealth = calculate_health(ftemperature, fhumidity, flight);
  Serial.println("stats updated");
}
