//PENDEKLARASIAN PINOUT PWM KENDALI MOSFET
const int Q1H = PA0; // MOSFET 1 TYPE MOSFET HIGH SIDE (PHASA U)
const int Q1L = PA1; // MOSFET 2 TYPE MOSFET LOW SIDE  (PHASA U)
const int Q2H = PB6; // MOSFET 3 TYPE MOSFET HIGH SIDE (PHASA V)
const int Q2L = PB7; // MOSFET 4 TYPE MOSFET LOW SIDE  (PHASA V)
const int Q3H = PB8; // MOSFET 5 TYPE MOSFET HIGH SIDE (PHASA W)
const int Q3L = PB9; // MOSFET 6 TYPE MOSFET LOW SIDE  (PHASA W)

//DEKLARASI PINOUT HALL EFFECT SENSOR
const int S1 = PB12; 
const int S2 = PB13;
const int S3 = PB14;

//DEKLARASI PINOUT PEDAL & PINOUT MAJU MUNDUR
const int Pd = PB0; // PINUOT PEDAL
const int St = PA3; // PINOUT MAJU MUNDUR
    
// DEKLARASI VARIABEL STATE
int buttonSt = 0;
int NilaiPedal;
int Speed, Forward, Backward;
int Hall_U, Hall_V, Hall_W; 
int U, V, W;
String H;
    
void setup() {
   pinMode(Q1H, OUTPUT); // INISIALISASI YANG SEBAGAI OUTPUT
   pinMode(Q1L, OUTPUT);
   pinMode(Q2H, OUTPUT);
   pinMode(Q2L, OUTPUT);
   pinMode(Q3H, OUTPUT);
   pinMode(Q3L, OUTPUT);
   pinMode(Pd, INPUT); // INISIALISASI YANG SEBAGAI INPUT
   pinMode(St, INPUT);
   pinMode(S1, INPUT); 
   pinMode(S2, INPUT);
   pinMode(S3, INPUT);  
   Serial.begin(9600); //MENGHUBUNGKAN SERIAL KOMUNKASI KE LAPTOP DENGAN BAUD RATE 9600
   delay(100);
}
     
void loop() {
   NilaiPedal = analogRead(Pd);
   Hall_U = digitalRead(S1);
   Hall_V = digitalRead(S2);
   Hall_W = digitalRead(S3);
   buttonSt = digitalRead(St);
    
   NilaiPedal = map(NilaiPedal, 179, 857, 0, 255);
   if (NilaiPedal >= 256){NilaiPedal = 255;} //Kalibrasi Nilai Pedal
   if (NilaiPedal <= -1) {NilaiPedal = 0;}   //Kalibrasi Nilai Pedal
   Speed = 255 - NilaiPedal;
    
   if(Hall_U == 1){U = 1;} else{U = 0;}
   if(Hall_V == 1){V = 1;} else{V = 0;}
   if(Hall_W == 1){W = 1;} else{W = 0;}
   H = String(U) + String(V) + String(W);
   Serial.println("\t |\t Hall Effect Sensor : " + H + "\t|\t" + "NilaiPedal : " + String(NilaiPedal) + " %" + "\t|\t" + "Gas : " + String(Speed) + " PWM");
     
   if(buttonSt == LOW){  //Kondisi Mobil Maju
      Maju();
      Rusak();
   }
   if(buttonSt == HIGH){ // Kondisi Mobil Mundur
      Mundur();
      Rusak();
   }
}

void Maju(){ 
   //PUTARAN SEARAH JARUM JAM
   if(H == "101"){ // Step 1 : 101
     analogWrite(Q1H, Speed);    // MENGAKTIFKAN MOSFET 1 SEBAGAI PWM
     digitalWrite(Q1L, LOW);     // MENONAKTIFKAN MOSFET 2 
     digitalWrite(Q2H, LOW);     // MENONAKTIFKAN MOSFET 3
     digitalWrite(Q2L, HIGH);    // MENGAKTIFKAN MOSFET 4 SEBAGAI GROUND
     digitalWrite(Q3H, LOW);     // MENONAKTIFKAN MOSFET 5
     digitalWrite(Q3L, LOW);     // MENONAKTIFKAN MOSFET 6 NC
     Serial.print("Step1 : " + H);
     delay(100);
   }
   if(H == "001"){ // Step 2 : 001
     analogWrite(Q1H, Speed);     // MENGAKTIFKAN MOSFET 1 SEBAGAI PWM
     digitalWrite(Q1L, LOW);      // MENONAKTIFKAN MOSFET 2 
     digitalWrite(Q2H, LOW);      // MENONAKTIFKAN MOSFET 3 NC
     digitalWrite(Q2L, LOW);      // MENONAKTIFKAN MOSFET 4 
     digitalWrite(Q3H, LOW);      // MENONAKTIFKAN MOSFET 5
     digitalWrite(Q3L, HIGH);     // MENGAKTIFKAN MOSFET 6 SEBAGAI GROUND
     Serial.print("Step2 : " + H);
     delay(100);
   }
   if(H == "011"){ // Step 3 : 011
     digitalWrite(Q1H, LOW);      // MENONAKTIFKAN MOSFET 1 NC
     digitalWrite(Q1L, LOW);      // MENONAKTIFKAN MOSFET 2
     analogWrite(Q2H, Speed);     // MENGAKTIFKAN MOSFET 3 SEBAGAI PWM
     digitalWrite(Q2L, LOW);      // MENONAKTIFKAN MOSFET 4
     digitalWrite(Q3H, LOW);      // MENONAKTIFKAN MOSFET 5 
     digitalWrite(Q3L, HIGH);     // MENGAKTIFKAN MOSFET 6 SEBAGAI GROUND
     Serial.print("Step3 : " + H);
     delay(100);
   }
   if(H == "010"){ // Step 4 : 010
     digitalWrite(Q1H, LOW);      // MENONAKTIFKAN MOSFET 1
     digitalWrite(Q1L, HIGH);     // MENGAKTIFKAN MOSFET 2 SEBAGAI GROUND
     analogWrite(Q2H, Speed);     // MENGAKTIFKAN MOSFET 3 SEBAGAI PWM
     digitalWrite(Q2L, LOW);      // MENONAKTIFKAN MOSFET 4
     digitalWrite(Q3H, LOW);      // MENONAKTIFKAN MOSFET 5 NC
     digitalWrite(Q3L, LOW);      // MENONAKTIFKAN MOSFET 6
     Serial.print("Step4 : " + H);
     delay(100);
   }
   if(H == "110"){ // Step 5 : 110
     digitalWrite(Q1H, LOW);     // MENONAKTIFKAN MOSFET 1
     digitalWrite(Q1L, HIGH);    // MENGAKTIFKAN MOSFET 2 SEBAGAI GROUND
     digitalWrite(Q2H, LOW);     // MENONAKTIFKAN MOSFET 3 NC
     digitalWrite(Q2L, LOW);     // MENONAKTIFKAN MOSFET 4
     analogWrite(Q3H, Speed);    // MENGAKTIFKAN MOSFET 5 SEBAGAI PWM
     digitalWrite(Q3L, HIGH);    // MENONAKTIFKAN MOSFET 6
     Serial.print("Step5 : " + H);
     delay(100);
   }
   if(H == "100"){ // Step 6 : 100
     digitalWrite(Q1H, LOW);     // MENONAKTIFKAN MOSFET 1 NC
     digitalWrite(Q1L, LOW);     // MENONAKTIFKAN MOSFET 2
     digitalWrite(Q2H, LOW);     // MENONAKTIFKAN MOSFET 3
     digitalWrite(Q2L, HIGH);    // MENGAKTIFKAN MOSFET 4 SEBAGAI GROUND
     analogWrite(Q3H, Speed);    // MENGAKTIFKAN MOSFET 5 SEBAGAI PWM
     digitalWrite(Q3L, LOW);     // MENONAKTIFKAN MOSFET 6
     Serial.print("Step6 : " + H);
     delay(100);
   }
}

void Mundur(){ 
   //PUTARAN TIDAK SEARAH JARUM JAM
   if(H == "100"){ // Step 1 : 100
     digitalWrite(Q1H, LOW);      // MENONAKTIFKAN MOSFET 1 NC
     digitalWrite(Q1L, LOW);      // MENONAKTIFKAN MOSFET 2 
     digitalWrite(Q2H, LOW);      // MENGAKTIFKAN MOSFET 3 SEBAGAI GROUND
     digitalWrite(Q2L, HIGH);     // MENONAKTIFKAN MOSFET 4
     digitalWrite(Q3H, LOW);      // MENONAKTIFKAN MOSFET 5
     analogWrite(Q3L, Speed);     // MENGAKTIFKAN MOSFET 6 SEBAGAI PWM
     Serial.print("Step1 : " + H);
     delay(100);
   }
   if(H == "110"){ // Step 2 : 110
     analogWrite(Q1H, Speed);     // MENGAKTIFKAN MOSFET 1 SEBAGAI PWM
     digitalWrite(Q1L, LOW);      // MENONAKTIFKAN MOSFET 2 
     digitalWrite(Q2H, LOW);      // MENONAKTIFKAN MOSFET 3 NC
     digitalWrite(Q2L, LOW);      // MENONAKTIFKAN MOSFET 4 
     digitalWrite(Q3H, LOW);      // MENONAKTIFKAN MOSFET 5
     digitalWrite(Q3L, HIGH);     // MENGAKTIFKAN MOSFET 6 SEBAGAI GROUND
     Serial.print("Step2 : " + H);
     delay(100);
   }
   if(H == "010"){ // Step 3 : 010
     analogWrite(Q1H, Speed);     // MENGAKTIFKAN MOSFET 1 SEBAGAI PWM
     digitalWrite(Q1L, LOW);      // MENONAKTIFKAN MOSFET 2
     digitalWrite(Q2H, LOW);      // MENONAKTIFKAN MOSFET 3
     digitalWrite(Q2L, HIGH);     // MENGAKTIFKAN MOSFET 4 SEBAGAI GROUND
     digitalWrite(Q3H, LOW);      // MENONAKTIFKAN MOSFET 5 NC
     digitalWrite(Q3L, LOW);      // MENONAKTIFKAN MOSFET 6
     Serial.print("Step3 : " + H);
     delay(100);
   }
   if(H == "011"){ // Step 4 : 011
     digitalWrite(Q1H, LOW);      // MENONAKTIFKAN MOSFET 1 NC
     digitalWrite(Q1L, LOW);      // MENONAKTIFKAN MOSFET 2
     digitalWrite(Q2H, LOW);      // MENONAKTIFKAN MOSFET 3
     digitalWrite(Q2L, HIGH);     // MENGAKTIFKAN MOSFET 4 SEBAGAI GROUND
     analogWrite(Q3H, Speed);     // MENGAKTIFKAN MOSFET 5 SEBAGAI PWM
     digitalWrite(Q3L, LOW);      // MENONAKTIFKAN MOSFET 6
     Serial.print("Step4 : " + H);
     delay(100);
   }
   if(H == "001"){ // Step 5 : 001
     digitalWrite(Q1H, LOW);     // MENONAKTIFKAN MOSFET 1
     digitalWrite(Q1L, HIGH);    // MENGAKTIFKAN MOSFET 2 SEBAGAI GROUND
     digitalWrite(Q2H, LOW);     // MENONAKTIFKAN MOSFET 3 NC
     digitalWrite(Q2L, LOW);     // MENONAKTIFKAN MOSFET 4
     analogWrite(Q3H, Speed);    // MENGAKTIFKAN MOSFET 5 SEBAGAI PWM
     digitalWrite(Q3L, HIGH);    // MENONAKTIFKAN MOSFET 6
     Serial.print("Step5 : " + H);
     delay(100);
   }
   if(H == "101"){ // Step 6 : 101
     digitalWrite(Q1H, LOW);      // MENONAKTIFKAN MOSFET 1
     digitalWrite(Q1L, HIGH);     // MENGAKTIFKAN MOSFET 2 SEBAGAI GROUND
     analogWrite(Q2H, Speed);     // MENGAKTIFKAN MOSFET 3 SEBAGAI PWM
     digitalWrite(Q2L, LOW);      // MENONAKTIFKAN MOSFET 4
     digitalWrite(Q3H, LOW);      // MENONAKTIFKAN MOSFET 5 NC
     digitalWrite(Q3L, LOW);      // MENONAKTIFKAN MOSFET 6
     Serial.print("Step6 : " + H);
     delay(100);
   }
}

void Rusak(){ 
   // KENDALI HALL EFFECT SENSOR RUSAK
   if(H == "111"){ // Bebas : 111
     digitalWrite(Q1H, LOW);      // Mosfet High Side
     digitalWrite(Q1L, HIGH);     // Mosfet Low Side
     digitalWrite(Q2H, LOW);      // Mosfet High Side
     digitalWrite(Q2L, HIGH);     // Mosfet Low Side
     digitalWrite(Q3H, LOW);      // Mosfet High Side
     digitalWrite(Q3L, HIGH);     // Mosfet Low Side
     Serial.print("Hall Rusak 1 111  ");
     delay(100);
   }
   if(H == "000"){ // Bebas : 000
     digitalWrite(Q1H, LOW);      // Mosfet High Side
     digitalWrite(Q1L, HIGH);     // Mosfet Low Side
     digitalWrite(Q2H, LOW);      // Mosfet High Side
     digitalWrite(Q2L, HIGH);     // Mosfet Low Side
     digitalWrite(Q3H, LOW);      // Mosfet High Side
     digitalWrite(Q3L, HIGH);     // Mosfet Low Side
     Serial.print("Hall Rusak 2  000  ");
     delay(100);
   }
}