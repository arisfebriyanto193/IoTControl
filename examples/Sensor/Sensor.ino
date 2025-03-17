#include <IoTControl.h>

// Konfigurasi WiFi
const char* ssid = "Tenda8";
const char* password = "q1111111";
String user_id = "USR_67ad54b8e5daf";

// Buat objek IoTControl
IoTControl iot(ssid, password, user_id);

void setup() {
  Serial.begin(115200);
  iot.connectWiFi();

  // Menambahkan sensor
  iot.setSensor("sensor1", "d256f");
  iot.setSensor("sensor2", "a1b2c3");
}

void loop() {
  // Simulasi nilai sensor
  float suhu = random(20, 30);       // Contoh nilai suhu antara 20 - 30
  float kelembaban = random(40, 60); // Contoh nilai kelembaban antara 40 - 60

  // Kirim data sensor ke server
  iot.sendSensor("sensor1", suhu);
  iot.sendSensor("sensor2", kelembaban);

  delay(5000); // Kirim data setiap 5 detik
}
