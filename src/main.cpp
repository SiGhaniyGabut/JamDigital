#include "DefinedNecessaries.h"
#include "FlashingViaOTA.h"
#include "FullDate.h"
#include "getWeatherInfo.h"
#include "TelnetConnection.h"
#include <string.h>

void setup() {
    Serial.begin(115200);
    timeClient.begin();

    // Wire.begin(LCD_SDA_PIN, LCD_SCK_PIN);

    lcd.init();
    lcd.backlight();

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED){
        delay(500);
        lcd.print(".");
    }

    FlashingViaOTA();
    setupTelnet();

    lcd.clear();
    lcd.print("Connected To: ");
    lcd.setCursor(0, 2);
    lcd.print("SSID: " + WiFi.SSID());
    lcd.setCursor(0, 3);
    lcd.print("IP: " + WiFi.localIP().toString());

    delay(5000);
    lcd.clear();
}

void greetings() {
    int hourNow = timeClient.getHours();
    lcd.setCursor(0, 0);

    if (timeClient.getMinutes() == 0 and timeClient.getSeconds() == 0) {
        lcd.clear();
    }

    if (hourNow < 5 or hourNow >= 20) {
        lcd.print("GOOD NIGHT");
    }

    if (hourNow >= 5 and hourNow < 11) {
        lcd.print("GOOD MORNING");
    }

    if (hourNow >= 11 and hourNow < 15) {
        lcd.print("GOOD AFTERNOON");
    }

    if (hourNow >= 15 and hourNow < 20) {
        lcd.print("GOOD EVENING");
    }
}

void printDate() {
    char Date[30];
    sprintf_P(Date, PSTR("%02d-%s-%4d"), fullDate.getDate(), monthsOfTheYear[fullDate.getMonth()-1], fullDate.getYear());

    lcd.setCursor(2, 1);
    lcd.print(daysOfTheWeek[timeClient.getDay()]);
    lcd.print(", ");
    lcd.print(Date);
}

void printTime() {
    char Time[10];
    sprintf_P(Time, PSTR("%02d:%02d"), timeClient.getHours(), timeClient.getMinutes());

    lcd.setCursor(15, 0);
    lcd.print(Time);
}

void loop() {
    ArduinoOTA.handle();
    timeClient.update();
    telnet.loop();

    unsigned long currentMillis = millis();
    unsigned long currentWeatherMillisUpdate = millis();

    if (fullDate.getYear() == 1970) {
        lcd.clear();

        lcd.print("NTP TIME FAILED !");
        lcd.setCursor(0, 2);
        lcd.print("Restarting in 5 sec");
        delay(5000);

        ESP.restart();
    }

    if(currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        greetings();
        printDate();
        printTime();
    }

    if(currentWeatherMillisUpdate - previousWeatherMillisUpdate >= weatherUpdateInterval){
        previousWeatherMillisUpdate = currentWeatherMillisUpdate;

        getWeatherInfo();
    }
}