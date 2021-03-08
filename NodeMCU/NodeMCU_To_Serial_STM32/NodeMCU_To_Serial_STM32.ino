#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <SimpleTimer.h>


SimpleTimer timer;
 
String myString; // complete message from arduino, which consistors of snesors data
char rdata; // menerima karakter
 
int V, I, P, T, v, E; // sensors 

void setup()
{
  // Memulai komunikasi serial
  Serial.begin(115200);
  delay(50);
}
 
void loop()
{
  if (Serial.available()) 
  {
    rdata = Serial.read(); 
    myString = myString+ rdata; 
   // Serial.print(rdata);
    if( rdata == '\n')
    {
         //  Serial.println(myString); 
        // Serial.println("fahad");
      // new code
      String l = getValue(myString, ',', 0);
      String m = getValue(myString, ',', 1);
      String n = getValue(myString, ',', 2);
      String o = getValue(myString, ',', 4);
      String p = getValue(myString, ',', 5);
      String q = getValue(myString, ',', 6); 
       
       
      V = l.toInt();
      I = m.toInt();
      P = n.toInt();
      T = o.toInt();
      v = p.toInt();
      E = q.toInt();
      
        myString = "";
      Serial.println("-----------------------");
      Serial.println("Data Mobil Listrik KMHE");
      Serial.println("-----------------------");
      Serial.println(V);
      Serial.println(I);
      Serial.println(P);
      Serial.println(T);
      Serial.println(v);
      Serial.println(E);
      Serial.println("-----------------------");
      // end new code
      Serial.println();
    }
  }
 
}

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;
 
    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
