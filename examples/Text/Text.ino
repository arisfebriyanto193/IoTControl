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
    
    iot.setText("pesan1", "t_icc87p8og"); 
    iot.setText("pesan2", "t_makspk093"); // Tambahkan textID
}

void loop() {
    String pesan = iot.getText("pesan1");
        String pesan2 = iot.getText("pesan2");
    Serial.println("Pesan terbaru: " + pesan);
        Serial.println("Pesan2 terbaru: " + pesan2);
    
    delay(1000);
}
