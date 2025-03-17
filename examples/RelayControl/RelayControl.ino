#include <IoTControl.h>

// Konfigurasi WiFi
const char* ssid = "Tenda8";
const char* password = "q1111111";
String user_id = "USR_67be7f7478241";
String esp_id = "ESP_67c13ba743425"; //ESP_67bd9e483201b

// Buat objek IoTControl
IoTControl iot(ssid, password, user_id, esp_id);

void setup() {
  Serial.begin(115200);
  iot.connectWiFi();

  // Menambahkan relay
  iot.setRelay("relay1", "b98ec897", 2);

}

void loop() {
  // Update status relay dari server
  iot.updateRelay("relay1");


  delay(1000); 
}
