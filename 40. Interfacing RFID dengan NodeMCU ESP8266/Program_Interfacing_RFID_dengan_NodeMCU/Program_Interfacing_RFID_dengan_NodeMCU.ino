/***************************************
 * Project Interfacing RFID dengan NodeMCU V3
 * Board  : NodeMCU ESP8266 V3
 * Input  : RFID RC-522
 * Output : Serial Monitor, Web page
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/

#include<Wire.h> 
#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>

#define SS_PIN D4  
#define RST_PIN D3 
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
const char* ssid     = "ArdutechWiFi"; // Nama Hotspot/WiFi
const char* password = "12345678"; //  Password

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int statuss = 0;
int out = 0;
WiFiServer server(80);
String ID_TAG;
//============
void readRFID(byte *buffer, byte bufferSize)
{
  ID_TAG="";
  for(byte i = 0;i<bufferSize; i++)
  {
    ID_TAG=ID_TAG+String(buffer[i], HEX);
  }
}
//==============================
void setup() 
{
  Serial.begin(9600);   
  SPI.begin();      
  mfrc522.PCD_Init();   
  Serial.println();  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi is connected");
  
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
  delay(3000);
  Serial.println("Tempelkan kartu RFID");
  server.begin();
}
void loop() 
{     
   if(!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()){
     
   }    
  readRFID(mfrc522.uid.uidByte, mfrc522.uid.size);  
  Serial.print("UID RFID :");
  Serial.println(ID_TAG);

  WiFiClient client = server.available();
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");  
  client.println("Refresh: 10");  
  client.println();
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.print("<p style='text-align: center;'><span style='font-size: x-large;'><strong>RFID Reader</strong></span></p>");
  client.println("<hr size='5px' color='red' width='30%' align='centre'>");
  client.print("<p style='text-align: center;'><span style='font-size: x-large;'>www.ardutech.com</span></p>");
  client.print("<p style='text-align: center;'><span style='color: #0000ff;'><strong style='font-size: large;'>RFID= ");
  client.println(ID_TAG); 
  client.print("</p>");
  client.println("</html>");
  delay(2000); 
} 
