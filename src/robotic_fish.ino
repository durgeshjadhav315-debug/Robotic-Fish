
/*
  PROJECT: ROBOTIC FISH
  Application: Underwater Sea Monitoring
  Controller: ESP32 DevKit

  Sensors:
  DS18B20 - Temperature
  TDS     - Water quality indicator
  SEN0189 - Turbidity
  MS5837  - Depth and pressure

  Actuator:
  MG996R  - Fish tail movement

  NOTE:
  This is initial integration firmware.
  Sensor calibration and hardware testing are required.
*/

#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP32Servo.h>
#include <MS5837.h>

// ---------------- PIN CONFIGURATION ----------------

#define TEMP_PIN       4
#define TDS_PIN        34
#define TURBIDITY_PIN  35
#define SERVO_PIN      18

#define I2C_SDA        21
#define I2C_SCL        22

// ---------------- OBJECTS ----------------

OneWire oneWire(TEMP_PIN);
DallasTemperature tempSensor(&oneWire);

Servo tailServo;
MS5837 depthSensor;

// ---------------- SETTINGS ----------------

const float ADC_REFERENCE = 3.3;
const float TDS_FACTOR = 0.5;

// Set this according to the actual sensor model.
// Verify the model marking before using in water.
const float WATER_DENSITY = 997.0;

// ---------------- VARIABLES ----------------

float temperatureC = NAN;
float tdsPPM = NAN;
float turbidityVoltage = NAN;
float depthMeters = NAN;
float pressureMbar = NAN;

bool depthSensorReady = false;

unsigned long lastRead = 0;
unsigned long lastTailMove = 0;

int tailAngle = 60;
bool tailDirection = true;

// ---------------- TEMPERATURE ----------------

void readTemperature() {

  tempSensor.requestTemperatures();

  float value = tempSensor.getTempCByIndex(0);

  if (value != DEVICE_DISCONNECTED_C &&
      value > -55 && value < 125) {

    temperatureC = value;

  } else {

    temperatureC = NAN;
    Serial.println("Temperature sensor error");
  }
}

// ---------------- TDS ----------------

void readTDS() {

  int raw = analogRead(TDS_PIN);

  float voltage = analogReadMilliVolts(TDS_PIN) / 1000.0;

  if (!isnan(temperatureC)) {

    float compensation =
      1.0 + 0.02 * (temperatureC - 25.0);

    float compensatedVoltage =
      voltage / compensation;

    float v = compensatedVoltage;

    // Common DFRobot-style TDS module approximation.
    float value =
      (133.42 * v * v * v
      - 255.86 * v * v
      + 857.39 * v) * TDS_FACTOR;

    tdsPPM = value;

  } else {

    tdsPPM = NAN;
  }

  Serial.print("TDS ADC: ");
  Serial.print(raw);

  Serial.print(" | Voltage: ");
  Serial.print(voltage, 3);

  Serial.println(" V");
}

// ---------------- TURBIDITY ----------------

void readTurbidity() {

  int raw = analogRead(TURBIDITY_PIN);

  // Voltage at ESP32 input after any divider.
  turbidityVoltage =
    analogReadMilliVolts(TURBIDITY_PIN) / 1000.0;

  Serial.print("Turbidity ADC: ");
  Serial.print(raw);

  Serial.print(" | Input Voltage: ");
  Serial.print(turbidityVoltage, 3);

  Serial.println(" V");

  // NTU calibration will be added after
  // measuring actual sensor output and
  // calibrating with reference samples.
}

// ---------------- DEPTH ----------------

void readDepth() {

  if (!depthSensorReady) {
    Serial.println("MS5837 unavailable");
    return;
  }

  depthSensor.read();

  pressureMbar = depthSensor.pressure();
  depthMeters = depthSensor.depth();

  Serial.print("Pressure: ");
  Serial.print(pressureMbar);

  Serial.print(" mbar | Depth: ");
  Serial.print(depthMeters, 3);

  Serial.println(" m");
}

// ---------------- SERVO ----------------

void controlTail() {

  unsigned long now = millis();

  if (now - lastTailMove >= 500) {

    lastTailMove = now;

    tailServo.write(tailAngle);

    if (tailDirection) {

      tailAngle = 120;
      tailDirection = false;

    } else {

      tailAngle = 60;
      tailDirection = true;
    }
  }
}

// ---------------- SETUP ----------------

void setup() {

  Serial.begin(115200);

  analogReadResolution(12);

  Wire.begin(I2C_SDA, I2C_SCL);

  tempSensor.begin();

  tailServo.setPeriodHertz(50);
  tailServo.attach(SERVO_PIN, 500, 2400);
  tailServo.write(90);

  if (depthSensor.init()) {

    depthSensor.setModel(MS5837::MS5837_30BA);
    depthSensor.setFluidDensity(WATER_DENSITY);

    depthSensorReady = true;

    Serial.println("MS5837 initialized");

  } else {

    Serial.println("MS5837 initialization failed");
  }

  Serial.println("Robotic Fish System Started");
}

// ---------------- MAIN LOOP ----------------

void loop() {

  controlTail();

  unsigned long now = millis();

  if (now - lastRead >= 2000) {

    lastRead = now;

    Serial.println("\n--- UNDERWATER MONITORING ---");

    readTemperature();
    readTDS();
    readTurbidity();
    readDepth();

    Serial.println("-----------------------------");
  }
}
