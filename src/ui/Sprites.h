#ifndef Sprites_h
#define Sprites_h

#include <Arduino.h>
#include <State.h>

const uint64_t PIX_HAPPY[] = {
  0x2040200c0c204020,
  0x1020100404102010
};
const unsigned short PIX_HAPPY_MS[] = {
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
const unsigned short PIX_IDLE_MS[] = {
  3000,150,2000,150,1500,1000,150 
};

const uint64_t PIX_SAD[] = {
  0x00080a02020a0800,
  0x0010120404121000
};
const unsigned short PIX_SAD_MS[] = {
  500,500,
};


const uint64_t PIX_SLEEP[] = {
  0x0008080202080800,
  0x0004040191d4b490,
  0x00040491d1b49400,
  0x0004040191d4b490
};
const unsigned short PIX_SLEEP_MS[] = {
  500,500,500,500
};


const uint64_t PIX_WHAT[] = {
  0x0070500404507000,
  0x0040400808404000,
  0x00c040101040c000,
  0x0030484845402000,
  0x006090908a804000,
  0x0030484845402000,
  0x006090908a804000
};
const unsigned short PIX_WHAT_MS[] = {
  800,150,500,150,150,150,150
};


const uint64_t PIX_HEART[] = {
  0x387c7e3f3f7e5c38,
  0xc78381c0c081a3c7
};
const unsigned short PIX_HEART_MS[] = {
  250,250
};


const uint64_t PIX_MOON[] = {
  0x00000042667e3c18,
  0x00100042667e3c18,
  0x10281042667e3c18
};
const unsigned short PIX_MOON_MS[] = {
  1000,100,100
};


const uint64_t PIX_WATER[] = {
  0x0c3e7fffff7b3e0c,
  0x030f1f3f3f1e0f03,
  0x0083c7cfcfc78300,
  0xc0e0f1f3f3b1e0c0,
  0x30f8fcfcfcecf830
};
const unsigned short PIX_WATER_MS[] = {
  150,150,150,150,150
};

const uint64_t PIX_SUN[] = {
  0x00183c7e7e3c1800,
  0x005a3c7e7e3c5a00,
  0x815a3c7e7e3c5a81,
  0x81183c7e7e3c1881
};
const unsigned short PIX_SUN_MS[] = {
  200,200,200,200
};


struct SpriteMetadata
{
    String name;
    ExpressionEnum expression;
    const uint64_t* images;
    const unsigned short* interval;
    byte length;
    byte repeats;
    byte intensity;

};

SpriteMetadata sprites[] = {
  { .name = "Idle", .expression = IDLE, .images = PIX_IDLE, .interval = PIX_IDLE_MS, .length = sizeof(PIX_IDLE)/8, .repeats = 1, .intensity = 0 },
  { .name = "Happy", .expression = HAPPY, .images = PIX_HAPPY, .interval = PIX_HAPPY_MS, .length = sizeof(PIX_HAPPY)/8, .repeats = 3, .intensity = 0 },
  { .name = "Sad", .expression = SAD, .images = PIX_SAD, .interval = PIX_SAD_MS, .length = sizeof(PIX_SAD)/8, .repeats = 3, .intensity = 0 },
  { .name = "Curious", .expression = CURIOUS, .images = PIX_WHAT, .interval = PIX_WHAT_MS, .length = sizeof(PIX_WHAT)/8, .repeats = 2, .intensity = 0 },
  { .name = "Sleeping", .expression = SLEEPING, .images = PIX_SLEEP, .interval = PIX_SLEEP_MS, .length = sizeof(PIX_SLEEP)/8, .repeats = 3, .intensity = 0 },
  { .name = "Sun", .expression = SUN, .images = PIX_SUN, .interval = PIX_SUN_MS, .length = sizeof(PIX_SUN)/8, .repeats = 1, .intensity = 0 },
  { .name = "Water", .expression = WATER, .images = PIX_WATER, .interval = PIX_WATER_MS, .length = sizeof(PIX_WATER)/8, .repeats = 3, .intensity = 0 },
  { .name = "Heart", .expression = HEART, .images = PIX_HEART, .interval = PIX_HEART_MS, .length = sizeof(PIX_HEART)/8, .repeats = 3, .intensity = 0 },
  { .name = "Moon", .expression = MOON, .images = PIX_MOON, .interval = PIX_MOON_MS, .length = sizeof(PIX_MOON)/8, .repeats = 4, .intensity = 0 }
};

const byte SPRITE_METADATA_ARR_SIZE = sizeof(sprites) / sizeof(sprites[0]);


#endif