/*
 * C++
 * Project: Matrix-Project
 * Author: Helgi Poulsen
 * Email: helgipoulsen@hotmail.com
 * 27-June-2019
 */

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <vector>

using namespace std;

#ifndef F1_H
#define F1_H
class F1 {
protected:
  String path;
  String path2;
  String path3;
  String thumbprint;

  String position;
  String driverCode;
  String status;

  String season;
  String round;
  String raceName;
  String circuitName;

  String name;
  String grid;
  String laps;
  String rank;
  String points;

  String q1;
  String q2;
  String q3;

  String wins;

  String date;
  String time;

  String constructor;
  String nationality;
  String locality;
  String country;

  String qdate;
  String qtime;

public:
  F1();
  F1(String s, String r);
  F1(String r, String rn, String cn, String l, String c, String d, String t,
     String qd, String qt);
  F1(String po, String c, String n, String p);
  F1(String po, String poi, String d);
  ~F1();

  vector<F1> f1Standings;
  vector<F1> f1StandingsInfo;
  vector<F1> constructorStandings;
  vector<F1> f1Scedule;
  vector<F1> f1Qualifying;

  void setPosition(String p) { position = p; }
  void setDriverCode(String d) { driverCode = d; }
  void setStatus(String s) { status = s; }
  void setSeason(String s) { season = s; }
  void setRound(String r) { round = r; }
  void setRaceName(String rn) { raceName = rn; }
  void setCircuitName(String cn) { circuitName = cn; }
  void setName(String n) { name = n; }
  void setGrid(String g) { grid = g; }
  void setLaps(String l) { laps = l; }
  void setRank(String r) { rank = r; }
  void setTime(String t);
  void setPoints(String p) { points = p; }
  void setQ1(String pQ1) { q1 = pQ1; }
  void setQ2(String pQ1) { q2 = pQ1; }
  void setQ3(String pQ3) { q3 = pQ3; }
  void setDate(String d) { date = d; }
  void setWins(String w) { wins = w; }
  void setConstructor(String c) { constructor = c; }
  void setNationality(String n) { nationality = n; }
  void setLocality(String l) { locality = l; }
  void setCountry(String c) { country = c; }
  void setQTime(String t);
  void setQDate(String d);

  String getLocality() { return locality; }
  String getCountry() { return country; }
  String getNationality() { return nationality; }
  String getConstructor() { return constructor; }
  String getWins() { return wins; }
  String getDate() { return date; }
  String getQ1() { return q1; }
  String getQ2() { return q2; }
  String getQ3() { return q3; }
  String getPosition() { return position; }
  String getDriverCode() { return driverCode; }
  String getStatus() { return status; }
  String getSeason() { return season; }
  String getRound() { return round; }
  String getRaceName() { return raceName; }
  String getCircuitName() { return circuitName; }
  String getName() { return name; }
  String getGrid() { return grid; }
  String getLaps() { return laps; }
  String getRank() { return rank; }
  String getTime() { return time; }
  String getPoints() { return points; }
  String getQTime() { return qtime; }
  String getQDate() { return qdate; }

  String getStandingsResult(HTTPClient &http, String key, int skip);
  String getF1StandingsInfo(HTTPClient &http, String key, int skip);
  String getConstructorsResult(HTTPClient &http, String key, int skip);
  String getF1Scedule(HTTPClient &http, String key, int skip);

  void start(boolean sp) { this->result(sp); };

  void raceScedule(boolean sp);
  void cStandings(boolean sp);
  virtual void result(boolean sp);
  virtual void info(boolean sp);
};
#endif
