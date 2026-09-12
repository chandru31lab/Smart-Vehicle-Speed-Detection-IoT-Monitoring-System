#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Speed Detector"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// WiFi
char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

// IR sensors
#define IR_SENSOR1_PIN 4
#define IR_SENSOR2_PIN 5

// Sensor distance
#define SENSOR_DISTANCE_CM 10.0

// Overspeed limit in m/s
// 5 m/s = 18 km/h
#define OVERSPEED_LIMIT 5.0

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Variables
unsigned long sensor1Time = 0;
unsigned long sensor2Time = 0;

float speed = 0.0;

int totalVehicles = 0;
int overspeedVehicles = 0;

bool sensor1Triggered = false;
bool waitingForSensor2 = false;

void setup()
{
  Serial.begin(115200);

  // Sensor setup
  pinMode(IR_SENSOR1_PIN, INPUT);
  pinMode(IR_SENSOR2_PIN, INPUT);

  // I2C LCD
  Wire.begin(21, 22);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Speed Detector");
  lcd.setCursor(0, 1);
  lcd.print("Connecting...");

  // Blynk connection
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Initial Blynk values
  Blynk.virtualWrite(V0, 0);
  Blynk.virtualWrite(V1, 0);
  Blynk.virtualWrite(V2, 0);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Speed Detector");
  lcd.setCursor(0, 1);
  lcd.print("Online");

  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Waiting...");
}

void loop()
{
  Blynk.run();

  // Read sensors
  int sensor1 = digitalRead(IR_SENSOR1_PIN);
  int sensor2 = digitalRead(IR_SENSOR2_PIN);

  // ----------------------------------------
  // SENSOR 1
  // ----------------------------------------
  if (sensor1 == HIGH && !sensor1Triggered)
  {
    sensor1Time = micros();

    sensor1Triggered = true;
    waitingForSensor2 = true;

    Serial.println("Sensor 1 Detected");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Vehicle Detected");
    lcd.setCursor(0, 1);
    lcd.print("Measuring...");
  }

  // ----------------------------------------
  // SENSOR 2
  // ----------------------------------------
  if (sensor2 == HIGH &&
      sensor1Triggered &&
      waitingForSensor2)
  {
    sensor2Time = micros();

    // Calculate time in seconds
    float timeTaken =
      (sensor2Time - sensor1Time) / 1000000.0;

    // Convert cm to meters
    float distance =
      SENSOR_DISTANCE_CM / 100.0;

    // Speed in m/s
    speed = distance / timeTaken;

    // Count vehicle
    totalVehicles++;

    // Check overspeed
    if (speed > OVERSPEED_LIMIT)
    {
      overspeedVehicles++;
    }

    // ----------------------------------------
    // SERIAL MONITOR
    // ----------------------------------------

    Serial.println("----------------------");

    Serial.print("Time: ");
    Serial.print(timeTaken, 4);
    Serial.println(" s");

    Serial.print("Speed: ");
    Serial.print(speed, 2);
    Serial.println(" m/s");

    Serial.print("Total Vehicles: ");
    Serial.println(totalVehicles);

    Serial.print("Overspeed Vehicles: ");
    Serial.println(overspeedVehicles);

    Serial.println("----------------------");

    // ----------------------------------------
    // LCD
    // ----------------------------------------

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Speed:");
    lcd.print(speed, 2);
    lcd.print("m/s");

    lcd.setCursor(0, 1);
    lcd.print("Vehicles:");
    lcd.print(totalVehicles);

    // ----------------------------------------
    // BLYNK
    // ----------------------------------------

    // Speed
    Blynk.virtualWrite(V0, speed);

    // Total vehicles
    Blynk.virtualWrite(V1, totalVehicles);

    // Overspeed vehicles
    Blynk.virtualWrite(V2, overspeedVehicles);

    // Wait for vehicle to completely pass
    delay(1000);

    // Reset
    sensor1Triggered = false;
    waitingForSensor2 = false;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Speed Detector");
    lcd.setCursor(0, 1);
    lcd.print("Waiting...");
  }
}
