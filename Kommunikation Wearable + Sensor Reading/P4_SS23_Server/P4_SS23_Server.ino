#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPAsyncWebServer.h>

#include <Wire.h>
#include <MPU6050.h>
#include <TFT_eSPI.h>

TFT_eSPI tft;
MPU6050 mpu;

int steps = 0;
int16_t accelX, accelY, accelZ;

bool bStepFlag;
unsigned long lastStepTime = 0;
unsigned long stepDelay = 500;
  
float stepThreshold = 4.0;

const char* ssid = "SSID";
const char* password = "PASSWORD";
const int buttonPin = 19; 

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);

   Wire.begin();

  mpu.initialize();

  tft.init();
  tft.setRotation(1);

  bStepFlag = false;

  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Verbindung zum Wi-Fi-Netzwerk herstellen...");
  }

  Serial.println("Verbunden mit Wi-Fi.");
  Serial.println(WiFi.localIP());
  
  pinMode(buttonPin, INPUT_PULLUP); // Button-Pin als Eingang mit Pull-Up-Widerstand konfigurieren
  
  server.on("/api", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.print("Button-Pin-Zustand: ");
//Serial.println(digitalRead(buttonPin));
Serial.print("Ich bin gerade mit meinem Hund im Park spazieren. Möchte jemande mitkommen? (Zum Antworten halte den Button für 2 Sekunden gedrückt.)");

    if (digitalRead(buttonPin) == LOW) { // Zustand umgekehrt
      Serial.println("Button wurde gedrückt und Antwort gesendet");
      String message = "Cool, ich komme zu dir";
      request->send(200, "text/plain", message);
    }
  });
  
  server.begin();
}

void loop()
{
  mpu.getAcceleration(&accelX, &accelY, &accelZ);

  if (accelY < -stepThreshold)
    bStepFlag = true;
  else if (bStepFlag && accelY > stepThreshold && (millis() - lastStepTime) > stepDelay)
  {
    bStepFlag = false;
    steps++;
    Serial.print("Schritte: ");
    Serial.println(steps);

    tft.fillScreen(TFT_BLACK);
    tft.setCursor(0, 0);
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(2);
    tft.println("Steps: ");
    tft.println(steps);
  }

  delay(300);
}