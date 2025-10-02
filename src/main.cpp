#include <Arduino.h>
#include <OneButton.h>

#define LED_PIN 33       // LED ngoài nối GPIO33
#define BUTTON_PIN 32    // Nút nhấn nối GPIO32

OneButton button(BUTTON_PIN, true);

bool ledState = false;
bool blinking = false;
unsigned long lastBlink = 0;

void singleClick() {
  blinking = false;             // tắt nhấp nháy nếu đang bật
  ledState = !ledState;         // đổi trạng thái LED
  digitalWrite(LED_PIN, ledState ? HIGH : LOW);
}

void doubleClick() {
  blinking = !blinking;         // bật/tắt chế độ nhấp nháy
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  button.attachClick(singleClick);
  button.attachDoubleClick(doubleClick);

  Serial.begin(115200);
}

void loop() {
  button.tick();

  if (blinking) {
    unsigned long currentMillis = millis();
    if (currentMillis - lastBlink >= 500) {
      lastBlink = currentMillis;
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState ? HIGH : LOW);
    }
  }
}
