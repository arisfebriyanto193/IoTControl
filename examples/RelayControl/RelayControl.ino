#include <IoTControl.h>

// Konfigurasi WiFi
const char* ssid = "Tenda8";
const char* password = "q1111111";
String user_id = "USR_6816c9c0b91cc";
String esp_id = "ESP_6816cd0f3936c";

// Buat objek IoTControl
IoTControl iot(ssid, password, user_id, esp_id);

void setup() {
  Serial.begin(115200);
  iot.connectWiFi();

  // Tambahkan relay-relay yang dikontrol
  iot.setRelay("buzzer", "0546c798", 15);
  iot.setRelay("ledH", "5fc5557a", 26);
  iot.setRelay("ledM", "fbb59bc9", 27);
  iot.setRelay("relay", "8df63203", 14);
    iot.setRelay("ledb", "b8059640", 2);
}

void loop() {
  // Sekarang update semua relay sekaligus hanya dengan 1 request
  iot.updateAllRelays();
  delay(1000);  // Delay kecil antar polling
}
