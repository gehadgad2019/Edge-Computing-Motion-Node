#include <Wire.h>
#include <LiquidCrystal_I2C.h> // The LCD library

// Initialize the LCD at standard I2C address 0x27, 20 columns, 4 rows
LiquidCrystal_I2C lcd(0x27, 20, 4); 

const int MPU = 0x68; // MPU6050 I2C address
float rawZ = 0;
float filteredZ = 0;
const float alpha = 0.2; 

void setup() {
  Wire.begin(); 
  
  // 1. Boot up the LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0); // Column 0, Row 0
  lcd.print("Edge Node Active");
  
  // 2. Boot up the Sensor
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
  Wire.write(0);    
  Wire.endTransmission(true);
}

void loop() {
  // Read the Sensor
  Wire.beginTransmission(MPU);
  Wire.write(0x3F); 
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 2, true); 
  rawZ = (Wire.read() << 8 | Wire.read()) / 16384.0; 
  
  // Filter the Data
  filteredZ = (alpha * rawZ) + ((1.0 - alpha) * filteredZ);
  
  // Print Raw Data to Row 1
  lcd.setCursor(0, 1);
  lcd.print("Raw Z: ");
  lcd.print(rawZ, 2); // Print with 2 decimal places
  lcd.print(" g   "); // Extra spaces clear old characters
  
  // Print Filtered Data to Row 2
  lcd.setCursor(0, 2);
  lcd.print("Fil Z: ");
  lcd.print(filteredZ, 2);
  lcd.print(" g   ");

  // Logic: Print alert to Row 3 if threshold crossed
  if (filteredZ > 1.5 || filteredZ < -0.5) {
      lcd.setCursor(0, 3);
      lcd.print("** IMPACT DETECTED **");
      delay(500); // Hold the alert on screen
      lcd.setCursor(0, 3);
      lcd.print("                     "); // Clear the alert
  }
  
  delay(50); 
}