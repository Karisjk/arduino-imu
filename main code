#include <Wire.h>
#include <MPU6050.h>
#include <math.h>

// Create an MPU6050 object
MPU6050 imu;

void setup() {
  // Initialize the serial communication
  Serial.begin(9600);
  
  // Initialize the I2C communication
  Wire.begin();
  
  // Initialize the MPU6050
  imu.initialize();
  
  // Check if the MPU6050 is connected
  if (imu.testConnection()) {
    Serial.println("MPU6050 connection successful");
  } else {
    Serial.println("MPU6050 connection failed");
    while (1); // Halt the program
  }
}

void loop() {
  // Variables to store the accelerometer data
  int16_t ax, ay, az;
  
  // Read the accelerometer data
  imu.getAcceleration(&ax, &ay, &az);
  
  // Convert raw values to G's (assuming default sensitivity of 16384 LSB/g)
  float ax_g = ax / 16384.0;
  float ay_g = ay / 16384.0;
  float az_g = az / 16384.0;

  // Calculate pitch and roll
  float pitch = atan2(ay_g, sqrt(ax_g * ax_g + az_g * az_g)) * 180.0 / PI;
  float roll = atan2(-ax_g, az_g) * 180.0 / PI;
  
  // Print the angles
  Serial.print("Pitch: "); Serial.print(pitch);
  Serial.print(" | Roll: "); Serial.println(roll);
  
  // Wait for a bit before reading again
  delay(1000);
}
