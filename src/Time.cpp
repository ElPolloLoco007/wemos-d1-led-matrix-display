#include "Time.h"

Time::Time() { path = "http://worldclockapi.com/api/json/gmt/now"; }

void Time::setTime(boolean sp) {

  HTTPClient http;
  http.begin(path);
  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK)
    getTime(http, "currentDateTime", 3);

  if (sp) {
    Serial.println("Time");
    Serial.println("---------");
    Serial.println(getDate());
    Serial.println(getClock());
    Serial.println(getDay());
    Serial.println("---------");
  }
}

String Time::getTime(HTTPClient &http, String key, int skip) {
  int tmpSkip = skip;
  bool found = false, look = false;
  unsigned ind = 0;
  String ret_str = "";
  String a = "";
  String b = "\"";
  String vString = "";
  wdt_disable();

  int len = http.getSize();
  char char_buff[1];
  WiFiClient *stream = http.getStreamPtr();
  while (http.connected() && (len > 0 || len == -1)) {
    size_t size = stream->available();
    if (size) {
      int c = stream->readBytes(
          char_buff, ((size > sizeof(char_buff)) ? sizeof(char_buff) : size));
      if (len > 0)
        len -= c;
      if (found) {
        if (skip == 0) {
          a += char_buff[0];
          if (a != b) {
            ret_str += char_buff[0];
          } else {
            skip = tmpSkip;
            found = false;
            if (key == "currentDateTime") {
              key = "dayOfTheWeek";
              setDate(ret_str.substring(0, 10));
              setClock(ret_str.substring(11, 16));
              ret_str = "";
              continue;
            }
            if (key == "dayOfTheWeek") {
              setDay(ret_str);
              ret_str = "";
              break;
            }
          }
          a = "";
        } else
          skip--;

      } else if ((!look) && (char_buff[0] == key[0])) {
        look = true;
        ind = 1;
      } else if (look && (char_buff[0] == key[ind])) {
        ind++;
        if (ind == key.length())
          found = true;
      } else if (look && (char_buff[0] != key[ind])) {
        ind = 0;
        look = false;
      }
    }
  }
  return ret_str;
}