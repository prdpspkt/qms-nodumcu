#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DMDESP.h>
#include <fonts/Arial_bold_14.h>
#include <fonts/SystemFont5x7.h>

//SETUP DMD
#define DISPLAYS_WIDE 1 
#define DISPLAYS_HIGH 1 
DMDESP Disp(DISPLAYS_WIDE, DISPLAYS_HIGH); 

const char *ssid = "Terminal AP";
const char *password = "TerminalPass";

ESP8266WebServer server(80);
//----------------------------------------------------------------------
// SETUP

void handlePost(){
  String text = server.arg("text");
  String alphabet = server.arg("alphabet");
  if(text != ""){
    Disp.clear();
    if(alphabet != ""){   
    Disp.setFont(SystemFont5x7);
    Disp.drawText(1, 4, alphabet );
    }
    Disp.setFont(Arial_bold_14);
    Disp.drawText(7,2, text);
    server.send(200, "text/html", "");
  }
}

void handleGet()
{
  server.send(200, "text/htnl", "Ok");
}

void setup() {
  WiFi.softAP(ssid, password);
  // DMDESP Setup
  Disp.start(); // Jalankan library DMDESP
  Disp.setBrightness(100); // Tingkat kecerahan
  Disp.setFont(SystemFont5x7); // Tentukan huruf
  Disp.drawText(1, 4, "Smile");
  Serial.begin(115200);
  Serial.println(WiFi.softAPIP());

  server.on("/text", HTTP_POST, handlePost);
  server.on("/", HTTP_GET, handleGet);
  server.begin();
}



//----------------------------------------------------------------------
// LOOP

void loop() {
Disp.loop();
server.handleClient();
}