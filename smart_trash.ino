
#include <Servo.h>

// ================================
// PIN CONFIGURATION
// ================================
#define TRIG_PIN 9
#define ECHO_PIN 10
#define SERVO_PIN 6

// ================================
// CONFIGURATION
// ================================
const int OPEN_ANGLE = 90;
const int CLOSE_ANGLE = 0;

const float DETECT_DISTANCE = 20.0;
const float RELEASE_DISTANCE = 25.0;

const unsigned long CLOSE_DELAY = 2000;
const unsigned long SENSOR_INTERVAL = 100;

// ================================
// OBJECTS & VARIABLES
// ================================
Servo trashServo;

bool lidIsOpen = false;

unsigned long lastDetectionTime = 0;
unsigned long lastSensorRead = 0;

// ================================
// READ ULTRASONIC SENSOR
// ================================
float getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  unsigned long duration = pulseIn(ECHO_PIN, HIGH, 30000UL);

  if (duration == 0) {
    return -1;
  }

  float distance = duration * 0.0343 / 2.0;

  if (distance < 2 || distance > 400) {
    return -1;
  }

  return distance;
}

// ================================
// OPEN TRASH LID
// ================================
void openLid() {
  if (!lidIsOpen) {
    trashServo.write(OPEN_ANGLE);
    lidIsOpen = true;

    Serial.println("LID: OPEN");
  }
}

// ================================
// CLOSE TRASH LID
// ================================
void closeLid() {
  if (lidIsOpen) {
    trashServo.write(CLOSE_ANGLE);
    lidIsOpen = false;

    Serial.println("LID: CLOSED");
  }
}

// ================================
// SETUP
// ================================
void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  trashServo.attach(SERVO_PIN);
  trashServo.write(CLOSE_ANGLE);

  Serial.println("========================");
  Serial.println("   SMART TRASH BIN");
  Serial.println("========================");

  delay(500);
}

// ================================
// MAIN LOOP
// ================================
void loop() {

  if (millis() - lastSensorRead >= SENSOR_INTERVAL) {

    lastSensorRead = millis();

    float distance = getDistance();

    if (distance > 0) {

      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.println(" cm");

      // Detect hand approaching
      if (distance <= DETECT_DISTANCE) {

        openLid();
        lastDetectionTime = millis();

      }

      // Keep lid open while object is nearby
      else if (lidIsOpen && distance <= RELEASE_DISTANCE) {

        lastDetectionTime = millis();

      }

    }

    // Close lid after object leaves
    if (lidIsOpen &&
        millis() - lastDetectionTime >= CLOSE_DELAY) {

      closeLid();

    }
  }
}
