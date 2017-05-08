int brightness = 50;
int brightnessFactor = 16;
int brightnessUpdate = 0;
int brightnessPrevious = 0;

void updateBrightness(boolean restore) {
  brightnessUpdate--;

  if (brightnessUpdate < 0) {
    int value = analogRead(PIN_PHOTORESISTOR);
    Serial.println(value);
    brightnessUpdate = 5 * SECONDS;

    brightnessPrevious = brightness;
    brightness = (16 - (value >> 6)) * brightnessFactor;

    if (brightnessPrevious != brightness) {
      Serial.print("Brightness changed from ");
      Serial.print(brightnessPrevious);
      Serial.print(" to ");
      Serial.println(brightness);
  
      if (restore && !hasNotification()) {
        matrixSetBrightness(brightness);  
        matrixDrawCanvas();
      }
      else {
        matrixSetBrightness(brightness);
      }
    }
  }
}
