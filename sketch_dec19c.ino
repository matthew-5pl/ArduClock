#include <Adafruit_NeoPixel.h>
#include <arduino-timer.h>
#define NUMPIXELS 12
#define PIN 6
#define TIME 10

Adafruit_NeoPixel pix = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

Timer<2> timer;

int h = 0;
int m = 0;
int s = 0;
int fs = 0;

bool clock() {
  s+=1;
  if(s >= 60) {
    s=0;
    m+=1;
  }
  if(m >= 60) {
    m=0;
    h+=1;
  }
  if(m >= 12) {
    m=0;
  }
  if(h >= 12) {
    h=0;
  }
  for(int i = 0; i < NUMPIXELS; i++)
  {
    pix.setPixelColor(i, pix.Color(0,0,0));
    pix.show();
  }
  pix.setPixelColor(fs, pix.Color(255,0,0));
  pix.setPixelColor(m, pix.Color(0,255,0));
  pix.setPixelColor(h, pix.Color(0,0,255));
  pix.show();
  return true;  
}

bool seconds() {
  fs+=1;
  if(fs >= 12) {
    fs=0;
  }
  return true;
}

void setup() {
  pix.begin();
  pix.setBrightness(50);
  for(int i = 0; i < NUMPIXELS; i++)
  {
    pix.setPixelColor(i, pix.Color(0,0,0));
    pix.show();
  }
}

void loop() {
  timer.tick();
  timer.every(1000, clock);
  timer.every(5000, seconds);
}
