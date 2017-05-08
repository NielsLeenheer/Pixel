boolean restoreToFactorySettings() {
  delay(500);

  if (digitalRead(PIN_FLASH_BUTTON) == LOW) {
    int loops = 0;

    while (digitalRead(PIN_FLASH_BUTTON) == LOW) {
      loops++;

      if (loops == 50) {
        beep();
      }

      delay(50);
    }

    if (loops >= 50) {
      return true;
    }
  }

  return false;
}
