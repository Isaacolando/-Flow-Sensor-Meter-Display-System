#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ─────────────────────────────────────────────
// 📟 OLED CONFIG
// ─────────────────────────────────────────────
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ─────────────────────────────────────────────
// 🔌 PINS (ESP32)
// ─────────────────────────────────────────────
#define FLOW_SENSOR 27
#define BUTTON_PIN 25
#define RELAY_PIN 26
#define LED_PIN 33

// ─────────────────────────────────────────────
// ⚙️ FLOW + COST
// ─────────────────────────────────────────────
const float CALIBRATION_FACTOR = 7.5;
const float COST_PER_ML = 12.0 / 80.0;

// ─────────────────────────────────────────────
// 📊 VARIABLES
// ─────────────────────────────────────────────
volatile int pulseCount = 0;

float totalVolume_ml = 0;
float flowRate_Lpm = 0;
float cost_KSh = 0;

bool dispensing = false;

unsigned long previousMillis = 0;
unsigned long lastPress = 0;

// ─────────────────────────────────────────────
// ⚡ FLOW INTERRUPT
// ─────────────────────────────────────────────
void IRAM_ATTR pulseISR() {
  if (dispensing) {
    pulseCount++;
  }
}

// ─────────────────────────────────────────────
// 🚀 SETUP
// ─────────────────────────────────────────────
void setup() {
  Serial.begin(115200);

  pinMode(FLOW_SENSOR, INPUT_PULLUP);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(LED_PIN, LOW);

  attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR), pulseISR, RISING);

  // I2C for OLED
  Wire.begin(21, 22);

  // OLED init
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found!");
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0, 0);
  display.println("Flow System");
  display.println("Initializing...");
  display.display();
  delay(2000);
}

// ─────────────────────────────────────────────
// 🔁 LOOP
// ─────────────────────────────────────────────
void loop() {

  // 🔘 BUTTON TOGGLE
  if (digitalRead(BUTTON_PIN) == LOW && millis() - lastPress > 300) {
    lastPress = millis();
    dispensing = !dispensing;

    if (dispensing) {
      digitalWrite(RELAY_PIN, HIGH);
      digitalWrite(LED_PIN, HIGH);
    } else {
      digitalWrite(RELAY_PIN, LOW);
      digitalWrite(LED_PIN, LOW);

      totalVolume_ml = 0;
      flowRate_Lpm = 0;
      cost_KSh = 0;
      pulseCount = 0;
    }
  }

  // 📊 CALCULATION EVERY 1s
  if (millis() - previousMillis >= 1000) {

    detachInterrupt(digitalPinToInterrupt(FLOW_SENSOR));
    int pulses = pulseCount;
    pulseCount = 0;
    attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR), pulseISR, RISING);

    previousMillis = millis();

    if (dispensing) {

      flowRate_Lpm = pulses / CALIBRATION_FACTOR;

      float ml_per_sec = (flowRate_Lpm * 1000.0) / 60.0;
      totalVolume_ml += ml_per_sec;

      cost_KSh = totalVolume_ml * COST_PER_ML;
    } else {
      flowRate_Lpm = 0;
    }

    displayData();
  }
}

// ─────────────────────────────────────────────
// 📟 OLED DISPLAY
// ─────────────────────────────────────────────
void displayData() {

  display.clearDisplay();
  display.setCursor(0, 0);

  if (!dispensing) {
    display.println("SYSTEM OFF");
    display.println("Rate: 12KSh/80ml");
    display.println("Press Button");
    display.display();
    return;
  }

  display.println("FLOW SYSTEM");
  display.println("----------------");

  display.print("Vol: ");
  display.print(totalVolume_ml, 0);
  display.println(" ml");

  display.print("Flow: ");
  display.print(flowRate_Lpm, 2);
  display.println(" L/min");

  display.print("Cost: ");
  display.print(cost_KSh, 2);
  display.println(" KSh");

  display.display();
}