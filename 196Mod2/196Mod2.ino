#include <Servo.h>

// Stepper motor definitions
#define STEPPER_PIN_1 46
#define STEPPER_PIN_2 48
#define STEPPER_PIN_3 50
#define STEPPER_PIN_4 52

// Servo definitions
Servo myservo;
#define SERVO_PIN 9

// Solenoid definitions
#define SOLENOID_PIN 22

// DC motor definitions (Using a simple on/off control here)
#define DCMOTOR_PIN 24

// Global variables for stepper motor
int step_number = 0;
int step_count = 0;
int step_delay = 2;
bool direction = false;

// Function declarations
void OneStep(bool dir);
void ActivateSolenoid(bool on);
void ControlDCMotor(bool on);

void setup() {
  // Setup for stepper motor
  pinMode(STEPPER_PIN_1, OUTPUT);
  pinMode(STEPPER_PIN_2, OUTPUT);
  pinMode(STEPPER_PIN_3, OUTPUT);
  pinMode(STEPPER_PIN_4, OUTPUT);

  // Setup for servo motor
  myservo.attach(SERVO_PIN);
  
  // Setup for solenoid
  pinMode(SOLENOID_PIN, OUTPUT);

  // Setup for DC motor
  pinMode(DCMOTOR_PIN, OUTPUT);
}

void loop() {
  // Control stepper motor
  OneStep(direction);
  delay(step_delay);
  step_count++;
  if (step_count > 1000) {
    direction = !direction;
    step_count = 0;
  }
  
  // Control servo motor
  myservo.write(90); // Set servo to mid-point. Modify as needed for your application.

  // Control solenoid
  ActivateSolenoid(true); // Activate solenoid. Modify as needed for your application.
  delay(1000); // Example delay
  ActivateSolenoid(false);
  
  // Control DC motor
  ControlDCMotor(true); // Turn on DC motor. Modify as needed for your application.
  delay(1000); // Example delay
  ControlDCMotor(false);
}

void OneStep(bool dir) {
  if (dir) {
    switch (step_number) {
      case 0:
        digitalWrite(STEPPER_PIN_1, HIGH);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 1:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, HIGH);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 2:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, HIGH);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 3:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, HIGH);
        break;
    }
  } else {
    switch (step_number) {
      case 0:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, HIGH);
        break;
      case 1:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, HIGH);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 2:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, HIGH);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 3:
        digitalWrite(STEPPER_PIN_1, HIGH);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
    }
  }
  
}

void ActivateSolenoid(bool on) {
  digitalWrite(SOLENOID_PIN, on ? HIGH : LOW);
}

void ControlDCMotor(bool on) {
  digitalWrite(DCMOTOR_PIN, on ? HIGH : LOW);
}
