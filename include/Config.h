/*
 * C++
 * Project: Matrix-Project
 * Author: Helgi Poulsen
 * Email: helgipoulsen@hotmail.com
 * 27-June-2019
 */

#ifndef _CONFIG_h
#define _CONFIG_h

#include "Arduino.h"

namespace PRODUCT {
String NAME = "Led Matrix Display";
String VERSION = "1.0";
String CREATOR = "Helgi Poulsen";

} // namespace PRODUCT

namespace NETWORK {
const char *NETWORK = "xxx";
const char *PASSWORD = "xxx";
} // namespace NETWORK

namespace GLOBALS {
const boolean SERIALPRINT = false;
}

void productInfo(boolean sp) {
  if (sp) {
    Serial.println("=======================");
    Serial.println(PRODUCT::NAME);
    Serial.println(PRODUCT::VERSION);
    Serial.println(PRODUCT::CREATOR);
    Serial.println("=======================");
  }
}

#endif