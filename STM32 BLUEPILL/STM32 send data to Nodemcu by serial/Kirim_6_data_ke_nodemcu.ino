#define Pot PB0
//#define enable PA0

float V = 0;
float I = 0;
float P = 0;
float t = 0;
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
  Serial.begin(115200);
  delay(100);
//  digitalWrite(enable, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  V = analogRead(Pot)*60/4000;
  I = V/5;
  P = I*V;
  t = V/2;
  v = 30+I;
  E = P*4;
  serialData();
}

void serialData() {
   sdata1 = V;
   sdata2 = I;
   sdata3 = P;
   sdata4 = t;
   sdata5 = v;
   sdata6 = E;

   cdata = cdata + sdata1 + "," + sdata2 + "," + sdata3 + ","  + sdata4 + "," + sdata5 + "," + sdata6; // comma will be used a delimeter
   Serial.println(cdata);
   delay(1000);
   cdata = "";
}
