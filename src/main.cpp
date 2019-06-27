#include "Config.h"
#include "F1.h"
#include "News.h"
#include "Qualifying.h"
#include "Race.h"
#include "RandomAPI.h"
#include "Time.h"
#include "Weather.h"
#include "Wifi.h"
#include <Arduino.h>
#include <MD_MAX72xx.h>
#include <MD_Parola.h>
#include <ctime>

#include <Adafruit_Sensor.h>
#include <DHT.h>
//-----------------------------
#define DHTPIN D4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

//-----------------------------
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 8
#define CLK_PIN D13
#define DATA_PIN D12
#define CS_PIN D10
MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

String dateNow;
int x = 1;

//-----------------------------------------------------------------------------------

void mainTime() {

  std::unique_ptr<Time> t(new Time());
  t->setTime(GLOBALS::SERIALPRINT);

  dateNow = t->getDate();
  P.displayText(dateNow.c_str(), PA_CENTER, 20, 2500, PA_SCROLL_DOWN,
                PA_SCROLL_DOWN);

  while (!P.displayAnimate()) {
    yield();
    wdt_reset();
  }

  String tmpDay = t->getDay();
  P.displayText(tmpDay.c_str(), PA_CENTER, 20, 2500, PA_SCROLL_DOWN,
                PA_SCROLL_DOWN);

  while (!P.displayAnimate()) {
    yield();
    wdt_reset();
  }

  String tmpClock = t->getClock();
  P.displayText(tmpClock.c_str(), PA_CENTER, 20, 5000, PA_SCROLL_DOWN,
                PA_SCROLL_DOWN);

  while (!P.displayAnimate()) {
    yield();
    wdt_reset();
  }
}

void mainWeather(DHT d) {

  std::unique_ptr<Weather> w(new Weather());

  w->setWeather(GLOBALS::SERIALPRINT);
  P.displayScroll(w->getWeather().c_str(), PA_RIGHT, PA_SCROLL_LEFT, 30);

  while (!P.displayAnimate()) {
    yield();
    wdt_reset();
  }
  w->setInsideWeather(d, GLOBALS::SERIALPRINT);
  P.displayScroll(w->getWeather().c_str(), PA_RIGHT, PA_SCROLL_LEFT, 30);

  while (!P.displayAnimate()) {
    yield();
    wdt_reset();
  }
}

void mainNews() {

  std::unique_ptr<News> n(new News());
  n->setNews(GLOBALS::SERIALPRINT);

  boolean x = true;

  String a = n->latestNews[0].getTopic();

  for (unsigned i = 0; i < n->latestNews.size(); ++i) {
    String tmp = n->latestNews[i].getTopic();

    if (a != tmp) {
      x = true;
    }

    if (x) {
      String t = n->latestNews[i].getTopic();
      if (n->latestNews[i].getHeadline() != "null") {
        P.displayText(t.c_str(), PA_CENTER, 20, 2500, PA_SCROLL_DOWN,
                      PA_SCROLL_DOWN);
        while (!P.displayAnimate()) {
          yield();
          wdt_reset();
        }
      }

      if (n->latestNews[i].getHeadline() != "null") {
        String h = n->latestNews[i].getHeadline();
        P.displayScroll(h.c_str(), PA_RIGHT, PA_SCROLL_LEFT, 30);

        while (!P.displayAnimate()) {
          yield();
          wdt_reset();
        }
      }
      a = tmp;
      x = false;
    } else {
      if (n->latestNews[i].getHeadline() != "null") {

        String h = n->latestNews[i].getHeadline();
        P.displayScroll(h.c_str(), PA_RIGHT, PA_SCROLL_LEFT, 30);

        while (!P.displayAnimate()) {
          yield();
          wdt_reset();
        }
      }
    }
  }
}

int rdn(int y, int m, int d) { /* Rata Die day one is 0001-01-01 */
  if (m < 3)
    y--, m += 12;
  return 365 * y + y / 4 - y / 100 + y / 400 + (153 * m - 457) / 5 + d - 306;
}

int dateDifference(String today, String future) {
  String m1, d1, m2, d2;
  int mo1, da1, mo2, da2;
  m1 = today.substring(5, 7);
  d1 = today.substring(8, 10);

  m2 = future.substring(5, 7);
  d2 = future.substring(8, 10);

  mo1 = m1.toInt();
  da1 = d1.toInt();

  mo2 = m2.toInt();
  da2 = d2.toInt();

  int days = rdn(2019, mo2, da2) - rdn(2019, mo1, da1);
  String tmp = String(days);

  return days;
}

void nextRace() {
  wdt_reset();

  std::unique_ptr<F1> f(new F1());
  f->raceScedule(GLOBALS::SERIALPRINT);

  for (unsigned i = 0; i < f->f1Scedule.size(); ++i) {

    if (dateDifference(dateNow, f->f1Scedule[i].getDate()) >= 0 &&
        dateDifference(dateNow, f->f1Scedule[i].getDate()) < 14) {

      // QUAL----------------------------------------------------------------------
      if (dateDifference(dateNow, f->f1Scedule[i].getQDate()) == 0) {
        String tmpQT = "QUAL TODAY!";
        P.displayText(tmpQT.c_str(), PA_CENTER, 20, 3000, PA_SCROLL_DOWN,
                      PA_SCROLL_DOWN);

        while (!P.displayAnimate()) {
          yield();
          wdt_reset();
        }
        String tmpQ = f->f1Scedule[i].getRaceName();
        P.displayText(tmpQ.c_str(), PA_CENTER, 20, 3000, PA_SCROLL_DOWN,
                      PA_SCROLL_DOWN);

        while (!P.displayAnimate()) {
          yield();
          wdt_reset();
        }

        tmpQ = "Time: ";
        tmpQ += f->f1Scedule[i].getQTime();

        P.displayText(tmpQ.c_str(), PA_CENTER, 20, 3000, PA_SCROLL_DOWN,
                      PA_SCROLL_DOWN);

        while (!P.displayAnimate()) {
          yield();
          wdt_reset();
        }
      }
      // RACE----------------------------------------------------------------------
      else if (dateDifference(dateNow, f->f1Scedule[i].getDate()) == 0) {
        String tmpRT = "RACE TODAY!";
        P.displayText(tmpRT.c_str(), PA_CENTER, 20, 3000, PA_SCROLL_DOWN,
                      PA_SCROLL_DOWN);

        while (!P.displayAnimate()) {
          yield();
          wdt_reset();
        }
        String tmpR = f->f1Scedule[i].getRaceName();
        P.displayText(tmpR.c_str(), PA_CENTER, 20, 3000, PA_SCROLL_DOWN,
                      PA_SCROLL_DOWN);

        while (!P.displayAnimate()) {
          yield();
          wdt_reset();
        }

        tmpR = "Time: ";
        tmpR += f->f1Scedule[i].getTime();

        P.displayText(tmpR.c_str(), PA_CENTER, 20, 3000, PA_SCROLL_DOWN,
                      PA_SCROLL_DOWN);

        while (!P.displayAnimate()) {
          yield();
          wdt_reset();
        }
      } else {
        //-------------------------------------------------------------------------
        String tmpNR = "Next Race";
        P.displayText(tmpNR.c_str(), PA_CENTER, 20, 3000, PA_SCROLL_DOWN,
                      PA_SCROLL_DOWN);

        while (!P.displayAnimate()) {
          yield();
          wdt_reset();
        }
        int d = dateDifference(dateNow, f->f1Scedule[i].getDate());
        String x = String(d);
        String daysUntilNextRace = "In " + x + " days";

        P.displayText(daysUntilNextRace.c_str(), PA_CENTER, 20, 2500,
                      PA_SCROLL_DOWN, PA_SCROLL_DOWN);

        while (!P.displayAnimate()) {
          yield();
          wdt_reset();
        }

        String tmp = "Round:" + f->f1Scedule[i].getRound();
        tmp += " - " + f->f1Scedule[i].getRaceName();
        tmp += " - " + f->f1Scedule[i].getCircuitName();
        tmp += " - " + f->f1Scedule[i].getLocality();
        tmp += " - " + f->f1Scedule[i].getCountry();

        tmp += " >>Race times:";
        tmp += " - " + f->f1Scedule[i].getDate();
        tmp += " - " + f->f1Scedule[i].getTime();
        tmp += " >>Qual times:";

        tmp += " " + f->f1Scedule[i].getQDate();
        tmp += " " + f->f1Scedule[i].getQTime();

        P.displayScroll(tmp.c_str(), PA_RIGHT, PA_SCROLL_LEFT, 25);

        while (!P.displayAnimate()) {
          yield();
          wdt_reset();
        }
      }
      //-------------------------------------------------------------------------
    }
  }
}

void mainF1standings() {
  wdt_reset();

  std::unique_ptr<F1> f(new F1());

  f->info(GLOBALS::SERIALPRINT);
  f->start(GLOBALS::SERIALPRINT);
  f->cStandings(GLOBALS::SERIALPRINT);

  for (unsigned i = 0; i < f->f1StandingsInfo.size(); ++i) {

    String tmp = "F1 Standings";
    P.displayText(tmp.c_str(), PA_CENTER, 20, 2500, PA_SCROLL_DOWN,
                  PA_SCROLL_DOWN);

    while (!P.displayAnimate()) {
      yield();
      wdt_reset();
    }

    tmp = " Season: " + f->f1StandingsInfo[i].getSeason();
    tmp += " Round: " + f->f1StandingsInfo[i].getRound();

    P.displayScroll(tmp.c_str(), PA_RIGHT, PA_SCROLL_LEFT, 25);

    while (!P.displayAnimate()) {
      yield();
      wdt_reset();
    }
  }

  for (unsigned i = 0; i < f->f1Standings.size(); ++i) {
    String tmp = f->f1Standings[i].getPosition() + ". ";
    tmp += f->f1Standings[i].getDriverCode();
    tmp += " P: " + f->f1Standings[i].getPoints();

    P.displayText(tmp.c_str(), PA_CENTER, 20, 2000, PA_SCROLL_DOWN,
                  PA_SCROLL_DOWN);
    while (!P.displayAnimate()) {
      yield();
      wdt_reset();
    }
  }
  String constr = "Constructors";
  P.displayText(constr.c_str(), PA_CENTER, 20, 2000, PA_SCROLL_DOWN,
                PA_SCROLL_DOWN);

  while (!P.displayAnimate()) {
    yield();
    wdt_reset();
  }
  for (unsigned i = 0; i < f->constructorStandings.size(); ++i) {
    String tmp = f->constructorStandings[i].getPosition() + ".";
    tmp += " " + f->constructorStandings[i].getConstructor();
    tmp += " " + f->constructorStandings[i].getNationality();
    tmp += " P: " + f->constructorStandings[i].getPoints();
    P.displayScroll(tmp.c_str(), PA_RIGHT, PA_SCROLL_LEFT, 25);

    while (!P.displayAnimate()) {
      yield();
      wdt_reset();
    }
  }
}

void mainRaceResults() {
  wdt_reset();

  std::unique_ptr<Race> r(new Race());

  r->info(GLOBALS::SERIALPRINT);

  String tmpRRI = "Race Results";
  P.displayText(tmpRRI.c_str(), PA_CENTER, 20, 2500, PA_SCROLL_DOWN,
                PA_SCROLL_DOWN);

  while (!P.displayAnimate()) {
    yield();
    wdt_reset();
  }
  tmpRRI = " Round: " + r->getRound();
  tmpRRI += " - Circuit: " + r->getCircuitName();

  P.displayScroll(tmpRRI.c_str(), PA_RIGHT, PA_SCROLL_LEFT, 25);

  while (!P.displayAnimate()) {
    yield();
    wdt_reset();
  }

  r->start(GLOBALS::SERIALPRINT);

  for (unsigned i = 0; i < r->raceResults.size(); ++i) {

    String tmp = r->raceResults[i].getPosition() + ".";
    tmp += r->raceResults[i].getDriverCode() + " ";
    tmp += "Status: ";
    tmp += r->raceResults[i].getStatus();
    tmp += " Points: " + r->raceResults[i].getPoints();

    P.displayScroll(tmp.c_str(), PA_RIGHT, PA_SCROLL_LEFT, 25);

    while (!P.displayAnimate()) {
      yield();
      wdt_reset();
    }
  }

  r->KMAGresult(GLOBALS::SERIALPRINT);
  String kmag = "KMAG Result";
  P.displayText(kmag.c_str(), PA_CENTER, 20, 2500, PA_SCROLL_DOWN,
                PA_SCROLL_DOWN);

  while (!P.displayAnimate()) {
    yield();
    wdt_reset();
  }

  String tmp = "Driver: " + r->getName();
  tmp += " - Grid Position: " + r->getGrid();
  tmp += " - Laps: " + r->getLaps();
  tmp += " - Status: " + r->getStatus();
  tmp += " - Fastest lap Rank: " + r->getRank();
  tmp += " - Fastest lap time: " + r->getTime();
  tmp += " - Position: " + r->getPosition();
  tmp += " - Points: " + r->getPoints();

  P.displayScroll(tmp.c_str(), PA_RIGHT, PA_SCROLL_LEFT, 25);

  while (!P.displayAnimate()) {
    yield();
    wdt_reset();
  }
}

void mainQualifyingResults() {
  std::unique_ptr<Qualifying> q(new Qualifying());

  q->info(GLOBALS::SERIALPRINT);

  String tmpQI = "Qual Results";
  P.displayText(tmpQI.c_str(), PA_CENTER, 20, 2500, PA_SCROLL_DOWN,
                PA_SCROLL_DOWN);

  while (!P.displayAnimate()) {
    yield();
    wdt_reset();
  }
  tmpQI = " Round: " + q->getRound();
  tmpQI += " Circuit name: " + q->getCircuitName();

  P.displayScroll(tmpQI.c_str(), PA_RIGHT, PA_SCROLL_LEFT, 25);

  while (!P.displayAnimate()) {
    yield();
    wdt_reset();
  }

  q->start(GLOBALS::SERIALPRINT);

  // Grip positions
  String gridPosition = "Grid Positions";
  P.displayText(gridPosition.c_str(), PA_CENTER, 20, 3000, PA_SCROLL_DOWN,
                PA_SCROLL_DOWN);
  while (!P.displayAnimate()) {
    yield();
    wdt_reset();
  }

  String gr = "";
  int x = 1;
  for (unsigned i = 0; i < q->qualifyingResults.size(); ++i) {
    gr += q->qualifyingResults[i].getPosition();
    gr += "." + q->qualifyingResults[i].getDriverCode();
    gr += " ";
    if (x % 2 == 0) {
      P.displayText(gr.c_str(), PA_CENTER, 20, 2500, PA_SCROLL_DOWN,
                    PA_SCROLL_DOWN);
      while (!P.displayAnimate()) {
        yield();
        wdt_reset();
      }
      gr = "";
    }
    x++;
  }

  // Qual results
  String qResults = "Qual Times";
  P.displayText(qResults.c_str(), PA_CENTER, 20, 3000, PA_SCROLL_DOWN,
                PA_SCROLL_DOWN);
  while (!P.displayAnimate()) {
    yield();
    wdt_reset();
  }

  for (unsigned i = 0; i < q->qualifyingResults.size(); ++i) {
    String tmp = q->qualifyingResults[i].getPosition();
    tmp += ". " + q->qualifyingResults[i].getDriverCode();
    tmp += " " + q->qualifyingResults[i].getQ1();
    tmp += " " + q->qualifyingResults[i].getQ2();
    tmp += " " + q->qualifyingResults[i].getQ3();

    P.displayScroll(tmp.c_str(), PA_RIGHT, PA_SCROLL_LEFT, 25);

    while (!P.displayAnimate()) {
      yield();
      wdt_reset();
    }
  }
}

void mainQuote() {

  String quo = "<Quote>";
  P.displayText(quo.c_str(), PA_CENTER, 20, 2500, PA_SCROLL_DOWN,
                PA_SCROLL_DOWN);

  while (!P.displayAnimate()) {
    yield();
    wdt_reset();
  }

  std::unique_ptr<RandomAPI> q(new RandomAPI());

  q->setQuote(GLOBALS::SERIALPRINT);
  String tmp = q->getQuote().c_str();
  P.displayScroll(tmp.c_str(), PA_RIGHT, PA_SCROLL_LEFT, 25);

  while (!P.displayAnimate()) {
    yield();
    wdt_reset();
  }
}

void mainAdvice() {

  String adv = "<Advice>";
  P.displayText(adv.c_str(), PA_CENTER, 20, 2500, PA_SCROLL_DOWN,
                PA_SCROLL_DOWN);

  while (!P.displayAnimate()) {
    yield();
    wdt_reset();
  }
  std::unique_ptr<RandomAPI> a(new RandomAPI());
  a->setAdvice(GLOBALS::SERIALPRINT);
  String tmp = a->getAdvice().c_str();
  P.displayScroll(tmp.c_str(), PA_RIGHT, PA_SCROLL_LEFT, 25);

  while (!P.displayAnimate()) {
    yield();
    wdt_reset();
  }
}
//------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  P.begin();
  P.setIntensity(5);
  dht.begin();

  Wifi w;
  w.connect(NETWORK::NETWORK, NETWORK::PASSWORD);
}
void loop() {

  productInfo(GLOBALS::SERIALPRINT);
  mainTime();
  wdt_reset();

  if (x == 1) {
    mainWeather(dht);
    wdt_reset();

    mainAdvice();
    wdt_reset();

    mainQuote();
    wdt_reset();
  }
  if (x == 2) {
    mainNews();
    wdt_reset();
  }
  if (x == 3) {
    nextRace();
    mainF1standings();
    wdt_reset();
  }
  if (x == 4) {
    mainRaceResults();
    mainQualifyingResults();
    wdt_reset();
    x = 0;
  }
  x++;
}
