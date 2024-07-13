# ArduinoTeplomer
Jednoduchý teploměr s dvěma senzory a I2C 16x2 displejem.
## Potřebný hardware pro složení:
 - Arduino Nano (nebo jiný mikrokontrolér)
 - Teploměr a vlhkoměr a DHT11
 - Teploměr DS18S20
 - Displej 16x2 pro sběrnici I2C
 - 2x tlačítko
 - 2x 10k ohm odpory
 - 1x 4k7 ohm odbor

Moje (prasácké) zpojení na breadboardu:
![20240713_232546](https://github.com/user-attachments/assets/3f4c0ff5-665e-4379-ab03-c0d0914073d1)

## Co plánuji s tímto dál?
- Přidat modul hodin reálného času a sedmisegmentovku které bude hodiny zobrazovat
- Vyřešit problémy s I2C displejem, a senzory s ESP8266 a přechod na ESP8266
- Posílání dat přes MQTT případně webové ovládání
