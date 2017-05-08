void beep() {
    digitalWrite(PIN_BEEPER, HIGH);
    delay(200);                    
    digitalWrite(PIN_BEEPER, LOW);
    delay(200);                    
}
