#include "ApiConnection.h"

ApiConnection::ApiConnection(/* args */) { payload = ""; }

ApiConnection::~ApiConnection() {}

boolean ApiConnection::setPayload(String path, String thumbprint) {
  HTTPClient http;

  if (thumbprint == "") {
    http.begin(path);
  } else {
    http.begin(path, thumbprint);
  }
  int httpCode = http.GET();
  if (httpCode > 0) {

    if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
      wdt_enable(60000);
      payload = http.getString();
    }
  } else {
    Serial.printf("[HTTP] GET failed, error: %s\n",
                  http.errorToString(httpCode).c_str());
  }

  http.end();
  return true;
}
