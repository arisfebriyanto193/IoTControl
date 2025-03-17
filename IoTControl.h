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
  //const String serverRelay = "http://192.168.0.107:88/api/api2/relay.php";
    const String serverRelay = "https://iot.microesp.my.id/api/api2/relay.php";
    //const String serverSensor = "http://192.168.0.107:88/api/api2/sensor.php";
    const String serverSensor = "https://iot.microesp.my.id/api/api2/sensor.php";
    const String serverDimmer = "https://iot2.microesp.my.id/api/api2/dimmer.php";
    const String serverText = "https://iot.microesp.my.id/api_txt.php";


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
  
  std::map<String, TextData> texts;  // Menyimpan teks berdasarkan nama
  

    std::map<String, Relay> relays;   // Menyimpan relay berdasarkan nama
    std::map<String, Dimmer> dimmers; // Menyimpan dimmer berdasarkan nama
    std::map<String, Sensor> sensors; // Menyimpan sensor berdasarkan nama

  public:
  public:
    IoTControl(const String& ssid, const String& password, const String& userID, const String& espID);



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
