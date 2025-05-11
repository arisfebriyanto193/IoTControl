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
  iot.setDimmer("lampu_kamar", "dmr_68186ad7df");
  pinMode(2, OUTPUT);
}

void loop() {
  int valueDim1 = iot.updateDimmer("lampu_kamar");


  Serial.println("dimmer1 " + String(valueDim1));

  delay(800);
}
