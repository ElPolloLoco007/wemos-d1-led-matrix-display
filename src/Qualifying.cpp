#include "Qualifying.h"

Qualifying::Qualifying() {
  path = "https://ergast.com/api/f1/current/last/qualifying.json";
  thumbprint = "A4:23:DA:00:88:4D:E0:CD:E4:F9:9A:4D:C8:87:04:85:EA:ED:DF:FE";
}

Qualifying::Qualifying(String p, String d, String a, String b, String c) {
  position = p;
  driverCode = d;
  q1 = a;
  q2 = b;
  q3 = c;
}

Qualifying::~Qualifying() {}

void Qualifying::result(boolean sp) {
  HTTPClient http;
  http.begin(path, thumbprint);
  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK)
    getQualifyingResult(http, "code", 3);

  if (sp) {
    Serial.println("Qualifying Results");
    Serial.println("---------");
    for (int i = 0; i < qualifyingResults.size(); ++i) {
      Serial.print(qualifyingResults[i].getPosition());
      Serial.print(". " + qualifyingResults[i].getDriverCode());
      Serial.print(" " + qualifyingResults[i].getQ1());
      Serial.print(" " + qualifyingResults[i].getQ2());
      Serial.println(" " + qualifyingResults[i].getQ3());
    }
    Serial.println("---------");
  }
}

String Qualifying::getQualifyingResult(HTTPClient &http, String key, int skip) {
  int tmpSkip = skip;
  bool found = false, look = false, pos = true;
  int ind = 0;
  String ret_str = "";
  int counter = 1;
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
        if (pos) {
          ret_str += counter;
          setPosition(ret_str);
          ret_str = "";
          counter++;
          pos = false;
        }
        if (skip == 0) {
          a += char_buff[0];
          if (a != b) {
            ret_str += char_buff[0];
          } else {
            skip = tmpSkip;
            found = false;
            if (key == "code") {
              key = "Q1";
              setDriverCode(ret_str);
              ret_str = "";
              continue;
            }
            if (key == "Q1") {
              if (counter > 16) {
                setQ1(ret_str);
                key = "code";
                pos = true;
                setQ2("-");
                setQ3("-");
                qualifyingResults.push_back(
                    Qualifying(position, driverCode, q1, q2, q3));
                ret_str = "";
              } else {
                key = "Q2";
                setQ1(ret_str);
                ret_str = "";
                continue;
              }
            }
            if (key == "Q2") {
              if (counter > 11) {
                setQ2(ret_str);
                key = "code";
                pos = true;
                setQ3("-");
                qualifyingResults.push_back(
                    Qualifying(position, driverCode, q1, q2, q3));
                ret_str = "";
              } else {
                key = "Q3";
                setQ2(ret_str);
                ret_str = "";
                continue;
              }
            }
            if (key == "Q3") {
              setQ3(ret_str);
              key = "code";
              pos = true;
              qualifyingResults.push_back(
                  Qualifying(position, driverCode, q1, q2, q3));
              ret_str = "";
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

void Qualifying::info(boolean sp) {

  HTTPClient http;
  http.begin(path, thumbprint);
  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK)
    getQualifyingInfo(http, "round", 3);

  if (sp) {
    Serial.println("Qualifying Info");
    Serial.println("---------");
    Serial.println("Round:" + getRound());
    Serial.println("Circuit Name:" + getCircuitName());
    Serial.println("---------");
  }
}

String Qualifying::getQualifyingInfo(HTTPClient &http, String key, int skip) {
  int tmpSkip = skip;
  bool found = false, look = false;
  int ind = 0;
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
            if (key == "round") {
              key = "circuitName";
              setRound(ret_str);
              ret_str = "";
              continue;
            }
            if (key == "circuitName") {
              key = "date";
              setCircuitName(ret_str);
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