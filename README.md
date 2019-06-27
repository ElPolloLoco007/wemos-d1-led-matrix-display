# Wemos D1 Led Matrix Display

This project is about getting data from free Api's with a Wemos D1 and displaying it on a dot matrix module.

* Time
* Weather
* Advice
* Quotes
* News
* F1

https://www.youtube.com/watch?v=MP3CKYKf75Y

## Getting Started
***
Go to Config.h set network and password of your wifi.

To get Serial Print of everything change SERIALPRINT in Config.h to true.

To use the weather api you need to add your key that you get when signing up:

```
path = "http://api.openweathermap.org/data/2.5/"
         "weather?q=Hoyvik,fo&APPID=xxxxxxxxxxxxxx";
}
```
For quotes I used myjson. I uploaded everything thats in my Quotes.json file. You can always add more and edit the uploaded data.

```
qPath = "https://api.myjson.com/bins/xxx";
```

### Components
* OTA WeMos D1 CH340 CH340G WiFi Development Board ESP8266 ESP-12 ESP-12E Module
* 2x MAX7219 Dot Matrix Module For Arduino Microcontroller 4 In One Display with 5P Line Red Green Blue 
* AM2302 DHT22 Digital Temperature & Humidity Sensor Module 

Can be bought cheaply on Aliexpress

 
### IMPORTANT

Create folder lib and add the libraries
### Libraries
* Adafruit_Sensor
* ArduinoJson-6.10.1
* DTH_sensor_library-1.3.4
* MD_MAX72XX
* MD_Parola

### Tools
* VS Code
* Trello (to keep track on what needs to be done)
#### Recomended Extensions
* PlatformIO
* c/c++


### Helpers
https://arduinojson.org/v6/assistant/

https://www.grc.com/fingerprints.htm

## Acknowledgement 
***
Hayk Hakobyan

https://arduino.stackexchange.com/questions/61828/parse-a-large-json-response-with-esp8266

For finding a great way to handle huge json objects.
