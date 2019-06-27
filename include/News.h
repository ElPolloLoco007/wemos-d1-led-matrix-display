/*
 * C++
 * Project: Led-Project
 * Author: Helgi Poulsen
 * Email: helgipoulsen@hotmail.com
 * 19-June-2019
 */

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

using namespace std;

#ifndef NEWS_H
#define NEWS_H

class News {
private:
  String thumbprint;

  String redditNewsPath;
  String redditTechPath;
  String redditNotTheOnionPath;

  String topic;
  String headline;

protected:
public:
  News();
  ~News();
  News(String t, String h);

  vector<News> latestNews;

  void setTopic(String t) { topic = t; }
  void setHeadline(String h) { headline = h; }
  void setNews(boolean sp);

  String getTopic() { return topic; }
  String getHeadline() { return headline; }

  String getRedditNews(HTTPClient &http, String key, int skip);
  String getRedditTechNews(HTTPClient &http, String key, int skip);
  String getRedditheOnionNews(HTTPClient &http, String key, int skip);

  void redditNews();
  void redditTechNews();
  void redditNotTheOnionNews();
};
#endif
