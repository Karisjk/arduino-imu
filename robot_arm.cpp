#include <Servo.h>

// Create servo objects
Servo servo1;
Servo servo2;
Servo servo3;

// Define servo pins
const int servoPin1 = 9;
const int servoPin2 = 10;
const int servoPin3 = 11;

// Define joystick pins
const int joy1XPin = A0; // Joystick 1 X-axis
const int joy2XPin = A2; // Joystick 2 X-axis
const int joy2YPin = A3; // Joystick 2 Y-axis

void setup() {
  // Attach servos to their respective pins
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);

  // (Optional) Initialize serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Read joystick values
  int joy1XValue = analogRead(joy1XPin);
  int joy2XValue = analogRead(joy2XPin);
  int joy2YValue = analogRead(joy2YPin);

  // Map joystick values to servo angles
  int angle1 = map(joy1XValue, 0, 1023, 0, 90); // Servo1 range: 0 to 90 degrees
  int angle2 = map(joy2XValue, 0, 1023, 0, 180); // Servo2 range: 0 to 180 degrees
  int angle3 = map(joy2YValue, 0, 1023, 0, 180); // Servo3 range: 0 to 180 degrees

  // Write angles to servos
  servo1.write(angle1);
  servo2.write(angle2);
  servo3.write(angle3);

  // (Optional) Print values for debugging
  Serial.print("Joystick 1 X: ");
  Serial.print(joy1XValue);
  Serial.print(" | Servo 1 Angle: ");
  Serial.println(angle1);

  Serial.print("Joystick 2 X: ");
  Serial.print(joy2XValue);
  Serial.print(" | Servo 2 Angle: ");
  Serial.println(angle2);

  Serial.print("Joystick 2 Y: ");
  Serial.print(joy2YValue);
  Serial.print(" | Servo 3 Angle: ");
  Serial.println(angle3);

  // Delay for smooth movement
  delay(15); // Adjust this value to experiment with different delays
}
