HardwareTimer pwmtimer3(3);

#define inpfrek PB10
#define outfrek PA7

long int ontime, offtime, duty, x;
float period, freq;

void setup() {
   pinMode(inpfrek, INPUT);
   pinMode(outfrek, PWM);

   pwmtimer3.pause();
   pwmtimer3.setPrescaleFactor(1);
   pwmtimer3.setOverflow(4200);
   /*
      STM32 memiliki 4 timer, masing-masing dengan 4 channel dan resolusi 16 bit, yang artinya bernilai 65535. Nilai ini penting untuk kita, sebagai keputusan resolusi
      seberapa akurat siklus tugas PWM yang dapat dihasilkan. Next, STM32 berjalan pada kecepatan 72MHz. Itu artinya kita akan dapatkan 72,000,000/65535 = 1.098 Hz pada pin PWM.
      
      Dalam hal ini, kita membutuhkan 17 kHz. Jika kita bagi frekuensi dasar mikrokontroler dengan frekuensi yang kita inginkan, kita akan dapatkan nilai overflow. 
      (72,000,000/17,000=+- 4235).
   */
   pwmtimer3.refresh();
   pwmtimer3.resume();

   Serial.begin(115200);
}

void loop() {
   x = 16;
   analogWrite(outfrek, x); //untuk setiap nilai pwm, dutycycle-nya 6%, untuk overflow 4200 -> 16 * 6% = 96%
   ontime = pulseIn(inpfrek,HIGH); // pulseIn adalah fungsi untuk menghitung lama waktu dalam mikrodetik
   offtime = pulseIn(inpfrek,LOW);
   period = ontime + offtime;
   freq = 1000000.0/period; // frekuensi = 1 detik / periode, 1000000 mikrodetik = 1 detik
   duty = (ontime/period)*100; //rumus dutycycle

//Menuliskan Hasil
  Serial.println();
  Serial.print("Pembacaan - x = ");
  Serial.println(x);
  Serial.println();
   
  Serial.print("Duty Cycle = ");
  Serial.print(duty);
  Serial.println(" %");
  
  Serial.print("Frekuensi = ");
  Serial.print(freq);
  Serial.println(" Hz");
   
  Serial.print("ontime = ");
  Serial.println(ontime);
  Serial.print("offtime = ");
  Serial.println(offtime);
  delay(1000);
}
  //https://forum.arduino.cc/index.php?topic=706130.0
