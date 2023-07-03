//Leider ist der von mir verwendete Pulssensor defekt. Allerdings wurde dieser Code mit einem Pulssensor von Team 7 getestet. Da hatte alles wie gewünscht funktioniert, weswegen ich mich entschieden habe den Code trotzdem abzugeben.


#include <PulseSensorPlayground.h>

int PulseSensorPin = 25;
int LED = 2; 

int Signal;
int Threshold = 100;

int bpm = 0; 

unsigned long sampleInterval = 100;
unsigned long lastSampleTime = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:

  unsigned long currentTime = millis(); //aktuelle Zeit in Millisekunden
  if(currentTime - lastSampleTime >= sampleInterval){
    lastSampleTime = currentTime; // Aktualisiere die letzre Probezeit 
  }

  Signal = analogRead(PulseSensorPin); 
  Serial.println(Signal);

  if(Signal > Threshold){
    digitalWrite(LED, LOW);
  }else {
    digitalWrite(LED, HIGH);
  }

  // Puls berechnen 
  bpm = map(Signal, Threshold, 1024, 0, 220); //Anpassung des Bereichs des Signals auf Herzschläge pro Minute (0-220bpm)

  // Puls anzeigen
  Serial.print("Puls: ");
  Serial.print(bpm);
  Serial.println(" bpm");
  delay(300);

}