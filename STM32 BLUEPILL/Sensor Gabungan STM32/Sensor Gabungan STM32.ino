#define Volt PB1
#define Arus PB0
#define Suhu PA7
//#define Suhu PA6
//Defenisi Sensor Hall Effect
#define Hall_Effect_1 PB12
#define Hall_Effect_2 PB13
#define Hall_Effect_3 PB14

unsigned long oldtime = 0, oldtime1 = 0, oldtime2 = 0, oldtime3 = 0, oldtime4 = 0, oldtime5 = 0, oldtime6 = 0;
unsigned long interval = 1000, interval1 = 1000, interval2 = 1000, interval3 = 1000, interval4 = 1000, interval5 = 2000, interval6 = 1000;

//Deklarasi Sensor tegangan
float Vstm; // tegangan terbaca pada stm32 antara 0-3.3V
float Vreal; // tegangan sesungguhnya yaitu antara 0-60V
float nilai; // nilai bit terbaca
float V = 0;

//Deklarasi Sensor Arus
int sensitivitas = 66; //tegantung sensor arus yang digunakan, yang ini 30A
int teganganoffset = 2495; //nilai pembacaan offset saat tidak ada arus yang lewat
int nilaiadc = 00;
double tegangan = 00;
double I = 00;

//Deklarasi Variabel Daya
float P = 0;

//Deklarasi Sensor suhu
float val = 0;
float mv = 0;
float T = 0;

//Deklarasi Sensor Hall
int rev = 0; //Deklarasi nilai variabel rev = 0
int mag = 0; //Deklarasi nilai variabel rev = 0
float rpm; //Deklarasi Variabel
float timeold = 0; //Deklarasi nilai variabel oldtime = 0      
float Speed = 0; //Deklarasi nilai variabel Speed = 0
float rotasi;
float time; //Deklarasi Variabel time
float v = 0;

//Deklarasi Energi yang yang terpakai
float E = 0;
int waktu = 0;

float sdata1 = 0; // tegangan
float sdata2 = 0; // arus
float sdata3 = 0; // daya
float sdata4 = 0; // suhu
float sdata5 = 0; // kecepatan
float sdata6 = 0; // energi

String Kirim_Data;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(115200);
  pinMode(PB12, INPUT);
  pinMode(PB13, INPUT);
  pinMode(PB14, INPUT);
  attachInterrupt(digitalPinToInterrupt(PB12),isr,RISING);  //Memasang interupsi
  attachInterrupt(digitalPinToInterrupt(PB13),isr,RISING);  //Memasang interupsi
  attachInterrupt(digitalPinToInterrupt(PB14),isr,RISING);  //Memasang interupsi
  delay(100);

}

void Sensor_Tegangan(){
  if((millis() - oldtime1) >= interval1){
    nilai=analogRead(Volt); // pembacaan pin
    Vstm=((nilai/4095)*3.3);
    Vreal = Vstm * (726+38.2)/38.2;
    V = Vreal;
    oldtime1 = millis();
  }
}

void Sensor_Arus(){
  if((millis() - oldtime2) >= interval2){
    nilaiadc = analogRead(Arus);
    tegangan = (nilaiadc / 4095.0) * 3300;
    I = ((tegangan - teganganoffset) / sensitivitas);
    if(I < 0){
      I = 0;
    }
    oldtime2 = millis();
  }
}

void Daya(){
  if((millis() - oldtime3) >= interval3){
    Sensor_Tegangan();
    Sensor_Arus();
    P = I*V;
    oldtime3 = millis();
  }
}

void Sensor_Temperatur(){
  if((millis() - oldtime4) >= interval4){
    //Data sensor suhu
    val = analogRead(Suhu);
    mv = ( val/4095.0)*3300;
    T = mv/10;
    oldtime4 = millis();
  }
}

void isr()          //interrupt service routine
{
  mag++; //Penambahan nilai variabel setiap interupsi
  rev = mag/3;
  if(rev > 24){
    mag = 0 ;
    rotasi++;
  }
  
}

void Sensor_Kecepatan(){
  if((millis() - oldtime5) >= interval5){
    detachInterrupt(digitalPinToInterrupt(PB12)); //Data menghitung ulang interupsi
    detachInterrupt(digitalPinToInterrupt(PB13)); //Data menghitung ulang interupsi
    detachInterrupt(digitalPinToInterrupt(PB14)); //Data menghitung ulang interupsi
    time=millis() - timeold; //waktu sekarang dikurang waktu sebelumnya
    rpm = 60000.0/time*rotasi; //menghitung semua
    timeold = millis();    //Menyimpan waktu saat ini
    rotasi = 0;
    rev = 0;
    Speed = (rpm*2*3.14*0.3)/60;
    v = Speed*3.6;
  
    attachInterrupt(PB12,isr,RISING); //interrupt akan dieksekusi jika terjadi perubahan nilai pembacaan dari LOWke HIGH( dieksekusi 1 kali pas terjadi perubahan )
    attachInterrupt(PB13,isr,RISING); //interrupt akan dieksekusi jika terjadi perubahan nilai pembacaan dari LOWke HIGH( dieksekusi 1 kali pas terjadi perubahan )
    attachInterrupt(PB14,isr,RISING); //interrupt akan dieksekusi jika terjadi perubahan nilai pembacaan dari LOWke HIGH( dieksekusi 1 kali pas terjadi perubahan )
    oldtime5 = millis();
  }
}

void Energi(){
  if((millis() - oldtime6) >= interval6){
    Daya();
    if(millis() == 3600000){
      waktu++;
    }
    E = (P/1000)*waktu;
    oldtime6 = millis();
  }
  waktu = 0;
}

void serialData() {
  Sensor_Tegangan();
  Sensor_Arus();
  Daya();
  Sensor_Temperatur();
  Sensor_Kecepatan();
  Energi();
   
  sdata1 = V;
  sdata2 = I;
  sdata3 = P;
  sdata4 = T;
  sdata5 = v;
  sdata6 = E;
  
  Kirim_Data = String(sdata1) + "," + String(sdata2) + "," + String(sdata3) + ","  + String(sdata4) + "," + String(sdata5) + "," + String(sdata6); 
  Serial2.println(Kirim_Data );
  Serial.println("----------------------");
  Serial.print("Tegangan V = ");
  Serial.println(sdata1 );
  Serial.print("Arus I = ");
  Serial.println(sdata2 );
  Serial.print("Daya P = ");
  Serial.println(sdata3 );
  Serial.print("Temperatur T = ");
  Serial.println(sdata4 );
  Serial.print("Kecepatan v = ");
  Serial.println(sdata5 );
  Serial.print ("Energi E = ");
  Serial.println(sdata6 );
  Serial.println("----------------------");
  
}

void loop() {
  // put your main code here, to run repeatedly
  if((millis() - oldtime) >= interval){
    serialData();
    oldtime = millis();
  }
}