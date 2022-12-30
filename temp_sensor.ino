#include "DHT.h"
#include "WiFi.h"
#include "HTTPClient.h"

#define DHTPIN 4 // SET TO MATCH YOUR WIRING
#define DHTTYPE DHT22 // OR DHT11

const String sensor_id = "ENTER_SENSOR_IDENTIFIER";
const char* ssid = "ENTER_SSID";
const char* password = "ENTER_PASSPHRASE";
const char* endpoint = "ENTER_SENSORSUITESERVER_ENDPOINT_URI";
unsigned long lastTime = 0;
unsigned long timerDelay = 60000; // Check every minute

DHT dht(DHTPIN, DHTTYPE);

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(9600);
  Serial.println(F("Booting Sensor!"));
  initWiFi();
  Serial.println("Timer set to 10 seconds");
  dht.begin();
}

float getHumidity() {
  float h = dht.readHumidity();

  if (isnan(h)) {
    Serial.println(F("Failed to read from DHT sensor!"));
  } else {
    return h;
  }
}

float getTemp() {
  float t = dht.readTemperature();

  if (isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
  } else {
    return t;
  }
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    if (WiFi.status() == WL_CONNECTED) {
      WiFiClient client;
      HTTPClient http;

      http.begin(client, endpoint);
      http.addHeader("Content-Type", "application/json");
      float humidity = getHumidity();
      float temperature = getTemp();
      String strtemp = String(temperature);
      String strhum = String(humidity);
      String payload = "{\"sensor_id\":\"" + sensor_id + "\",\"temperature_c\":\"" + strtemp + "\",\"humidity\":\"" + strhum + "\"}";
      Serial.print("Connecting to endpoint: ");
      Serial.print(endpoint);
      Serial.print(". Payload data: ");
      Serial.println(payload);
      int httpResponseCode = http.POST(payload);
      Serial.print(" :: Response Code: ");
      Serial.println(httpResponseCode);
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}