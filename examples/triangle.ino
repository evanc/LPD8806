#include <Adafruit_GFX.h>
#include "LPD8806.h"
#include "SPI.h"

// pins for the LED module
int dataPin = 4;
int clockPin = 5;

int j = 0;
int c =0;

// Color definitions
#define RED      0xF800
#define GREEN    0x07E0

#define WIDTH 16
#define HEIGHT 10
#define STRIPLENGTH 160

LPD8806 strip = LPD8806(WIDTH, HEIGHT, STRIPLENGTH, dataPin, clockPin);

struct corner {
  int x;
  int y;
  boolean Dx;
  boolean Dy;
} cornera, cornerb, cornerc;

corner corners [3] = {cornera, cornerb, cornerc};

void setup() {
  strip.begin();
  strip.show();

  for (c = 0; c < 3; c++) {
    corners[c].x = random(0, WIDTH);
    corners[c].y = random(0, HEIGHT);
    corners[c].Dx = random(0, 2) == 0;
    corners[c].Dy = random(0, 2) == 0;
  }
}

void loop() {
  strip.fillScreen(0);
  
  for (c = 0; c < 3; c++) {
    int projX = corners[c].x + (corners[c].Dx ? 1 : -1);
    if (projX > WIDTH || projX < 0) {
       corners[c].Dx = !corners[c].Dx;
    }
    int projY = corners[c].y + (corners[c].Dy ? 1 : -1);
    if (projY > HEIGHT || projY < 0) {
       corners[c].Dy = !corners[c].Dy;
    }
    
    corners[c].x += (corners[c].Dx ? 1 : -1);
    corners[c].y += (corners[c].Dy ? 1 : -1);
  
  }
  
  strip.fillTriangle(corners[0].x, corners[0].y, corners[1].x, corners[1].y, corners[2].x, corners[2].y, GREEN);  
  strip.drawTriangle(corners[0].x, corners[0].y, corners[1].x, corners[1].y, corners[2].x, corners[2].y, RED);

  strip.show();
  delay(40);
}
