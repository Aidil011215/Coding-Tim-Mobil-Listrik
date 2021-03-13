#include <SoftwareSerial.h>
 
String myString; // complete message from arduino, which consistors of snesors data
char rdata; // menerima karakter
 
float V, I, P, T, v, E; // sensors 

void setup()
{
  // Memulai komunikasi serial
  Serial.begin(115200);
  delay(50);
}
 
void loop()
{
  if (Serial.available() > 0) 
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
      String o = getValue(myString, ',', 3);
      String p = getValue(myString, ',', 4);
      String q = getValue(myString, ',', 5); 
       
       
      V = l.toFloat();
      I = m.toFloat();
      P = n.toFloat();
      T = o.toFloat();
      v = p.toFloat();
      E = q.toFloat();
      
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

String getValue(String data, char separator, float index)
{
    float found = 0;
    float strIndex[] = { 0, -1 };
    float maxIndex = data.length() - 1;
 
    for (float i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
