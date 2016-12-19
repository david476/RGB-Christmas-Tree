#include <Adafruit_NeoPixel.h>
#define PIN 5
#define LOWER_LENGTH 420
#define UPPER_LENGTH 30

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LOWER_LENGTH + UPPER_LENGTH, PIN, NEO_GRB + NEO_KHZ800);

int lowerLights[LOWER_LENGTH];
int upperLights[UPPER_LENGTH];

void setupLights() {
  strip.begin();
  strip.show();
  clearStrip();
  setupRainbowFade();
  loopRainbowFade();
  //setupSpacedPulses();
}

void loopLights() {
  loopRainbowFade();
  //loopSpacedPulses();
}

void writeLights() {
  for(int i = 0; i < LOWER_LENGTH; i++) {
    strip.setPixelColor(i, lowerLights[i]);
    httpServer.handleClient();
  }

  for(int i = LOWER_LENGTH; i < LOWER_LENGTH+UPPER_LENGTH; i++) {
    strip.setPixelColor(i, upperLights[i-LOWER_LENGTH]);
    httpServer.handleClient();
  }
  
  strip.show();
}

void setUpper(uint32_t c) {
  for(int i = 0; i < UPPER_LENGTH; i++) {
    upperLights[i] = c;
    httpServer.handleClient();
  }
}

void incrementLower() {
  for(int i = LOWER_LENGTH-1; i > 0; i--) {
    lowerLights[i] = lowerLights[i-1];
    httpServer.handleClient();
  }
  lowerLights[0] = 0;
}

void clearStrip() {
  for(int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, 0);
    httpServer.handleClient();
  }
  strip.show();
}

