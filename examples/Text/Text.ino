#include "IoTControl.h"


IoTControl iot("Tenda8", "q1111111", "USR_67ba5fed3b00f");

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
