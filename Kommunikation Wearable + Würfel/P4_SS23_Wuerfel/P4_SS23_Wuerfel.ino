#include <WiFi.h>
#include <Wire.h>
#include <MPU6050.h>

const char* ssid = "SSID";
const char* password = "PASSWORD";

WiFiServer server(80);

MPU6050 mpu;

int steps = 0;
int16_t accelX, accelY, accelZ;

bool bStepFlag;
unsigned long lastStepTime = 0;
unsigned long stepDelay = 500;

float stepThresholdLow = 1.5;
float stepThresholdHigh = 4.0;

void setup() {
  Serial.begin(115200);
  Serial.println();
 bStepFlag = false;
   Wire.begin();
 
  mpu.initialize();

  Serial.printf("Verbinde mit %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" verbunden");

  server.begin();
  Serial.printf("Webserver gestartet, öffnen Sie http://%s/ in einem Webbrowser\n", WiFi.localIP().toString().c_str());
}

String prepareHtmlPage() {
  String stepsData = "[500, 10726, 7022, 6083, " + String(steps) + "]"; // Daten für die Schritte pro Tag anpassen

  String htmlPage =
    String("HTTP/1.1 200 OK\r\n") +
    "Content-Type: text/html\r\n" +
    "Connection: close\r\n" +
    "Refresh: 5\r\n" +
    "\r\n" +
    "<!DOCTYPE HTML>" +
    "<html>" +
    "<head>" +
    "<script src=\"https://cdn.jsdelivr.net/npm/chart.js\"></script>" + // Chart.js Bibliothek einbinden
    "</head>" +
    "<body>" +
    "<canvas id=\"stepChart\"></canvas>" + // Platzhalter für das Diagramm
    "<script>" +
    "document.addEventListener('DOMContentLoaded', function() {" +
    "  var ctx = document.getElementById('stepChart').getContext('2d');" +
    "  var chart = new Chart(ctx, {" +
    "    type: 'bar'," +
    "    data: {" +
    "      labels: ['16.07', '17.07.', '18.07,', 'Gestern', 'Heute']," + // Labels für die Tage anpassen
    "      datasets: [{\"label\": 'Schritte'," +
    "        data: " + stepsData + "," +
    "        backgroundColor: ['#274211', '#274211', '#274211', '#274211', '#DF2089']," + // Hintergrundfarben der Balken anpassen
    "        borderWidth: 1" +
    "      }]" +
    "    }," +
    "    options: {" +
    "      animation: {" +
    "        duration: 0" + // Animation deaktivieren
    "      }," +
    "      scales: {" +
    "        y: {" +
    "          beginAtZero: true" +
    "        }" +
    "      }" +
    "    }" +
    "  });" +
    "});" +
    "</script>" +
    "</body>" +
    "</html>" +
    "\r\n";
  return htmlPage;
}



void loop() {
  mpu.getAcceleration(&accelX, &accelY, &accelZ);

  if (accelY < -stepThresholdHigh)
    bStepFlag = true;
  else if (bStepFlag && accelY > stepThresholdHigh && (millis() - lastStepTime) > stepDelay) {
    bStepFlag = false;
    steps++;
    Serial.print("Steps: ");
    Serial.println(steps);
    delay(300);
  }

  WiFiClient client = server.available();

  if (client) {
    Serial.println("\n[Client hat sich verbunden]");
    while (client.connected()) {
      if (client.available()) {
        String line = client.readStringUntil('\r');
        Serial.print(line);
        if (line.length() == 1 && line[0] == '\n') {
          client.println(prepareHtmlPage());
          break;
        }
      }
    }
    client.stop();
    Serial.println("[Client getrennt]");
    delay(10);
  }

}
