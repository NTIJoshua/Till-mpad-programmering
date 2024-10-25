# Klock-, Temperaturstyrd Servo och Alarmprojekt

Detta Arduino-projekt använder en DS3231 för att visa tid, mäta temperatur och styra en servo beroende på temperaturen. Projektet inkluderar även en alarmfunktion som kan ställas in med knappar och aktiveras vid angiven tid, då en LED-lampa blinkar för att indikera alarmet.

## Funktioner

- **Tidvisning**: Använder DS3231 för att visa aktuell tid på en OLED-skärm.
- **Temperaturmätning**: Mäter temperaturen med DS3231:s inbyggda sensor och visar den på skärmen.
- **Temperaturstyrd Servo**: Servon rör sig beroende på aktuell temperatur och mappas till ett vinkelområde mellan 0-180 grader.
- **Alarmfunktion**: Alarmet kan ställas med knappar:
  - Lägg till en timme till alarmet.
  - Lägg till en minut till alarmet.
  - Starta/stopp av alarm.
- **LED-indikation**: När alarmet aktiveras blinkar en LED-lampa i 5 sekunder.

## Komponenter

- DS3231 RTC-modul (för tid och temperatur)
- SSD1306 OLED-skärm
- 9g-servo
- Tre knappar (för att ställa in och stoppa alarm)
- LED (ansluten till digital pin 5)
- Arduino-kort

## Pin-konfiguration

- **servoPin**: Digital pin 9 (servo)
- **buttonStop**: Digital pin 2 (start/stopp för alarm)
- **buttonSetHour**: Digital pin 3 (lägg till en timme till alarm)
- **buttonSetMinute**: Digital pin 4 (lägg till en minut till alarm)
- **ledPin**: Digital pin 5 (LED-indikation för alarm)

## Användning

1. **Installation**:
   - Anslut komponenterna till de angivna pinnarna på Arduino-kortet.
   - Ladda upp koden till Arduino.

2. **Ställa in Alarmet**:
   - **Start/Stopp-knapp (digital 2)**: Tryck för att starta eller stoppa alarmet. Om alarmet startas visas en nedräkning på OLED-skärmen.
   - **Lägg till en timme-knapp (digital 3)**: Tryck för att lägga till en timme till alarmet.
   - **Lägg till en minut-knapp (digital 4)**: Tryck för att lägga till en minut till alarmet.

3. **Alarmindikering**:
   - När alarmet når noll blinkar LED-lampan i 5 sekunder för att indikera alarmet.

4. **Visning på OLED-skärmen**:
   - **Tid**: Visar aktuell tid i formatet `hh:mm:ss`.
   - **Temperatur**: Visar temperaturen från DS3231:s sensor.
   - **Alarm Left**: Visar tiden som återstår på alarmet i formatet `mm:ss`.

## Krav

- Arduino IDE (för att kompilera och ladda upp koden)
- RTClib-bibliotek (för att hantera DS3231 RTC)
- U8glib-bibliotek (för att hantera SSD1306 OLED-skärmen)
- Servo-bibliotek (för att kontrollera servon)

## Exempelkörning

Vid körning kommer OLED-skärmen visa:
- Tid, Temperatur och Alarmnedräkning samtidigt.
- Alarmets LED-indikation när nedräkningen når noll.

## Felhantering

- Om RTC-modulen inte kan hittas kommer koden att visa ett felmeddelande i serial-monitorn och stanna.
- Varje knapp har en "debounce"-fördröjning på 200 ms för att undvika felaktiga knapptryck.

---

Den här README-filen ger en översikt över projektets funktioner och hjälper dig att snabbt förstå och använda koden.
