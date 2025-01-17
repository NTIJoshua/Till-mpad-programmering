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

  // Convert angles to servo friendly values, between min and max angles.
  int servoXAngle = map(angleX, -90, 90, minServoAngle, maxServoAngle);
  int servoYAngle = map(angleY, -90, 90, minServoAngle, maxServoAngle);

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
  delay(100);
}