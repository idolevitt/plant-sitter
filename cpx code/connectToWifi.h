/*
 * This file is responsible for connecting to the wifi
 */

// WiFi connection credentials
const char wifiSSID[] = "XXXXXXXXX"; // fill in your wifi name
const char wifiPass[] = "XXXXXXXXX"; // fill in your wifi password


void connectToWifi() {
  SerialAT.begin(115200);

  SerialMon.println("Initializing modem...");
  modem.restart();

  String modemInfo = modem.getModemInfo();
  SerialMon.print("Modem Info: ");
  SerialMon.println(modemInfo);

  SerialMon.print(F("Setting SSID/password..."));
  if (!modem.networkConnect(wifiSSID, wifiPass)) {
    SerialMon.println(" fail");
    while (true);
  }
  SerialMon.println(" success");

  SerialMon.print("Waiting for network...");
  if (!modem.waitForNetwork()) {
    SerialMon.println(" fail");
    while (true);
  }
  SerialMon.println(" success");

  if (modem.isNetworkConnected()) {
    SerialMon.println("Network connected");
  }
}
