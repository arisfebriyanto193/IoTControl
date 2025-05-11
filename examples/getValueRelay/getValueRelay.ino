#include <IoTControl.h>

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

  // Menambahkan relay
  iot.setRelay("relay1", "127564b3", 2);

}

void loop() {
  // Update status relay dari server

int statusRelay = iot.getValueRelay("relay1");
//getValueRelay
  Serial.println(statusRelay);



 if (statusRelay == 1){
  digitalWrite(2, 1);
}
else{
    digitalWrite(2, 0);
}
  delay(1000); // Tunggu 5 detik sebelum update berikutnya
}



