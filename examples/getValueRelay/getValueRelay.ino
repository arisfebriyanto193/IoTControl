#include <IoTControl.h>

// Konfigurasi WiFi
const char* ssid = "UDINUS I.4";
const char* password = "";
String user_id = "USR_67c2912cdb761";
String esp_id = "ESP_67d13e7ba6d04"; //ESP_67bd9e483201b

// Buat objek IoTControl
IoTControl iot(ssid, password, user_id, esp_id);

void setup() {
  Serial.begin(115200);
  iot.connectWiFi();

  // Menambahkan relay
  iot.setRelay("relay1", "2e857a5a", 2);

}

void loop() {
  // Update status relay dari server

int statusRelay = iot.getValueRelay("relay1");
//getValueRelay
  Serial.println(statusRelay);


if (statusRelay != -1){
  Serial.println("Koneksi Eror");
}

else if (statusRelay == 1){
  digitalWrite(2, 1);
}
else{
    digitalWrite(2, 0);
}
  delay(1000); // Tunggu 5 detik sebelum update berikutnya
}



