#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

#define RECV_PIN 27   // пин, к которому подключён OUT TSOP4838

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  Serial.begin(115200);
  irrecv.enableIRIn();  // запускаем приёмник
  Serial.println("IR receiver is ready...");
}

void loop() {
  if (irrecv.decode(&results)) {
    // Выводим raw-данные
    Serial.println("----  Income data");
    Serial.printf("Raw data (%d):\n", results.rawlen);
    for (uint16_t i = 1; i < results.rawlen; i++) {
      unsigned int duration = results.rawbuf[i] * kRawTick; // kRawTick = 2.5 мкс
      Serial.printf("%u ", duration);
    }
    Serial.println();
    Serial.println("HEX code:");
    Serial.println(resultToHumanReadableBasic(&results)); // Печатаем расшифровку
    // Serial.println("Test:");
    // serialPrintUint64(results.value, HEX);
    // Serial.println("!!!!!");

    irrecv.resume(); // ждём следующий сигнал
  }
}