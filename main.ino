#include <Wire.h>
#include <VL53L1X.h>

// === SENSOR OBJECT ===
VL53L1X sensor;

// === FIRST MOTOR (M1) PINS ===
#define ENA  8   // PWM pin for Motor 1 speed control
#define IN1  4   // IN1 for Motor 1 direction
#define IN2  5   // IN2 for Motor 1 direction

// === SECOND MOTOR (M2) PINS ===
#define ENB  11   // PWM pin for Motor 2 speed control
#define IN3  9    // IN3 for Motor 2 direction
#define IN4  10   // IN4 for Motor 2 direction

// === CONFIGURATION CONSTANTS ===
#define NUM_INITIAL_READINGS 60    // Number of readings for zero offset
#define THRESHOLD 20              // Threshold in mm
#define MOTOR_SPEED 255            // Motor speed (0-255)
#define TIME_LIMIT 5000           // Time limit in milliseconds

// === VARIABLES ===
uint16_t zeroOffset = 0;          // Zero offset for distance
bool motorsRunning = false;       // Motor running state
unsigned long motorStartTime = 0; // Timestamp when motors started

void setup()
{
  // Initialize Serial
  Serial.begin(115200);
  while (!Serial) {}

  // Initialize I2C communication
  Wire.begin();
  Wire.setClock(400000); // Use 400 kHz I2C

  // Initialize the sensor
  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1); // Stop program if sensor initialization fails
  }

  // Configure the sensor
  sensor.setDistanceMode(VL53L1X::Long);
  sensor.setMeasurementTimingBudget(50000);
  sensor.startContinuous(50); // Start continuous measurements every 50 ms

  // === Setup Motor 1 pins ===
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // === Setup Motor 2 pins ===
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.println("VL53L1X and Motor Control Initialized!");

  // === Calculate Zero Offset ===
  Serial.println("Calculating zero offset...");
  uint32_t sum = 0;
  for (int i = 0; i < NUM_INITIAL_READINGS; i++)
  {
    uint16_t reading = sensor.read();
    if (sensor.timeoutOccurred())
    {
      Serial.println("Sensor timeout during zero offset calculation!");
    }
    else
    {
      sum += reading;
      Serial.print("Initial reading ");
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(reading);
      Serial.println(" mm");
    }
    delay(100);
  }
  zeroOffset = sum / NUM_INITIAL_READINGS;
  Serial.print("Zero offset set to: ");
  Serial.print(zeroOffset);
  Serial.println(" mm");
}

void loop()
{
  // Read distance from the sensor
  uint16_t distance = sensor.read();
  if (sensor.timeoutOccurred())
  {
    Serial.println("Sensor timeout occurred!");
    return;
  }

  // Calculate the difference from zero offset
  int16_t difference = distance - zeroOffset;

  // Print distance and difference
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" mm, Difference: ");
  Serial.print(difference);
  Serial.println(" mm");

  // Check if the difference is within the threshold
  if (abs(difference) >= THRESHOLD)
  {
    if (!motorsRunning)
    {
      // Start motors
      runMotor(MOTOR_SPEED);
      runMotor2(MOTOR_SPEED);
      motorsRunning = true;
      motorStartTime = millis();
      Serial.println("Motors started.");
    }
    else
    {
      // Check if time limit has been reached
      unsigned long currentTime = millis();
      if (currentTime - motorStartTime >= TIME_LIMIT)
      {
        // Stop motors after time limit
        stopMotor();
        stopMotor2();
        motorsRunning = false;
        Serial.println("Motors stopped due to time limit.");
      }
    }
  }
  else
  {
    if (motorsRunning)
    {
      // Stop motors if the difference is out of threshold
      stopMotor();
      stopMotor2();
      motorsRunning = false;
      Serial.println("Motors stopped due to distance out of threshold.");
    }
  }

  delay(50);
}

// === FUNCTIONS FOR MOTOR 1 ===
void runMotor(int speed)
{
  digitalWrite(IN1, HIGH);  // Set M1 direction
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speed);  // Set speed using PWM
}

void stopMotor()
{
  analogWrite(ENA, 0);      // Stop motor (0 PWM)
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

// === FUNCTIONS FOR MOTOR 2 ===
void runMotor2(int speed)
{
  digitalWrite(IN3, HIGH);  // Set M2 direction
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speed);  // Set speed using PWM
}

void stopMotor2()
{
  analogWrite(ENB, 0);      // Stop motor (0 PWM)
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
