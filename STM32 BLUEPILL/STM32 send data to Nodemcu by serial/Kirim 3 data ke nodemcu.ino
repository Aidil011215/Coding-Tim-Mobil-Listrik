#define Pot PB0

int v = 0;
int i = 0;
int p = 0;

float sdata1 = 0; // tegangan
float sdata2 = 0; // arus
float sdata3 = 0; // daya

String cdata;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  v = analogRead(Pot);
  i = v*2;
  p = i+5;
  serialData();
}

void serialData() {
   sdata1 = v;
   sdata2 = i;
   sdata3 = p;

   cdata = cdata + sdata1 + "," + sdata2 + "," + sdata3; // comma will be used a delimeter
   Serial.println(cdata);
   delay(1000);
   cdata = "";
}
