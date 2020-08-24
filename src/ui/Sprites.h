#ifndef Sprites_h
#define Sprites_h


#include <Arduino.h>
#include <string.h>

const uint64_t PIX_HAPPY[] = {
  0x2040200c0c204020,
  0x1020100404102010
};
const short PIX_HAPPY_MS[] = {
  500,500
};


const uint64_t PIX_IDLE[] = {
  0x0038280202283800,
  0x0008080202080800,
  0x0038280202283800,
  0x0008080202080800,
  0x0038280202382800,
  0x0028380202283800,
  0x0008080202080800  
};
const short PIX_IDLE_MS[] = {
  3000,150,2000,150,1500,1000,150 
};

const uint64_t PIX_SAD[] = {
  0x00080a02020a0800,
  0x0010120404121000
};
const short PIX_SAD_MS[] = {
  500,500,
};


const uint64_t PIX_SLEEP[] = {
  0x0008080202080800,
  0x0004040191d4b490,
  0x00040491d1b49400,
  0x0004040191d4b490
};
const short PIX_SLEEP_MS[] = {
  500,500,500,500
};


const uint64_t PIX_WHAT[] = {
  0x0070500404507000,
  0x0040400808404000,
  0x00c040101040c000,
  0x00c040101040c000,
  0x0030484845402000,
  0x006090908a804000,
  0x0030484845402000,
  0x006090908a804000
};
const short PIX_WHAT_MS[] = {
  800,150,500,150,150,150,150
};


const uint64_t PIX_HEART[] = {
  0x387c7e3f3f7e5c38,
  0xc78381c0c081a3c7
};
const short PIX_HEART_MS[] = {
  250,250
};


const uint64_t PIX_MOON[] = {
  0x00000042667e3c18,
  0x00100042667e3c18,
  0x10281042667e3c18
};
const short PIX_MOON_MS[] = {
  1000,100,100
};


const uint64_t PIX_WATER[] = {
  0x0c3e7fffff7b3e0c,
  0x030f1f3f3f1e0f03,
  0x0083c7cfcfc78300,
  0xc0e0f1f3f3b1e0c0,
  0x30f8fcfcfcecf830
};
const short PIX_WATER_MS[] = {
  150,150,150,150,150
};

const uint64_t PIX_SUN[] = {
  0x00183c7e7e3c1800,
  0x005a3c7e7e3c5a00,
  0x815a3c7e7e3c5a81,
  0x81183c7e7e3c1881
};
const short PIX_SUN_MS[] = {
  200,200,200,200
};


const int PIX_SUN_LEN = sizeof(PIX_SUN)/8;
const int PIX_WATER_LEN = sizeof(PIX_WATER)/8;
const int PIX_MOON_LEN = sizeof(PIX_MOON)/8;
const int PIX_HEART_LEN = sizeof(PIX_HEART)/8;
const int PIX_WHAT_LEN = sizeof(PIX_WHAT)/8;
const int PIX_SLEEP_LEN = sizeof(PIX_SLEEP)/8;
const int PIX_SAD_LEN = sizeof(PIX_SAD)/8;
const int PIX_HAPPY_LEN = sizeof(PIX_HAPPY)/8;
const int PIX_IDLE_LEN = sizeof(PIX_IDLE)/8;

#endif