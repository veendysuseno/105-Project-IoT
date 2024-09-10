/***************************************
 * Project Early Warning Kebocoran Gas via Email
 * Board  : NodeMCU ESP8266 V3
 * Input  : MQ2
 * Output : email
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#include <ESP8266WiFi.h>
#define MQ2Pin D5 
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
const char* ssid = "ArdutechWiFi";  // Nama Hotspot/WiFi
const char* password = "12345678";  //  Password
const char* host = "maker.ifttt.com";
//---GANTI SESUAI DENGAN API KEY ANDA
const char* apiKey = "dJu1HVacDg29kd5yuEOksz";
int MQ2Value; 
//==================================================
void kirim_email(){
    Serial.print("Connecting to ");
    Serial.println(host);          
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
            Serial.println("connection failed");
            return;
        }    
    String url = "/trigger/GAS_ON/with/key/";
    url += apiKey;
    Serial.print("Requesting URL: ");
    Serial.println(url);
    client.print(String("POST ") + url + " HTTP/1.1\r\n" +
    "Host: " + host + "\r\n" + 
    "Content-Type: application/x-www-form-urlencoded\r\n" + 
    "Content-Length: 13\r\n\r\n" +
    "value1=" + "BAHAYA" + "\r\n");
    delay(20000);   
}
//===============================================
void setup() {
    Serial.begin(9600);
    Serial.println("Kirim email dg IFTTT");
    delay(100);
    pinMode(MQ2Pin, INPUT);    
    Serial.print("Connecting to ");
    Serial.println(ssid);    
    WiFi.begin(ssid, password);    
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("WiFi connected");
    Serial.println("");    
    
}
//==================================================
void loop() {  
   MQ2Value = digitalRead(MQ2Pin);  
   if (!MQ2Value){
      Serial.println("Gas terdeteksi...");
      Serial.println("Kirim email...");
      kirim_email();       
   }
     
}
