#include "Wifi.h"

void Wifi::connect(const char *pNetwork, const char *pPassword) {

  // Connecting to wifi
  WiFi.begin(pNetwork, pPassword);
  int counter = 1;
  Serial.println("STARTING");
  Serial.print("Connecting");

  // While not connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");

    counter++;
    if (counter == 5) {
      counter = 1;
    }
  }

  // Connected
  Serial.println();
  Serial.print("Connected, IP address: ");

  Serial.println(WiFi.localIP());
}




