# Sensorstyrd balansplatta projekt.

Detta Arduino-projekt använder en LIS3DH, en typ av accelerometer, för att mäta acceleration som oftast kommer i gravitationskrafter. Projektet använder datan för att hålla en platta upprätt.

## Funktioner

- **Balansering**: Använder Servo motorer för att flytta en platta.
- **Accelerometer**: Mäter accelerationen med LIS3DH:s inbyggda sensor och skickar datan till datorn.
- **Balansstyrd Servo**: Servon rör sig beroende på aktuell sensor och mappas till ett vinkelområde mellan 0-180 grader.

## Komponenter

- LIS3DH Accelerometer-modul (För balans)
- 9g-servo
- Arduino-kort

## Pin-konfiguration

- **servoPin1**: Digital pin 8 (X-axis servo)
- **servoPin2**: Digital pin 9 (Y-axis servo)

## Användning

1. **Installation**:
   - Anslut komponenterna till de angivna pinnarna på Arduino-kortet.
   - Sätt ihop servorna och plattan.
   - Ladda upp koden till Arduino.

2. **Ställa in Alarmet**: Flytta runt plattan.


## Krav

- Arduino IDE (för att kompilera och ladda upp koden)
- Adafruit_LIS3DH bibliotek (för att hantera LIS3DH accelerometer)
- Adafruit_Sensor bibliotek (för att hantera LIS3dh accelerometer)
- Servo-bibliotek (för att kontrollera servon)

## Exempelkörning

Vid körning kommer servos:
- Flytta sig så att plattformen är platt.

## Felhantering

- En kort delay på 1 ms.
- Optimering av kod.

---

Den här README-filen ger en översikt över projektets funktioner och hjälper dig att snabbt förstå och använda koden.