#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, PB6 /*SCL*/, PB7 /*SDA*/);

void setup(void) {
  u8g2.begin();
  u8g2.setFont(u8g2_font_6x10_tr);                                        //Memilih font dan ukuran
}

void draw(const char * s)
{
  u8g2.firstPage();
  do {
    u8g2.drawStr(2,15,"Hai!");                                            // Menuliskan pesan "Hai!"
    u8g2.drawStr(2,30,s);                                                 // Menampilkan data s
    u8g2.drawFrame(0,0,u8g2.getDisplayWidth(),u8g2.getDisplayHeight() );  // Dapatkan nilai lebar dan panjang display tergantung rotasi
    u8g2.drawStr(2, 45, u8x8_u16toa(u8g2.getDisplayWidth(), 5));          // Menuliskan lebar display
    u8g2.drawStr(2, 60, u8x8_u16toa(u8g2.getDisplayHeight(), 5));         // Menuliskan panjang display
    
  } while ( u8g2.nextPage() );
  delay(2000);
}

void loop(void) {
  
  //data s
  u8g2.clearDisplay();                                                    // Membersihkan Layar
  u8g2.setDisplayRotation(U8G2_R0);                                       // Mengatur Mode Rotasi - RO - display diputar 0 derajat searah jarum jam
  u8g2.setFlipMode(0);                                                    // Mengatur Mode Flip(0) - Membalik Rotasi 0 derajat
  draw("R0,F0");                                                          // R0, F0 = R2, F1
  u8g2.clearDisplay();                                                    // Membersihkan Layar
  u8g2.setFlipMode(1);                                                    // Mengatur Mode Flip(1) - Membalik Rotasi 180 derajat
  draw("R0,F1");                                                          // R0, F1 = R2, F0

  u8g2.clearDisplay();                                                    // Membersihkan Layar
  u8g2.setDisplayRotation(U8G2_R1);                                       // Mengatur Mode Rotasi - R1 - display diputar 90 derajat searah jarum jam
  u8g2.setFlipMode(0);                                                    // Mengatur Mode Flip(0) - Membalik Rotasi 0 derajat
  draw("R1,F0");                                                          // R3, F0 = R1, F1
  u8g2.clearDisplay();                                                    // Membersihkan Layar
  u8g2.setFlipMode(1);                                                    // Mengatur Mode Flip(1) - Membalik Rotasi 180 derajat  
  draw("R1,F1");                                                          // R1, F1 = R3, F0

  u8g2.clearDisplay();                                                    // Membersihkan Layar
  u8g2.setDisplayRotation(U8G2_R2);                                       // Mengatur Mode Rotasi - R2 - display diputar 180 derajat searah jarum jam
  u8g2.setFlipMode(0);                                                    // Mengatur Mode Flip(0) - Membalik Rotasi 0 derajat  
  draw("R2,F0");                                                          // R2, F0 = R0, F1
  u8g2.clearDisplay();                                                    // Membersihkan Layar
  u8g2.setFlipMode(1);                                                    // Mengatur Mode Flip(1) - Membalik Rotasi 180 derajat  
  draw("R2,F1");                                                          // R2, F1 = R0, F0

  u8g2.clearDisplay();                                                    // Membersihkan Layar
  u8g2.setDisplayRotation(U8G2_R3);                                       // Mengatur Mode Rotasi - R3 - display diputar 270 derajat searah jarum jam
  u8g2.setFlipMode(0);                                                    // Mengatur Mode Flip(0) - Membalik Rotasi 0 derajat  
  draw("R3,F0");                                                          // R3, F0 = R1, F1
  u8g2.clearDisplay();                                                    // Membersihkan Layar
  u8g2.setFlipMode(1);                                                    // Mengatur Mode Flip(1) - Membalik Rotasi 180 derajat  
  draw("R3,F1");                                                          // R3, F1 = R1, F0 
}

/*
 Untuk rotasi display (jika perlu)
*/
