/*

 @file X_mas_tree_ATtiny13A.ino
 
 @brief Mini 12 LED Christmas tree (ATtiny13A)
 @author Kei Takagi
 @date 2016.11.25
 
 Copyright (c) 2016 Kei Takagi
 Released under the MIT license
 http://opensource.org/licenses/mit-license.php
 
  Tree LED No.
        0
        1
       3  2
     7 6  5 4
   B  A    9  8
    
 */

#define PATTERN 50
#define SPEED 30

const uint8_t pin[12] = {
  PB3 << 4 | PB2,// 0
  PB2 << 4 | PB3,// 1
  PB4 << 4 | PB3,// 2
  PB3 << 4 | PB4,// 3
  PB2 << 4 | PB4,// 4
  PB4 << 4 | PB2,// 5
  PB4 << 4 | PB1,// 6
  PB1 << 4 | PB4,// 7
  PB1 << 4 | PB2,// 8
  PB2 << 4 | PB1,// 9
  PB1 << 4 | PB3,// A
  PB3 << 4 | PB1 // B
};

void setup() {
  DDRB = 0;
}

static int i, j;
static boolean flg1 = true;

void loop() {

  if (SPEED < j) {
    j = 0;
    if ( flg1) {
      if (i < PATTERN ) {
        i++;
      } 
      else {
        flg1 = false;
      }
    } 
    else {
      if (i > 0 ) {
        i--;
      } 
      else {
        flg1 = true;
      }
    }
  }
  j++;

  LED(anime(i));
}

word anime(int in) {
  switch (in) {
  case 0:
    return 0B0000000000000001;
  case 1:
    return 0B0000000000000011;
  case 2:
    return 0B0000000000000111;
  case 3:
    return 0B0000000000001111;
  case 4:
    return 0B0000000010001111;
  case 5:
    return 0B0000000011001111;
  case 6:
    return 0B0000000011101111;
  case 7:
    return 0B0000000011111111;
  case 8:
    return 0B0000000111111111;
  case 9:
    return 0B0000001111111111;
  case 10:
    return 0B0000011111111111;
  case 11:
    return 0B0000111111111111;
  case 12:
    return 0B0000111111111111;
  case 13:
    return 0B0000111111111101;
  case 14:
    return 0B0000111111110111;
  case 15:
    return 0B0000111111111011;
  case 16:
    return 0B0000111111101111;
  case 17:
    return 0B0000111111011111;
  case 18:
    return 0B0000111110111111;
  case 19:
    return 0B0000111101111111;
  case 20:
    return 0B0000111011111111;
  case 21:
    return 0B0000110111111111;
  case 22:
    return 0B0000101111111111;
  case 23:
    return 0B0000011111111111;
  case 24:
    return 0B0000111111111111;
  case 25:
    return 0B0000111111111101;
  case 26:
    return 0B0000111111111011;
  case 27:
    return 0B0000111111110111;
  case 28:
    return 0B0000111111101111;
  case 29:
    return 0B0000111111011111;
  case 30:
    return 0B0000111110111111;
  case 31:
    return 0B0000111101111111;
  case 32:
    return 0B0000111011111111;
  case 33:
    return 0B0000110111111111;
  case 34:
    return 0B0000101111111111;
  case 35:
    return 0B0000011111111111;
  case 36:
    return 0B0000111111111111;
  case 37:
    return 0B0000111111111111;
  case 38:
    return 0B0000100111111111;
  case 39:
    return 0B0000111111111111;
  case 40:
    return 0B0000111110011111;
  case 41:
    return 0B0000111111111111;
  case 42:
    return 0B0000111111110011;
  case 43:
    return 0B0000111111111111;
  case 44:
    return 0B0000100111111111;
  case 45:
    return 0B0000100110011111;
  case 46:
    return 0B0000111110011111;
  case 47:
    return 0B0000111111110011;
  case 48:
    return 0B0000111111111101;
  case 49:
    return 0B0000111111111111;
  case 50:
    return 0B0000111111111111;
  }
}

void LED(word in) {
  for (int k = 0; k < 12; k++) {
    if ((in >> k) & 0x01 == 0x01) {
      DDRB = (1 << (pin[k] & 0x0F)) | (1 << ((pin[k] & 0xF0) >> 4));
      PORTB = 1 << ((pin[k] & 0xF0) >> 4);
    }
    delay(1);
  }
}


