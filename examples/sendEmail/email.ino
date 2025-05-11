#include "IoTControl.h"

// Konfigurasi WiFi
const char* ssid = "Tenda8";
const char* password = "q1111111";
String user_id = "USR_6812efe00eee4";
String esp_id = "ESP_6812eff71379e";
// Buat objek IoTControl
IoTControl iot(ssid, password, user_id, esp_id);

void setup() {
    Serial.begin(115200);
    iot.connectWiFi();
  
    iot.setEmail("email1", "email_681bf5450fdb6");
  }
  
  void loop() {
    iot.sendEmail("email1");
    delay(5000);
     iot.resetEmail("email1");
  delay(1000);
  }
  