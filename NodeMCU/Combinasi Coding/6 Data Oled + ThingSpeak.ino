#include <ThingSpeak.h>
//#include <WiFi.h> nodemcu ada banyak versi, pakai library ini salah
//pakai library di bawah untuk nodemcu 0.9 ESP-12 Module, ukuran kecil boardnya
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <Wire.h> 
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int pot = A0;
float V = 0;
float I = 0;
float P = 0;
float T = 0;
float v = 0;
float E = 0;

// Hostpot
const char *ssid =  "untan";

WiFiClient client;

//thingspeak settings
unsigned long channel =  1317822; //your channel ID number
const char *apiKey = "YPYIRSVFF8YQRLET"; //your channel write API Key

//int lum, i = 0;

void setup() {

  pinMode(pot, INPUT);
  Serial.begin(115200);
  delay(10);

  //connect to WiFi
  Serial.print("Connecting to: "); 
  Serial.println(ssid);
  WiFi.begin(ssid);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWiFi connected\n");
  ThingSpeak.begin(client); //initialize ThingSpeak

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Clear the buffer
  display.clearDisplay();
  display.display();
  
}

void loop() {
  V = analogRead(pot);
  displayTemp(V);
  I =  V*3.3/1023;
  P = I*18;
  T = P/I;
  v = T*P;
  E = V-I;
  
  Serial.print("Data V : ");
  Serial.println(V);
  Serial.print("Data I : ");
  Serial.println(I);
  Serial.print("Data P : ");
  Serial.println(P);
  Serial.print("Data T : ");
  Serial.println(T);
  Serial.print("Data v : ");
  Serial.println(v);
  Serial.print("Data E : ");
  Serial.println(E);
  delay(200);

  int a = ThingSpeak.writeField(channel, 1, V, apiKey);
  delay(200);
  int b = ThingSpeak.writeField(channel, 2, I, apiKey);
  delay(200);
  int c = ThingSpeak.writeField(channel, 3, P, apiKey);
  delay(200);
  int x = ThingSpeak.writeField(channel, 4, T, apiKey);
  delay(200);
  int y = ThingSpeak.writeField(channel, 5, v, apiKey);
  delay(200);
  int z = ThingSpeak.writeField(channel, 6, E, apiKey);
  delay(200);

  Serial.println("Waiting...\n");
  delay(1000);
}

void displayTemp(float val) {
  display.clearDisplay();
  display.display();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("   Data Nilai Mobil");
  display.println("---------------------");

  //baris 1
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,16);
  display.println("V");
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(8,16);
  display.println(":");
  display.setCursor(16,16);
  display.setTextSize(1);
  display.print(V, 1);
  display.display();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,28);
  display.println("I");
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(8,28);
  display.println(":");
  display.setCursor(16,28);
  display.setTextSize(1);
  display.print(I, 1);
  display.display();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,40);
  display.println("P");
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(8,40);
  display.println(":");
  display.setCursor(16,40);
  display.setTextSize(1);
  display.print(P, 1);
  display.display();

  //baris 2
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(70,16);
  display.println("T");
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(78,16);
  display.println(":");
  display.setCursor(86,16);
  display.setTextSize(1);
  display.print(T, 1);
  display.display();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(70,28);
  display.println("v");
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(78,28);
  display.println(":");
  display.setCursor(86,28);
  display.setTextSize(1);
  display.print(v, 1);
  display.display();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(70,40);
  display.println("E");
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(78,40);
  display.println(":");
  display.setCursor(86,40);
  display.setTextSize(1);
  display.print(E, 1);
  display.display();
}
