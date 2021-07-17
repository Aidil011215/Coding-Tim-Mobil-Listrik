//Coding untuk mengirim banyak data ke mikrokontroler lain dengan aman

#define Pot1 PB1
#define Pot2 PB0
#define Pot3 PA7
#define Pot4 PA6
#define Pot5 PA5
#define Pot6 PA4

unsigned long oldtime = 0;
unsigned long interval = 100;

float V = 0;
float I = 0;
float P = 0;
float T = 0;
float v = 0;
float E = 0;

float sdata1 = 0; // tegangan
float sdata2 = 0; // arus
float sdata3 = 0; // daya
float sdata4 = 0; // suhu
float sdata5 = 0; // kecepatan
float sdata6 = 0; // energi

String cdata;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); //Serial komunikasi untuk dihubungkan ke laptop/PC dengan baud rate 115200
  Serial3.begin(115200); //Serial komunikasi HardwareSerial dari Serial3 untuk dihubungkan ke mikrokontroler lain pada baud rate 115200
  delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  V = analogRead(Pot2);
  I = analogRead(Pot2);
  P = analogRead(Pot3);
  T = analogRead(Pot4);
  v = analogRead(Pot5);
  E = analogRead(Pot6);
  
  sdata1 = V;
  sdata2 = I;
  sdata3 = P;
  sdata4 = T;
  sdata5 = v;
  sdata6 = E;

   if((millis() - oldtime) >= interval){
    cdata = String(sdata1) + "," + String(sdata2) + "," + String(sdata3) + ","  + String(sdata4) + "," + String(sdata5) + "," + String(sdata6); 
     Serial.println(cdata); //Mengirimkan data ke laptop/PC untuk ditampilkan pada serial monitor
     Serial3.println(cdata); //Mengirimkan data ke mikrokontroler lain melalui Serial Komunikasi HardwareSerial dari Serial3
     oldtime = millis();
   }
   cdata = "";
}