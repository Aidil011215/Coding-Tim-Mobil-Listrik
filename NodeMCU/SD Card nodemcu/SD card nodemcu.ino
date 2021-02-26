//NodMCU -->data --> SD Card
// sumber referensi
// https://www.instructables.com/SD-Card-Module-With-ESP8266/

#include <SD.h>    //Mrndenefisikan library atau perpustakaan SD.h
#define CS_PIN  D8 //Medenefisikan variabel CS_PIN pada pin D8 di STM32
#define pot A0     // Mendenefisikan variabel pot pada pin A0 di STM32

int b; //Mendeklarasikan variabel b pada tipe integer
int c; //Mendeklarasikan variabel c pada tipe integer
File dataFile; //Mendeklarasikan variabel dataFile pada tipe File atau dokumen


void setup()
{
  Serial.begin(9600); //Menghubungkan mikrokontroler dengan laptop pada serial baud atau parameter 9600
  pinMode(pot, INPUT); //Menetapkan variabel pot sebagai input
  Serial.println("Inisialisasi SD CARD..."); //Menampilkan diserial kata "Inisialisasi SD CARD..." di serial monitor laptop
   
  // Periksa apakah kartu SD ada dan dapat diinisialisasi
  if (!SD.begin(CS_PIN)) {
    Serial.println("Gagal, cek apakah SD card terhubung."); //Menampilkan diserial kata "Gagal, cek apakah SD card terhubung." di serial monitor laptop
    return;
  }
   
  // jika Anda sampai di sini, itu karena kartu diinisialisasi dengan benar
  Serial.println("Inisialisasi kartu."); //Menampilkan kata "Inisialisasi kartu." pada serial monitor laptop
 
}

void loop() {
  b = analogRead(pot); //Menjadikan variabel b sebagai pembaca sinyal analog dari variabel pot
  Serial.print("Nilai Potensiometer: "); //Menampilkan kata "Nilai Potensiometer: " pada serial monitor laptop
  Serial.println(b); //Menampilkan nilai dari variabel b diserial monitor laptop
  c = b*2; //Mengkalikan variabel b dengan 2 dan menjadikan variabel c sebagai hasil
  Serial.print(": "); //Menampilkan diserial kata di serial monitor laptop
  Serial.println(c); //Menampilkan nilai dari variabel c diserial monitor laptop
 
  dataFile = SD.open("NilaiPot.xls", FILE_WRITE); //Menjadikan variabel dataFile sebagai alat untuk membuat file dan membuka file di SD card 
  // jika file dibuka dengan benar, tulis datanya
  if (dataFile) {
    Serial.println("File Nilaipot.xls Berhasil Dibuka."); //Menampilkan diserial kata "File Nilaipot.xls Berhasil Dibuka." di serial monitor laptop
      
      dataFile.print("Nilai Pot"); //Mecetak kata pada file yang dibuat di SD card
      dataFile.print("\t\t"); //Tab 2 kali
      dataFile.println("Nilai Pot*2"); //Mecetak kata pada file yang dibuat di SD card
      dataFile.print("");
      dataFile.print(b); //Mecetak nilai dari variabel b pada file yang dibuat di SD card
      dataFile.print("\t\t"); //Tab 2 kali
      dataFile.println(c); //Mecetak nilai dari variabel b pada file yang dibuat di SD card
 
      //menutup file setelah menggunakannya
      dataFile.close();
  }
  // jika file tidak dapat dibuka, data tidak akan ditulis.
  else {
    Serial.println("Gagal membuka file NilaiPot.xls"); //Menampilkan kata "Gagal membuka  file NilaiPot.xls" diserial monitor laptop
  }
 
  //menunggu interval untuk pembacaan baru dari data
  delay(2000);
 
}
