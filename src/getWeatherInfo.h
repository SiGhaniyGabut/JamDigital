void getWeatherInfo() {
    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
    client->setFingerprint(fingerprint);

    HTTPClient https;

    if(https.begin(*client, weatherApiUrl)){
        int httpResponseCode = https.GET();

        if(httpResponseCode > 0) {

            if(weatherNotConnected == true) {
                lcd.clear();
            }

            String payload = https.getString();

            DynamicJsonDocument weatherJSON(1024);
            auto error = deserializeJson(weatherJSON, payload);

            if (error) {
                lcd.print("JSON FAILED: ");
                lcd.print(error.c_str());
            }

            char temperature[5];
            char feels_like[5];

            sprintf_P(temperature, PSTR("%.fC"), weatherJSON["main"]["temp"].as<float>());
            sprintf_P(feels_like, PSTR("%.fC"), weatherJSON["main"]["feels_like"].as<float>());

            String cityName = weatherJSON["name"].as<String>();
            String humidity = weatherJSON["main"]["humidity"].as<String>();
            String cloud = weatherJSON["clouds"]["all"].as<String>();
            String weather = weatherJSON["weather"][0]["main"].as<String>();
            String weatherDescription = weatherJSON["weather"][0]["description"].as<String>();
            String weatherDetail = weather + ", " + weatherDescription;
            
            telnet.println("------- WEATHER INFORMATION --------");
            telnet.print("CITY: ");
            telnet.println(cityName);
            telnet.print("TEMPERATURE: ");
            telnet.println(temperature);
            telnet.print("FEELS LIKE: ");
            telnet.println(feels_like);
            telnet.print("WEATHER: ");
            telnet.println(weatherDetail);
            telnet.print("HUMIDITY: ");
            telnet.println(humidity + "%");
            telnet.print("CLOUDS COVER: ");
            telnet.println(cloud + "%");
            telnet.println("------------------------------------");

            lcd.setCursor(2, 2);
            lcd.print(weatherDescription);
            lcd.setCursor(0, 3);
            lcd.print("T:");
            lcd.print(temperature);
            lcd.setCursor(6, 3);
            lcd.print("FL:");
            lcd.print(feels_like);
            lcd.setCursor(13, 3);
            lcd.print("HUM:" + humidity + "%");

            weatherNotConnected = false;
        }
        else {
            lcd.clear();
            lcd.setCursor(1, 3);
            lcd.print("WEATHER != CONNECT");

            weatherNotConnected = true;
        }
    }

    https.end();
}
