#include "F1.h"

F1::F1(/* args */) {
  path = "https://ergast.com/api/f1/current/driverStandings.json";
  path2 = "https://ergast.com/api/f1/current/constructorStandings.json";
  path3 = "https://ergast.com/api/f1/current.json";
  thumbprint = "A4:23:DA:00:88:4D:E0:CD:E4:F9:9A:4D:C8:87:04:85:EA:ED:DF:FE";
}

F1::~F1() {}

F1::F1(String po, String poi, String d) {
  position = po;
  points = poi;
  driverCode = d;
}
F1::F1(String po, String c, String n, String p) {
  position = po;
  constructor = c;
  nationality = n;
  points = p;
}

F1::F1(String s, String r) {
  season = s;
  round = r;
}

F1::F1(String r, String rn, String cn, String l, String c, String d, String t,
       String qd, String qt) {
  round = r;
  raceName = rn;
  circuitName = cn;
  locality = l;
  country = c;
  date = d;
  time = t;
  qdate = qd;
  qtime = qt;
}
//----------------------------------------------------------------------------

void F1::result(boolean sp) {

  HTTPClient http;
  http.begin(path, thumbprint);
  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK)
    getStandingsResult(http, "points", 3);

  if (sp) {
    Serial.println("Driver Standings");
    Serial.println("---------");
    for (int i = 0; i < f1Standings.size(); ++i) {
      Serial.print(f1Standings[i].getPosition() + ". ");
      Serial.print(f1Standings[i].getDriverCode() + " ");
      Serial.println(f1Standings[i].getPoints() + " ");
    }
    Serial.println("---------");
  }
}

String F1::getStandingsResult(HTTPClient &http, String key, int skip) {
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
              key = "code";
              points = ret_str;
              ret_str = "";
              continue;
            }
            if (key == "code") {
              setDriverCode(ret_str);
              key = "points";
              pos = true;
              f1Standings.push_back(F1(position, points, driverCode));
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
//----------------------------------------------------------------------------

void F1::info(boolean sp) {

  HTTPClient http;
  http.begin(path, thumbprint);
  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK)
    getF1StandingsInfo(http, "season", 3);
  if (sp) {
    Serial.println("Race Info");
    Serial.println("---------");

    for (int i = 0; i < f1StandingsInfo.size(); ++i) {
      Serial.print("Season:" + f1StandingsInfo[i].getSeason() + " Round:");
      Serial.println(f1StandingsInfo[i].getRound());
    }
    Serial.println("---------");
  }
}

String F1::getF1StandingsInfo(HTTPClient &http, String key, int skip) {
  int tmpSkip = skip;
  bool found = false, look = false;
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
        if (skip == 0) {
          a += char_buff[0];
          if (a != b) {
            ret_str += char_buff[0];
          } else {
            skip = tmpSkip;
            found = false;
            if (key == "season") {
              key = "round";
              setSeason(ret_str);
              ret_str = "";
              continue;
            }
            if (key == "round") {
              setRound(ret_str);
              f1StandingsInfo.push_back(F1(season, round));
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
//----------------------------------------------------------------------------

void F1::cStandings(boolean sp) {

  HTTPClient http;
  http.begin(path2, thumbprint);
  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK)
    getConstructorsResult(http, "points", 3);

  if (sp) {
    Serial.println("Constructor Standings");
    Serial.println("---------");
    for (int i = 0; i < constructorStandings.size(); ++i) {
      Serial.print(constructorStandings[i].getPosition() + ". ");
      Serial.print(constructorStandings[i].getConstructor() + " ");
      Serial.print(constructorStandings[i].getNationality() + " ");
      Serial.println(constructorStandings[i].getPoints() + " ");
    }
    Serial.println("---------");
  }
}

String F1::getConstructorsResult(HTTPClient &http, String key, int skip) {
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
              key = "name";
              setPoints(ret_str);
              ret_str = "";
              continue;
            }
            if (key == "name") {
              key = "nationality";
              setConstructor(ret_str);
              ret_str = "";
              continue;
            }
            if (key == "nationality") {
              setNationality(ret_str);
              key = "points";
              pos = true;
              constructorStandings.push_back(
                  F1(position, constructor, nationality, points));
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
//----------------------------------------------------------------------------

void F1::raceScedule(boolean sp) {

  HTTPClient http;
  http.begin(path3, thumbprint);
  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK)
    getF1Scedule(http, "round", 3);
  if (sp) {
    Serial.println("F1 scedule");
    Serial.println("---------");

    for (int i = 0; i < f1Scedule.size(); ++i) {
      Serial.println(f1Scedule[i].getRound());
      Serial.println(f1Scedule[i].getRaceName());
      Serial.println(f1Scedule[i].getCircuitName());
      Serial.println(f1Scedule[i].getLocality());
      Serial.println(f1Scedule[i].getCountry());
      Serial.println(f1Scedule[i].getDate());
      Serial.println(f1Scedule[i].getTime());
      Serial.println(f1Scedule[i].getQDate());
      Serial.println(f1Scedule[i].getQTime());
    }
    Serial.println("---------");
  }
}

String F1::getF1Scedule(HTTPClient &http, String key, int skip) {
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

        if (skip == 0) {
          a += char_buff[0];
          if (a != b) {
            ret_str += char_buff[0];
          } else {
            skip = tmpSkip;
            found = false;
            if (key == "round") {
              key = "raceName";
              setRound(ret_str);
              ret_str = "";
              continue;
            }
            if (key == "raceName") {
              key = "circuitName";
              setRaceName(ret_str);

              ret_str = "";
              continue;
            }
            if (key == "circuitName") {
              key = "locality";
              setCircuitName(ret_str);

              ret_str = "";
              continue;
            }
            if (key == "locality") {
              key = "country";
              setLocality(ret_str);

              ret_str = "";
              continue;
            }
            if (key == "country") {
              key = "date";
              setCountry(ret_str);

              ret_str = "";
              continue;
            }
            if (key == "date") {
              key = "time";
              setDate(ret_str);
              setQDate(ret_str);

              ret_str = "";
              continue;
            }
            if (key == "time") {
              key = "round";
              setTime(ret_str);
              setQTime(ret_str);

              pos = true;
              f1Scedule.push_back(F1(
                  getRound(), getRaceName(), getCircuitName(), getLocality(),
                  getCountry(), getDate(), getTime(), getQDate(), getQTime()));

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

void F1::setQTime(String t) {
  String hour;
  String min = "00";
  int h, m;
  hour = t.substring(0, 2);

  h = hour.toInt();
  h = h + 1;
  if (h < 10) {
    qtime = "0";
    qtime += String(h);
    qtime += String(":");
    qtime += String(min);
  } else {
    qtime = String(h);
    qtime += String(":");
    qtime += String(min);
  }
}

void F1::setQDate(String d) {
  String year, month, day;
  int ye, mo, da;
  year = d.substring(0, 4);
  month = d.substring(5, 7);
  day = d.substring(8, 10);

  ye = year.toInt();
  mo = month.toInt();
  da = day.toInt();

  da--;
  if (da == 0) {
    if (mo == 1) {
      day = 31;
    }
    if (mo == 2) {
      day = 28;
    }
    if (mo == 3) {
      day = 31;
    }
    if (mo == 4) {
      day = 30;
    }
    if (mo == 5) {
      day = 31;
    }
    if (mo == 6) {
      day = 30;
    }
    if (mo == 7) {
      day = 31;
    }
    if (mo == 8) {
      day = 31;
    }
    if (mo == 9) {
      day = 30;
    }
    if (mo == 10) {
      day = 31;
    }
    if (mo == 11) {
      day = 30;
    }
    if (mo == 12) {
      day = 31;
    }
  } else {
    if (da < 10) {
      day = "0";
      day += String(da);
    } else {
      day = String(da);
    }
  }

  qdate = year;
  qdate += "-";
  qdate += month;
  qdate += "-";
  qdate += day;
}
void F1::setTime(String t) {
  String hour, min;
  int h, m;
  hour = t.substring(0, 2);
  min = t.substring(3, 5);

  h = hour.toInt();
  m = min.toInt();
  h = h + 1;
  if (h < 10) {
    time = "0";
    time += String(h);
    time += String(":");
    time += String(min);
  } else {
    time = String(h);
    time += String(":");
    time += String(min);
  }
}

//----------------------------------------------------------------------------
