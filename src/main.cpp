#include <Arduino.h>
#include <OneButton.h>

#define LED_PIN 4        // LED rời nối GPIO4
#define BUTTON_PIN 35    // Nút nhấn nối GPIO35

OneButton button(BUTTON_PIN, true);  // true = INPUT_PULLUP

bool ledState = false;
bool blinking = false;
unsigned long lastToggle = 0;
const unsigned long blinkInterval = 500; // 500ms

// ===== Xử lý Single Click =====
void singleClick() {
  blinking = false; // thoát chế độ nhấp nháy nếu đang chạy
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState ? HIGH : LOW);
  Serial.println(ledState ? "LED ON (single click)" : "LED OFF (single click)");
}

// ===== Xử lý Double Click =====
void doubleClick() {
  blinking = !blinking;
  if (!blinking) {
    digitalWrite(LED_PIN, LOW); // thoát nhấp nháy thì tắt LED
    ledState = false;
    Serial.println("Stop blinking (double click)");
  } else {
    Serial.println("Start blinking (double click)");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  button.attachClick(singleClick);
  button.attachDoubleClick(doubleClick);

  Serial.println("Ready: SingleClick = toggle LED, DoubleClick = blink LED");
}

void loop() {
  button.tick();

  if (blinking) {
    unsigned long currentMillis = millis();
    if (currentMillis - lastToggle >= blinkInterval) {
      lastToggle = currentMillis;
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState ? HIGH : LOW);
    }
  }
}
