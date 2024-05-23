#include <Servo.h>

// Define joystick pins
const int VRxPin = A0;  // Analog pin for X-axis
const int VRyPin = A1;  // Analog pin for Y-axis
const int SWPin = 2;    // Digital pin for button

// Define LED pins
const int leftLEDPin = 3;
const int rightLEDPin = 4;
const int upLEDPin = 5;
const int downLEDPin = 6;
const int buttonLEDPin = 7;  // LED for button press

// Define Servo pin
const int servoPin = 9;

// Threshold for joystick movement
const int threshold = 200;

// Create Servo object
Servo myServo;

void setup() {
  // Initialize the serial communication
  Serial.begin(9600);

  // Configure the button pin as input with pull-up resistor
  pinMode(SWPin, INPUT_PULLUP);

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
  // Read the joystick X and Y positions
  int xPosition = analogRead(VRxPin);
  int yPosition = analogRead(VRyPin);

  // Read the joystick button state
  int buttonState = digitalRead(SWPin);

  // Determine joystick direction and control LEDs
  if (xPosition < (512 - threshold)) {
    // Joystick moved left
    digitalWrite(leftLEDPin, HIGH);
    digitalWrite(rightLEDPin, LOW);
  } else if (xPosition > (512 + threshold)) {
    // Joystick moved right
    digitalWrite(rightLEDPin, HIGH);
    digitalWrite(leftLEDPin, LOW);
  } else {
    digitalWrite(leftLEDPin, LOW);
    digitalWrite(rightLEDPin, LOW);
  }

  if (yPosition < (512 - threshold)) {
    // Joystick moved up
    digitalWrite(upLEDPin, HIGH);
    digitalWrite(downLEDPin, LOW);
  } else if (yPosition > (512 + threshold)) {
    // Joystick moved down
    digitalWrite(downLEDPin, HIGH);
    digitalWrite(upLEDPin, LOW);
  } else {
    digitalWrite(upLEDPin, LOW);
    digitalWrite(downLEDPin, LOW);
  }

  // Button press
  if (buttonState == LOW) {
    // Button is pressed
    digitalWrite(buttonLEDPin, HIGH);
  } else {
    digitalWrite(buttonLEDPin, LOW);
  }

  // Control the servo motor based on X position
  // Map the joystick value (0 to 1023) to the servo angle (0 to 180)
  int servoAngle = map(xPosition, 0, 1023, 0, 180);
  myServo.write(servoAngle);

  // Print the values to the Serial Monitor
  Serial.print("X: ");
  Serial.print(xPosition);
  Serial.print(" | Y: ");
  Serial.print(yPosition);
  Serial.print(" | Button: ");
  Serial.println(buttonState == LOW ? "Pressed" : "Released");
  Serial.print(" | Servo Angle: ");
  Serial.println(servoAngle);

  // Small delay for readability
  delay(100);
}
