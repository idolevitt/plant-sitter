/*
 * This file is responsible for communicating with MQTT
 */
PubSubClient mqtt(client);

#define MQTT_USERNAME  "XXXXXXXXX" // fill in your MQTT username
#define MQTT_PASSWORD  "XXXXXXXXX" // fill in your MQTT password

String tempStr;
String humidityStr;
String lightStr;
String healthStr;

char temp[50];
char humidity[50];
char light[50];
char health[50];

const char MQTT_CLIENTID[] = MQTT_USERNAME __DATE__ __TIME__;

uint32_t lastReconnectAttempt = 0;

const char* broker = "io.adafruit.com";

/*
 * MQTT feeds
 */
const char* sosButtonlTopic = MQTT_USERNAME "/feeds/SOS_button";
const char temperatureTopic[] = MQTT_USERNAME "/feeds/Temperature_level";
const char humidityTopic[] = MQTT_USERNAME "/feeds/Humidity level";
const char lightTopic[] = MQTT_USERNAME "/feeds/light level";
const char healthTopic[] = MQTT_USERNAME "/feeds/health rate";

void publishStats(float ftemperature, float fhumidity, float flight, float fhealth);
void publish_health(float fhealth);
float publish_light(float flight);
float publish_humidity(float fhumidity);
float publish_temperature(float ftemperature);
boolean mqttConnect();
void mqttCallback(char* topic, byte* payload, unsigned int len);
void MQTTBrokerSetup();
void startMQTTFlow(float ftemperature, float fhumidity, float flight, float fhealth);


/*
 * entry point function - starts MQTT flow
 */
void startMQTTFlow(float ftemperature, float fhumidity, float flight, float fhealth) {
  mqtt.loop();
  publishStats(ftemperature, fhumidity, flight, fhealth);
}

/*
 * send stats to MQTT
 */
void publishStats(float ftemperature, float fhumidity, float flight, float fhealth) {
  publish_temperature(ftemperature);

  publish_humidity(fhumidity);

  publish_light(flight);

  publish_health(fhealth);
}

void MQTTBrokerSetup() {
  mqtt.setServer(broker, 1883);
  mqtt.setCallback(mqttCallback);
}

void connectToMQTT() {
  if (!mqtt.connected()) {
    SerialMon.println("=== MQTT NOT CONNECTED ===");
    // Reconnect every 10 seconds
    uint32_t t = millis();
    if (t - lastReconnectAttempt > 1000L) {
      lastReconnectAttempt = t;
      if (mqttConnect()) {
        lastReconnectAttempt = 0;
      }
    }
    delay(100);
    return;
  }
}

/*
   connect to MQTT
*/
boolean mqttConnect() {
  SerialMon.print("Connecting to ");
  SerialMon.print(broker);

  // no password? no problem
  // boolean status = mqtt.connect(MQTT_CLIENTID);
  boolean status = mqtt.connect(MQTT_CLIENTID, MQTT_USERNAME, MQTT_PASSWORD);

  if (status == false) {
    SerialMon.println(" fail");
    return false;
  }
  SerialMon.println(" success");
  mqtt.subscribe(sosButtonlTopic);
  return mqtt.connected();
}

/*
 * manage callbacks from MQTT
 * allow activating SOS button from web
 */
void mqttCallback(char* topic, byte* payload, unsigned int len) {
  SerialMon.print("Message arrived [");
  SerialMon.print(topic);
  SerialMon.print("]: ");
  SerialMon.write(payload, len);
  SerialMon.println();

  // Only proceed if incoming message's topic matches
  if (String(topic) == sosButtonlTopic) {
    int numericValue = payload[0] - '0';
    if (numericValue == 1) {
      sosMessage();
    }
  }
}

/*
   publish temperature rate
*/
float publish_temperature(float ftemperature) {
  Serial.print("publishing temperature:  ");
  tempStr = String(ftemperature);
  tempStr.toCharArray(temp, String(ftemperature).length() + 1);
  Serial.println(temp);
  mqtt.publish(temperatureTopic, temp);
  return ftemperature;
}

/*
   publish soil humidity rate
*/
float publish_humidity(float fhumidity) {
  Serial.print("publishing humidity:  ");
  humidityStr = String(fhumidity);
  humidityStr.toCharArray(humidity, String(fhumidity).length() + 1);
  Serial.println(fhumidity);
  mqtt.publish(humidityTopic, humidity);
  return fhumidity;
}

/*
   publish light rate
*/
float publish_light(float flight) {
  Serial.print("publishing light:  ");
  lightStr = String(flight);
  lightStr.toCharArray(light, String(flight).length() + 1);
  Serial.println(String(flight));
  mqtt.publish(lightTopic, light);
  return flight;
}

/*
   publish health rate
*/
void publish_health(float fhealth) {
  Serial.print("publishing health:  ");
  healthStr = String(fhealth);
  healthStr.toCharArray(health, String(fhealth).length() + 1);
  Serial.println(String(fhealth));
  mqtt.publish(healthTopic, health);
}
