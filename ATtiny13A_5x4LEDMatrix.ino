/*

 @file ATtiny13A_5x4LEDMatrix.ino

   <Fuse>
    hFuse    0xFF
    lFuse    0x7A
    Lock Bit 0x3F
 
 @brief 5x4 LED Matrix (ATtiny13a)
 @author Kei Takagi
 @date 2016.11.22
 
 Copyright (c) 2016 Kei Takagi
 Released under the MIT license
 http://opensource.org/licenses/mit-license.php
 
 */

#include <avr/eeprom.h>
#include <avr/pgmspace.h>

#define  SCROLL_SPEED 20
#define  EEPROM_SIZE 64
#define  ROW_SIZE 5
#define  COL_SIZE 4

const byte PINS_H[20] PROGMEM = {
  PB1,PB2,PB4,PB3,PB0,PB0,PB1,PB2,PB4,PB3,PB0,PB4,PB1,PB3,PB2,PB4,PB1,PB3,PB2,PB0};
const byte PINS_L[20] PROGMEM = {
  PB0,PB1,PB2,PB4,PB3,PB1,PB2,PB4,PB3,PB0,PB4,PB1,PB3,PB2,PB0,PB0,PB4,PB1,PB3,PB2};

const word CHAR_FONT[26] PROGMEM = {
  0B011111010001111, //A
  0B111111010101010, //B
  0B011101000110001, //C
  0B111111000101110, //D
  0B111111010110101, //E
  0B111111010010000, //F
  0B011101010100110, //G
  0B111110010011111, //H
  0B100011111110001, //I
  0B000110000111111, //J
  0B111110010011011, //K
  0B111110000100001, //L
  0B111110110011111, //M
  0B111111000001111, //N
  0B011101000101110, //O
  0B111111010001000, //P
  0B011101000101111, //Q
  0B111111010001011, //R
  0B111011010110111, //S
  0B100001111110000, //T
  0B111110000111111, //U
  0B111100000111110, //V
  0B111110011011111, //W
  0B110110010011011, //X
  0B110000011111000, //Y
  0B100111010111001  //Z
};
const word NUMBER_FONT[10] PROGMEM = {
  0B111111000111111, //0
  0B000001111100000, //1
  0B101111010111101, //2
  0B101011010111111, //3
  0B111000010011111, //4
  0B111011010110111, //5
  0B111111010110111, //6
  0B100011001011100, //7
  0B111111010111111, //8
  0B111001010011111  //9
};

void setup() {
  DDRB = 0; // PB0 - PB4:OUTPU
}

void loop() {
  byte  r,pin, dot_area[ROW_SIZE];
  word  j, i, k, font,wait,point;
  for (i = 0; i < ROW_SIZE ; i++)dot_area[i] = 0x00;
  for (i = 0; i < EEPROM_SIZE; i++)  {
    eeprom_busy_wait();
    r = eeprom_read_byte((uint8_t *)(i));
    if (r == 0x00)break;
    font = moji(r);
    for (j = 0; j < COL_SIZE; j++) {
      dot_area[0] = dot_area[1];
      dot_area[1] = dot_area[2];
      dot_area[2] = dot_area[3];
      dot_area[3] = dot_area[4];
      if (j == 0) dot_area[4] = (uint8_t)(font >> 10);
      else if (j == 1) dot_area[4] = (uint8_t)((font >> 5) & 0B11111);
      else if (j == 2) dot_area[4] = (uint8_t)(font & 0B11111);
      else dot_area[4] = 0;
      for (wait = 0; wait < SCROLL_SPEED; wait++) {
        for ( k = 0; k < 240; k++) {
          point = k % 20;
          pin =(uint8_t)pgm_read_byte_near(PINS_H + point) << 4 | (uint8_t)pgm_read_byte_near(PINS_L + point);
          if ((( dot_area[point / ROW_SIZE] >> (4 - (point % ROW_SIZE))) & 0x01) == 0x01) {
            DDRB = (1 << ((pin & 0xF0) >> 4)) |  (1 << (pin & 0x0F ));
            PORTB = 1 << ( pin & 0x0F );
          } 
          else {
            DDRB = 0;
          }
        }
      }
    }
  }
}

uint16_t moji(char c)
{
  if('A' <= c &&  c <= 'Z') return pgm_read_word_near( CHAR_FONT + (c - 'A') ); 
  if('0' <= c &&  c <= '9') return pgm_read_word_near( NUMBER_FONT + (c - '0') ); 
  return 0B000000000000000;
}

