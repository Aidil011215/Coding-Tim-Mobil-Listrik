//Mendeklarasikan library atau perpustakaan
#include <SPI.h> 
#include <Wire.h>
#include <SD.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> 
#define BLYNK_PRINT Serial

//Deklarasi untuk pin LCD Oled
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

String myString; // complete message from arduino, which consistors of snesors data
char rdata; // menerima karakter

// Deklarasi untuk SSD1306 display terhubung ke I2C (pin SDA dan SCL)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int data = 0;

//Dekalrasi Variabel
float V, I, P, T, v, E;

// Hostpot dan Konfigurasi Blynk
const char auth[] = "JkBH5KigBFGw0cpfckcvgbGUGQazQiM0";
const char ssid[] = "vivo 1807";
const char pass[] = "alfineokee";

WiFiClient client;

//Deklarasi untuk pin pada SD Card
#define CS_PIN D8 //Medenefisikan variabel CS_PIN pada pin D8 di NodeMCU
File dataFile; //Mendeklarasikan variabel dataFile pada tipe File atau Dokumen


void setup() {
  pinMode(data, INPUT);
  Serial.begin(115200);
  delay(10);

  //Status sambungan ke wifi
  Serial.print("Tersambung ke Wifi: "); 
  Serial.println(ssid);
  //WiFi.begin(ssid); digunakan saat wifi tanpa password
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
    Serial.println("\nWiFi connected\n"); 
    Blynk.begin(auth, ssid, pass);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  //Setting LCD Oled
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Clear the buffer
  display.clearDisplay();
  display.display();

  //Menghubungkan SD Card ke NodeMCU
  Serial.println("Inisialisasi SD CARD..."); //Menampilkan diserial kata "Inisialisasi SD CARD..." di serial monitor laptop

  //Periksa apakah kartu SD ada dan dapat diinisialisasi
  if (!SD.begin(CS_PIN)) {
    Serial.println("Gagal, cek apakah SD card terhubung."); //Menampilkan diserial kata "Gagal, cek apakah SD card terhubung." di serial monitor laptop
    return;
  }
   
  // jika Anda sampai di sini, itu karena kartu diinisialisasi dengan benar
  Serial.println("Inisialisasi kartu."); //Menampilkan kata "Inisialisasi kartu." pada serial monitor laptop

  dataFile = SD.open("Data Mobil.xls", FILE_WRITE); //Menjadikan variabel dataFile sebagai alat untuk membuat file dan membuka file di SD card 
  // jika file dibuka dengan benar, tulis datanya
  if (dataFile) { 
      //Mecetak kata-kata pada file yang dibuat di SD card
      dataFile.print("Tegangan"); 
      dataFile.print("\t\t"); //Tab 2 kali
      dataFile.print("Arus"); 
      dataFile.print("\t\t"); //Tab 2 kali
      dataFile.print("Daya"); 
      dataFile.print("\t\t"); //Tab 2 kali
      dataFile.print("Temperature"); 
      dataFile.print("\t\t"); //Tab 2 kali
      dataFile.print("Kecepatan"); 
      dataFile.print("\t\t"); //Tab 2 kali
      dataFile.print("Energi"); 
      dataFile.println("");
 
      //menutup file setelah menggunakannya
      dataFile.close();
  }
  // jika file tidak dapat dibuka, data tidak akan ditulis.
  else {
    Serial.println("Gagal membuka file Data Mobil.xls"); //Menampilkan kata "Gagal membuka  file NilaiPot.xls" diserial monitor laptop
  }

}

void loop() {
  
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
      String o = getValue(myString, ',', 3);
      String p = getValue(myString, ',', 4);
      String q = getValue(myString, ',', 5); 
       
       
      V = l.toFloat();
      I = m.toInt();
      P = n.toInt();
      T = o.toInt();
      v = p.toInt();
      E = q.toInt();
      
        myString = "";
      Serial.println("-----------------------");
      
      Serial.println("Data Mobil Listrik KMHE");
      Serial.println("-----------------------");
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
      Serial.println("-----------------------");
      // end new code
      Serial.println();

      Blynk.run();
      Blynk.virtualWrite(V0, V);
      Blynk.virtualWrite(V1, I);
      Blynk.virtualWrite(V2, P);
      Blynk.virtualWrite(V3, T);
      Blynk.virtualWrite(V4, v);
      Blynk.virtualWrite(V5, E);
    
      SD_Card();
      Serial.println("Waiting...\n");
      delay(50);
      displayOLED();
      delay(50);
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

void SD_Card(){

  dataFile = SD.open("Data Mobil.xls", FILE_WRITE); //Menjadikan variabel dataFile sebagai alat untuk membuat file dan membuka file di SD card 
  // jika file dibuka dengan benar, tulis datanya
  if (dataFile) {
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0,52);
      display.println("File Terbuka"); 
      
      Serial.println("File Data Mobil.xls Berhasil Dibuka."); //Menampilkan diserial kata "File Nilaipot.xls Berhasil Dibuka."
      //Mecetak nilai variabel pada file yang dibuat di SD card
      dataFile.print(V);
      dataFile.print("\t\t"); //Tab 2 kali
      dataFile.print(I);
      dataFile.print("\t\t"); //Tab 2 kali
      dataFile.print(P); 
      dataFile.print("\t\t"); //Tab 2 kali
      dataFile.print(T); 
      dataFile.print("\t\t"); //Tab 2 kali
      dataFile.print(v); 
      dataFile.print("\t\t"); //Tab 2 kali
      dataFile.print(E);
      dataFile.println("");
 
  //menutup file setelah menggunakannya
      dataFile.close();
      delay(1000);
  }
  // jika file tidak dapat dibuka, data tidak akan ditulis.
  else {
    Serial.println("Gagal membuka file Data Mobil.xls"); //Menampilkan kata "Gagal membuka  file NilaiPot.xls" diserial monitor laptop
  }
   //menunggu interval untuk pembacaan baru dari data
  delay(200);
}

void displayOLED() {   //Menampilkan data di LCD Oled
  display.clearDisplay();
  display.display();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("   Data Nilai Mobil"); //Menampilkan kata pada baris 1
  display.println("---------------------"); //Menampilkan kata pada baris 2

  //Kolom 1 baris 3
  //Menampilkan nilai variabel V di LCD Oled
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

  //Kolom 1 Baris 4
  //Menampilkan nilai variabel I di LCD Oled
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

  //Kolom 1 Baris 5
  //Menampilkan nilai variabel P di LCD Oled
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

  //Kolom 2 Baris 3
  //Menampilkan nilai variabel T di LCD Oled
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

  //Kolom 2 Baris 4
  //Menampilkan nilai variabel v di LCD Oled
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

  //Kolom 2 Baris 5
  //Menampilkan nilai variabel E di LCD Oled
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
  delay(100);
}
