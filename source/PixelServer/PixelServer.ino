#define FS_NO_GLOBALS true;

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <FS.h>
#include <DNSServer.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFSEditor.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>

#define SECONDS 100000;


/* Debug mode */
const boolean DEBUG = true;


/* Set up which PIN is used for which function */
const int PIN_NEOPIXEL = D1;
const int PIN_FLASH_BUTTON = D3;
const int PIN_BEEPER = D2;
const int PIN_PHOTORESISTOR = A0;


/* Default configuration */
char* ssid = "********";
char* password = "********";
char* mdns = "pixel";


/* Default variables */
boolean captivePortal = false;


void setup(void){
  /* Enable serial port for debugging */
  Serial.begin(115200);

  /* Set up the proper mode for the PINs we are going to use */
  pinMode(PIN_BEEPER, OUTPUT);
  pinMode(PIN_FLASH_BUTTON, INPUT);

  /* Initialize the LED matrix */
  setupMatrix();

  /* Read configuration from the SPIFFS */
  SPIFFS.begin();

  if (restoreToFactorySettings()) {
    Serial.println("Restore to factory settings");
    ssid = "********";
    password = "********";
    saveConfiguration();
  } else {
    readConfiguration();
  }

  /* Measure the light and set the brightness */
  updateBrightness(false);

  /* Seed the random generator */
  randomSeed(analogRead(0));


  /* Connect to the WiFi */  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  matrixAnimate("wifi-searching");

  Serial.println("");
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("Password: ");
  Serial.println(password);

  byte retries = 0;
  
  while (WiFi.status() != WL_CONNECTED && retries < 10) {
    matrixAnimate("wifi-searching");
    Serial.print(".");
    retries++;
  }

  captivePortal = WiFi.status() != WL_CONNECTED;

  if (captivePortal) {
    WiFi.disconnect(true);

    Serial.println("Starting AP mode");

    /* Set up Access Point */
    WiFi.mode(WIFI_AP);
    WiFi.softAP(mdns);
    delay(500);

    /* Set up the captive portal */
    setupCaptivePortal();

    Serial.println("");
    Serial.print("Connect to ");
    Serial.println(mdns);
    Serial.print("IP address: ");
    Serial.println(WiFi.softAPIP());

    /* Animate the icon */
    matrixAnimate("wifi-failed");    
  } 
  
  else {
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  
    /* Animate the icon */
    matrixAnimate("wifi-success");
  }

  /* Set up mDNS */
  if (MDNS.begin(mdns)) {
    Serial.println("MDNS responder started");
  }

  /* Start the webserver */
  setupWebServer();
}

void loop(void){
  /* Handle captive portal */
  if (captivePortal) {
    loopCaptivePortal();
  }

  /* Check if the flash button is pressed */
  if (digitalRead(PIN_FLASH_BUTTON) == LOW) {
    //beep();
    canvasDrawBitmap(getRandomIcon());
    delay(500);
  }

  /* Handle commands that can't be executed async */
  handleCommands();

  /* Clear notifications */
  clearNotification();

  /* Update brightness */
  updateBrightness(true);
}
