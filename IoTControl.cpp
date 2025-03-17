#include "IoTControl.h"

IoTControl::IoTControl(const String& ssid, const String& password, const String& userID, const String& espID)
    : ssid(ssid), password(password), userID(userID), espID(espID) {} // Tambahkan espID


  String getMacAddress() {
    uint8_t baseMac[6];
    esp_wifi_get_mac(WIFI_IF_STA, baseMac);
    char macStr[18];
    snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
             baseMac[0], baseMac[1], baseMac[2], baseMac[3], baseMac[4], baseMac[5]);
    return String(macStr);
}




void IoTControl::connectWiFi() {
  WiFi.begin(ssid.c_str(), password.c_str());
  Serial.print("Menghubungkan ke WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi terhubung!");
}

void IoTControl::setRelay(const String& name, const String& relayID, int relayPin) {
  relays[name] = { relayID, relayPin };
  pinMode(relayPin, OUTPUT);
}



void IoTControl::setSensor(const String& name, const String& sensorID) {
  sensors[name] = { sensorID, 0 };
}

void IoTControl::updateRelay(const String& name) {
  if (WiFi.status() == WL_CONNECTED && relays.count(name)) {
    Relay& relay = relays[name];
    HTTPClient http;
    String url = serverRelay + "?user_id=" + userID + "&relay_id=" + relay.relayID + "&esp_id=" + espID + "&device_mac=" + getMacAddress();
    
    http.begin(url);
    // Serial.println(url);
     //Serial.println(" ");
    
    int httpCode = http.GET();
    if (httpCode > 0) {
        String payload = http.getString();
        Serial.println("Response: " + payload);
        
        // Parsing JSON
        StaticJsonDocument<200> doc;
        DeserializationError error = deserializeJson(doc, payload);

        if (!error) {
            int status = doc["status"];  // Ambil nilai status
            digitalWrite(relay.relayPin, status ? HIGH : LOW);
            // Serial.print("Status relay: ");
            // Serial.println(status);
        } else {
            Serial.println("Gagal parsing JSON!");
        }
    } else {
        Serial.println("Gagal mendapatkan data relay " + name + ", kode: " + String(httpCode));
    }
    http.end();
  } else {
    Serial.println("WiFi tidak terhubung atau relay tidak ditemukan!");
  }
}

void IoTControl::sendSensor(const String& name, float value) {
  if (WiFi.status() == WL_CONNECTED && sensors.count(name)) {
    Sensor& sensor = sensors[name];
    sensor.value = value;

    HTTPClient http;
    String postData = "user_id=" + userID +  "&esp_id="+ espID +  "&sensor_id=" + sensor.sensorID + "&value=" + String(sensor.value) + "&mac=" + getMacAddress();
    http.begin(serverSensor);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    int httpResponseCode = http.POST(postData);

    if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println("Server Response: " + response);
    } else {
        Serial.println("Error sending POST request");
    }

    http.end();
  } else {
    Serial.println("WiFi tidak terkoneksi atau sensor tidak ditemukan!");
  }
}


void IoTControl::setDimmer(const String& name, const String& dimmerID) {
  dimmers[name] = { dimmerID, 0 };
}



int IoTControl::getValueRelay(const String& name) {
  if (WiFi.status() == WL_CONNECTED && relays.count(name)) {
    Relay& relay = relays[name];
    HTTPClient http;
    
    // Request ke server dengan `relay_id`
    String url = serverRelay + "?user_id=" + userID + "&relay_id=" + relay.relayID + "&esp_id=" + espID + "&device_mac=" + getMacAddress();
    http.begin(url);
    
    int httpCode = http.GET();
    if (httpCode > 0) {
      String payload = http.getString();
      
      // Parsing JSON
      StaticJsonDocument<200> doc;
      DeserializationError error = deserializeJson(doc, payload);

     /// Serial.println(payload);
      
      if (!error) {
        if (doc.containsKey("status")) {
          int relayStatus = doc["status"].as<int>();  // Ambil nilai status
          return relayStatus;
        } else {
          Serial.println("⚠️ JSON tidak memiliki key 'status'!");
          return -1;
        }
      } else {
        Serial.println("❌ Gagal parsing JSON! Error: " + String(error.c_str()));
        return -1;
      }
    } else {
      Serial.println("Gagal mendapatkan data relay " + name + ", kode: " + String(httpCode));
      return -1;
    }
    http.end();
  } else {
    Serial.println("WiFi tidak terhubung atau relay tidak ditemukan!");
    return -1;
  }
}



int IoTControl::updateDimmer(const String& name) {
  if (WiFi.status() == WL_CONNECTED && dimmers.count(name)) {
    Dimmer& dimmer = dimmers[name];
    HTTPClient http;
    String url = serverDimmer + "?user_id=" + userID + "&dimmer_id=" + dimmer.dimmerID + "&esp_id=" + espID + "&mac=" + getMacAddress();
    http.begin(url);

    int httpResponseCode = http.GET();
    if (httpResponseCode > 0) {
      String response = http.getString();
     // Serial.println("Dimmer Response: " + response);

      // Parse JSON
      StaticJsonDocument<200> doc;
      DeserializationError error = deserializeJson(doc, response);

      if (error) {
        Serial.println("❌ Gagal parsing JSON!");
        return -1;
      }

      if (doc.containsKey("dimmer")) {
        dimmer.value = doc["dimmer"].as<int>();  // Ambil nilai dimmer
        return dimmer.value;
      } else {
        Serial.println("⚠️ JSON tidak memiliki key 'dimmer'!");
        return -1;
      }
    } else {
      Serial.println("Gagal mendapatkan data dimmer " + name + ", kode: " + String(httpResponseCode));
      return -1;
    }
    http.end();
  } else {
    Serial.println("WiFi tidak terhubung atau dimmer tidak ditemukan!");
    return -1;
  }
}


void IoTControl::setText(const String& name, const String& textID) {
  texts[name] = { textID, "" };
}

String IoTControl::getText(const String& name) {
  if (WiFi.status() == WL_CONNECTED && texts.count(name)) {
      TextData& text = texts[name];
      HTTPClient http;

      // Tambahkan MAC address untuk validasi
      String url = serverText + "?user_id=" + userID + "&text_id=" + text.textID + "&esp_id=" + espID + "&mac=" + getMacAddress();
      
      http.begin(url);
      int httpResponseCode = http.GET();

      if (httpResponseCode > 0) { // Pastikan ada respons dari server
          String payload = http.getString();
          StaticJsonDocument<256> doc;
          DeserializationError error = deserializeJson(doc, payload);

          if (!error) {
              if (doc.containsKey("konten")) {
                  text.value = doc["konten"].as<String>();
                 // Serial.println("✅ Text (" + name + "): " + text.value);
              } else if (doc.containsKey("error")) {
                  Serial.println("⚠️ Server Error: " + String(doc["error"].as<const char*>()));
              } else {
                  Serial.println("⚠️ Tidak ada konten teks!");
              }
          } else {
              Serial.println("⚠️ Gagal parsing JSON! Error: " + String(error.c_str()));
          }
      } else {
          Serial.println("⚠️ Gagal mendapatkan data teks, kode: " + String(httpResponseCode));
      }

      http.end();
  } else {
      Serial.println("⚠️ WiFi tidak terhubung atau teks tidak ditemukan!");
  }
  return texts[name].value;
}

void IoTControl::setGps(const String& name, const String& gpsID) {
  gpsDevices[name] = { gpsID, 0.0, 0.0 };
}

void IoTControl::updateGps(const String& name, float latitude, float longitude) {
  if (WiFi.status() == WL_CONNECTED && gpsDevices.count(name)) {
    GPS& gps = gpsDevices[name];
    gps.latitude = latitude;
    gps.longitude = longitude;

    HTTPClient http;
    String url = serverGps + "?user_id=" + userID +
                 "&gps_id=" + gps.gpsID +
                 "&latitude=" + String(latitude, 6) +
                 "&longitude=" + String(longitude, 6) +
                 "&esp_id=" + espID +
                 "&device_mac=" + getMacAddress();

    http.begin(url);
    int httpCode = http.GET();

    if (httpCode > 0) {
      String response = http.getString();
      Serial.println("GPS Response: " + response);
    } else {
      Serial.println("Gagal mengirim data GPS, kode: " + String(httpCode));
    }

    http.end();
  } else {
    Serial.println("⚠️ WiFi tidak terhubung atau GPS tidak ditemukan!");
  }
}
