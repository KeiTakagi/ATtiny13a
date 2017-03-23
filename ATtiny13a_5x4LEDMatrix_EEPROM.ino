/*

 @file ATtiny13a_5x4LEDMatrix_EEPROM.ino

   <Fuse>
    hFuse    0xFF
    lFuse    0x7A
    Lock Bit 0x3F
 
 @brief 5x4 LED Matrix (ATtiny13a)
        It is for making messages of EEPROM.
 @author Kei Takagi
 @date 2016.11.22
 
 Copyright (c) 2016 Kei Takagi
 Released under the MIT license
 http://opensource.org/licenses/mit-license.php
 
 */
#include <avr/pgmspace.h>
#include <avr/eeprom.h>

#define  EEPROM_SIZE 64

                                       //0123456789012345678901234567890123456789012345678901234567891234
const byte str[EEPROM_SIZE+1] PROGMEM = "THIS IS A 5X4LED MATRIX MADE WITH ATTINY13 THANK YOU FOR VIEWING";

void setup() {
  byte i, ws;
  for (i = 0; i < EEPROM_SIZE ; i++) {
    ws = pgm_read_byte_near(str + i);
    eeprom_busy_wait();
    eeprom_write_byte((uint8_t *)(i), ws);
  }
}

void loop() {
}


