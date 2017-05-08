uint32_t canvas[64];

void canvasFillColor(uint32_t color) {
  for (int i = 0; i < 64; i++) {
    canvas[i] = color;
  }

  if (!hasNotification()) {
    matrixFillColor(color);
  }
}

void canvasDrawPixel(uint32_t x, uint32_t y, uint32_t color) {
  canvas[x + (y * 8)] = color;

  if (!hasNotification()) {
    matrixDrawPixel(x, y, color);
  }
}

void canvasDrawBitmap(String b) {
  for (int i = 0; i < 64; i++) {
     String value = b.substring(i * 6, (i * 6) + 6);
     canvas[i] = strtol( &value[0], NULL, 16);
  }

  if (!hasNotification()) {
    matrixDrawBitmap(b);
  }
}

String canvasGetBitmap() {
  String buffer = "";
  char hex[6] = "";
  
  for (int i = 0; i < 64; i++) {
    sprintf(hex, "%06x", canvas[i]);
    buffer += hex;
  }

  return buffer;
}
