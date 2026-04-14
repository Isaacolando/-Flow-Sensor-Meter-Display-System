// ESP32 Flow Sensor Dispensing System - Embedded Systems Lab
// Dispenses at least 850 ml with real-time flow rate, volume & cost

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pin definitions for ESP32
const int sensorPin = 27;     // YF-S201 Flow sensor (interrupt)
const int buttonPin = 14;     // Start/Stop button
const int pumpPin   = 26;     // Relay for pump/valve control

// I2C LCD (address usually 0x27 or 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);

volatile int pulseCount = 0;
float totalVolume_ml = 0.0;
float flowRate_Lpm = 0.0;
float cost_KSh = 0.0;
bool dispensing = false;           // Dispensing state
unsigned long previousMillis = 0;
const float calibrationFactor = 7.5;  // For YF-S201: pulses per liter/min

// Interrupt Service Routine (must be in IRAM for ESP32)
void IRAM_ATTR pulseISR() {
  pulseCount++;
}

void setup() {
  Serial.begin(115200);
  
  // Pin setup
  pinMode(sensorPin, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(pumpPin, OUTPUT);
  digitalWrite(pumpPin, LOW);   // Pump OFF initially
  
  attachInterrupt(digitalPinToInterrupt(sensorPin), pulseISR, RISING);
  
  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("Flow Dispensing");
  lcd.setCursor(0,1);
  lcd.print("System Ready");
  delay(2000);
  
  Serial.println("ESP32 Flow Meter Ready - Target: 850 ml");
}

void loop() {
  unsigned long currentMillis = millis();

  // Button toggle for start/stop dispensing
  if (digitalRead(buttonPin) == LOW) {
    delay(200); // debounce
    if (digitalRead(buttonPin) == LOW) {
      dispensing = !dispensing;
      digitalWrite(pumpPin, dispensing ? HIGH : LOW);
      lcd.clear();
      lcd.print(dispensing ? "Dispensing..." : "Stopped");
      delay(500);
    }
  }

  // Update every 1 second
  if (currentMillis - previousMillis >= 1000) {
    previousMillis = currentMillis;

    if (dispensing) {
      // Calculate flow rate
      flowRate_Lpm = (float)pulseCount / calibrationFactor;
      
      // Volume added in last second
      float ml_this_sec = (flowRate_Lpm * 1000.0) / 60.0;
      totalVolume_ml += ml_this_sec;
      
      // Cost: 12 KSh / 80 ml = 0.15 KSh per ml
      cost_KSh = totalVolume_ml * 0.15;
      
      // Auto-stop at 850 ml (or slightly over)
      if (totalVolume_ml >= 850.0) {
        dispensing = false;
        digitalWrite(pumpPin, LOW);
        lcd.clear();
        lcd.print("Target Reached!");
        lcd.setCursor(0,1);
        lcd.print("850 ml Done");
      }
    } else {
      flowRate_Lpm = 0.0;   // No flow when stopped
    }

    pulseCount = 0;   // Reset for next second

    // Display on LCD (scrolling info)
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Vol:");
    lcd.print(totalVolume_ml, 0);
    lcd.print("ml  ");

    lcd.setCursor(0, 1);
    lcd.print("Flow:");
    lcd.print(flowRate_Lpm, 1);
    lcd.print("L/m");

    // Serial output (for debugging + full info)
    Serial.printf("Volume: %.0f ml | Flow: %.1f L/min | Cost: KSh %.1f | Dispensing: %s\n",
                  totalVolume_ml, flowRate_Lpm, cost_KSh, dispensing ? "YES" : "NO");
  }
}