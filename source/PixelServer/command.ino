String command = "";

void setCommand(String value) {
  command = value;
}

void handleCommands() {
  if (command != "") {
    Serial.print("Command found: ");
    Serial.println(command);

    if (command == "beep") {
      beep();
    }
    
    if (command == "tripple-beep") {
      beep();
      beep();
      beep();
    }

    if (command == "reset") {
      beep();
      ESP.restart();
    }
    
    command = "";
  }
}
