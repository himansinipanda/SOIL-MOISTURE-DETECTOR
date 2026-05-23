# 🌱 Soil Moisture Detector with Auto Irrigation

> **DRIEMS Polytechnic** | Department of Computer Science & Engineering  
> Semester: 4th | Section: A | Group No: 10 | Academic Year: 2025–2026  
> Project Guide: **Er. Subhashree Samantaray**

---

## 📋 Abstract

Efficient water management is a crucial aspect of modern agriculture.  
This project measures and monitors soil moisture content in real time using an **ESP32 microcontroller** and a **soil moisture sensor**. When moisture drops below a set threshold, a **water pump is automatically activated** via a relay module. The live moisture percentage is monitored through the **Blynk mobile app**, and push notifications are sent when watering begins.

---

## ✨ Features

- Real-time soil moisture monitoring (0–100%)
- Automatic pump control via relay (turns ON when dry, OFF when wet)
- Blynk app integration — live gauge + push notifications
- Configurable dry/wet thresholds
- Spam-safe notifications (one alert per dry cycle)
- Serial monitor logging for debugging

---

## 🔧 Components & Cost

| Component | Approx. Cost |
|---|---|
| Analog Soil Moisture Sensor Module | ₹ 33 |
| ESP32 | ₹ 400 |
| 5V Single-Channel Relay Module | ₹ 33 |
| DC Mini Water Pump | ₹ 44 |
| 9V Battery | ₹ 30 |
| Jumper Wires | ₹ 49 |
| Breadboard | ₹ 35 |
| **Total** | **₹ ~624** |

---

## 📐 Circuit Connections

| ESP32 Pin | Connected To |
|---|---|
| GPIO 34 | Soil Sensor Analog Output (AO) |
| GPIO 26 | Relay Module IN |
| 3.3V / GND | Soil Sensor VCC / GND |
| 5V / GND | Relay VCC / GND |

> See [`circuit/CIRCUIT_DIAGRAM.png`](circuit/CIRCUIT_DIAGRAM.png) for the full wiring diagram.

---

## 🛠️ Setup Instructions

### 1. Install Arduino IDE Dependencies

Install the following libraries via **Arduino IDE → Library Manager**:

- `Blynk` by Volodymyr Shymanskyy
- `WiFi` (bundled with ESP32 board package)

Install the **ESP32 board** via Boards Manager:  
`https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`

### 2. Configure Credentials

Open `src/soil_moisture_detector.ino` and fill in your details:

```cpp
#define BLYNK_TEMPLATE_ID   "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Automatic plant watering system"
#define BLYNK_AUTH_TOKEN    "YOUR_BLYNK_AUTH_TOKEN"

char ssid[] = "YOUR_WIFI_SSID";
char pass[] = "YOUR_WIFI_PASSWORD";
```

### 3. Calibrate the Sensor

Measure `analogRead()` values from your sensor in **dry air** and **fully wet soil**, then update:

```cpp
int dryValue = 3200;   // Raw ADC reading in dry conditions
int wetValue = 1400;   // Raw ADC reading in wet conditions
```

### 4. Set Irrigation Thresholds

```cpp
int startWateringAt = 30;   // Pump ON when moisture < 30%
int stopWateringAt  = 60;   // Pump OFF when moisture ≥ 60%
```

### 5. Blynk App Setup

1. Create a new template in [Blynk Cloud](https://blynk.cloud)
2. Add a **Gauge** widget → Virtual Pin **V0** (range 0–100)
3. Add an **Event** named `low_moisture` for push notifications
4. Copy your **Template ID** and **Auth Token** into the sketch

### 6. Upload

Select **Board:** `ESP32 Dev Module` → correct **Port** → click **Upload**.

---

## 📊 How It Works

```
Soil Sensor → ESP32 (analogRead) → Map to 0–100%
                     ↓
          Compare with thresholds
         /                        \
  moisture < 30%             moisture ≥ 60%
  Relay LOW → Pump ON        Relay HIGH → Pump OFF
  Blynk notification sent    Ready for next cycle
```

---

## 📁 Repository Structure

```
soil-moisture-detector/
├── src/
│   └── soil_moisture_detector.ino   # Main Arduino sketch
├── circuit/
│   └── CIRCUIT_DIAGRAM.png          # Wiring diagram
├── docs/
│   └── PROJECT_PROPOSAL.pdf         # Original project proposal
└── README.md
```

---

## 👥 Team Members

| Reg. No | Name |
|---|---|
| F24026007046 | Harisankar Nayak |
| F24026007047 | Himansini Panda |
| F24026007048 | Hruday Kumar Behera |
| F24026007049 | Jatin Mohapatra |
| F24026007050 | Jayasha Swain |

---

## 📜 License

This project is submitted as part of the academic curriculum at **DRIEMS Polytechnic, Tangi, Cuttack-754022** for the academic year 2025–2026.
