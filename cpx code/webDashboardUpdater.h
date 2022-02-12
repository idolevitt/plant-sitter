/*
 * This file is responsible for communicating with the web dashboard server
 */
 
#if !defined(TINY_GSM_RX_BUFFER)
#define TINY_GSM_RX_BUFFER 650
#endif

// See all AT commands, if wanted
//#define DUMP_AT_COMMANDS

// Define the serial console for debug prints, if needed
#define TINY_GSM_DEBUG SerialMon

// Range to attempt to autobaud
#define GSM_AUTOBAUD_MIN 9600
#define GSM_AUTOBAUD_MAX 115200

// Server details
const char webDashboardServer[] = "XXXXXXXXXXX"; // fill in the ip of the web dashboard server


const int  port = XXXXXXXXX; // fill in the port number of the web dashboard server

void updateWebDashboard(float fhumidity, float ftemperature) {

  SerialMon.print("Connecting to ");
  SerialMon.println(webDashboardServer);
  if (!client.connect(webDashboardServer, port)) {
    SerialMon.println(" fail");
    delay(10000);
    return;
  }
  SerialMon.println(" success");

  // Make a HTTP GET request:
  SerialMon.println("Performing HTTP GET request...");
  String parametersString = String("/?fhumidity=") + String(fhumidity) + String("&ftemperature=") + String(ftemperature);
  client.print(String("GET ") + parametersString + " HTTP/1.1\r\n");
  client.print(String("Host: ") + webDashboardServer + "\r\n");
  client.print("Connection: close\r\n\r\n");
  client.println();

  uint32_t timeout = millis();
  while (client.connected() && millis() - timeout < 10000L) {
    // Print available data
    while (client.available()) {
      char c = client.read();
      SerialMon.print(c);
      timeout = millis();
    }
  }
  SerialMon.println();

  // Shutdown

  client.stop();
  SerialMon.println(F("Server disconnected"));

  modem.networkDisconnect();
  SerialMon.println(F("WiFi disconnected"));
}
