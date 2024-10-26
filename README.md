## Smart Irrigation System with LCD Display Using Arduino Uno

### Project Overview
This smart irrigation system automates plant watering by monitoring soil moisture levels and activating a pump motor when necessary. An LCD screen displays real-time soil moisture readings and pump status, providing immediate feedback for users. The system includes an Arduino Uno, a soil moisture sensor, a pump motor, a relay module, and an LCD display.

### Table of Contents
1. [Components](#components)
2. [Circuit](#circuit)
3. [Hardware Assembly](#hardware-assembly)
4. [Software Code](#software-code)
5. [Working Principle](#working-principle)
6. [Testing and Calibration](#testing-and-calibration)
7. [Future Enhancements](#future-enhancements)
8. [Conclusion](#conclusion)

---

### #1. Components

| Component             | Quantity | Description                                       |
|-----------------------|----------|---------------------------------------------------|
| Arduino Uno           | 1        | Microcontroller for controlling the system        |
| Soil Moisture Sensor  | 1        | Measures soil moisture levels                     |
| Relay Module          | 1        | Controls the pump motor                           |
| Pump Motor            | 1        | DC pump to supply water to plants                 |
| LCD Display (16x2)    | 1        | Displays soil moisture and pump status            |
| I2C Module for LCD    | 1        | Reduces pin usage for connecting LCD to Arduino   |
| Power Supply          | 1        | Powers the motor                                  |
| Jumper Wires          | As needed| For connections between components                |
| Breadboard            | 1        | For prototyping the circuit                       |

---

### 2. Circuit 



**Connections:**
- **Soil Moisture Sensor:**
  - VCC to Arduino **5V**
  - GND to Arduino **GND**
  - Analog Output (A0) to Arduino **A0**
  
- **Relay Module:**
  - VCC to Arduino **5V**
  - GND to Arduino **GND**
  - Input (IN) to Arduino **Digital Pin 8**
  
- **Pump Motor:**
  - Positive terminal connected to **NO** (Normally Open) on the relay.
  - Negative terminal connected to the external **GND**.
  - Relay common (COM) connected to the **positive** terminal of the external power supply.
  
- **LCD Display with I2C Module:**
  - Connect **SDA** to Arduino **A4**
  - Connect **SCL** to Arduino **A5**
  - **VCC** to Arduino **5V**
  - **GND** to Arduino **GND**

---

### 3. Hardware Assembly
1. **Connect the Soil Moisture Sensor** to the Arduino as per the circuit diagram.
2. **Wire the Relay Module** to the Arduino to control the pump motor.
3. **Connect the Pump Motor** to the relay module and external power supply.
4. **Attach the LCD Display** to the Arduino using the I2C module for simplified connections.
5. Double-check all connections to ensure there are no loose wires or incorrect connections.

---

### 4. Software Code
The following code reads the soil moisture sensor, displays the moisture level and pump status on the LCD, and activates the pump when necessary.

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SOIL_MOISTURE_PIN A0     // Soil Moisture Sensor connected to A0
#define RELAY_PIN 8              // Relay connected to Digital Pin 8
#define DRY_THRESHOLD 500        // Threshold value to trigger watering

// Set up the LCD with I2C address 0x27, 16 columns, and 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  pinMode(SOIL_MOISTURE_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);  // Start with pump off

  lcd.begin();  // Initialize the LCD
  lcd.backlight();  // Turn on LCD backlight
  lcd.setCursor(0, 0);
  lcd.print("Smart Irrigation");
}

void loop() {
  int soilMoistureValue = analogRead(SOIL_MOISTURE_PIN);
  Serial.print("Soil Moisture Level: ");
  Serial.println(soilMoistureValue);

  lcd.setCursor(0, 1);  // Display soil moisture value
  lcd.print("Moisture: ");
  lcd.print(soilMoistureValue);

  // Check if soil is dry
  if (soilMoistureValue > DRY_THRESHOLD) {
    digitalWrite(RELAY_PIN, HIGH);  // Turn pump on
    lcd.setCursor(0, 1);
    lcd.print("Pump ON           ");
    Serial.println("Pump ON: Soil is dry.");
  } else {
    digitalWrite(RELAY_PIN, LOW);  // Turn pump off
    lcd.setCursor(0, 1);
    lcd.print("Pump OFF          ");
    Serial.println("Pump OFF: Soil is moist.");
  }

  delay(1000);  // Wait for 1 second before the next reading
}
```

#### Code Explanation:
- **Library Inclusions**: Uses `Wire` and `LiquidCrystal_I2C` libraries to control the LCD via I2C.
- **Pin Definitions**: Defines pins for soil moisture sensor and relay.
- **LCD Initialization**: Initializes the LCD and prints “Smart Irrigation” on startup.
- **Main Loop**:
  - Reads the soil moisture value, prints it on the LCD, and activates the pump based on the threshold.
  - Displays the pump status (ON/OFF) on the LCD.

---

### 5. Working Principle
- The soil moisture sensor measures the soil’s moisture level and outputs an analog signal.
- The Arduino reads this signal and compares it to a predefined threshold to decide when to activate the pump.
- The LCD display provides real-time feedback, showing the moisture level and pump status.
- This setup ensures efficient water usage by activating the pump only when the soil is dry.

---

### 6. Testing and Calibration
1. **Calibration**: Place the soil moisture sensor in wet and dry soil to record the corresponding analog values. Adjust the `DRY_THRESHOLD` based on these readings.
2. **Testing**: Test the pump activation with different soil moisture values, checking that the LCD displays accurate feedback.
3. **Adjustments**: Modify the threshold or delay settings if needed to match watering frequency to your requirements.

---

### 7. Future Enhancements
- **Mobile Connectivity**: Integrate a Wi-Fi or Bluetooth module to remotely monitor soil moisture and control the pump.
- **Enhanced Display**: Use a larger display to show additional parameters, such as temperature or humidity.
- **Battery Backup**: Implement a backup power supply to maintain functionality during power outages.

---

### 8. Conclusion
This smart irrigation system combines automation with real-time monitoring for efficient plant watering. The LCD display adds an extra layer of usability by providing clear feedback on soil moisture and pump status. This project is an excellent example of integrating various sensors and components to create a functional, user-friendly system.
