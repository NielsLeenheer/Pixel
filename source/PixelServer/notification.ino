long notificationTimeout = 0;

void showNotification(String icon) {
  Serial.println("Show notification...");

  matrixDrawIcon(icon);
  setCommand("tripple-beep");
  notificationTimeout = 30 * SECONDS;
}

void clearNotification() {
  if (notificationTimeout > 0) {
    notificationTimeout--;

    if (notificationTimeout == 0) {
      matrixDrawCanvas();
      Serial.println("Clear notification...");
    }
  }
}

boolean hasNotification() {
  return notificationTimeout != 0;
}
