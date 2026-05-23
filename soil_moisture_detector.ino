// =====================================================================
//  Soil Moisture Detector with Auto Irrigation
//  DRIEMS Polytechnic — Dept. of CSE | Semester 4 | Group 10
//  Academic Year: 2025-2026
//  Guide: Er. Subhashree Samantaray
// =====================================================================

#define BLYNK_TEMPLATE_ID   "YOUR_TEMPLATE_ID"       // ← Replace with your Blynk Template ID
#define BLYNK_TEMPLATE_NAME "Automatic plant watering system"
#define BLYNK_AUTH_TOKEN    "YOUR_BLYNK_AUTH_TOKEN"  // ← Replace with your Blynk Auth Token

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// ---- WiFi Credentials ----
char ssid[] = "YOUR_WIFI_SSID";      // ← Replace with your WiFi SSID
char pass[] = "YOUR_WIFI_PASSWORD";  // ← Replace with your WiFi Password

// ---- Pin Definitions ----
#define SOIL_PIN   34   // Analog input pin for soil moisture sensor
#define RELAY_PIN  26   // Digital output pin for relay (controls water pump)

// ---- Sensor Calibration ----
// Adjust these values based on your specific soil moisture sensor readings:
//   dryValue  = analogRead() when sensor is in completely dry soil/air
//   wetValue  = analogRead() when sensor is in fully saturated (wet) soil
int dryValue = 3200;
int wetValue = 1400;

// ---- Irrigation Thresholds (in %) ----
int startWateringAt = 30;   // Pump turns ON when moisture drops below this %
int stopWateringAt  = 60;   // Pump turns OFF when moisture reaches this %

// ---- State Variables ----
BlynkTimer timer;
bool pumpState        = false;
bool notificationSent = false;   // Prevents repeated Blynk notifications

// =====================================================================
//  sendSoilMoisture()
//  Called every 3 seconds by the Blynk timer.
//  Reads the sensor, maps the value to a percentage, updates Blynk,
//  and controls the relay accordingly.
// =====================================================================
void sendSoilMoisture()
{
  int soilValue = analogRead(SOIL_PIN);

  // Map raw ADC value to 0–100% moisture
  int moisturePercent = map(soilValue, dryValue, wetValue, 0, 100);
  moisturePercent = constrain(moisturePercent, 0, 100);

  Serial.print("Moisture: ");
  Serial.print(moisturePercent);
  Serial.println(" %");

  // Send moisture value to Blynk virtual pin V0 (e.g., Gauge widget)
  Blynk.virtualWrite(V0, moisturePercent);

  // ---- Turn Pump ON (soil is dry) ----
  if (moisturePercent <= startWateringAt && !pumpState)
  {
    digitalWrite(RELAY_PIN, LOW);   // LOW activates relay (active-low module)
    pumpState = true;
    Serial.println("Pump ON");

    if (!notificationSent)
    {
      Blynk.logEvent("low_moisture", "Soil is dry! Watering started.");
      notificationSent = true;
    }
  }

  // ---- Turn Pump OFF (soil has reached target moisture) ----
  if (moisturePercent >= stopWateringAt && pumpState)
  {
    digitalWrite(RELAY_PIN, HIGH);  // HIGH deactivates relay
    pumpState = false;
    notificationSent = false;       // Reset for next dry cycle
    Serial.println("Pump OFF - Target moisture reached");
  }
}

// =====================================================================
//  setup()
// =====================================================================
void setup()
{
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);  // Ensure pump is OFF on startup

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Schedule sendSoilMoisture() to run every 3 seconds
  timer.setInterval(3000L, sendSoilMoisture);
}

// =====================================================================
//  loop()
// =====================================================================
void loop()
{
  Blynk.run();
  timer.run();
}
