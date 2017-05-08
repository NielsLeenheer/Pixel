Adafruit_NeoPixel matrix = Adafruit_NeoPixel(64, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

void setupMatrix() {
  matrix.begin();
  matrix.show(); 
}

void matrixFillColor(uint32_t color) {
  for (int i = 0; i < 64; i++) {
    matrix.setPixelColor(i, color);
  }
  
  matrix.show();
}

void matrixDrawPixel(uint32_t x, uint32_t y, uint32_t color) {
  matrix.setPixelColor(x + (y * 8), color);
  matrix.show();
}

void matrixDrawBitmap(String b) {
  for (int i = 0; i < 64; i++) {
     String value = b.substring(i * 6, (i * 6) + 6);
     long color = strtol( &value[0], NULL, 16);
     matrix.setPixelColor(i, color);
  }

  matrix.show();
}

void matrixDrawIcon(String id) {
  matrixDrawBitmap(getIcon(id));
}

void matrixDrawCanvas() {
  for (int i = 0; i < 64; i++) {
    matrix.setPixelColor(i, canvas[i]);
  }
  
  matrix.show();
}

void matrixAnimate(String id) {
  if (id == "wifi-searching") {
    matrixDrawIcon("wifi-1");
    delay(250);
    matrixDrawIcon("wifi-2");
    delay(250);
    matrixDrawIcon("wifi-3");
    delay(250);
  }

  if (id == "wifi-success") {
    matrixDrawIcon("wifi-4");
    delay(500);

    matrix.clear();
    matrix.show();
  }

  if (id == "wifi-failed") {
    matrixDrawIcon("wifi-1");
    delay(1500);
  
    matrix.clear();
    matrix.show();
    delay(500);

    matrixDrawIcon("dead");
    delay(1500);

    matrix.clear();
    matrix.show();
  }
}

void matrixSetBrightness(int brightness) {
  matrix.setBrightness(brightness);
}
