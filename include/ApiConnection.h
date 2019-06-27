/*
 * C++
 * Project: Matrix-Project
 * Author: Helgi Poulsen
 * Email: helgipoulsen@hotmail.com
 * 27-June-2019
 */

#ifndef APICONNECTION_H
#define APICONNECTION_H
//----------------------------------------------
#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
//----------------------------------------------

class ApiConnection {
private:
  String payload;

public:
  ApiConnection(/* args */);
  ~ApiConnection();

  boolean setPayload(String path, String thumbprint);
  String getPayload() { return payload; };
};

#endif
