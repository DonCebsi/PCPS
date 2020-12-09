# PlantX Pflichtenheft

![PlantX Logo](../art/PlantX.svg)

## Methodologie
Wir verwenden eine von uns angepasste agile Entwicklung mit Scrum. Alle Mitglieder der Gruppe sind die Product Owner und tragen mögliche Product Backlog Items bei, die dann durch eine Abstimmung auf die untenstehenden mandatory goals, die wir auf jeden Fall erreichen wollen und ein stretch goal, dass wir bei genügend Zeit bearbeiten, eingeengt haben.

Der Gruppenleiter, Martin Haug, fungiert gleichzeitig auch als Scrum Master, die von der ganzen Gruppe in Sprint Items zerlegten Backlog Items werden in jeweils eine Woche langen Sprintzyklen von vorher zugewiesenen Teammitgliedern erledigt.

Wir versuchen die Qualität der Software mit Unittests und manuellen Testläufen abzusichern. Dabei ist unser Ziel vollständige Zweigabdeckung. Unter 90% Zweigabdeckung kann kein Merge in Master stattfinden (dazu später mehr). Der Testbeauftragte, der sich für die Erreichung dieser Ziele einsetzt, ist Ruhan Aka.

Um unsere Arbeit im Repository zu koordinieren, benutzen wir das Git flow Modell. Dabei gibt es neben dem Master auch noch einen develop-Zweig und einen separaten Zweig für jedes größere, sich in Entwicklung befindliche Features. Alle Commits auf dem Masterzweig haben "Release-Qualität", eignen sich also für eine Milestone-Präsentation. Um in den Master zu mergen, wird ein neuer Release-Zweig mit dem aktuellen Stand von develop geöffnet, der dann die restlichen Bugfixes und Tests bis zum Merge mit Master aufnimmt. Alle Master-Commits werden auf die anderen Zweige zurückgemergt.

Mindestens alle öffentlichen Funktionen sollen mit dokumentierenden, automatisch auslesbaren Kommentaren versehen werden. Außerdem wird eine Setup-Anleitung bereitgestellt. Der Koordinator für die Dokumentation ist Daniel Maelzer.

## Zielsetzung

### Mandatory Goals

#### 1. Entwicklung und Interaktion
**User Story:** 
Der Benutzer kann durch Ein- und Ausgaben mit einem sich entwickelnden, reaktiven Organismus interagieren. Dieses System versetzt in die Lage, die Performance von interplanetaren portablen Gewächshäusern zu bewerten.

**Kriterien zur Fertigstellung:**
- Dem Nutzer werden Möglichkeiten (die in anderen Items spezifiziert werden) gegeben, den Organismus zu versorgen.
- Bei angemessener Pflege entwickelt sich der Organismus über die Zeit.
- Diese Entwicklung hängt von mehreren Komponenten ab:
Umgebungseinflüsse, wie Temperatur, Licht und Luftfeuchtigkeit
Alter des Organismus und vorherige Entwicklung

**Technologieübersicht:**
- Seed Studio (Hardware/Sensorik)
- Arduino IDE
- Backendtechnologie (Web und Datenbank)

#### 2. Statusverlauf im Web-Interface
**User Story:**
Der Benutzer ist in der Lage, sich den aktuellen sowie den vergangenen Status der Pflanze anhand aufbereiteter Daten anzeigen zu lassen.

**Kriterien zur Fertigstellung:**
- Der Nutzer kann den aktuellen Status der Pflanze begutachten
- Der Nutzer kann den vergangenen Status der Pflanze begutachten
- Der Nutzer kann diese Ergebnisse filtern
- Der Nutzer kann sich die visuelle Entwicklung seiner Pflanze anschauen

**Technologieübersicht:**
- HTML
- CSS
- JAVASCRIPT
- RASPBIAN
- PHP

#### 3. Visualisierung
**User Story:**
Der Benutzer sollte die Entwicklung des Organismus visuell nachvollziehen können, um die Auswirkungen der Umgebung und die Entwicklung des Organismus nachvollziehen und entsprechend reagieren zu können.

**Kriterien zur Fertigstellung:**
- Auf einem Display wird der Zustand des Organismus visualisiert.
- Diese Visualisierung soll intuitiv verständlich sein.
- Die Darstellung reagiert plausibel und zuverlässig auf Veränderungen des Zustands des Organismus

**Technologieübersicht:**
- Seed Studio (Hardware/Sensorik)
- Arduino IDE
- Illustrationsprogramme für Displaygrafik

#### 4. Ausfallsicherheit
**User Story:**
Der Benutzer bekommt zu jedem Zeitpunkt vom System - also auch bei partiellen Ausfällen oder voller werdenden Speicher - die bestmögliche Sicherheit der gesammelten Daten, damit er sich darauf verlassen kann.

**Kriterien zur Fertigstellung:**
- Bei Verbindungsabbruch zum Raspberry Pi speichert der Arduino alle Sensor-Werte lokal
- Diese Daten werden bei knappen Speicherplatz (eventuell verlustbehaftet) komprimiert, so dass die ältesten Daten nicht vollständig verloren gehen.
- Die Speicherung der Daten überlebt einen Netzreset und Neustart
- Die lokale Simulation wird während Sensor- oder Konnektivitätseinschränkungen fortgesetzt
- Dabei werden Sensorausfälle durch Werte außerhalb des plausibelen Bereichs und historische Analyse erkannt.
- Wenn eine Pflanze die Verbindung zum Raspberry Pi verliert, kann sie über eine noch bestehende Verbindung einer anderen Pflanze weiterhin die Daten senden.

**Technologieübersicht:**
- Arduino

#### 5. Handhabung mehrerer Pflanzen
**User Story:**
Der User kann über das Web-Interface Pflanzen mit unterschiedlichen Bedürfnissen vom Arduino auf den Raspberry Pi auslagen und umgekehrt gespeicherte Pflanzen vom Raspberry Pi auf den Arduino senden.

**Kriterien zur Fertigstellung:**
- Verhalten der Pflanze auf dem Raspberry Pi spezifizieren. (Schläft, wächst weiter ect.)
- Funktion in Übertragungsprotokoll vom Raspberry Pi und Arduino implementieren.
- User-Interface anpassen.

**Technologieübersicht:**
- Arduino
- Datenbank (Redis oder MySQL)
- TCP/IP
- JAVASCRIPT

#### 6. Template zur Erstellung eines Organismus
**User Story:**
Der Benutzer ist in der Lage ein neues Organismus mit spezifizierten Bedürfnissen zu erstellen.

**Kriterien zur Fertigstellung:**
- alle Bedürfnisse sollten festgelegt werden
- Template für ein Organismus
- Stufen-abhängige Entwicklungsphasen mit entsprechendes Bild
- Namensgebung
- Grundbedarf
- eventuelle Erstellung durch ein geeignetes User-Interface

**Technologieübersicht:**
- Web-Interface
- Raspberry
- Arduino

### Strech-Goals

#### 1. Export und Verwaltung
**User Story:**
Der Benutzer ist in der Lage mittels Web-Interface Daten eines Geräte (Pflanze) zu exportieren/speichern und auf ein neues Gerät aufzuspielen.

**Kriterien zur Fertigstellung:**
- Der Nutzer kann Daten exportieren
- Der Nutzer kann Geräte hinzufügen und löschen
- Der Nutzer kann exportierte Daten auf Geräte importieren

**Technologieübersicht:**
- Backend API

#### 2. Musik
**User Story:**
Wenn der Benutzer den Organismus mit Musik beschallt, reagiert sie mit einer verbesserten Entwicklung.

**Kriterien zur Fertigstellung:**
Der Organismus reagiert auf akustische Einflüsse mit stärkerem Wachstum.

**Technologieübersicht:**
- Mikrofon
- Seeed Studio Arduino IDE


## Produkteinsatz
### Anwendungsbereiche
PlantX ist ein System zur Simulation digitaler Pflanzen.
Es ermöglicht die effiziente Evaluierung der Performance von (interplanetaren) Gewächshäusern.

Anwender können über unseren Webinterface jederzeit das Wohlergehen ihrer digitalen Pflanzen überprüfen.
Außerdem ermöglicht der Service die Visualisierung der Historie der Pflanze und
den Zugriff auf die gesammelten Daten.
Durch selbst erstellbare Templates können schnell und einfach neue Pflanzenarten hinzufügen.

Auch mit unzuverlässigen Verbindungen der Komponenten kommt unser System zurecht.
Dabei werden die gespeicherten Daten, wenn der vorhandene Speicherplatz knapp wird,
durch geschickte Datenkompression erhalten bleiben. 
Die einzelnen Organismen können durch WiFi-Module drahtlos Daten verschicken und
bilden damit ein Netzwerk, dass Daten (womöglich über mehrere Knoten) zur
Basisstation transportiert.

## Rollenverteilung
Wir haben drei Kleingruppen für die Gebiete Arduino (Calvin Heung, Tobias bUmland, Laurenz Mädje und Martin Haug), Backend mit Datenbank (Andrej Ni, Anata Lamichhane, Neha Shrestha, Marcel Engelmann) und Web Frontend (Daniel Maelzer, Falk Schimweg, Ruhan Aka) gebildet, die jeweils die ihnen zugeordneten Sprint Items bearbeiten.