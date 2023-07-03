#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "SSID";
const char* password = "PASSWORD";
const int buttonPin = 19; 

bool buttonPressed = false; // Variable zum Verfolgen des Button-Zustands

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Verbindung zum Wi-Fi-Netzwerk herstellen...");
  }

  Serial.println("Verbunden mit Wi-Fi.");
  
  pinMode(buttonPin, INPUT_PULLUP); // Button-Pin als Eingang mit Pull-Up-Widerstand konfigurieren
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    int buttonState = digitalRead(buttonPin);
    //Serial.println("Button-Zustand: " + String(buttonState));

    if (buttonState == LOW && !buttonPressed) { // Überprüfen, ob der Button gedrückt wurde und ob der Button bereits gedrückt wurde
      buttonPressed = true; // Button-Zustand auf gedrückt setzen
      Serial.println("Button wurde gedrückt"); 
    }

    if (buttonPressed) {
      HTTPClient http;
      http.begin("http://172.20.10.2/api"); // IP Adresse des ESP32
      http.addHeader("Content-Type", "text/plain");

      int httpCode = http.GET();
      Serial.println("HTTP-Code: " + String(httpCode)); 

      if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK) {
          String response = http.getString();
          Serial.println("Antwort erhalten: " + response);
        }
      } else {
        Serial.println("Du hast (noch) keine Antwort erhalten.");
      }
    
      http.end();
    }
  }
  
  delay(2000); // Eine Verzögerung, um die Schleife zu entlasten
}

