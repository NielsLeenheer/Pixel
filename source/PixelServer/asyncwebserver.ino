AsyncWebServer server(80);

void setupWebServer() {
  server.on("/api", HTTP_GET, [](AsyncWebServerRequest *request){
    String response = "";

    if (request->arg("command") == "random") {
      canvasDrawBitmap(getRandomIcon());
      response = canvasGetBitmap();
    }
    
    else if (request->arg("command") == "get") {
      response = canvasGetBitmap();
    }
    
    else if (request->arg("command") == "draw" && request->hasArg("x") && request->hasArg("y") && request->hasArg("color")) {
      String value = request->arg("color");
      long color = strtol( &value[0], NULL, 16);

      value = request->arg("x");
      long x = strtol( &value[0], NULL, 10);

      value = request->arg("y");
      long y = strtol( &value[0], NULL, 10);

      canvasDrawPixel(x, y, color);
    }

    else if (request->arg("command") == "draw" && request->hasArg("color")) {
      String value = request->arg("color");
      long color = strtol( &value[0], NULL, 16);
      canvasFillColor(color); 
    }

    else if (request->arg("command") == "draw" && request->hasArg("bitmap")) {
      String bitmap = request->arg("bitmap");
      canvasDrawBitmap(bitmap);
    }

    else if (request->arg("command") == "draw" && request->hasArg("icon")) {
      String icon = request->arg("icon");
      canvasDrawBitmap(getIcon(icon));
    }

    else if (request->arg("command") == "save" && request->hasArg("icon") && request->hasArg("bitmap")) {
      String bitmap = request->arg("bitmap");
      String icon = request->arg("icon");
      saveIcon(icon, bitmap);
      canvasDrawBitmap(getIcon(icon));

      setCommand("beep");
    }

    else if (request->arg("command") == "notify" && request->hasArg("icon")) {  
      showNotification(request->arg("icon"));
    }

    request->send(200, "text/plain", response);
  });

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    if (captivePortal && handleCaptivePortalRequest(request)) {
      return;
    }

    request->redirect("/index.htm");
  });

  server.onNotFound([](AsyncWebServerRequest *request){
    if (captivePortal && handleCaptivePortalRequest(request)) {
      return;
    }
    
    request->send(404);
  });

  /* Add handlers for the captive portal */
  setupCaptivePortalWebServer();

  /* Add SPIFFS editor */
  if (DEBUG) {
    server.addHandler(new SPIFFSEditor("admin","admin"));
  }

  /* Add static files from SPIFFS */
  server.serveStatic("/", SPIFFS, "/web/").setDefaultFile("index.htm");

  /* Add Websocket server */
  setupWebsocketServer();
  
  /* Start web server */
  server.begin();
  Serial.println("HTTP server started");  
}
