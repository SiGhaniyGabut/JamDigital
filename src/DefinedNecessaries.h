#include <Arduino.h>

// Flashing Over Air
#include <ArduinoOTA.h>

// NodeMCU Library
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

#include <LiquidCrystal_I2C.h>
// #include <Wire.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include <ArduinoJson.h>
#include <WiFiClientSecureBearSSL.h>
#include <ESP8266HTTPClient.h>

#include <WiFiUdp.h>
#include <ESPTelnet.h>

#include "secret_key.h"

const char* deviceName = "My Digital Clock";

String ssid  = "kaa.noy"; 
String pass  = "Paviliong4";

// #define LCD_SDA_PIN 4       // Pin D2
// #define LCD_SCK_PIN 5       // Pin D1

// TIME
const long utcOffsetInSeconds = 25200;  // +7 * 60 * 60 (UTC +7 ASIA/JAKARTA)
char monthsOfTheYear[12][12] = {"JAN", "FEB", "MAR", "APR", "MEI", "JUN", "JUL", "AUG", "SEP", "OKT", "NOV", "DES"};
char daysOfTheWeek[7][12] = {"MIN", "SEN", "SEL", "RAB", "KAM", "JUM", "SAB"};

WiFiUDP ntpUDP;
NTPClient timeClient( ntpUDP, "pool.ntp.org", utcOffsetInSeconds );

LiquidCrystal_I2C lcd(0x3F, 20, 4);     // 0x27: Alamat dari modul I2C. 20: Jumlah kolom LCD. 4: Jumlah baris LCD

ESPTelnet telnet;

unsigned long previousMillis = 0;
const long interval = 1000;

unsigned long previousWeatherMillisUpdate = 0;
const long weatherUpdateInterval = 60000; // 1 Minutes
// const long weatherUpdateInterval = 10000; // 10 Seconds (DEBUGGING)


const uint8_t fingerprint[20] = {0xEE, 0xAA, 0x58, 0x6D, 0x4F, 0x1F, 0x42, 0xF4, 0x18, 0x5B, 0x7F, 0xB0, 0xF2, 0x0A, 0x4C, 0xDD, 0x97, 0x47, 0x7D, 0x99};
String weatherAPIKey =  API_KEY;
String city = "1642911"; // Penggilingan, Jakarta Timur

String weatherApiUrl = "https://api.openweathermap.org/data/2.5/weather?id=" + city + "&appid=" + weatherAPIKey +"&units=metric&lang=id";

bool weatherNotConnected = true;