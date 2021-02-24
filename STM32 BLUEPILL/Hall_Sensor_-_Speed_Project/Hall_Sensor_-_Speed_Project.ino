float rev=0; //Deklarasi nilai variabel rev = 0
float rpm; //Deklarasi Variabel
float oldtime=0; //Deklarasi nilai variabel oldtime = 0      
float time; //Deklarasi Variabel time
float Speed = 0; //Deklarasi nilai variabel Speed = 0
float Kilometer = 0;

float rev1=0; //Deklarasi nilai variabel rev = 0
float rpm1; //Deklarasi Variabel
float oldtime1=0; //Deklarasi nilai variabel oldtime = 0      
float Speed1 = 0; //Deklarasi nilai variabel Speed = 0
float Kilometer1 = 0;

void isr()          //interrupt service routine
{
rev++; //Penambahan nilai variabel setiap interupsi

}
void isr1()          //interrupt service routine
{
rev1++;
}

void setup()
{
//pinMode(PA11 ,INPUT);// Mendeklarasikan PIN PA11 pada kondidi HIGH
pinMode(PA7, INPUT);
pinMode(PA6, INPUT);
attachInterrupt(digitalPinToInterrupt(PA7),isr,RISING);  //Memasang interupsi
attachInterrupt(digitalPinToInterrupt(PA6),isr1,RISING);  //Memasang interupsi
Serial.begin(9600); //Untuk menampilkan diserial monitor

}

void loop()
{
delay(2000);// Penundaan 2 detik
detachInterrupt(digitalPinToInterrupt(PA7)); //Data menghitung ulang interupsi

time=millis() - oldtime; //waktu sekarang dikurang waktu sebelumnya
rpm = (rev/time)*60000; //menghitung semua
oldtime = millis();    //Menyimpan waktu saat ini
rev = 0;
Speed = (rpm*2*3.14*0.3)/60;
Kilometer = Speed*3,6;

detachInterrupt(digitalPinToInterrupt(PA6)); //Data menghitung ulang intrupsi
time=millis() - oldtime1; //waktu sekarang dikurang waktu sebelumnya
rpm1 = (rev1/time)*60000; //menghitung semua
oldtime1 = millis();    //Menyimpan waktu saat ini
rev1 = 0;
Speed1 = (rpm1*2*3.14*0.3)/60;
Kilometer1 = Speed1*3,6;

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

  Serial.println("-------------"); //Menampilkan ----- diserial monitor 
  Serial.print("RPM1 : "); //Menampilkan RPM diserial monitor
  Serial.println(rpm1); //Menampilkan nilai rpm di serial monitor
  Serial.println("-------------"); //Menampilkan ----- diserial monitor 
  Serial.print("Speed1 : "); //Menampilkan Speed diserial monitor
  Serial.print(Speed1); //Menampilkan nilai rpm di serial monitor
  Serial.println(" m/s"); //Menampilkan Speed diserial monitor
  Serial.print("Kilometer1 : "); //Menampilkan Speed diserial monitor
  Serial.print(Kilometer1); //Menampilkan nilai Speed diserial monitor
  Serial.println(" Km/jam"); //Menampilkan Speed diserial monitor
  Serial.println("\n\n"); //Menampilkan Spasi 2x ke bawah diserial monitor

  attachInterrupt(PA7,isr,RISING); //interrupt akan dieksekusi jika terjadi perubahan nilai pembacaan dari LOWke HIGH( dieksekusi 1 kali pas terjadi perubahan )
  attachInterrupt(PA6,isr1,RISING);


}
