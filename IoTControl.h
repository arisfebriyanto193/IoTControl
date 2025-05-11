#ifndef IOTCONTROL_H
#define IOTCONTROL_H

#include <Arduino.h>

#ifdef ESP8266
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
#else
  #include <WiFi.h>
  #include <HTTPClient.h>
  #include <esp_wifi.h>
#endif

#include <ArduinoJson.h>
#include <map>

class IoTControl {
  private:
    const String serverRelay = "https://iot.microesp.my.id/api/api1/relay.php";
    const String serverRelay1 = "https://iot.microesp.my.id/api/api2/relay.php";
    const String serverSensor = "https://iot.microesp.my.id/api/api1/sensor.php";
    const String serverEmail =   "https://iot.microesp.my.id/api/api1/email.php";
    const String serverDimmer = "https://iot.microesp.my.id/api/api2/dimmer.php";
    const String serverText   = "https://iot.microesp.my.id/api/api2/text.php";
    const String serverGps    = "https://iot.microesp.my.id/api/api2/gps2.php";

    String ssid;
    String password;
    String userID;
    String espID;

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


    // Tambahkan di struct bagian private
struct Email {
  String emailID;
};




  public:
    std::map<String, Relay> relays;
    std::map<String, Sensor> sensors;
    std::map<String, Dimmer> dimmers;
    std::map<String, TextData> texts;
    std::map<String, GPS> gpsDevices;
    // Tambahkan di bagian public
std::map<String, Email> emails;

    IoTControl(const String& ssid, const String& password, const String& userID, const String& espID);



    void setEmail(const String& name, const String& emailID);
    void sendEmail(const String& name);
    void resetEmail(const String& name);
    


    void connectWiFi();
    void updateAllRelays();  // Tambahkan deklarasi ini di bagian public
   void sendSensors();

    // Relay
    void setRelay(const String& name, const String& relayID, int relayPin);
    void updateRelay(const String& name);
    int getValueRelay(const String& name);
    void updateSensorValue(const String& name, float value);

    // Sensor
    void setSensor(const String& name, const String& sensorID);
    void sendSensor(const String& name, float value);


    // Dimmer
    void setDimmer(const String& name, const String& dimmerID);
    int updateDimmer(const String& name);

    // Text
    void setText(const String& name, const String& textID);
    String getText(const String& name);

    // GPS
    void setGps(const String& name, const String& gpsID);
    void updateGps(const String& name, float latitude, float longitude);
};

#endif
