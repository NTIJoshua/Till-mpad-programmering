/*
Balancing plate

Balances a plate with the use of an accelerometer.

Created 7 February 2025
 by Joshua Odgowu
*/

// Libraries
#include <Adafruit_LIS3DH.h> // Include the library for LIS3DH
#include <Adafruit_Sensor.h> // Needed for sensors
#include <Servo.h> // Include library to use servo motors

// Create a LIS3DH-object
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

// Constants and variables for servo motors
Servo servoX; // Servo motor for X-axis
Servo servoY; // Servo motor for Y-axis
const int servoXPin = 8; // Pin for controlling X-axis servomotor
const int servoYPin = 9; // Pin for controlling Y-axis servomotor

// Buffer variables
const int buffLength = 5;
int bufferX[buffLength];
int bufferY[buffLength];
int indexX=0;
int indexY=0;

int angleXMed;
int angleYMed;

// Adjusting parameters
const int minServoAngle = 0;   // Smallest angle the servo can move to.
const int maxServoAngle = 179; // Biggest angle the servo can move to.

void setup() {
  // Initialize serial communication for debugging purposes. 
  Serial.begin(9600);

  // Initialize LIS3DH
  if (!lis.begin(0x18)) { // Standard I2C-address for LIS3DH
    Serial.println("Could not find LIS3DH. Control connections.");
    while (1);
  }

  Serial.println("LIS3DH initialized!");
  lis.setRange(LIS3DH_RANGE_2_G); //  Measuring range (2G, 4G, 8G, 16G)

  // Initialise servomotors and put them in center
  servoX.attach(servoXPin);
  servoY.attach(servoYPin);
  servoX.write(90); // Center for X-axis
  servoY.write(90); // Center for Y-axis
}

void loop() {
  // Read accelerometerdata
  sensors_event_t event;
  lis.getEvent(&event);

  // Calculate angles based on accelerometer data
  float angleX = atan2(event.acceleration.y, event.acceleration.z) * 180.0 / PI; // X (in degrees)
  float angleY = atan2(event.acceleration.x, event.acceleration.z) * 180.0 / PI; // Y (in degrees)


  bufferX[indexX]=angleX;
  bufferY[indexY]=angleY;

  // Use a modulo operator to index 
  indexX=(indexX+1)%buffLength;
  indexY=(indexY+1)%buffLength;

  // Make an average so the motion is smoother; a filter of sorts.
  for(int i=0; i < buffLength ; i++) {
    angleXMed = angleXMed + bufferX[i];
  }
  angleXMed = angleXMed/buffLength;

  for(int i=0; i < buffLength ; i++) {
    angleYMed = angleYMed + bufferY[i];
  }
  angleYMed = angleYMed/buffLength;

  // Convert angles to servo friendly values, between min and max angles.
  int servoXAngle = map(angleXMed, -90, 90, minServoAngle, maxServoAngle);
  int servoYAngle = map(angleYMed, -90, 90, minServoAngle, maxServoAngle);

  // Constrain angles for safety.
  servoXAngle = constrain(servoXAngle, minServoAngle, maxServoAngle);
  servoYAngle = constrain(servoYAngle, minServoAngle, maxServoAngle);

  // Debugging: Write out the calculated angles to the serial monitor.
  Serial.print("X angle: ");
  Serial.print(servoXAngle);
  Serial.print(" Y angle: ");
  Serial.println(servoYAngle);

  // Move the servo to the specified angle.
  servoX.write(servoXAngle);
  servoY.write(servoYAngle);

  // Short pause for stability. 
  delay(1);
}