/*
 * C++
 * Project: Matrix-Project
 * Author: Helgi Poulsen
 * Email: helgipoulsen@hotmail.com
 * 27-June-2019
 */

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <MD_MAX72xx.h>
#include <MD_Parola.h>

using namespace std;

#ifndef WIFI_H
#define WIFI_H

class Wifi {
private:
public:
  void connect(const char *pNetwork, const char *pPassword);
};
#endif