HardwareTimer pwmtimer4(4);
int nPWM = 0;

void setup() {
   pinMode(PB0, INPUT);
   pinMode(PA0, PWM);

   pwmtimer4.pause();
   pwmtimer4.setPrescaleFactor(1);
   pwmtimer4.setOverflow(4235);
   /*
      STM32 has 4 timers, each with 4 channels and 16 bit resolution. That means 65535 values. This value is important to us, as the resolution decides 
      how accurately the pwm duty cycle can be generated. Next, STM32 runs at speeds of 72MHz. That means that we will get 72,000,000/65535 = 1.098 kHz on our PWM pins.
      
      We need a pwm frequency of 17 kHz. If we divide the controllers base frequency by the wanted pwm frequency, we will get the overflow value. (72,000,000/17,000=+- 4235).
   */
   pwmtimer4.refresh();
   pwmtimer4.resume();

   pwmWrite(PA0, 0);

   Serial.begin(9600);
   while (!Serial);
}

void loop() {
  if (Serial.available()){

       nPWM = Serial.parseInt();
         Serial.print("Nilai Frekuensi PWM = ");
         Serial.print(nPWM);
         Serial.println(" Hz");
    
    pwmWrite(PA0, nPWM);
  }

  //https://forum.arduino.cc/index.php?topic=706130.0
