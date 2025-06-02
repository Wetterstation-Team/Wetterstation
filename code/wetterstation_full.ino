#include <WiFi.h> 
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <ESPAsyncWebServer.h>
#include "index.h"

#define DHTPIN 10
#define DHTTYPE DHT11
#define SPEAKER 3

hw_timer_t *timer = NULL;

DHT dht(DHTPIN, DHTTYPE);

float temperature;
float humidity;
volatile bool updateStats;

const char* ssid = "G55AB";
const char* password = "Gast-L53";

AsyncWebServer server(80);

String header;

unsigned long currentTime = millis();
unsigned long previousTime;

bool speakerState = false;

void IRAM_ATTR onTimer() {
  updateStats = true;
}

void setup() {
  digitalWrite(LED_BUILTIN, LOW);

  pinMode(SPEAKER, OUTPUT);
  Serial.begin(115200);

  dht.begin();
  timer = timerBegin(1000000);
  timerAttachInterrupt(timer, &onTimer);
  timerAlarm(timer, 10000000, true, 0);

  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.print(" with password ");
  Serial.print(password);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(200, "text/html", website);
  });
  server.on("/temp", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(200, "text/plain", (String) dht.readTemperature());
  });
  server.on("/hum", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(200, "text/plain", (String) dht.readHumidity());
  });
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest* request) {
    speakerState = true;
    request->send(200, "text/html", website);
  });
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest* request) {
    speakerState = false;
    request->send(200, "text/html", website);
  });
  server.begin();
}

void loop() {
  if (updateStats) {
    if (speakerState) {
          tone(3, 440);
    }
    float tempHumidity = dht.readHumidity();
    float tempTemperature = dht.readTemperature();
  
    if (isnan(tempHumidity) || isnan(tempTemperature)) {
      Serial.println("Error reading temperature or humidity!");
      updateStats = false;
      return;
    }

    temperature = tempTemperature;
    humidity = tempHumidity;
    updateStats = false;
    noTone(3);
  }
}
