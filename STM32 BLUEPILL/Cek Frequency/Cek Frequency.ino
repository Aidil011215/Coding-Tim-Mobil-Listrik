/* ini merupakan program pengecekan frequency dan duty cycle 
 * menggunakan STM32 bluepill, sampai ke 32 kHz pembacaan jadi tidak stabil  
*/
#define inpfrek PB10

int ontime,offtime,duty;
float freq,period;

void setup() {
pinMode(PB10, INPUT);
Serial.begin(115200);
}

void loop() {
   ontime = pulseIn(inpfrek,HIGH); // pulseIn adalah fungsi untuk menghitung lama waktu dalam mikrodetik
   offtime = pulseIn(inpfrek,LOW);
   period = ontime+offtime;
   freq = 1000000.0/period; // frekuensi = 1 detik / periode
   duty = (ontime/period)*100; 
  Serial.println(duty);
  Serial.println(freq);
  delay(1);
}
