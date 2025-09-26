// send IR signal
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

// Подключение ИК-светодиода через транзистор к D5 (GPIO14)
const uint16_t kIrLedPin = 14; // D5 на ESP8266 = GPIO14

IRsend irsend(kIrLedPin, 0, 56000);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);  // задаём пин со светодиодом как выход
  Serial.begin(115200);
  irsend.begin();
  Serial.println("IR sender ready (D5 - GPIO14)");
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  uint32_t necCode = 0x20DF10EF; // Пример NEC-кода (кнопка пульта)
  Serial.printf("Отправка NEC кода: 0x%08X\n", necCode);

  irsend.sendNEC(necCode, 32);   // Отправка команды NEC (32 бита)
  digitalWrite(LED_BUILTIN, LOW);
  delay(3000);                   // Повтор каждые 5 секунд
}