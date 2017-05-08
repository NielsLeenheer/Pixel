DNSServer dnsServer;

void setupCaptivePortal() {
  dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer.start(53, "*", WiFi.softAPIP());
  Serial.println("DNS server started");
}

void loopCaptivePortal() {
  dnsServer.processNextRequest();
}

void setupCaptivePortalWebServer() {
  server.on("/ping", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "pong");
  });

  server.on("/reset", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "");
    setCommand("reset");
  });

  server.on("/config", HTTP_GET, [](AsyncWebServerRequest *request){
    if (request->hasArg("ssid") && request->hasArg("password")) {
      String ssidString = request->arg("ssid");
      ssid = const_cast<char*>(ssidString.c_str());

      String passwordString = request->arg("password");
      password = const_cast<char*>(passwordString.c_str());

      saveConfiguration();
    }
    
    request->send(200, "text/plain", "");
  });

  server.on("/scan", HTTP_GET, [](AsyncWebServerRequest *request){
    String json = "[";
    int n = WiFi.scanComplete();
    
    Serial.print("WiFi.scanComplete(): ");
    Serial.println(n);
    
    if (n == -2){
      WiFi.scanNetworks(true);
    } else if (n) {
      for (int i = 0; i < n; ++i) {
        if (i) json += ",";
        json += "{";
        json += "\"rssi\":"+String(WiFi.RSSI(i));
        json += ",\"ssid\":\""+WiFi.SSID(i)+"\"";
        json += ",\"bssid\":\""+WiFi.BSSIDstr(i)+"\"";
        json += ",\"channel\":"+String(WiFi.channel(i));
        json += ",\"secure\":"+String(WiFi.encryptionType(i));
        json += ",\"hidden\":"+String(WiFi.isHidden(i)?"true":"false");
        json += "}";
      }
      WiFi.scanDelete();
      if (WiFi.scanComplete() == -2) {
        WiFi.scanNetworks(true);
      }
    }
    json += "]";
    request->send(200, "text/json", json);
    json = String();
  }); 
}

boolean handleCaptivePortalRequest(AsyncWebServerRequest *request) {
  if (!isIp(request->host()) && request->host() != String(mdns) + ".local") {
    Serial.println("Redirecting to http://" + toStringIp(WiFi.softAPIP()) + "/setup.htm");

    AsyncWebServerResponse *response = request->beginResponse (302, "text/plain", "");
    response->addHeader("Cache-Control", "no-cache, no-store, must-revalidate");
    response->addHeader("Pragma", "no-cache");
    response->addHeader("Expires", "-1");
    response->setContentLength(0);
    response->addHeader("Location", "http://" + toStringIp(WiFi.softAPIP()) + "/setup.htm");
    request->send(response);
    
    return true;
  }  

  return false;
}
