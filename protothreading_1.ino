#include "Streaming.h"
#include "cpu1.h"

TaskHandle_t TaskA;

void setup() {
  Serial.begin(115200); //Serial line activation
  delay(100); //Start-up delay

  f001[0] = 1000; f001[1] = 50;
  f002[0] = 1000; f002[1] = 30;
  
  xTaskCreatePinnedToCore(
    SchedulerMain,
    "process1",
    1000,
    NULL,
    1,
    &TaskA,
    1);
  
}

void loop() {
  while(true) {}
}
