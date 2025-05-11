
#include <IoTControl.h>

// Konfigurasi WiFi
const char* ssid = "Tenda8";
const char* password = "q1111111";
String user_id = "USR_6816c9c0b91cc";
String esp_id = "ESP_6816ec168182f";
// Buat objek IoTControl
IoTControl iot(ssid, password, user_id, esp_id);

void setup() {
  Serial.begin(115200);
  iot.connectWiFi();

  // Menambahkan sensor
  iot.setSensor("sensor1", "snr_6816eb9");
  iot.setSensor("sensor2", "snr_6816eba6");
  iot.setSensor("sensor3", "snr_6816ebb6");
}

void loop() {
  // Set nilai sensor
  iot.sensors["sensor1"].value = random(0, 100);
  iot.sensors["sensor2"].value = random(0, 10);
  iot.sensors["sensor3"].value = random(10, 20);

  // Kirim semua sensor sekaligus dalam satu batch
  iot.sendSensors();

  delay(1000); // Delay antar pengiriman data batch
}
