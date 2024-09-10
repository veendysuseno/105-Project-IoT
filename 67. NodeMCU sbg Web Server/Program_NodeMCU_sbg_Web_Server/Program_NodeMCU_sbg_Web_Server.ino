/***************************************
 * Project NodeMCU Sebagai Web Server
 * Board  : NodeMCU ESP8266 V3
 * Input  : -
 * Output : -
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
const char* ssid = "ArdutechWiFi";  // Nama Hotspot/WiFi     
const char* password = "12345678";  //Password     

ESP8266WebServer server(80);     
//==========================================
void setup() {
  Serial.begin(9600);
  Serial.print("Connecting to : ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);     
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  } 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/", []() {
  server.send(200, "text/plain", "NodeMCU sbg Web Server");
  });

  server.on("/cek1", []() {
    server.send(200, "text/plain", "Cek 1......");
  });
  server.on("/cek2", []() {
    server.send(200, "text/plain", "Cek 2......");
  });

  server.begin();
  Serial.println("Server Started....");
}
//==============================
void loop() {
   server.handleClient();
}
