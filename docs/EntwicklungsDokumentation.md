# Entwicklerdokumentation

Die Entwicklerdokumentation beinhaltet unsere im Gruppenmeeting erstellten Issues zur Entwicklung unseres Projektes. Anhand dieser lässt sich der Verlauf unseres Projektes darstellen. Die Ergebnisse und Aufgabenverteilung unserer Teammeetings liegen im Unterordner /sprintmeetings.

**#1**

## Entwicklung und Interaktion
### User Story
Der Benutzer kann durch Ein- und Ausgaben mit einem sich entwickelnden, 
reaktiven Organismus interagieren. Dieses System versetzt in die Lage, 
die Performance von interplanetaren portablen Gewächshäusern zu bewerten.

### Kriterien zur Fertigstellung
- [x] Dem Nutzer werden Möglichkeiten (die in anderen Items spezifiziert werden) gegeben,
      den Organismus zu versorgen.
- [x] Bei angemessener Pflege entwickelt sich der Organismus über die Zeit.
- [x] Diese Entwicklung hängt von mehreren Komponenten ab: 
  - [x] Umgebungseinflüsse, wie Temperatur, Licht und Luftfeuchtigkeit
  - [x] Alter des Organismus und vorherige Entwicklung

### Technologieübersicht
- Seed Studio (Hardware/Sensorik)
- Arduino IDE
- Backendtechnologie (Web und SQL)

### Geschätze Dauer
4 Wochen

### Abhängigkeiten
Keine

### Milestone
Milestone 2

### Assignee
Alle

### Labels
arduino, backend, product-backlog-item, selected

---
**#2**

## Statusverlauf im Web-Interface
### User Story
Der Benutzer ist in der Lage, sich den aktuellen sowie den vergangenen Status der Pflanze
anhand aufbereiteter Daten anzeigen zu lassen.

### Kriterien zur Fertigstellung
- [x] Der Nutzer kann den aktuellen Status der Pflanze begutachten
- [x] Der Nutzer kann den vergangenen Status der Pflanze begutachten
- [x] Der Nutzer kann sich die visuelle Entwicklung seiner Pflanze anschauen

### Technologieübersicht
HTML, CSS, JAVASCRIPT, RASPBIAN, PHP

### Geschätze Dauer
3-4 Wochen

### Abhängigkeiten
Back-End (Datenbank), #4 

### Milestone
Milestone 2

### Assignee
Alle

### Labels
backend, product-backlog-item, selected, web-frontend

---
**#3**

## Export und Verwaltung
### User Story
Der Benutzer ist in der Lage mittels Web-Interface Daten eines Geräte (Pflanze) zu exportieren/speichern und auf ein neues Gerät aufzuspielen.

### Kriterien zur Fertigstellung
- [x] Der Nutzer kann Daten exportieren
- [x] Der Nutzer kann Geräte hinzufügen und löschen
- [x] Der Nutzer kann exportierte Daten auf Geräte importieren

### Technologieübersicht
MYSQL

### Geschätze Dauer
1 Woche

### Abhängigkeiten
Back-End (Datenbank) und Web-Interface

### Milestone
Milestone 3

### Assignee
Alle

### Labels
backend, product-backlog-item, selected, stretchgoal, web-frontend

---
**#4**

## ISSUENAME
### User Story
Der Benutzer sollte die Entwicklung des Organismus visuell nachvollziehen können,
um die Auswirkungen der Umgebung und die Entwicklung des Organismus nachvollziehen und entsprechend reagieren zu können.

### Kriterien zur Fertigstellung
- [x] Auf einem Display wird der Zustand des Organismus visualisiert.
- [x] Diese Visualisierung soll intuitiv verständlich sein.
- [x] Die Darstellung reagiert plausibel und zuverlässig auf Veränderungen des Zustands des Organismus

### Technologieübersicht
- Seed Studio (Hardware/Sensorik)
- Arduino IDE
- Illustrationsprogramme für Displaygrafik

### Geschätze Dauer
14 Tage

### Abhängigkeiten
#1

### Milestone
Milestone 1

### Assignee
Alle

### Labels
arduino, product-backlog-item, selected, web-frontend

---
**#5**

## Ausfallsicherheit
### User Story
Der Benutzer bekommt zu jedem Zeitpunkt vom System - also auch bei partiellen Ausfällen oder voller werdenden Speicher - die bestmögliche Sicherheit der gesammelten Daten, damit er sich darauf verlassen kann.

### Kriterien zur Fertigstellung
- [x] Bei Verbindungsabbruch zum Raspberry Pi speichert der Arduino alle Sensor-Werte lokal
  - [x] Diese Daten werden bei knappen Speicherplatz (eventuell verlustbehaftet) komprimiert, so dass die ältesten Daten nicht vollständig verloren gehen.
- [x] Die Speicherung der Daten überlebt einen Netzreset und Neustart
- [x] Die lokale Simulation wird während Sensor- oder Konnektivitätseinschränkungen fortgesetzt

### Technologieübersicht
Arduino

### Geschätze Dauer
6 Wochen

### Abhängigkeiten
Backlog Item #1

### Milestone
Milestone 2

### Assignee
Alle

### Labels
arduino, product-backlog-item, selected

---
**#6**

## Einfaches Provisioning des Raspberry Pis
### User Story
Der Benutzer ist in der Lage, den Raspberry Pi durch wenige (< 5) Kommandos als das Gegenstück eines Arduinos einzurichten, um ihn einfach austauschbar und Updates schmerzlos zu machen.

### Kriterien zur Fertigstellung
- [ ] Von einer bootbaren Raspbian-Installation aus kann man ein Skript ausführen, dass den Raspberry komplett einrichtet

### Technologieübersicht
Docker oder Ansible, Raspbian

### Geschätze Dauer
1 Woche

### Abhängigkeiten
Keine

### Milestone
Keine

### Assignee
Alle

### Labels
backend, not selected, product-backlog-item, web-frontend

---
**#7**

## Handy App
### User Story
Der Benutzer ist in der Lage, von einer Smartphone App auf das Web-Interface
zugreifen zu können.

### Kriterien zur Fertigstellung
- [ ] Startfähige Android App
- [ ] Featuregleichheit mit dem Web-Interface

### Technologieübersicht
Android Platform, Kolin oder Java? React Native? Xamarin?

### Geschätze Dauer
3 Wochen 

### Abhängigkeiten
Web-Interface

### Milestone
Keine

### Assignee
Alle

### Labels
not selected, product-backlog-item, web-frontend

---
**#8**

## Handhabung mehrerer Pflanzen
### User Story
Der User kann über das Web-Interface Pflanzen mit unterschiedlichen Bedürfnissen vom Arduino auf den Raspberry Pi auslagen und umgekehrt gespeicherte Pflanzen vom Raspberry Pi auf den Arduino senden.

### Kriterien zur Fertigstellung
- [x] Verhalten der Pflanze auf dem Raspberry Pi spezifizieren. (Schläft, wächst weiter ect.)
- [x] Funktion in Übertragungsprotokoll vom Raspberry Pi und Arduino implementieren.
- [x] User-Interface anpassen.

### Technologieübersicht
Arduino, MySQL, TCP/IP, JAVASCRIPT

### Geschätze Dauer
2 Wochen

### Abhängigkeiten
#4 #2

### Milestone
Milestone 3

### Assignee
Alle    

### Labels
arduino, backend, product-backlog-item, selected, web-frontend

---
**#9**

## Auswahl des Organismus
### User Story
Der Benutzer hat die Auswahl zwischen verschiedene Organismen, die jeweils unterschiedliche Bedürfnisse haben. Die Organismen können sich, wenn die Bedürfnisse erfüllt sind, weiterentwickeln bzw. wachsen.

### Kriterien zur Fertigstellung
- [x] Template für ein Organismus
    - [x] alle möglichen Bedürfnisse müssen berücksichtigt werden 
- [x] Interface
    - [x] Namensgebung
    - [x] Auswahl des Organismus

### Technologieübersicht
Arduino, Rasperry, Web-Interface

### Geschätze Dauer
49 Tage

### Abhängigkeiten
#1 , Web-Interface, Datenbank

### Milestone
Keine

### Assignee
Alle

### Labels
backend, duplicate, product-backlog-item, web-frontend
---
**#10**

## Parasitärer Befall
### User Story
Ein Benutzer kann Typen von Organismen einsetzen, die andere Organismen auf getrennten Arduinos parasitär befallen und in ihrer Entwicklung manipulieren, um die Wechselwirkungen zwischen verschiedenen Organismen zu analysieren.

### Kriterien zur Fertigstellung
- [ ] Jeder Organismus definiert, ob und welche anderen Organismen er befallen kann
- [ ] Der Befall wird ggf. visuell dargestellt
- [ ] Der Befall wirkt sich auf die Entwicklung aus
- [ ] Der Befall kann wieder rückgängig gemacht werden

### Technologieübersicht
Arduino, Web-App

### Geschätze Dauer
2 Wochen

### Abhängigkeiten
#11 

### Milestone
Keine

### Assignee
Alle

### Labels
arduino, not selected, product-backlog-item

---
**#11**

## Template zur Erstellung eines Organismus
### User Story
Der Benutzer ist in der Lage ein neues Organismus mit spezifizierten Bedürfnissen zu erstellen.

### Kriterien zur Fertigstellung
- [x] alle Bedürfnisse sollten festgelegt werden
- [x] Template für ein Organismus
    - [x] Stufen-abhängige Entwicklungsphasen mit entsprechendes Bild
    - [x] Namensgebung
    - [x] Grundbedarf
- [x] eventuelle Erstellung durch ein geeignetes User-Interface

### Technologieübersicht
Web-Interface, Raspberry, Arduino

### Geschätze Dauer
1 Woche

### Abhängigkeiten
#1, Web-Interface

### Milestone
Milestone 3

### Assignee
No

### Labels
backend, product-backlog-item, selected, web-frontend

---
**#12**

## Musik
### User Story
Wenn der Benutzer den Organismus mit Musik beschallt, reagiert
sie mit einer verbesserten Entwicklung

### Kriterien zur Fertigstellung
- [ ] Der Organismus reagiert auf akustische Einflüsse mit stärkerem Wachstum.

### Technologieübersicht
Mikrofon / Seeed Studio
Arduino IDE

### Geschätze Dauer
7 Tage

### Abhängigkeiten
Keine

### Milestone
Keine

### Assignee
No

### Labels
arduino, product-backlog-item, stretchgoal

---
**#13**

## Früchte der Pflanze
### User Story
Der Benutzer ist in der Lage, visuell zu erkennen ob die Pflanze Früchte trägt wenn es ihr gut geht.

### Kriterien zur Fertigstellung
- [ ] Visualisierung der Früchte
- [ ] Eigenschaften um Fruchtwachstum zu modellieren
- [ ] Speicherung der Früchte im Backend

### Technologieübersicht
Arduino, JavaScript

### Geschätze Dauer
14 Tage

### Abhängigkeiten
Visualisierung #4

### Milestone
Keine

### Assignee
No

### Labels
arduino, backend, not selected, product-backlog-item

---
**#14**

## Pflichtenheft Anwendungsgebiete

Anwendungsbereich für PlantX

### Kriterien zur Fertigstellung
- [x] Rechtschreibung
- [x] Grammatik
- [x] Form

### Assignee
Calvin Don-Shing Heung

### Labels
documentation

---
**#15**

## Abnahme Pflichtenheft

Abnahme und Abgabe des Pflichtenheft

### Assignee
Daniel Thorsten Maelzer

### Labels
documentation

---
**#16**

## Pflichtenheft Methodologie beschreiben

### Assignee
Martin Ernst Haug

### Labels
documentation

---
**#17**

## Notifications
### User Story
Der Benutzer bekommt eine Nachricht, wenn bestimmte Ereignisse(z.B. Pflanze benötigt dringend Wasser, Temperatur ist zu niedrig) auftauchen. 


### Kriterien zur Fertigstellung
- [ ] Ereignisse werden festgelegt
- [ ] Benachrichtigung über E-Mail oder App-Benachrichtigung

### Technologieübersicht
Web

### Geschätze Dauer
1 Woche

### Abhängigkeiten
Web, Internetzugang

### Milestone
Keine

### Assignee
Keine

### Labels
not selected, product-backlog-item

---
**#18**

## Hardware-Setup
### Beschreibung
Anschließen von Sensoren, Aktoren, Display und Kommunikationsmodulen an Arduino.
Nach dem Abschluss dieses Sprint Items ist jedem angeschlossenen Sensor erstmal fest ein Anschluss zugewiesen

Gehört zu Product Backlog Item #1 (closed).

### Abhängigkeiten
Keine

### Implementierung
Sinnvolle physische Anordnung festlegen, kurzer Funktionstest aller angeschlossener Komponenten

### Milestone
Sprint 1

### Assignee
Martin Ernst Haug

### Labels
arduino, in-lab, sprint-item


---
**#19**

## Sensor-Daten im EEPROM speichern
### Beschreibung
Die akzeptierten Sensordaten sollen im persistenten Speicher des Arduinos abgelegt werden.
Bei vollem Speicher werden die ältesten Daten gelöscht.

Gehört zu Product Backlog Item #1 (closed)Entwicklung und Interaktion.

### Abhängigkeiten
#18 (closed) #28 (closed)

### Implementierung
GPIO, https://www.arduino.cc/en/Tutorial/EEPROMWrite

### Milestone
Sprint 1

### Assignee
Calvin Don-Shing Heung

### Labels
arduino, sprint-item

---
**#20**

## Byte-Stream Kommunikation
### Beschreibung
Der Arduino und der Raspberry Pi sollen über einen zuverlässigen
Byte-Stream reine Daten austauschen können.
Ein sinnvolles Protokoll wird in einem späteren Sprint Item spezifiziert.

Gehört zu Product Backlog Item #1 (closed) und #8 (closed).

### Abhängigkeiten
- Sprint Item #18 
- Konfigurierter Raspberry Pi

### Implementierung
Arduino WiFi (https://store.arduino.cc/arduino-uno-wifi)

### Milestone
Sprint 1

### Assignee
Martin Ernst Haug

### Labels
arduino, backend, in-lab, sprint-item

---
**#21**

## Kommunikations-Protokoll
### Beschreibung
Es existiert ein Protokoll zur Kommunikation zwischen Arduino und Raspberry Pi, dass 
es ermöglicht in eine jeweilige Richtung folgende Daten zu übertragen:
- Uno -> Pi: Pings, Sensorwerte und der Pflanzenstatus
- Pi -> Uno: Backpings

Das Protokoll soll direkt auf Byte-Ebene arbeiten und möglichst optimiert sein.

### Abhängigkeiten
Sprint Item #20

### Implementierung
Auf Basis des zuverlässigen Byte-Stream aus #20 wird direkt das Protokoll entwickelt.

### Milestone
Sprint 2

### Assignee
Laurenz Elias Mädje

### Labels
arduino, backend, in-lab, sprint-item

---
**#22**

## Kompression von Sensordaten
### Beschreibung
Wenn der Speicher auf dem Arduino voll läuft, sollen die Sensordaten komprimiert werden, indem ihre zeitliche Auflösung reduziert wird

Gehört zu Product Backlog Item #5 (closed).

### Abhängigkeiten
Sprint Item #19 (closed)

### Implementierung
Noch keine Informationen

### Milestone
Sprint 3

### Assignee
Calvin Don-Shing Heung

### Labels
arduino, sprint-item

---
**#23**

## Daten einsehen via Web-Interface
### Beschreibung
Die gespeicherten Sensor Daten sollen über ein Web-Interface in Tabellen und Diagrammen aufgelistet werden können.

Gehört zu Product Backlog Item #3 (closed), #2 (closed)

### Abhängigkeiten
Sprint Item #19 (closed), #24 (closed), Back-End

### Implementierung
/

### Milestone
Sprint 1

### Assignee
Falk Boudewijn Schimweg

### Labels
sprint-item, web-frontend

---
**#24**

## Web-Interface erreichbar machen
### Beschreibung
Web-Interface auf RaspberryPi zum laufen bringen und von außen ansteuerbar machen.

Gehört zu Product Backlog Item #2 (closed)

### Abhängigkeiten
Keine

### Implementierung
Auf Tobias Antwort warten

### Milestone
Sprint 1

### Assignee
Daniel Thorsten Maelzer

### Labels
sprint-item, web-frontend

---
**#25**

## Web-Interface goes Content
### Beschreibung
Das Web-Interface kann Daten aus der Datenbank auslesen und anhand von Diagrammen und Tabellen visualisiert anzeigen.

Gehört zu Product Backlog Item #2 (closed)

### Abhängigkeiten
Sprint Item #24 (closed), Back-End

### Implementierung
API GraphQL zur Aufbereitung, PHP zum fetchen der Daten

### Milestone
Sprint 3

### Assignee
Keine

### Labels
duplicate, sprint-item, web-frontend

---
**#26**

## Web-Interface -> Filter und Visualisierung
### Beschreibung
Der Benutzer kann die Sensordaten mit vorgegebenen Filtern filtern.
Der Status der Pflanze wird jetzt durch aus dem Template verfügbare Bilder dargestellt.

Gehört zu Product Backlog Item #2 (closed) und #4 (closed)

### Abhängigkeiten
Sprint Item #24 (closed) #25 (closed)

### Implementierung
Abhängig von vorangegangener Entwicklung

### Milestone
Sprint 4

### Assignee
Web-Team

### Labels
sprint-item, web-frontend

---
**#27**

## Bilder auf Display darstellen
### Beschreibung
Der Arduino soll einzelne Bilder auf dem Display darstellen können.

Gehört zu Product Backlog Item #4 (closed) .

### Abhängigkeiten
Sprint Item #18 (closed)

### Implementierung
Je nach Art des Displays 
https://www.arduino.cc/en/Reference/LiquidCrystal oder https://www.arduino.cc/en/Reference/Wire

### Milestone
Sprint 2

### Assignee
Tobias Fritz Umland

### Labels
arduino, in-lab, sprint-item

---
**#28**

## Daten auslesen und auf Plausibilität überprüfen
### Beschreibung
Für alle Sensoren sollen ihre Werte gelesen werden und anschließend auf ihre Plausibilität überprüft werden.

_Gehört zu Product Backlog Item #1 (closed)

### Abhängigkeiten
Sprint Item #18 (closed)

### Implementierung
GPIO, Hard-gecodete Werte im Sourcecode festlegen und auffällige Werte verwerfen.

### Milestone
Sprint 1

### Assignee
Arduino Team

### Labels
arduino, in-lab, sprint-item

---
**#29**

## Gesundheitswert der Pflanze berechnen
### Beschreibung
Es soll eine Funktion implementiert werden, die basierend auf den Messwerten einen Gesundheitswert für die Pflanze berechnet.

Gehört zu Product Backlog Item #1 (closed).

### Abhängigkeiten
Sprint Item #19 (closed)

### Implementierung
- Messwerte abrufen: https://www.arduino.cc/en/Tutorial/EEPROMRead
- Funktion überlegen
- aktuellen Gesundheitswert speichern: https://www.arduino.cc/en/Tutorial/EEPROMWrite

### Milestone
Sprint 2

### Assignee
Martin Ernst Haug

### Labels
arduino, sprint-item

---
**#30**

## Regelmäßige Datenabfrage
### Beschreibung
Alle Sensoren sollen in regelmäßigen Abständen abgefragt und abgespeichert werden.

_Gehört zu Product Backlog Item #1 (closed)

### Abhängigkeiten
#18 (closed), #19 (closed), #28 (closed)

### Implementierung
/

### Milestone
Sprint 3

### Assignee
Calvin Don-Shing Heung

### Labels
arduino, duplicate, sprint-item

---
**#31**

## Raspberry einrichten
### Beschreibung
Die erforderten Tools/Programme sollen auf dem Raspberry Pi installiert werden.

### Abhängigkeiten
Sprint Item #18 (closed)

### Implementierung
Redis, NodeJS

### Milestone
Sprint 1

### Assignee
Daniel Thorsten Maelzer

### Labels
backend, in-lab, sprint-item

---
**#32**

## Gesundheits- und Sensorwerte an Rasberry Pi übertragen
### Beschreibung
Die Gesundheits- und Sensorwerte sollen an den Rasberry Pi gesendet werden.

Gehört zu Product Backlog Item #2 (closed)Statusverlauf im Web-Interface.

### Abhängigkeiten
Sprint Item #21 (closed)

### Implementierung
Übertragen der Daten mit dem Protokoll aus Sprint Item #21 (closed)

### Milestone
Sprint 3

### Assignee
Tobias Fritz Umland

### Labels
arduino, backend, in-lab, sprint-item

---
**#33**

## Löschen von Sensor-Daten
### Beschreibung
Eine Funktion die Sensor-Daten im spezifizierten Speicherort im EEPROM löscht.

Gehört zu Product Backlog Item #5 (closed)

### Abhängigkeiten
#19 (closed)

### Implementierung
https://www.arduino.cc/en/Tutorial/EEPROMClear, aber aufpassen das man 255 reinschreibt statt 0

### Milestone
Sprint 1

### Assignee
Calvin Don-Shing Heung

### Labels
arduino, sprint-item

---
**#34**

## Datenbank-Modell erstellen
### Beschreibung
Es soll ein (erweiterbares) Datenbank-Modell erstellt werden, welches zeigt wie und welche Daten gespeichert werden.

### Abhängigkeiten
Keine

### Implementierung
- Jede Pflanze soll eine eigene ID bekommen, damit keine Daten überschrieben werden.
- Die derzeitig aktiven Pflanzen (auf dem Arduino) sollen makiert werden.
- Der Status der Pflanzen soll gespeichert werden.

### Milestone
Sprint 1

### Assignee
Neha Shrestha

### Labels
backend, sprint-item

---
**#35**

## Datenbankabfrage
### Beschreibung
Der Webserver kann Anfragen an die Datenbank senden um gewünschte Datensätze zu bekommen.

Gehört zu Product Backlog Item #2 (closed) 

### Abhängigkeiten
Sprint Item #26 (closed)

### Implementierung
Redis

### Milestone
Sprint 2

### Assignee
Andrej Ni

### Labels
backend, sprint-item, web-frontend

---
**#36**

## Daten speichern
### Beschreibung
Die übermittelten Daten vom Arduino sollen in der Datenbank gespeichert werden.

Gehört zu Product Backlog Item #.

### Abhängigkeiten
Sprint Item #20 (closed)

### Implementierung
Keine

### Milestone
Sprint 1

### Assignee
Marcel Engelmann

### Labels
backend, sprint-item

---
**#37**

## Pflanzenart speichern
### Beschreibung
Die vom Benutzer erstellten Pflanzentypen sollen gespeichert werden.

Gehört zu Product Backlog Item #11 (closed)  .

### Abhängigkeiten
Keine

### Implementierung
Keine

### Milestone
Sprint 2

### Assignee
Marcel Engelmann

### Labels
backend, sprint-item, web-frontend

---
**#38**

## Datenbank backup
### Beschreibung
Der Benutzer kann die Messwerte der Datenbank als Download anfordern.

Gehört zu Product Backlog Item #3 (closed).

### Abhängigkeiten
Keine

### Implementierung
Keine

### Milestone
Sprint 3

### Assignee
Marcel Engelmann

### Labels
backend, sprint-item, web-frontend

---
**#39**

## Datenbank upload
### Beschreibung
Der Benutzer kann Messwerte aus einer Datei hochladen, um diese in der Datenbank zu speichern. (Upload einer Backup Datei)

Gehört zu Product Backlog Item #3 (closed).

### Abhängigkeiten
Keine

### Implementierung
Redis

### Milestone
Sprint 5

### Assignee
Marcel Engelmann

### Labels
backend, sprint-item, web-frontend

---
**#40**

## Aktive Pflanze wählen
### Beschreibung
Der Benutzer soll über das Web-Interface in der Lage sein die aktiven Pflanzen zu wählen, welche auf den Arduinos laufen.

Gehört zu Product Backlog Item #8 (closed) .

### Abhängigkeiten
Keine

### Implementierung
Redis

### Milestone
Sprint 3

### Assignee
Marcel Engelmann

### Labels
backend, sprint-item, web-frontend

---
**#41**

## Signal zum Wechseln von Pflanzen empfangen
### Beschreibung
Das Backend kann den Arduino jederzeit benachrichtigen, eine andere Pflanze darzustellen. Dieses Signal soll empfangen und ein Ausführungspfad zum Pflanzentausch begangen werden

Gehört zu Product Backlog Item #8 (closed).

### Abhängigkeiten
Sprint Item #20 (closed)

### Implementierung
Bis jetzt nichts spezielles

### Milestone
Sprint 3

### Assignee
Martin Ernst Haug

### Labels
arduino, backend, sprint-item

---
**#42**

## Neue Pflanzendaten herunterladen
### Beschreibung
Historische Sensordaten und Pflanzenparameter (inkl. Bilder) vom Arduino empfangen, speichern und die neue Pflanze simulieren

Gehört zu Product Backlog Item #8 (closed).

### Abhängigkeiten
Sprint Item #41 (closed)

### Implementierung
Keine   

### Milestone
Sprint 3

### Assignee
Martin Ernst Haug

### Labels
arduino, backend, duplicate, sprint-item

---
**#43**

## Regelmäßiger Ping zum Raspberry Pi
### Beschreibung
Die Verbindung zum Raspberry soll ständig durch ein Ping/Pong Signal getestet werden.

Gehört zu Product Backlog Item #5 (closed).

### Abhängigkeiten
Sprint Item #21 (closed)

### Implementierung
Keine

### Milestone
Sprint 4

### Assignee
Laurenz Elias Mädje

### Labels
arduino, backend, in-lab, sprint-item

---
**#44**

## Zum Zustand gehöriges Bild anzeigen
### Beschreibung
Basierend auf den Gesundheitswerten der Pflanze muss das passende Bild auf dem Bildschirm angezeigt werden

Gehört zu Product Backlog Item #4 (closed).

### Abhängigkeiten
Sprint Item #27 (closed), #29 (closed)

### Milestone
Sprint 2

### Assignee
Tobias Fritz Umland

### Labels
arduino, in-lab, sprint-item

---
**#45**

## Bilder zu jedem Status erstellen
### Beschreibung
Die Konzepte für jeden Status fertigstellen und an das gegebene Bildschirm anpassen.

### Abhängigkeiten
Front-End

### Implementierung
Photoshop

### Milestone
Sprint 1

### Assignee
Ruhan Muhammet Ali Aka

### Labels
sprint-item, web-frontend

---
**#46**

## Beispiel Daten ausfüllen
### Beschreibung
Bespiel Daten erstellen

### Abhängigkeiten
Keine

### Milestone
Sprint 2

### Assignee
Matin Ernst Haug

### Labels
backend, sprint-item

---
**#47**

## Test Frameworks für die Sprint-Items erstellen
### Beschreibung
Die einzelnen, vorläufig fertigen, Sprint-Items testen.

### Abhängigkeiten
Keine

### Milestone
Sprint 3

### Assignee
Ruhan Muhammet Ali Aka

### Labels
arduino, backend, sprint-item, web-frontend

---
**#48**

## Konfigurations-Protokoll
### Beschreibung
Das bestehende Protokoll wird erweitert, sodass vom Pi zum Arduino eine Nachricht
mit MessageType `PLANT` geschickt werden, die folgende Daten enthält:
- Eigenschaften der Pflanzen
- Status der Pflanze
- Bilder der Pflanzen (wenn möglich)

_Gehört zu Product Backlog Item #8._

### Abhängigkeiten
Sprint Item #21.

### Implementierung
Byte-Stream auf Basis von SoftwareSerial.

### Milestone
Sprint 4

### Assignee
Laurenz Elias Mädje

### Labels
arduino, in-lab, sprint-item

---
**#49**

## Transparenz/Warnings
### Beschreibung
Der Callee bekommt nichts von der Kompression mit (Transparenz) und Warnings fixen.

_Gehört zu Product Backlog Item #5 (closed)

### Abhängigkeiten
Keine

### Implementierung
Calvins Programmierskillz

### Milestone
Sprint 4

### Assignee
Calvin Don-Shing Heung

### Labels
arduino, sprint-item, suggestion

---
**#50**

## Datenbankmodell Visualisierung
### Beschreibung
Zum erstellten Datenbankmodell soll eine Visualisierung angefertigt werden.

### Abhängigkeiten
Sprint Item #34 (closed)

### Implementierung
Zeichnung

### Milestone
Sprint 4

### Assignee
Neha Shrestha

### Labels
backend, sprint-item

---
**#51**

## Filterung von Daten
### Beschreibung
Der Nutzer kann Daten der Pflanze durch voreingestellte Filter filtern.

_Gehört zu Product Backlog Item #2 (closed)

### Abhängigkeiten
Keine

### Implementierung
Angular.JS, Redis

### Milestone
Sprint 4

### Assignee
Falk Boudewijn Schimweg

### Labels
sprint-item, web-frontend

---
**#52**

## Senden der Pflanze
### Beschreibung
Der Pi stellt eine Funktion bereit, die ermöglicht, eine Typ 3 Nachricht an den Arduino zu senden. Die Datenbank wird entsprechend angepasst. Übertragen wird:
- Eigenschaften der Pflanzen
- Status der Pflanze
- Bilder der Pflanzen (wenn möglich)

_Gehört zu Product Backlog Item #8._

### Abhängigkeiten
Sprint Item #48

### Implementierung
Analog zu dem Empfangen der Daten muss ein Buffer an den Arduino mit der entsprechenden ID versenden. z.B. nach einem Ping

### Milestone
Sprint 4

### Assignee
Martin Ernst Haug

### Labels
backend, in-lab, sprint-item

---
**#53**

## Zeit zu Sensoren hinzufügen
### Beschreibung
Zeit zu Sensorlib hinzufügen

### Abhängigkeiten
Keine

### Implementierung
Zeitsensor : RTC V1.2

### Milestone
Sprint 5

### Assignee
Calvin Don-Shing Heung

### Labels
arduino, sprint-item

---
**#54**

## Speicheroptimierung
### Beschreibung
Die Ausnutzung des RAMs auf dem Arduino wird optimiert.

### Abhängigkeiten
Keine

### Implementierung
Mehr Pass-By-Reference. Refactorings wo nötig.

### Milestone
Sprint 5

### Assignee
Laurenz Elias Mädje

### Labels
arduino, in-lab, sprint-item

---
**#55**

## Nodes API
### Beschreibung
automatisches erkennen von neuen Nodes und entsprechende pflanze speichern

### Abhängigkeiten
Keine

### Implementierung
In SaveToDatabase.js

### Milestone
Sprint 5

### Assignee
Andrej Ni

### Labels
backend, sprint-item

---
**#56**

## Arduinotests
### Beschreibung
Tests für Arduino

### Abhängigkeiten
ArduinoLibs

### Implementierung
Arduino UNIT TEST

### Milestone
Sprint 6

### Assignee
Calvin Don-Shing Heung

### Labels
arduino, sprint-item

---
**#57**

## Status-Display
### Beschreibung
Das Display zeigt an, ob der Arduino mit dem Raspberry verbunden ist.

Gehört zu Product Backlog Item #4 (closed).

### Abhängigkeiten
Keine

### Implementierung
Mit der Display-Library

### Milestone
Sprint 5

### Assignee
Laurenz Elias Mädje

### Labels
arduino, in-lab, sprint-item

---
**#58**

## Backend tests für das API
### Beschreibung
Backend Tests für API schreiben

### Abhängigkeiten
Keine

### Implementierung
TestframeWork

### Milestone
Sprint 6

### Assignee
Ruhan Muhammet Ali Aka

### Labels
backend, sprint-item

---
**#59**

## Backup API spezifizieren
### Beschreibung
API zum runter und hochladen von Backup-Dateien festlegen.

### Abhängigkeiten
Backend

### Implementierung
Angular

### Milestone
Sprint 5

### Assignee
Falk Boudewijn Schimweg

### Labels
backend, sprint-item, web-frontend

---
**#60**

## Backup Interface
### Beschreibung
Entwicklung eines Interface für das hoch und runterladen von Backups

### Abhängigkeiten
Sprint Item #59 (closed) und Backend

### Implementierung
Angular

### Milestone
Sprint 5

### Assignee
Falk Boudewijn Schimweg

### Labels
backend, sprint-item, web-frontend

---
**#61**

## Node-Management
### Beschreibung
Deployment von Pflanzen auf Knoten

### Abhängigkeiten
Keine

### Implementierung
Angular

### Milestone
Sprint 5

### Assignee
Daniel Thorsten Maelzer

### Labels
backend, sprint-item, web-frontend

---
**#62**

## Delete Plant Template
### Beschreibung
Der Benutzer hat die Möglichkeit Pflanzen-Templates zu löschen

### Abhängigkeiten
Keine

### Implementierung
Angular

### Milestone
Sprint 6

### Assignee
Daniel Thorsten Maelzer

### Labels
backend, sprint-item, web-frontend

---
**#63**

## Dokumentationsguide
### Beschreibung
Bereitstellung eines Dokumentes als Leitfaden für die Dokumentation des Projektes in den 3 Teams (Web,Arduino,Backend)

### Abhängigkeiten
Keine

### Implementierung
Markdown

### Milestone
Sprint 5

### Assignee
Daniel Thorsten Maelzer

### Labels
sprint-item

---
**#64**

## Datenbank-Modell erweitern
### Beschreibung
Erstelltes Datenbank-Modell erweitern

### Abhängigkeiten
Keine

### Implementierung
Zeichnung

### Milestone
Sprint 5

### Assignee
Neha Shrestha

### Labels
documentation, sprint-item

---
**#65**

## EEPROM Schreibzyklen verringern
### Beschreibung
Weniger Schreibzyklen auf den EEPROM verwenden, um diesen zu schonen.

### Abhängigkeiten
Sprint Item #22 (closed)

### Implementierung
Besseres Design.

### Milestone
Sprint 6

### Assignee
Laurenz Elias Mädje

### Labels
arduino, sprint-item

---
**#66**

## Arduino Edge Case Tests
### Beschreibung
Edge Cases Testen

### Abhängigkeiten
Keine

### Implementierung
Arduino Unit Test

### Milestone
Sprint 6

### Assignee
Tobias Fritz Umland

### Labels
arduino, sprint-item

---
**#67**

## Adapt PlantTemplate class to new API
### Beschreibung
Adapt PlantTemplate class in typescript to new the API (grouped boost params).

### Abhängigkeiten
Keine

### Implementierung
Wiki

### Milestone
Sprint 6

### Assignee
Falk Boudewijn Schimweg

### Labels
bug, sprint-item, web-frontend

---
**#68**

## Senden der Pflanze vom Backend an den Arduino + API Endpunkt
### Beschreibung
Serialisieren der Pflanze im vom Protokoll spezifizierten Format und dann über den Socket zum zugehörigen Arduino schicken.

Gehört zu Product Backlog Item #8 (closed).

### Abhängigkeiten
Sprint Item #52 (closed)

### Implementierung
Der NodeJS Buffer. Es gibt eine loadPlant-Funktion, die von einer Route aufgerufen wird und dann den Sendeauftrag in eine Warteschlange stellt. Nach dem nächsten Ping des zugehörigen Arduino soll sowohl Spec als auch State verschickt werden

### Milestone
Sprint 6

### Assignee
Martin Ernst Haug

### Labels
arduino, backend, sprint-item

---
**#69**

## Trusted Handling
### Beschreibung
Funktion, die überprüft wenn ein Wert trusted = false ist, den letzten bekannten Wert übernimmt.

### Abhängigkeiten
Keine

### Implementierung
globales snapshot

### Milestone
Sprint 6

### Assignee
Calvin Don-Shing Heung

### Labels
arduino, sprint-item

---
**#70**

## Musikeinfluss auf Planze
### Beschreibung
Wenn akustische Einflüsse auf die Pflanze existieren, wächst sie schneller.

Gehört zu Product Backlog Item #12.

### Abhängigkeiten
Keine

### Implementierung
Lautstärke-Sensor

### Milestone
Sprint 6

### Assignee
Laurenz Elias Mädje

### Labels
arduino, in-lab, sprint-item

---
**#71**

## Remove JSON check in import function
### Beschreibung
The backup files for plants are not JSONs, but the web interface requires JSON files to be uploaded.

### Abhängigkeiten
Keine

### Implementierung
Bug

### Milestone
Sprint 6

### Assignee
Falk Boudewijn Schimweg

### Labels
bug, sprint-item, web-frontend

---
**#72**

## CSS
### Beschreibung
Das Frontend mittels Verschönerungstechniken a la CSS verschönern

### Abhängigkeiten
Keine

### Implementierung
ZE ÖS ÖS

### Milestone
Sprint 6

### Assignee
Daniel Thorsten Maelzer

### Labels
sprint-item, web-frontend

---
**#73**

## Send deployed information
### Beschreibung
Send the information of the node which a plant is deployed on in the /api/plants and /api/plants/:id calls.
See API docu in the wiki for details.

### Abhängigkeiten
Keine

### Milestone
Sprint 6

### Assignee
Andrej Ni

### Labels
backend, bug, sprint-item

---
**#74**

## Send plant status
### Beschreibung
Send the plant status (=picture to display) in the /api/plants and /api/plants/:id calls.

### Abhängigkeiten
Keine

### Milestone
Sprint 6

### Assignee
Andrej Ni

### Labels
backend, sprint-item

---
**#2**

## Unix timestamp
### Beschreibung
Send unix integer timestamps in the /api/plants/:id call.

### Abhängigkeiten
Keine

### Milestone
Sprint 7

### Assignee
Martin Ernst Haug

### Labels
backend

---
**#76**

## 404 Error code if plant not found
### Beschreibung
Return 404 error code instead of 500 if plant was not found

### Abhängigkeiten
Keine

### Milestone
Sprint 7

### Assignee
Falk Boudewijn Schimweg

### Labels
backend

---
**#77**

## Defaultsite und Buttonfarbe
### Beschreibung
Defaultseite erstellen wenn keine Pflanzen existieren mit Hinweis darauf, wie man vorgehen muss.
Button-Farbe für Create/Cancel ändern.

### Abhängigkeiten
Keine

### Implementierung
Angular JS

### Milestone
Sprint 7

### Assignee
Daniel Thorsten Maelzer

### Labels
web-frontend

---
**#2**

## Display deployment information
### Beschreibung
Display the deployment information for plants in overview and detail view and highlight deployed plants in overview.

Depends on #73 (closed)

### Abhängigkeiten
Keine

### Implementierung
Angular JS

### Milestone
Sprint 7

### Assignee
Falk Boudewijn Schimweg

### Labels
web-frontend

---
**#79**

## Send node connectivity information
### Beschreibung
Send connected information in the /api/nodes response (as now described in the wiki).

### Abhängigkeiten
Keine

### Milestone
Sprint 7

### Assignee
Falk Boudewijn Schimweg

### Labels
backend, sprint-item

---
**#80**

## Template-Wertebereiche korrigieren
### Beschreibung
Die Wertebereiche für Light und Humidity müssen angepasst werden und resistancy in suspectibility umbenannt werden. Außerdem brauchen die suspectibility Werte mehr Nachkommawerte.

### Abhängigkeiten
Keine

### Milestone
Sprint 7

### Assignee
Falk Boudewijn Schimweg

### Labels
bug, web-frontend

---
**#81**

## Multiple plants are marked as deployed to node 1
### Beschreibung
In the plant overview are multiple plants marked as deployed to node 1

### Abhängigkeiten
Keine

### Milestone
Sprint 7

### Assignee
Falk Boudewijn Schimweg

### Labels
backend, bug

---
**#2**

## Delete-Bug
### Beschreibung
Beim Delete-Aufruf bekommt der Client keine Antwort.

### Abhängigkeiten
Keine

### Milestone
Sprint 8

### Assignee
Martin Ernst Haug

### Labels
backend

---