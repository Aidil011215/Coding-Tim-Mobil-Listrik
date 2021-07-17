#include <ThingSpeak.h>
//#include <WiFi.h> nodemcu ada banyak versi, pakai library ini salah
//pakai library di bawah untuk nodemcu 0.9 ESP-12 Module, ukuran kecil boardnya
#include <ESP8266WiFi.h>

const int pot = A0;
float teg,val, vbat;

// Hostpot
const char *ssid =  "vivo 1807";
const char *pass =  "alfineokee";

WiFiClient client;

//thingspeak settings
unsigned long channel = 1308894; //your channel ID number
const char *apiKey = "R7HQU5307762GTYR"; //your channel write API Key

//int lum, i = 0;

void setup() {

  pinMode(pot, INPUT);
  Serial.begin(115200);
  delay(10);

  //connect to WiFi
  Serial.print("Connecting to: "); 
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWiFi connected\n");
  ThingSpeak.begin(client); //initialize ThingSpeak
  
}

void loop() {
  val = analogRead(pot);
  teg =  val*3.3/1023;
  vbat = teg*18;
  Serial.print("Data: ");
  Serial.println(val);
  delay(200);

  int x = ThingSpeak.writeField(channel, 1, teg, apiKey);
  delay(200);
  int y = ThingSpeak.writeField(channel, 2, val, apiKey);
  delay(200);
  int z = ThingSpeak.writeField(channel, 3, vbat, apiKey);

  Serial.println("Waiting...\n");
  delay(1000);
}
