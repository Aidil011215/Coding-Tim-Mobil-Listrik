HardwareTimer pwmtimer3(3);

#define inpfrek PB10

long int ontime, offtime, duty;
float period, freq;

void setup() {
   pinMode(inpfrek, INPUT);
   pinMode(PA7, PWM);

   pwmtimer3.pause();
   pwmtimer3.setPrescaleFactor(1);
   pwmtimer3.setOverflow(4200);
   /*
      STM32 has 4 timers, each with 4 channels and 16 bit resolution. That means 65535 values. This value is important to us, as the resolution decides 
      how accurately the pwm duty cycle can be generated. Next, STM32 runs at speeds of 72MHz. That means that we will get 72,000,000/65535 = 1.098 kHz on our PWM pins.
      
      We need a pwm frequency of 17 kHz. If we divide the controllers base frequency by the wanted pwm frequency, we will get the overflow value. (72,000,000/17,000=+- 4235).
   */
   pwmtimer3.refresh();
   pwmtimer3.resume();

   Serial.begin(115200);
}

void loop() {
   
   analogWrite(PA7, 16); //untuk setiap nilai pwm, dutycycle-nya 6%, untuk overflow 4200 -> 16 * 6% = 96%
   ontime = pulseIn(inpfrek,HIGH); // pulseIn adalah fungsi untuk menghitung lama waktu dalam mikrodetik
   offtime = pulseIn(inpfrek,LOW);
   period = ontime + offtime;
   freq = 1000000.0/period; // frekuensi = 1 detik / periode, 1000000 mikrodetik = 1 detik
   duty = (ontime/period)*100; //rumus dutycycle

  Serial.println();
  Serial.println("Pembacaan");
  Serial.print("Duty Cycle = ");
  Serial.print(duty);
  Serial.println(" %");
  
  Serial.print("Frekuensi = ");
  Serial.print(freq);
  Serial.println(" Hz");
  delay(1000);
}
  //https://forum.arduino.cc/index.php?topic=706130.0
