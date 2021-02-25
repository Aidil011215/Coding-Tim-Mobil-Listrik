#include <SD.h>
#define CS_PIN  D8
#define pot A0
int b;
int c;

void setup()
{
  Serial.begin(9600);
  pinMode(pot, INPUT);
  Serial.print("Inisialisasi SD CARD...");
   
  // verifica se o cartão SD está presente e se pode ser inicializado
  if (!SD.begin(CS_PIN)) {
    Serial.println("Gagal, cek apakah SD card terhubung.");
    //programa encerrrado
    return;
  }
   
  //se chegou aqui é porque o cartão foi inicializado corretamente  
  // sumber referensi
  // https://www.instructables.com/SD-Card-Module-With-ESP8266/
  Serial.println("Inisialisasi kartu.");
 
}

void loop() {
//faz a leitura da umidade
  b = analogRead(pot);
  Serial.print("Nilai Potensiometer: ");
  Serial.println(b);
  //faz a leitura da temperatura
  c = b*2;
  Serial.print(": ");
  Serial.println(c);
 
  File dataFile = SD.open("LOG.txt", FILE_WRITE);
  // jika file dibuka dengan benar, tulis datanya
  if (dataFile) {
    Serial.println("File Berhasil Dibuka.");
      //pemformatan dalam file: baris demi baris >> UMIDADE | TEMPERATURA
      dataFile.print(b);
      dataFile.print(" | ");
      dataFile.println(c);
 
      //menutup file setelah menggunakannya
      dataFile.close();
  }
  // jika file tidak dapat dibuka, data tidak akan ditulis.
  else {
    Serial.println("Gagal membuka file LOG.txt");
  }
 
  //menunggu interval untuk pembacaan baru dari data
  delay(2000);
 
}
