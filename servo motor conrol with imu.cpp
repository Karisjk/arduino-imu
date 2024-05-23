#include <Wire.h>
#include <MPU6050.h>
#include <Servo.h>

// Define motor control pins
const int motorPin1 = 8;
const int motorPin2 = 9;

// Define LED pins
const int leftLEDPin = 3;
const int rightLEDPin = 4;
const int upLEDPin = 5;
const int downLEDPin = 6;
const int buttonLEDPin = 7;  // Repurposed for indicating stable state

// Define Servo pin
const int servoPin = 9;

// Create Servo object
Servo myServo;

// Create MPU6050 object
MPU6050 imu;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Initialize I2C communication
  Wire.begin();
  
  // Initialize the IMU
  imu.initialize();

  // Configure motor control pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);

  // Configure LED pins as outputs
  pinMode(leftLEDPin, OUTPUT);
  pinMode(rightLEDPin, OUTPUT);
  pinMode(upLEDPin, OUTPUT);
  pinMode(downLEDPin, OUTPUT);
  pinMode(buttonLEDPin, OUTPUT);

  // Attach the servo
  myServo.attach(servoPin);
}

void loop() {
  // Read the IMU data
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  imu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Use acceleration data to determine orientation
  // Simple thresholding to determine direction
  int threshold = 10000;

  if (ax < -threshold) {
    // Move motor left
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    // Indicate direction with LEDs
    digitalWrite(leftLEDPin, HIGH);
    digitalWrite(rightLEDPin, LOW);
  } else if (ax > threshold) {
    // Move motor right
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    // Indicate direction with LEDs
    digitalWrite(leftLEDPin, LOW);
    digitalWrite(rightLEDPin, HIGH);
  } else {
    // Stop motor
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    // Turn off direction LEDs
    digitalWrite(leftLEDPin, LOW);
    digitalWrite(rightLEDPin, LOW);
  }

  if (ay < -threshold) {
    // Indicate up direction with LED
    digitalWrite(upLEDPin, HIGH);
    digitalWrite(downLEDPin, LOW);
  } else if (ay > threshold) {
    // Indicate down direction with LED
    digitalWrite(upLEDPin, LOW);
    digitalWrite(downLEDPin, HIGH);
  } else {
    // Turn off up and down LEDs
    digitalWrite(upLEDPin, LOW);
    digitalWrite(downLEDPin, LOW);
  }

  // Indicate stable state with button LED if no significant movement
  if (abs(ax) < threshold && abs(ay) < threshold) {
    digitalWrite(buttonLEDPin, HIGH);
  } else {
    digitalWrite(buttonLEDPin, LOW);
  }

  // Control the servo motor based on X position
  // Map the ax value (-32768 to 32767) to the servo angle (0 to 180)
  int servoAngle = map(ax, -32768, 32767, 0, 180);
  myServo.write(servoAngle);

  // Print IMU data to the Serial Monitor
  Serial.print("ax: "); Serial.print(ax);
  Serial.print(" | ay: "); Serial.print(ay);
  Serial.print(" | az: "); Serial.print(az);
  Serial.print(" | gx: "); Serial.print(gx);
  Serial.print(" | gy: "); Serial.print(gy);
  Serial.print(" | gz: "); Serial.println(gz);
  Serial.print(" | Servo Angle: "); Serial.println(servoAngle);

  // Small delay for readability
  delay(100);
}
