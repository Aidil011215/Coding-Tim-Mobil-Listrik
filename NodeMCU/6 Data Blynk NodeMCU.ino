#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>

char auth[] = "JkBH5KigBFGw0cpfckcvgbGUGQazQiM0";
char ssid[] = "vivo 1807";
char pass[] = "alfineokee";

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  
}

void loop()
{ 
  
  Blynk.run();
  int pot = analogRead(A0);
  int A = pot + 400;
  int B = pot * 3;
  int C = pot * 4;
  int D = pot + 200;
  int E = pot /2;

  Blynk.virtualWrite(V0, pot);
  Blynk.virtualWrite(V1, A);
  Blynk.virtualWrite(V2, B);
  Blynk.virtualWrite(V3, C);
  Blynk.virtualWrite(V4, D);
  Blynk.virtualWrite(V5, E);
  
  Serial.println("-------------");
  Serial.print("Nilai Pot : ");
  Serial.println(pot);
  Serial.print("Nilai A : ");
  Serial.println(A);
  Serial.print("Nilai B : ");
  Serial.println(B);
  Serial.print("Nilai C : ");
  Serial.println(C);
  Serial.print("Nilai D : ");
  Serial.println(D);
  Serial.print("Nilai E : ");
  Serial.println(E);
  delay(1000);


}
