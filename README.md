# Wetterstation
Von Oliver Thann und Stefan Ziehensack

## Einführung
Diese Aufgabe erzielt es eine einfache Wetterstation und webserver zu machen.

## Projektbeschreibung
Das ziel dieser Aufgabe war es, eine Wetterstation zu erstellen mithilfe von unserem ESP32 und dem DHT11 sensor. Weiterseits sollen die Daten auf einem von dem Webserver aus gehosteten Webservers in einem graphen mit Zeitstempel angezeigt werden.
Außerdem haben wir mithilfe der eingebauten RGB LED eine Status LED gemacht haben.

## Theorie
Die Funktion der Wetterstation haben wir mithilfe der Adafruit DHT library bekommen.
Den Webserver haben wir mithilfe von der ESP32 Async Webserver library umgesetzt.
Den Chart am Webserver haben wir mit chart.js gemacht.
Die StatusLED haben wir mithilfe der Neopixel library gemacht.

## Arbeitsschritt
Angefangen haben wir mit der Wetterstation indem wir erstmal die Sensordaten auf dem Serial monitor angezeigt haben um zu sehen wie das funktioniert.
Danach haben wir probiert den webserver hinzuzufügen was etwas länger gebraucht hat nachdem es ein paar probleme mit dem Internet gab
Als nächstes haben wir den chart hinzugefügt was am längest gedauert hat nachdem char.js, das Internet und die Kombination aus Javascript und c++ manchmal unverhersehbare fehler geliefert hat.

## Code
Code ist im code Folder

## Schaltung
![alt text](Schaltung.png)
## Zusammenfassung
Das projekt hat uns gezeigt wie man am ESP mit webservern, temperatur sensoren arbeitet und wie man die LED einzeln ansteuert.

## Quellen
https://github.com/ESP32Async/ESPAsyncWebServer
https://arduinogetstarted.com/tutorials/arduino-dht11
https://www.w3schools.com/js/js_graphics_chartjs.asp
