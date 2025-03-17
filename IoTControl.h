#ifndef IOTCONTROL_H
#define IOTCONTROL_H

#include <Arduino.h>
#ifdef ESP8266
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
#else
  #include <WiFi.h>
  #include <HTTPClient.h>
#endif

#include <esp_wifi.h>
#include <ArduinoJson.h>
#include <map>

class IoTControl {
  private:
    const String serverRelay = "https://iot.microesp.my.id/api/api2/relay.php";
    const String serverSensor = "https://iot.microesp.my.id/api/api2/sensor.php";
    const String serverDimmer = "https://iot.microesp.my.id/api/api2/dimmer.php";
    const String serverText = "https://iot.microesp.my.id/api/api2/text.php";
    const String serverGps = "https://iot.microesp.my.id/api/api2/gps2.php";


    String ssid;
    String password;
    String userID;
    String espID; // Tambahkan ini

    struct Relay {
      String relayID;
      int relayPin;
    };

    struct Dimmer {
      String dimmerID;
      int value;
    };
    struct Sensor {
      String sensorID;
      float value;
    };
    struct TextData {
      String textID;
      String value;
  };

  struct GPS {
    String gpsID;
    float latitude;
    float longitude;
};
  
std::map<String, GPS> gpsDevices;  

std::map<String, Relay> relays;
std::map<String, Sensor> sensors;
std::map<String, Dimmer> dimmers;
std::map<String, TextData> texts;
  public:
  public:
    IoTControl(const String& ssid, const String& password, const String& userID, const String& espID);

    void setGps(const String& name, const String& gpsID);
    void updateGps(const String& name, float latitude, float longitude);


    void connectWiFi();
    void setRelay(const String& name, const String& relayID, int relayPin);
    void setDimmer(const String& name, const String& dimmerID);
    int updateDimmer(const String& name);
    void setSensor(const String& name, const String& sensorID);
    void updateRelay(const String& name);
  
    void sendSensor(const String& name, float value);

    void setText(const String& name, const String& textID);
String getText(const String& name);


int getValueRelay(const String& name);

};

#endif
