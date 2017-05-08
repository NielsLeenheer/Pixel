AsyncWebSocket ws("/ws");

void setupWebsocketServer() {
  ws.onEvent(onWsEvent);
  server.addHandler(&ws);
}

void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
  if (type == WS_EVT_CONNECT)
  {
    Serial.printf("ws[%s][%u] connect\n", server->url(), client->id());
    client->ping();
  }
  else if (type == WS_EVT_DISCONNECT)
  {
    Serial.printf("ws[%s][%u] disconnect: %u\n", server->url(), client->id());
  } 
  else if (type == WS_EVT_ERROR) 
  {
    Serial.printf("ws[%s][%u] error(%u): %s\n", server->url(), client->id(), *((uint16_t*)arg), (char*)data);
  } 
  else if(type == WS_EVT_PONG) 
  {
    Serial.printf("ws[%s][%u] pong[%u]: %s\n", server->url(), client->id(), len, (len)?(char*)data:"");
  } 
  else if (type == WS_EVT_DATA)
  {
    AwsFrameInfo * info = (AwsFrameInfo*)arg;
    String msg = "";
    if(info->final && info->index == 0 && info->len == len)
    {
      if (info->opcode == WS_TEXT) {
        for(size_t i=0; i < info->len; i++) {
          msg += (char) data[i];
        }
      } else {
        char buff[3];
        for(size_t i=0; i < info->len; i++) {
          sprintf(buff, "%02x ", (uint8_t) data[i]);
          msg += buff ;
        }
      }
      
      Serial.printf("%s\n",msg.c_str());

      handleJSON(msg);
    } 
    else 
    {
      if (info->opcode == WS_TEXT) {
        for(size_t i=0; i < info->len; i++) {
          msg += (char) data[i];
        }
      } else {
        char buff[3];
        for(size_t i=0; i < info->len; i++) {
          sprintf(buff, "%02x ", (uint8_t) data[i]);
          msg += buff ;
        }
      }

      Serial.printf("%s\n",msg.c_str());

      if (info->final) {
        handleJSON(msg);
      }
    }
  }
}

void handleJSON(String json) {
  /* Repeat command to all clients, so they can update their views too */
  ws.textAll(json);

  /* Parse the commands */
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);

  if (root["command"] == "draw" && root.containsKey("color") && root.containsKey("x") && root.containsKey("y")) {
    String value = root["color"].asString();
    long color = strtol( &value[0], NULL, 16);
  
    value = root["x"].asString();
    long x = strtol( &value[0], NULL, 10);
  
    value = root["y"].asString();
    long y = strtol( &value[0], NULL, 10);
  
    canvasDrawPixel(x, y, color);
  }

  else if (root["command"] == "draw" && root.containsKey("color")) {
    String value = root["color"].asString();
    long color = strtol( &value[0], NULL, 16);
    canvasFillColor(color); 
  }

  else if (root["command"] == "draw" && root.containsKey("bitmap")) {
    String bitmap = root["bitmap"].asString();
    canvasDrawBitmap(bitmap);
  }

  else if (root["command"] == "draw" && root.containsKey("icon")) {
    String icon = root["icon"].asString();
    canvasDrawBitmap(getIcon(icon));
  }
}
