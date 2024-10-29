#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LCD (address, columns, rows)
LiquidCrystal_I2C lcd(0x27, 16, 2);  
const int moistureSensorPin = A0;  // Pin for the moisture sensor
const int relayPin = 7;            // Pin for the relay module

void setup() {
  lcd.init();                      // Initialize the LCD
  lcd.backlight();                 // Turn on the backlight
  pinMode(relayPin, OUTPUT);       // Set relay pin as output
  digitalWrite(relayPin, LOW);     // Ensure the pump is off initially
  Serial.begin(9600);              // Begin serial communication
  lcd.setCursor(0, 0);             // Set cursor position
  lcd.print("System Init...");
  delay(2000);                     // Display message for 2 seconds
  lcd.clear();
}

void loop() {
  int moistureLevel = analogRead(moistureSensorPin);  // Read moisture level
  Serial.print("Moisture Level: ");                   // Debug: print to Serial Monitor
  Serial.println(moistureLevel);

  // Display the current moisture level on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Moisture: ");
  lcd.print(moistureLevel);

  // Moisture threshold logic
  if (moistureLevel > 900) {  // Adjust this threshold based on your sensor
    // Soil is dry
    digitalWrite(relayPin, HIGH);  // Turn the pump on
    lcd.setCursor(0, 1);           // Move to the second line
    lcd.print("Soil: DRY, ON  ");  // Display "Soil: DRY"
    Serial.println("Pump: ON");    // Debug: indicate pump state in Serial Monitor
  } else {
    // Soil is moist
    digitalWrite(relayPin, LOW);   // Turn the pump off
    lcd.setCursor(0, 1);
    lcd.print("Soil: MOIST, OFF   ");  // Display "Soil: MOIST"
    Serial.println("Pump: OFF");   // Debug: indicate pump state in Serial Monitor
  }

  delay(2000);  // Delay for stability
}
