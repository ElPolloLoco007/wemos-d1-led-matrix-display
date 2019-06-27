#include "Weather.h"

Weather::Weather() {
  path = "http://api.openweathermap.org/data/2.5/"
         "weather?q=Hoyvik,fo&APPID=xxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
}

Weather::~Weather() {}

void Weather::setWeather(boolean sp) {
  wdt_disable();

  ac.setPayload(path, "");

  DynamicJsonDocument doc(2000);

  deserializeJson(doc, ac.getPayload());

  const char *name = doc["name"]; // "Torshavn"

  JsonObject weather_0 = doc["weather"][0];
  const char *weather_0_main = weather_0["main"]; // "Rain"

  JsonObject main = doc["main"];
  int main_temp = main["temp"]; // 281.15
  main_temp = main_temp - 273;
  String mt = String(main_temp);

  JsonObject wind = doc["wind"];

  int wind_speed = wind["speed"]; // 10.8
  int wind_deg = wind["deg"];     // 340
  String ws = String(wind_speed);
  String wd = String(wind_deg);

  weather = name;
  weather += ": ";
  weather += weather_0_main;
  weather += " ";
  weather += mt.c_str();
  weather += "\260";
  weather += "C ";
  weather += ws.c_str();
  weather += "m/s ";
  weather += wd.c_str();
  weather += "\260";
  if (sp) {
    Serial.println("Weather");
    Serial.println("---------");
    Serial.println(weather.c_str());
    Serial.println("---------");
  }
  delay(1);
}
void Weather::setInsideWeather(DHT d, boolean sp) {
  float h = d.readHumidity();
  // Read temperature as Celsius (the default)
  float t = d.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  float hic = d.computeHeatIndex(t, h, false);

  if (sp) {
    Serial.println("Inside weather");
    Serial.println("---------");
    Serial.print(F("Humidity: "));
    Serial.print(h);
    Serial.print(F("%  Temperature: "));
    Serial.print(t);
    Serial.print(F("°C "));

    Serial.print(F("  Heat index: "));
    Serial.print(hic);
    Serial.println(F("°C "));
    Serial.println("---------");
  }

  String tmpH = String(h);
  String tmpT = String(t);
  String tmpHic = String(hic);

  weather = "Inside: ";
  weather += "Humidity:  ";
  weather += tmpH.c_str();
  weather += "%  Temperature: ";
  weather += tmpT.c_str();
  weather += "\260";
  weather += "C";
  weather += "  Heat index: ";
  weather += tmpHic.c_str();
  weather += "\260C ";
  delay(1);
}