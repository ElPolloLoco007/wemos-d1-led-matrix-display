#include "RandomAPI.h"

RandomAPI::RandomAPI() {
  // to edit json go to https://api.myjson.com/6sr9x
  qPath = "https://api.myjson.com/bins/6sr9x";
  qThumbprint = "BF:66:82:DA:8F:9F:82:C1:B3:F7:EC:5F:B8:BD:B9:72:8C:37:64:A8";
  aPath = "https://api.adviceslip.com/advice";
  aTumbprint = "FA:77:56:09:28:B0:1F:B8:FC:A0:6F:13:15:71:93:8D:EE:32:13:91";
}
RandomAPI::~RandomAPI() {}

void RandomAPI::setQuote(boolean sp) {

  ac.setPayload(qPath, qThumbprint);

  const size_t capacity = JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(99) + 9080;
  DynamicJsonDocument doc(capacity);

  deserializeJson(doc, ac.getPayload());

  JsonObject object = doc["object"];
  int randNumber = random(100);
  String q = object[String(randNumber)];
  quote = q;
  if (sp) {
    Serial.println("Quote");
    Serial.println("---------");
    Serial.println(quote);
    Serial.println("---------");
  }
}

void RandomAPI::setAdvice(boolean sp) {
  ac.setPayload(aPath, aTumbprint);

  DynamicJsonDocument doc(500);
  deserializeJson(doc, ac.getPayload());

  String tmp = doc["slip"]["advice"];
  advice = tmp;
  if (sp) {
    Serial.println("Advice");
    Serial.println("---------");
    Serial.println(advice);
    Serial.println("---------");
  }
}