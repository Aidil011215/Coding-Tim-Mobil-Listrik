int rotation = 0; //deklarasi nilai rotasi

float mag = 0; //Deklarasi untuk pembacaan nilai magnet 
float rpm; //Deklarasi Variabel
float oldtime = 0; //Deklarasi nilai variabel oldtime = 0      
float time; //Deklarasi Variabel time
float Speed = 0; //Deklarasi nilai variabel Speed = 0
float Kilometer = 0;
float rev; //fungsi untuk menghitung maget

void isr()          //interrupt service routine
{
mag++; //Penambahan nilai variabel setiap interupsi
rev = mag/3;
if(rev > 23){
  rotation = rotation +1;
  mag = 0;
Serial.print("rotasi");
Serial.println(rotation);

}
}

void setup()
{
//pinMode(PA11 ,INPUT);// Mendeklarasikan PIN PA11 pada kondidi HIGH
pinMode(PB12, INPUT);
pinMode(PB13, INPUT);
pinMode(PB14, INPUT);
attachInterrupt(digitalPinToInterrupt(PB12),isr,RISING);//Memasang interupsi
attachInterrupt(digitalPinToInterrupt(PB13),isr,RISING);
attachInterrupt(digitalPinToInterrupt(PB14),isr,RISING);
Serial.begin(9600); //Untuk menampilkan diserial monitor
}

void loop(){
delay(2000);// Penundaan 2 detik
detachInterrupt(digitalPinToInterrupt(PB12)); //Data menghitung ulang interupsi
detachInterrupt(digitalPinToInterrupt(PB13));
detachInterrupt(digitalPinToInterrupt(PB14));

time = millis() - oldtime; //waktu sekarang dikurang waktu sebelumnya
rpm = ((rev/23)+rotation)*60000/time; //menghitung semua
oldtime = millis();    //Menyimpan waktu saat ini
rotation = 0;
rev = 0;
Speed = (rpm*2*3.14*0.3)/60;
Kilometer = Speed*3,6;


  Serial.println("-------------"); //Menampilkan ----- diserial monitor 
  Serial.print("RPM : "); //Menampilkan RPM diserial monitor
  Serial.println(rpm); //Menampilkan nilai rpm di serial monitor
  Serial.println("-------------"); //Menampilkan ----- diserial monitor 
  Serial.print("Speed : "); //Menampilkan Speed diserial monitor
  Serial.print(Speed); //Menampilkan nilai rpm di serial monitor
  Serial.println(" m/s"); //Menampilkan Speed diserial monitor
  Serial.print("Kilometer : "); //Menampilkan Speed diserial monitor
  Serial.print(Kilometer); //Menampilkan nilai Speed diserial monitor
  Serial.println(" Km/jam"); //Menampilkan Speed diserial monitor
  Serial.println("\n\n"); //Menampilkan Spasi 2x ke bawah diserial monitor

  attachInterrupt(PB12,isr,RISING); //interrupt akan dieksekusi jika terjadi perubahan nilai pembacaan dari LOWke HIGH( dieksekusi 1 kali pas terjadi perubahan )
  attachInterrupt(PB13,isr,RISING);
  attachInterrupt(PB14,isr,RISING);
} 
