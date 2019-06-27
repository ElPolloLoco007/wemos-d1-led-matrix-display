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
#include <vector>
using namespace std;

#include "F1.h"

class Qualifying : public F1 {
private:
  String raceName;

public:
  Qualifying(/* args */);
  Qualifying(String p, String d, String a, String b, String c);
  ~Qualifying();

  vector<Qualifying> qualifyingResults;

  String getQualifyingResult(HTTPClient &http, String key, int skip);
  String getQualifyingInfo(HTTPClient &http, String key, int skip);

  void result(boolean sp);
  void info(boolean sp);
};
