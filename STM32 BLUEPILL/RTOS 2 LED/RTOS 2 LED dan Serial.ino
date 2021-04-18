#include <MapleFreeRTOS821.h>
#define Led_Kuning PB0
#define Led_Merah PB11
 
void tugas1(void *pvParameters) {
  for (;;) {
      pinMode(Led_Kuning, OUTPUT);
      vTaskDelay(1000);
      digitalWrite(Led_Kuning, HIGH);
      vTaskDelay(1000);
      digitalWrite(Led_Kuning, LOW);
  }
}
 
void tugas2(void *pvParameters) {
  for (;;) {
      pinMode(Led_Merah, OUTPUT);
      vTaskDelay(200);
      digitalWrite(Led_Merah, HIGH);
      vTaskDelay(200);
      digitalWrite(Led_Merah, LOW);
  }
}

void tugas3(void *pvParameters){
  int detik = 0;
  int menit = 0;
  for (;;) {
    detik++;
    Serial.print ("Durasi Program Berjalan : ");
    Serial.print (menit);
    Serial.print (" menit ");
    Serial.print (detik);
    Serial.println (" detik");
    if (detik >= 59){
       menit++;
       detik = -1;
    }
    vTaskDelay(1000); 
  }  
}
 
void setup() {
Serial.begin(9600);
  xTaskCreate(tugas1,"Led Kuning",
              configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY + 2,NULL);
  xTaskCreate(tugas2,"Led Merah",
              configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY + 2,NULL);
  xTaskCreate(tugas3,"Print di Serial Monitor",
              configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY + 2,NULL); 
  vTaskStartScheduler();
}
 
void loop() {
}

//https://how2electronics.com/how-to-use-freertos-for-stm32f103c8-in-arduino-ide/
//https://circuitdigest.com/microcontroller-projects/arduino-freertos-tutorial1-creating-freertos-task-to-blink-led-in-arduino-uno
