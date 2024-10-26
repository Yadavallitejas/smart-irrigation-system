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