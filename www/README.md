# Plantx

# Dokumentation

## Web-Dokumentation

### Features / Benutzerdokumentation

Die gelisteten Komponenten stellen die Schnittstelle zwischen dem BackEnd und dem FrontEnd dar. Im folgenden sind alle Komponenten und ihre Funktionalitäten erklärt. 

#### Plant-List
Die Komponente "Plant-List" zeigt alle Pflanzen an, die jemals mit dem Arduino verbunden waren. Inaktive Pflanzen werden ausgegraut dargestellt. In der Übersicht (http://raspimittwoch.sese.tu-berlin.de/plants) werden die zuletzt empfangenen Werte jeder Pflanze unter dem jeweiligen Pflanzennamen dargestellt. Durch ein Klick auf das PlantX Logo gelangt man immer zurück zur Pflanzenübersicht. Falls noch keine Pflanzen auf dem Arduino angelegt wurden, gelangt man in der oberen rechten Ecke über den Button "New" zur Plant-Creator Komponente, die Pflanzen erstellen kann. Möchte man bereits exportierte Data-Sets importieren, kann man dies neben dem Button "New" auf "import" machen und eine Datei hochladen. Durch einen Klick auf die jeweilige Pflanze gelangt man zur Plant-Detail Komponente.
#### Plant-Detail
Die "Plant-Detail" Komponente zeigt alle Informationen in Bezug auf eine ausgewählte Pflanze an. Im oberen Bereich stehen die zuletzt empfangenen Sensordaten. Sollte eine aktive Verbindung zu einer Pflanze bestehen, werden die Live-Daten in einem Graphen visuell dargestellt. Man kann die empfangenen Sensordaten nach Kategorie ausblenden, indem man die entsprechende Kategorie (size, health, humidity, ...) anklickt. Mithilfe der Filterungsoption am unteren Ende der Seite kann man die empfangenen Sensordaten filtern. Jede Pflanze kann gelöscht, exportiert und einem Arduino/Node zugewiesen werden. Wenn kein Back-End verbunden ist erscheint unter dem Filter eine Meldung "Waiting for backend..."
#### Plant-Import
Die Komponente "Plant-Import" kann exportierte Pflanzen wieder importieren. Die option Möglichkeit gibt einem die Möglichkeit eine andere Pflanze zu überschreiben.
#### Plant-Creator
Die Komponente "Plant-Creator" kann mithilfe von Templates Pflanzen erstellen. Für die Pflanzenerstellung ist ein Template nötig, das man über den New-Button im geöffneten Fenster erstellen kann. Nun kann man die Umwelteinflüsse der simulierten Pflanze spezifizieren. Die Wertebereiche der einzelnen Options sind im [struct PlantType](#struct-PlantType{) spezifiziert. Nach der Erstellung des Templates kann man dieses im Dropdown Menü auswählen, der Pflanzen einen Namen geben und die Pflanze erstellen. Wenn es keinen Fehler gab wird die Pflanze jetzt in der Übersicht gelistet.

#### struct PlantType{

    string name;
    
    float maxSize;  
    float growSpeed;        ]0;1[    
    float regenationSpeed;  ]0;+Inf[ 

    Range<float> temperaturRange;   [-40;80]
    float temperatureOptimum;       [-40;80]
    float temperatureBoost;         ]0;+Inf[
    float temperaturePrecision;     ]0;+Inf[
    float temperatureResistancy;    ]0;100[
    
    int moistureThreshold;          [0;950]
    int moistureStruggleSeconds;    [0;+Inf[
    float moistureLackResistancy;   ]0;100[
    bool waterCanGetAboveGround;

    Range<float> humidityRange;     ]0.05;0.99[
    float humidityOptimum;          ]0.05;0.99[
    float humidityBoost;            ]0;+Inf[
    float humidityPrecision;        ]0;+Inf[
    float humidityResistancy;       ]0;100[

    int darkMaxSeconds;         ]0;+Inf[
    int lightMaxSeconds;        [0;+Inf[
    int darkLightThreshold;     [0;40000]
    float darkResistancy;       ]0;100[   
    float lightResistancy;      ]0;100[
    float lightOpimum;          ]0.05;0.99[
    float lightBoost;           [0;+Inf[
    float lightPrecision;       ]0;100[

}

### Installationsanleitung

Um das Web Front-End auf dem RaspberryPi zu deployen, muss man folgende Schritte befolgen:
1. Das "www" Verzeichnis auf dem RaspberryPi abspeichern.
2. Den Outputpath der angular.json (www/) ändern.
3. npm install im "www" Ordner
4. npm build im "www" Ordner


The web-interface is based on the JavaScript framework angular. It consists of threee components, the app component, the plant-list component and the plant-detail component.
* app - The main compoent which holds the website header.
* plant-list - Loaded by default in the app component and hold a pre-view list of plants.
* plant-detail - Opened by clicking on a plant in the pre-view and displays the meassurement values over time.

The web-interface also uses the route app for asynchronously loading the plant-list/-detail views.

The data connection to the server is provided by the data service, which requests via HTTP/GET the values from the back-end.

## Development server

Run `ng serve` for a dev server. Navigate to `http://localhost:4200/`. The app will automatically reload if you change any of the source files.

## Code scaffolding

Run `ng generate component component-name` to generate a new component. You can also use `ng generate directive|pipe|service|class|guard|interface|enum|module`.

## Build

Run `ng build` to build the project. The build artifacts will be stored in the `dist/` directory. Use the `--prod` flag for a production build.

## Running unit tests

Run `ng test` to execute the unit tests via [Karma](https://karma-runner.github.io).

## Running end-to-end tests

Run `ng e2e` to execute the end-to-end tests via [Protractor](http://www.protractortest.org/).

## Further help

To get more help on the Angular CLI use `ng help` or go check out the [Angular CLI README](https://github.com/angular/angular-cli/blob/master/README.md).
