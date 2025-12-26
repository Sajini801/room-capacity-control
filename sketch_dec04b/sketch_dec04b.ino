#include <Servo.h>

// Pin Definitions
const int redPin = 9;       // Red pin of RGB LED
const int greenPin = 10;    // Green pin of RGB LED
const int bluePin = 11;     // Blue pin of RGB LED
const int tiltSensorPin = 2; // Tilt sensor pin
const int servoPin = 6;     // Servo motor pin

// Variables
int count = 0;              // Count to track people
int tiltState = 0;          // Variable to read tilt sensor state
int previousTiltState = -1; // To detect changes in tilt sensor state
Servo myServo;              // Servo object

// RGB Control Function
void setRGB(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void setup() {
  // Pin Setup
  pinMode(tiltSensorPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Initialize Servo
  myServo.attach(servoPin);
  myServo.write(90); // Set servo to initial position (90 degrees)

  // Serial Monitor for Debugging
  Serial.begin(9600);
}

void loop() {
  // Read tilt sensor state
  tiltState = digitalRead(tiltSensorPin);

  // If tilt is right and count < 10
  if (tiltState == HIGH && previousTiltState != HIGH && count < 10) {
    setRGB(0, 0, 255); // RGB to blue
    myServo.write(0);  // Servo to 0 degrees
    count++;           // Increment count
    delay(500);        // Debounce delay
  }
  // If tilt is left
  else if (tiltState == LOW && previousTiltState != LOW) {
    if (count == 10) {
      setRGB(0, 255, 0); // RGB to green
      myServo.attach(servoPin); // Reattach servo
    }
    setRGB(0, 255, 0);   // RGB to green
    myServo.write(180);  // Servo to 180 degrees
    count--;             // Decrement count
    delay(500);          // Debounce delay
  }

  // If count reaches 10
  if (count == 10) {
    setRGB(255, 0, 0); // RGB to red
    myServo.detach();  // Stop servo motor
  } else if (!myServo.attached()) {
    myServo.attach(servoPin); // Re-enable servo motor if count < 10
  }

  // Debugging output
  Serial.print("Count: ");
  Serial.println(count);

  // Update previous tilt state
  previousTiltState = tiltState;
}
