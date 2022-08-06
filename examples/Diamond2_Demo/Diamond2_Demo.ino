/**
   @file Diamond2_Demo.ino
   @author Kongduino
   @brief Implementation of the Diamond2 and Diamond2 Lite Block Ciphers by Mike Johnson as a class.
   @version 0.1
   @date 2022-08-07
   @copyright Copyright (c) 2022. MIT License.
**/

#include <Adafruit_TinyUSB.h>
// Enable this if compiling for RAK4631 / Arduino BSP / nRF52840
// Disable this if compiling for RAK4631-RUI3 or other boards that don't need Adafruit_TinyUSB

#include <DIAMOND2_Class.h>

void setup() {
  Serial.begin(115200);
  delay(8000);
  for (uint8_t i = 5; i > 0; i--) {
    Serial.print(i);
    Serial.print(", ");
    delay(500);
  }
  Serial.println("0!\nDIAMOND");
  static byte encryption_key[32] = {
    0xE8, 0x34, 0xFD, 0xB9, 0x33, 0xC5, 0x02, 0x92,
    0x3D, 0x92, 0xBC, 0x9E, 0x14, 0x36, 0x8E, 0x70,
    0xD4, 0x1C, 0x66, 0xCB, 0xDF, 0x36, 0x15, 0x50,
    0x33, 0xA6, 0x6E, 0x07, 0xE6, 0xCC, 0x6D, 0x8D
  };
  double t0, t1;
  char buff[191] = "tagada pouet pouet\ntagada pouet pouet\ntagada pouet pouet\ntagada pouet pouet\ntagada pouet pouet\ntagada pouet pouet\ntagada pouet pouet\ntagada pouet pouet\ntagada pouet pouet\ntagada pouet pouet\n";
  char enc[190];
  byte lastciphertext[16];
  byte thisciphertext[16];
  memcpy(enc, buff, 190);
  Serial.println("Plain Text:");
  hexDump((unsigned char *)enc, 190);
  t0 = micros();
  memset(lastciphertext, 0, 16);
  D2 d2_0(encryption_key, 32, 10, false, 16);
  d2_0.encrypt_block(lastciphertext, lastciphertext);
  int blockpos = 0;
  int bytesinbuf = 190;
  for (int i = 0; i < bytesinbuf; i++) {
    enc[i] ^= lastciphertext[blockpos++];
    if (blockpos >= 16) {
      blockpos = 0;
      d2_0.encrypt_block((byte*)(enc + i - 15), lastciphertext);
    }
  }
  t1 = micros() - t0;
  Serial.printf("Encoded in %d micros:\n", t1);
  hexDump((unsigned char *)enc, 190);

  t0 = micros();
  memset(lastciphertext, 0, 16);
  d2_0.encrypt_block(lastciphertext, lastciphertext);
  blockpos = 0;
  for (int i = 0; i < bytesinbuf; i++) {
    thisciphertext[blockpos] = enc[i];
    enc[i] ^= lastciphertext[blockpos++];
    if (blockpos >= 16) {
      blockpos = 0;
      d2_0.encrypt_block(thisciphertext, lastciphertext);
    }
  }
  t1 = micros() - t0;
  Serial.printf("Encoded in %d micros:\n", t1);
  hexDump((unsigned char *)enc, 190);
  if (memcmp(enc, buff, 190) == 0) Serial.println("Match!");
  else Serial.println("Uh oh, not a match...");
}

void loop() {
  // put your main code here, to run repeatedly:

}

void hexDump(unsigned char *buf, uint16_t len) {
  char alphabet[17] = "0123456789abcdef";
  Serial.print(F("   +------------------------------------------------+ +----------------+\n"));
  Serial.print(F("   |.0 .1 .2 .3 .4 .5 .6 .7 .8 .9 .a .b .c .d .e .f | |      ASCII     |\n"));
  for (uint16_t i = 0; i < len; i += 16) {
    if (i % 128 == 0)
      Serial.print(F("   +------------------------------------------------+ +----------------+\n"));
    char s[] = "|                                                | |                |\n";
    uint8_t ix = 1, iy = 52;
    for (uint8_t j = 0; j < 16; j++) {
      if (i + j < len) {
        uint8_t c = buf[i + j];
        s[ix++] = alphabet[(c >> 4) & 0x0F];
        s[ix++] = alphabet[c & 0x0F];
        ix++;
        if (c > 31 && c < 128) s[iy++] = c;
        else s[iy++] = '.';
      }
    }
    uint8_t index = i / 16;
    if (i < 256) Serial.write(' ');
    Serial.print(index, HEX); Serial.write('.');
    Serial.print(s);
  }
  Serial.print(F("   +------------------------------------------------+ +----------------+\n"));
}
