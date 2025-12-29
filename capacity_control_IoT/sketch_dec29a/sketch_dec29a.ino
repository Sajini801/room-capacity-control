#include <Servo.h>

//  Pin Definitions
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;
const int tiltSensorPin = 2;   // Tilt sensor
const int servoPin = 6;        // Servo motor

// === Variables ===
int count = 0;                  // Number of people
int tiltState = 0;
int previousTiltState = -1;
int rgbState = 0;               

Servo myServo;

// === RGB Function ===
void setRGB(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void setup() {
  pinMode(tiltSensorPin, INPUT_PULLUP);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  myServo.attach(servoPin);
  myServo.write(90);  // Neutral position

  Serial.begin(9600);
  Serial.println("Occupancy System Ready");
}

void loop() {
  tiltState = digitalRead(tiltSensorPin);

  // === ENTRY ===
  if (tiltState == HIGH && previousTiltState != HIGH && count < 10) {
    count++;
    setRGB(0, 0, 255);      // Blue
    rgbState = 1;
    myServo.write(0);       // Open door
    delay(500);
  }

  // === EXIT ===
  else if (tiltState == LOW && previousTiltState != LOW && count > 0) {
    count--;
    setRGB(0, 255, 0);      // Green
    rgbState = 2;
    myServo.write(180);     // Open exit
    delay(500);
  }

  // === ROOM FULL ===
  if (count == 10) {
    setRGB(255, 0, 0);      // Red
    rgbState = 3;
    myServo.detach();       // Lock door
  } 
  else if (!myServo.attached()) {
    myServo.attach(servoPin);
  }

  // === SERIAL OUTPUT (MATLAB / PYTHON FRIENDLY) ===
  Serial.print("COUNT:");
  Serial.print(count);
  Serial.print(",TILT:");
  Serial.print(tiltState);
  Serial.print(",RGB:");
  Serial.println(rgbState);

  previousTiltState = tiltState;
  delay(3000);
}
