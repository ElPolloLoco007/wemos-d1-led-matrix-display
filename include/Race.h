/*
 * C++
 * Project: Matrix-Project
 * Author: Helgi Poulsen
 * Email: helgipoulsen@hotmail.com
 * 27-June-2019
 */

#include "ApiConnection.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <algorithm>
#include <vector>

using namespace std;

#include "F1.h"

#ifndef RACE_H
#define RACE_H
class Race : public F1 {
private:
  String raceName;

public:
  Race();
  Race(String po, String poi, String co, String st);
  ~Race();

  vector<Race> raceResults;

  String getRaceResult(HTTPClient &http, String key, int skip);
  String getRaceInfo(HTTPClient &http, String key, int skip);
  String getKMAGResult(HTTPClient &http, String key, int skip);

  void KMAGresult(boolean sp);
  void result(boolean sp);
  void info(boolean sp);
};
#endif
