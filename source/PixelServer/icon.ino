String getIcon(String id) {
  if (id == "wifi-1") {
    return "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000ffffffffffff000000000000000000000000000000000000ffffffffffff";
  }
  else if (id == "wifi-2") {
    return "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000ffffffffffff000000000000000000000000000000ffffff000000000000000000000000000000000000000000ffffff000000ffffffffffff000000000000000000000000000000000000ffffffffffff";
  }
  else if (id == "wifi-3") {
    return "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000ffffffffffffffffff000000000000000000000000ffffff000000000000000000000000000000000000ffffff000000000000ffffffffffff000000000000000000ffffff000000ffffff000000000000000000000000000000ffffff000000ffffff000000ffffffffffff000000000000000000000000000000000000ffffffffffff";
  }
  else if (id == "wifi-4") {
    return "000000000000000000ffffffffffffffffffffffff000000000000000000ffffff000000000000000000000000000000000000ffffff000000000000ffffffffffffffffff000000ffffff000000000000ffffff000000000000000000000000ffffff000000ffffff000000000000ffffffffffff000000ffffff000000ffffff000000ffffff000000000000000000ffffff000000ffffff000000ffffff000000ffffffffffff000000000000000000000000000000000000ffffffffffff";
  }
  else if (id == "dead") {
    return "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff000000ffffffffffffffffff000000ffffffffffffffffffffffffffffff000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff000000ffffff000000ffffff000000ffffff000000000000000000ffffff000000ffffff000000ffffff000000000000";
  }  
  else if (id == "shirt") {
    return "000000000000ffffff000000000000ffffff000000000000000000ffffffffffffffffffffffffffffffffffff000000ffffffffffffffffffffffffffffffffffffffffffffffff000000ffffffffffffffffffffffffffffffffffff000000000000000000ffffffffffffffffffffffff000000000000000000000000ffffffffffffffffffffffff000000000000000000000000ffffffffffffffffffffffff000000000000000000000000ffffffffffffffffffffffff000000000000";
  }
  else if (id == "mailbox") {
    return "000000000000000000000000199409000000000000000000000000000000000000199409000000eaebea000000000000000000000000199409000000eaebea000000000000000000000000000000118211199409199409199409000000000000000000000000199409199409199409199409000000000000000000000000199409199409199409199409000000000000000000000000199409199409199409199409000000000000000000000000021c02199409199409021c02000000000000";
  }
  else if (id == "bell") {
    return "000000000000000000675408675408000000000000000000000000000000675408f2ce02f2ce02675408000000000000000000675408f2ce02f2ce02f2ce02f2ce02675408000000000000f2ce02f2ce02f2ce02f2ce02f2ce02f2ce02000000000000f2ce02f2ce02f2ce02f2ce02f2ce02f2ce02000000675408f2ce02f2ce02f2ce02f2ce02f2ce02f2ce02675408f2ce02f2ce02f2ce02f2ce02f2ce02f2ce02f2ce02f2ce02000000000000000000675408675408000000000000000000";
  }

  return getIconFromFile(id);
}

String getIconFromFile(String id) {
  String icon = "";

  fs::File iconFile = SPIFFS.open("/monsters/" + id + ".txt", "r");
  
  if (iconFile) {
    while (iconFile.available()) {
      byte b = iconFile.read();
      icon += (char) b;
    }

    iconFile.close();
  }  

  return icon;
}

void saveIcon(String id, String bitmap) {
  Serial.print("Saving icon with id ");
  Serial.println(id);
  Serial.println(bitmap);

  fs::File iconFile = SPIFFS.open("/monsters/" + id + ".txt", "w");
  if (iconFile) {
    Serial.print("File ");
    Serial.print("/monsters/" + id + ".txt");
    Serial.println(" opened");
    
    iconFile.println(bitmap);
    iconFile.close();

    Serial.println("Done!");
  }
}

String getRandomIcon() {
  int files = 0;
  String icon = "";

  /* Count the number of .txt files on the SPIFFS */
  fs::Dir root = SPIFFS.openDir("/monsters");
  while (root.next()) {
    String filename = root.fileName();
    
    filename.toLowerCase();
    if (filename.endsWith(".txt")) {
      Serial.print(filename);
      Serial.println();
      files++;
    }
  }

  /* Randomly choose a number */
  long r = random(0, files);

  /* Find the chosen file */
  files = 0;
  
  root = SPIFFS.openDir("/monsters");
  while (root.next()) {
    String filename = root.fileName();
    filename.toLowerCase();
    if (filename.endsWith(".txt")) {
      if (files == r) {
        fs::File entry = root.openFile("r");
        
        while (entry.available()) {
          byte b = entry.read();
          icon += (char) b;
        }

        entry.close();
        break;
      }
      
      files++;
    }
  }

  return icon;
}
