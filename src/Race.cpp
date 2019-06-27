#include "Race.h"

Race::Race() {
  path = "https://ergast.com/api/f1/current/last/results.json";
  thumbprint = "A4:23:DA:00:88:4D:E0:CD:E4:F9:9A:4D:C8:87:04:85:EA:ED:DF:FE";
}
Race::Race(String po, String poi, String co, String st) {
  position = po;
  points = poi;
  driverCode = co;
  status = st;
}

Race::~Race() {}

void Race::result(boolean sp) {

  HTTPClient http;
  http.begin(path, thumbprint);
  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK)
    getRaceResult(http, "points", 3);

  if (sp) {
    Serial.println("Race Results");
    Serial.println("---------");
    for (int i = 0; i < raceResults.size(); ++i) {
      Serial.print(raceResults[i].getPosition() + ". ");
      Serial.print(raceResults[i].getDriverCode() + " ");
      Serial.print(raceResults[i].getPoints() + " ");

      Serial.println(raceResults[i].getStatus());
    }
    Serial.println("---------");
  }
}

String Race::getRaceResult(HTTPClient &http, String key, int skip) {
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
            if (key == "points") {
              setPoints(ret_str);
              key = "code";
              ret_str = "";
              continue;
            }
            if (key == "code") {
              setDriverCode(ret_str);
              key = "status";
              ret_str = "";
              continue;
            }
            if (key == "status") {
              setStatus(ret_str);
              key = "points";
              pos = true;
              raceResults.push_back(Race(position, points, driverCode, status));
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

void Race::info(boolean sp) {

  HTTPClient http;
  http.begin(path, thumbprint);
  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK)
    getRaceInfo(http, "round", 3);
  if (sp) {
    Serial.println("Race Info");
    Serial.println("---------");

    Serial.println("Round:" + getRound());
    Serial.println("Circuit Name:" + getCircuitName());

    Serial.println("---------");
  }
}

String Race::getRaceInfo(HTTPClient &http, String key, int skip) {
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

void Race::KMAGresult(boolean sp) {

  HTTPClient http;
  http.begin(path, thumbprint);
  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK)
    getKMAGResult(http, "kevin", 3);

  if (sp) {
    Serial.println("KMAG");
    Serial.println("---------");

    Serial.print("Driver: " + getName());
    Serial.print(" Grid Position: " + getGrid());
    Serial.print(" Laps: " + getLaps());
    Serial.print(" Status: " + getStatus());
    Serial.print(" Fastest lap Rank: " + getRank());
    Serial.print(" Fastest lap time: " + getTime());
    Serial.print(" Position: " + getPosition());
    Serial.println(" Points: " + getPoints());

    Serial.println("---------");
  }
}

String Race::getKMAGResult(HTTPClient &http, String key, int skip) {
  int tmpSkip = skip;
  bool found = false, look = false;
  int ind = 0;
  String ret_str = "Kevin Ma";
  int counter = 1;
  String a = "";
  String b = "\"";
  String vString = "";

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
            if (key == "kevin") {
              key = "grid";
              setName(ret_str);
              ret_str = "";
              continue;
            }
            if (key == "grid") {
              key = "laps";
              setGrid(ret_str);
              ret_str = "";
              continue;
            }
            if (key == "laps") {
              key = "status";
              setLaps(ret_str);
              ret_str = "";
              continue;
            }
            if (key == "status") {
              key = "rank";
              setStatus(ret_str);
              ret_str = "";
              continue;
            }
            if (key == "rank") {
              key = "time";
              setRank(ret_str);
              ret_str = "";
              continue;
            }
            if (key == "time") {
              key = "position";
              setTime(ret_str);
              ret_str = "";
              continue;
            }
            if (key == "position") {
              key = "points";
              setPosition(ret_str);
              ret_str = "";
              continue;
            }
            if (key == "points") {
              setPoints(ret_str);
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