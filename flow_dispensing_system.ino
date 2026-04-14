// ESP32 Flow Sensor Dispensing System - Embedded Systems Lab
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int sensorPin = 27;     // Flow sensor
const int buttonPin = 14;     // Start/Stop button
const int pumpPin   = 26;     // Relay for pump

LiquidCrystal_I2C lcd(0x27, 16, 2);

volatile int pulseCount = 0;
float totalVolume_ml = 0.0;
float flowRate_Lpm = 0.0;
float cost_KSh = 0.0;
bool dispensing = false;
unsigned long previousMillis = 0;
const float calibrationFactor = 7.5;

void IRAM_ATTR pulseISR() {
  pulseCount++;
}

void setup() {
  Serial.begin(115200);
  pinMode(sensorPin, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(pumpPin, OUTPUT);
  digitalWrite(pumpPin, LOW);

  attachInterrupt(digitalPinToInterrupt(sensorPin), pulseISR, RISING);

  lcd.init();
  lcd.backlight();
  lcd.print("Flow Dispensing");
  lcd.setCursor(0,1);
  lcd.print("System Ready");
  delay(2000);
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    delay(200);
    if (digitalRead(buttonPin) == LOW) {
      dispensing = !dispensing;
      digitalWrite(pumpPin, dispensing ? HIGH : LOW);
      lcd.clear();
      lcd.print(dispensing ? "Dispensing..." : "Stopped");
      delay(500);
    }
  }

  if (millis() - previousMillis >= 1000) {
    previousMillis = millis();

    if (dispensing) {
      flowRate_Lpm = (float)pulseCount / calibrationFactor;
      float ml_this_sec = (flowRate_Lpm * 1000.0) / 60.0;
      totalVolume_ml += ml_this_sec;
      cost_KSh = totalVolume_ml * 0.15;

      if (totalVolume_ml >= 850.0) {
        dispensing = false;
        digitalWrite(pumpPin, LOW);
        lcd.clear();
        lcd.print("Target Reached!");
        lcd.setCursor(0,1);
        lcd.print("850 ml Done");
      }
    } else {
      flowRate_Lpm = 0.0;
    }

    pulseCount = 0;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Vol:");
    lcd.print(totalVolume_ml, 0);
    lcd.print("ml");

    lcd.setCursor(0, 1);
    lcd.print("Flow:");
    lcd.print(flowRate_Lpm, 1);
    lcd.print("L/m");

    Serial.printf("Vol: %.0f ml | Flow: %.1f L/min | Cost: KSh %.1f | Disp: %s\n",
                  totalVolume_ml, flowRate_Lpm, cost_KSh, dispensing ? "ON" : "OFF");
  }
}