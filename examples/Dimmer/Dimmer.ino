#include "IoTControl.h"

IoTControl iot("Tenda8", "q1111111", "USR_67ba5fedhyr0f", "");

void setup() {
  Serial.begin(115200);
  iot.connectWiFi();
  iot.setDimmer("lampu_kamar", "dmr_67b0hffbf0");
  iot.setDimmer("lampu_teras", "dmr_67ba65kh49");
  pinMode(2, OUTPUT);
}

void loop() {
  int valueDim1 = iot.updateDimmer("lampu_kamar");
  int valueDim2 = iot.updateDimmer("lampu_teras");

  Serial.println("dimmer1 " + String(valueDim1));
  Serial.println("dimmer2 " + String(valueDim2));
  delay(800);
}
