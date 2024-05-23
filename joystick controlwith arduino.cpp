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

// Threshold for joystick movement
const int threshold = 200;

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
}

void loop() {
  // Read the joystick X and Y positions
  int xPosition = analogRead(VRxPin);
  int yPosition = analogRead(VRyPin);

  // Read the joystick button state
  int buttonState = digitalRead(SWPin);

  // Determine joystick direction
  if (xPosition < (512 - threshold)) {
    // Joystick moved left
    digitalWrite(leftLEDPin, HIGH);
  } else {
    digitalWrite(leftLEDPin, LOW);
  }

  if (xPosition > (512 + threshold)) {
    // Joystick moved right
    digitalWrite(rightLEDPin, HIGH);
  } else {
    digitalWrite(rightLEDPin, LOW);
  }

  if (yPosition < (512 - threshold)) {
    // Joystick moved up
    digitalWrite(upLEDPin, HIGH);
  } else {
    digitalWrite(upLEDPin, LOW);
  }

  if (yPosition > (512 + threshold)) {
    // Joystick moved down
    digitalWrite(downLEDPin, HIGH);
  } else {
    digitalWrite(downLEDPin, LOW);
  }

  // Button press
  if (buttonState == LOW) {
    // Button is pressed
    digitalWrite(buttonLEDPin, HIGH);
  } else {
    digitalWrite(buttonLEDPin, LOW);
  }

  // Print the values to the Serial Monitor
  Serial.print("X: ");
  Serial.print(xPosition);
  Serial.print(" | Y: ");
  Serial.print(yPosition);
  Serial.print(" | Button: ");
  Serial.println(buttonState == LOW ? "Pressed" : "Released");

  // Small delay for readability
  delay(100);
}
