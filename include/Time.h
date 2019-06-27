/*
 * C++
 * Project: Matrix-Project
 * Author: Helgi Poulsen
 * Email: helgipoulsen@hotmail.com
 * 27-June-2019
 */

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <MD_MAX72xx.h>
#include <MD_Parola.h>

using namespace std;

#ifndef TIME_H
#define TIME_H

class Time {
private:
  String path;

  String date;
  String clock;
  String day;

public:
  Time();

  void setClock(String c) { clock = c; }
  void setDate(String d) { date = d; }
  void setDay(String d) { day = d; }
  void setTime(boolean sp);

  String getTime(HTTPClient &http, String key, int skip);
  String getDate() { return date; }
  String getClock() { return clock; }
  String getDay() { return day; }
};
#endif