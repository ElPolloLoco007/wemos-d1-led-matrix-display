/*
 * C++
 * Project: Matrix-Project
 * Author: Helgi Poulsen
 * Email: helgipoulsen@hotmail.com
 * 27-June-2019
 */

#include "ApiConnection.h"
#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <DHT.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

using namespace std;

#ifndef WEATHER_H
#define WEATHER_H

class Weather {
private:
  ApiConnection ac;

  String path;
  String key;
  String payload;
  string weather;

public:
  Weather();
  ~Weather();

  void setWeather(boolean sp);
  void setInsideWeather(DHT d, boolean sp);

  string getWeather() { return weather; }
};

#endif
