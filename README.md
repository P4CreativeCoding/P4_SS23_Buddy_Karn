# Buddy, ein Semesterprojekt von Kim Karn

## Was ist Buddy?

Buddy begleitet und unterstützt Personen in ihrem Alltag und fördert ihre Motivation und die Freunde an körperlicher Aktivität. Er besteht aus zwei Teilen: dem Wearable und dem Würfel. Mit dem Wearable werden körperliche Daten (Schritte und Puls) getrackt, die auf einem Display angezeigt werden. Der namensgebende Motivationsbuddy ist bei jeder Aktivität mit dabei und sendet den Nutzenden Erinnerungen und kleine Prompts. Außerdem kann man sich mit dem Wearable mit anderen Personen vernetzen. Mit dem Würfel können die Nutzenden sich jede Woche neue Aktivitäten auswürfeln. Die gesammelten Daten des Wearables sind ebenfalls auf einer Seite des Würfels zu sehen.

<hr>

## Was ist das Ziel von Buddy?

Ziel ist es Personen nach einer Reha bei der Aufrechterhaltung ihrer Motivation vor allem in Bezug auf die körperliche Aktivität zu unterstützen. Dadurch können die positiven Effekte einer Reha und die Gesundheit der Nutzenden langfristig aufrechterhalten werden. Dieses Ziel soll durch Monitoring, Erinnerungen, Vernetzung mit anderen Personen und Hilfe bei dem Aufbauen einer Routine gelingen.

<hr>

## Was wurde umgesetzt?

Aufgrund der eingeschränkten Ressourcen konnte das Konzept nicht mit den erforderlichen Komponenten umgesetzt werden. Die wichtigsten Funktionen wurden jedoch beispielhaft im Rahmen des MVP bewiesen. Das beinhaltet die Kommunikation zwischen zwei Wearables, die Erfassung der körperlichen Daten, die Übertragung der Daten und die Funktionalität des Würfels.

<hr>

### Übersicht

**P4_SS23_Server.ino** <br>
Der ESP32 fungiert als Server. Sobald der Client einen http.GET request macht, antwortet der Server. Die Antwort erfolgt mithilfe eines Knopfes. Außerdem werden die Schritte über einen Beschleunigungssensor ausgelesen und auf einem Display angezeigt. <br>

**P4_SS23_Client.ino** <br>
Der ESP32 fungiert als Client. Sobald der Knopf gedrückt wurde, wird immer wieder ein http.GET an den Server gesendet. Diese und die Server Datei sollen die Kommunkation zwischen zwei Wearables verdeutlichen.<br>

**P4_SS23_Pulssensor.ino** <br>
Ein Pulssensor wird an einen ESP 32 angeschlossen. Die Daten (bpm) werden im Seriellen Monitor ausgegeben. <br>

**P4_SS23_Wuerfel.ino** <br>
Über einen ESP23 wird ein Webserver gestartet auf dem die Schrittdaten von dem Beschleunigungssensor angezeigt werden. Das soll die Datenübertragung zwischen Wearable und Würfel verdeutlichen.
Die Funktionalität des Würfels kann man zudem über folgende Website testen: https://activity-roll.onrender.com/ <br>

<hr>

### Liste der Bauteile

- 2x DEBO JT ESP32 NodeMCU ESP32 WiFi- und Bluetooth-Modul

- 1x DEBO TFT 1.8 TD Entwicklerboards - Display, 1,8", Touch, ST7735R

- 1x DEBO SENS 3AXISH Entwicklerboards - Beschleunigung & Gyroskop, mit Header, MPU-60

- 1x ARD SEN HEART Arduino - Puls-/Herzschlag-Sensor

- 2x
  Tastschalter

...und sehr viele Jumber Wires und ein Breadboard.

<hr>

### Inbetriebnahme

(Schaltpläne, Anleitung, etc.)
