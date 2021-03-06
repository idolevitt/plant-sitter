/*
 * This file is responsible for making the ciruit express say "water me"
 */
 
#include <Wire.h>
#include <SPI.h>

const uint8_t spWATER[]         PROGMEM = {0xAA, 0x15, 0x7A, 0x23, 0x5C, 0x12, 0xE9, 0xD1, 0x0D, 0x5A, 0x76, 0x75, 0xB2, 0xAA, 0xD0, 0x3B, 0xD9, 0xED, 0x81, 0x99, 0x4A, 0x1B, 0xD5, 0x8C, 0x25, 0xFA, 0xDD, 0xF5, 0xA9, 0xA3, 0x9F, 0x2C, 0xE3, 0x2E, 0xB7, 0xBE, 0xCD, 0xEE, 0xD6, 0x9C, 0xDC, 0x44, 0xAB, 0xAD, 0x6E, 0x67, 0x0E, 0xE9, 0xCD, 0x7D, 0xBB, 0x1E, 0x0C, 0x1C, 0x24, 0xCA, 0x5C, 0x59, 0x03, 0x00, 0x01, 0xB6, 0x2A, 0x15,   0xEA, 0x4C, 0x01, 0xD8, 0x2E, 0xC8, 0x03, 0xA3, 0xAB, 0x91, 0x39, 0x2C, 0x17, 0x8D, 0xAE, 0x36, 0xE6, 0x34, 0x7F, 0x3D, 0xE6, 0xEA, 0x13, 0x6C, 0x79, 0x73, 0x3B, 0xAA, 0x1B, 0xB0, 0xD3, 0x3C, 0xFD, 0x6A, 0x4F, 0xF1, 0x09, 0x35, 0x9E, 0xA5, 0xBE, 0xFF, 0x0F};

const uint8_t spME[]         PROGMEM = {0xA1, 0x8F, 0x5C, 0xB5, 0x56, 0x92, 0xE4, 0xE1, 0xF4, 0xDD, 0x0B, 0x59, 0x6B, 0xE3, 0x53, 0x8C, 0x14, 0x44, 0x15, 0x8B, 0x46, 0x3A, 0xB3, 0x03, 0x7B, 0xBE, 0x99, 0x89, 0x49, 0xB7, 0x72, 0xC4, 0xEA, 0x4C};

void playWaterMeSound();
void sosMessage(int value);

/*
    plays "WATER ME"
*/
void playWaterMeSound() {
  SerialMon.println(" fail");
  CircuitPlayground.speaker.say(spWATER);
  delay(300);
  CircuitPlayground.speaker.say(spME);
  CircuitPlayground.speaker.end();
}

/*
    plays "WATER ME" and blinks red lights
*/
void sosMessage() {
  playWaterMeSound();
  for (int j = 0; j < 5; ++j) {
    for (int i = 0; i < 10; ++i) {
      CircuitPlayground.setPixelColor(i, 255, 0, 0);
    }
    delay(500);
    for (int i = 0; i < 10; ++i) {
      CircuitPlayground.setPixelColor(i, 0, 0, 0);
    }
    delay(500);
  }
  playWaterMeSound();
}
