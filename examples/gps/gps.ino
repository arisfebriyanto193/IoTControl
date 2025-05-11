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

  // Masukkan GPS dengan ID
  iot.setGps("Tracker1", "GPS_f98174ddfb");
}


void loop() {
  float latitude = 2.080000;
  float longitude = 102.400000;

  // Update lokasi GPS
  iot.updateGps("Tracker1", latitude, longitude);

  delay(5000); // Kirim data setiap 5 detik
}

