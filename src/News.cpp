#include "News.h"

News::News() {

  //--------------
  thumbprint = "E3:C0:F1:CF:CB:A4:61:09:02:1A:74:06:71:83:CD:A8:59:28:B4:0D";
  redditNewsPath = "https://www.reddit.com/r/worldnews.json";
  redditTechPath = "https://www.reddit.com/r/technews.json";
  redditNotTheOnionPath = "https://www.reddit.com/r/nottheonion.json";
}
News::~News() {}
News::News(String t, String h) {
  topic = t;
  headline = h;
}

void News::setNews(boolean sp) {

  redditNews();
  redditTechNews();
  redditNotTheOnionNews();

  if (sp) {
    boolean x = true;
    Serial.println("Latest News");
    Serial.println("---------");
    String a = latestNews[0].getTopic();

    for (unsigned i = 0; i < latestNews.size(); ++i) {
      String tmp = latestNews[i].getTopic();

      if (a != tmp) {
        x = true;
      }
      if (x) {
        Serial.println(latestNews[i].getTopic());
        Serial.println(latestNews[i].getHeadline());
        a = tmp;
        x = false;
      } else {
        Serial.println(latestNews[i].getHeadline());
      }
    }
    Serial.println("---------");
  }
}

void News::redditNews() {
  HTTPClient http;
  http.begin(redditNewsPath, thumbprint);
  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK)
    getRedditNews(http, "\"title", 4);
}

String News::getRedditNews(HTTPClient &http, String key, int skip) {
  int tmpSkip = skip;
  bool found = false, look = false;
  unsigned ind = 0;
  String ret_str = "";
  int counter = 0;
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
            if (key == "\"title") {
              setTopic("World News");
              headline = ret_str;
              latestNews.push_back(News(getTopic(), headline));
              ret_str = "";
              counter++;
              if (counter == 5) {
                break;
              }
              continue;
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

void News::redditTechNews() {
  HTTPClient http;
  http.begin(redditTechPath, thumbprint);
  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK)
    getRedditTechNews(http, "\"title", 4);
}

String News::getRedditTechNews(HTTPClient &http, String key, int skip) {
  int tmpSkip = skip;
  bool found = false, look = false;
  unsigned ind = 0;
  String ret_str = "";
  int counter = 0;
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
            if (key == "\"title") {
              setTopic("Tech News");
              headline = ret_str;
              latestNews.push_back(News(getTopic(), headline));
              ret_str = "";
              counter++;
              if (counter == 5) {
                break;
              }
              continue;
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

void News::redditNotTheOnionNews() {
  HTTPClient http;
  http.begin(redditNotTheOnionPath, thumbprint);
  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK)
    getRedditheOnionNews(http, "\"title", 4);
}

String News::getRedditheOnionNews(HTTPClient &http, String key, int skip) {
  int tmpSkip = skip;
  bool found = false, look = false;
  unsigned ind = 0;
  String ret_str = "";
  int counter = 0;
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
            if (key == "\"title") {
              setTopic("Not The Onion");
              headline = ret_str;
              latestNews.push_back(News(getTopic(), headline));
              ret_str = "";
              counter++;
              if (counter == 3) {
                break;
              }
              continue;
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