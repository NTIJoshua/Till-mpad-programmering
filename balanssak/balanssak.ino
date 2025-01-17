#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include <Servo.h>

// Skapa LIS3DH- och Servo-objekt
Adafruit_LIS3DH lis = Adafruit_LIS3DH();
Servo servoX;
Servo servoY;

// Offset för att centrera servona
int servoXOffset = 90;
int servoYOffset = 90;

void setup() {
  Serial.begin(9600);

  // Initiera LIS3DH
  if (!lis.begin(0x18)) { // 0x18 är standard I2C-adressen
    Serial.println("Kan inte hitta LIS3DH!");
    while (1);
  }
  
  lis.setRange(LIS3DH_RANGE_2_G); // Ställ in mätnoggrannhet till ±2G
  Serial.println("LIS3DH initierad.");

  // Initiera servon
  servoX.attach(9); // Servo för X-axeln
  servoY.attach(10); // Servo för Y-axeln
  servoX.write(servoXOffset); // Centrera servona
  servoY.write(servoYOffset);
}

void loop() {
  // Läs accelerometerdata
  sensors_event_t event;
  lis.getEvent(&event);

  // Hämta lutningsvinklar för X- och Y-axeln
  float angleX = atan2(event.acceleration.y, event.acceleration.z) * 180 / PI;
  float angleY = atan2(event.acceleration.x, event.acceleration.z) * 180 / PI;

  // Justera servon baserat på vinklar
  int servoXPos = servoXOffset + angleX;
  int servoYPos = servoYOffset + angleY;

  // Begränsa servopositioner till mellan 0 och 180 grader
  servoXPos = constrain(servoXPos, 0, 180);
  servoYPos = constrain(servoYPos, 0, 180);

  // Skriv servopositioner
  servoX.write(servoXPos);
  servoY.write(servoYPos);

  // Debug-utskrift
  Serial.print("Vinkel X: "); Serial.print(angleX);
  Serial.print(" | Vinkel Y: "); Serial.println(angleY);

  // Kort fördröjning för stabilisering
  delay(10);
}
