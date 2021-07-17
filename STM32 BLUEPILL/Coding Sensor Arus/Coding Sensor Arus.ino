const int pinADC = PA0;
int sensitivitas = 66; //tegantung sensor arus yang digunakan, yang ini 30A
int teganganoffset = 2459; //nilai pembacaan offset saat tidak ada arus yang lewat
int nilaiadc = 00;
double tegangan = 00;
double nilaiarus = 00;

void setup(){
Serial.begin(9600); //baud komunikasi serial monitor 9600bps

}

void data_olah(){
  nilaiadc = analogRead(pinADC);
  tegangan = (nilaiadc / 4095.0) * 3300;
  nilaiarus = ((tegangan - teganganoffset) / sensitivitas); 
}

void loop(){
  data_olah();
  Serial.print("Nilai ADC yang terbaca = " );
  Serial.print(nilaiadc);

  Serial.print("\t tegangan (mV) = ");
  Serial.print(tegangan,3); // cetak arus dengan 3 tempat desimal6uuk
 
  Serial.print("\t Arus = ");
  Serial.println(nilaiarus,3);// cetak arus dengan 3 tempat desimal

  delay(1000);
}
