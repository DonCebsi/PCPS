#### Hardware-Setup
Um unseren Projekt zu benutzen benötigt man folgende Hardware:
- [Arduino UNO](https://www.seeedstudio.com/Arduino-Uno-Rev3-p-2995.html)
- [Grove - Base Shield V2](https://www.seeedstudio.com/Base-Shield-V2-p-1378.html)
- [Grove - Temperature&Humidity Sensor Pro](https://www.seeedstudio.com/Grove-Temperature%26Humidity-Sensor-Pro%EF%BC%88AM2302%EF%BC%89-p-838.html)
- [Grove - Digital Light Sensor](https://www.seeedstudio.com/Grove-Digital-Light-Sensor-p-1281.html)
- [Grove - Moisture Sensor](https://www.seeedstudio.com/Grove-Moisture-Sensor-p-955.html)
- [Grove - RTC](https://www.seeedstudio.com/Grove-RTC-p-758.html)
- [Grove - Rotary Angle Sensor](https://www.seeedstudio.com/Grove-Rotary-Angle-Sensor-p-770.html)
- [I2C LCD](https://www.seeedstudio.com/I2C_LCD-\(With-universal-Grove-cable\)-p-2601.html)
- [XBEE - Wifi module](https://www.seeedstudio.com/XBee-Wi-Fi-Module-2400MHz-72000Kbps-20-Pin-XB2B-WFPT-001-p-1965.html)
- [XBEE - Socket](https://www.seeedstudio.com/Grove-Bee-Socket-p-1449.html)
- [Grove - Water Sensor](https://www.seeedstudio.com/Grove-Water-Sensor-p-748.html)
- [Batterie](https://www.google.de/search?q=cr1225+3V&spell=1&sa=X&ved=0ahUKEwigjaHegIDcAhVSYVAKHWDeC3gQBQglKAA&biw=1536&bih=743&dpr=1.25)

Anschließend muss man die Sensoren an folgende Positionen des Base Shield anstecken. Benutzen Sie hierbei die Grove Kabeln:
- Temperature & Humidity Sensor an der Position A1
- Moisture Sensor an A3
- Rotary Angle Sensor an A0
- Wasser Sensor an DD3
- I2C LCD an I2C
- alle anderen Sensoren können beliebig gewählt werden

#### Software-Setup:
Unsere Bibliotheken sind von diesen externen Bibliotheken abhängig:
- [I2C_LCD.h](https://github.com/SparkingStudio/I2C_LCD/blob/master/resources/I2C_LCD_Library.zip)
- [DHT.h](https://github.com/adafruit/DHT-sensor-library)
- [Digital_Light_TSL2561.h](https://github.com/Seeed-Studio/Grove_Digital_Light_Sensor)
- [RTClib.h](https://github.com/adafruit/RTClib)


Damit also unsere eigenen Bibliotheken funktionieren, müssen diese extern zusätzlich installiert werden.
Falls Sie nicht wissen wie man das macht, können Sie [hier](http://wiki.seeedstudio.com/How_to_install_Arduino_Library/) oder [hier](https://www.arduino.cc/en/Guide/Libraries) genauer nachschauen.

Anschliessend müssen Sie unsere internen Bibliotheken auf dem Arduino IDE installieren.
Diese befinden sich im Ordner "[lib](https://gitlab.tubit.tu-berlin.de/mhaug/pcps/tree/develop/arduino/lib)".  
Passen Sie darauf auf, dass die Bibliotheken, die Sie installieren, auch genauso heißen wie unsere benannten Dateien heißen.  
Nach der Installation von den externen und unseren Bibliotheken müssen Sie unsere main-Datei, welche sich im "[src](https://gitlab.tubit.tu-berlin.de/mhaug/pcps/tree/develop/arduino/src)" Ordner befindet, auf den Arduino hochladen, 
dafür gibt es wiederum ein [Guide](http://wiki.seeedstudio.com/Upload_Code/).

#### Benutzeranleitung
Nachdem Sie erfolgreich die Hardwareanleitung, sowie die Softwareanleitung, abgeschlossen haben, können Sie nun
den Bodenfeuchtigkeitssensor in die Erde direkt neben ihrer Pflanze reinstecken, um somit akkurate Messwerte zu erreichen.
Mithilfe des "Rotary Angle Sensor" können Sie das komplette EEPROM löschen.
Achten Sie darauf, das sowohl der Lichtsensor als auch die Temperatur-und Luftfeuchtigkeitsensor nicht von der Pflanze verdeckt sind.
