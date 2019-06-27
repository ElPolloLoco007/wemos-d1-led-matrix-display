/*
 * C++
 * Project: Led-Project
 * Author: Helgi Poulsen
 * Email: helgipoulsen@hotmail.com
 * 17-June-2019
 */

#include "ApiConnection.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

using namespace std;

#ifndef RANDOMAPI_H
#define RANDOMAPI

class RandomAPI {
private:
  ApiConnection ac;

  String quote;
  String advice;

  String aPath;
  String aTumbprint;

  String qPath;
  String qThumbprint;

protected:
public:
  RandomAPI();
  ~RandomAPI();

  void setQuote(boolean sp);
  void setAdvice(boolean sp);

  String getQuote() { return quote; }
  String getAdvice() { return advice; }
};
#endif
