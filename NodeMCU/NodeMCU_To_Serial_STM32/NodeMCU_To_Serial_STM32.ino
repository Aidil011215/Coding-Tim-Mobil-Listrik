//#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <SimpleTimer.h>


SimpleTimer timer;
 
String myString; // complete message from arduino, which consistors of snesors data
char rdata; // menerima karakter
 
int firstVal, secondVal,thirdVal; // sensors 
// This function sends Arduino's up time every second to Virtual Pin (1).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
 
 
 
void setup()
{
  // Debug console
  Serial.begin(115200);
 
}
 
void loop()
{
   if (Serial.available() == 0 ) 
   {
   }
   
  if (Serial.available() > 0 ) 
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
 
 
firstVal = l.toInt();
secondVal = m.toInt();
thirdVal = n.toInt();

  myString = "";

Serial.println(firstVal);
Serial.println(secondVal);
Serial.println(thirdVal);
// end new code
Serial.println("Test");
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
