/***************************************
 * Project GPS Tracker dg Web Page
 * Board  : NodeMCU ESP8266 V3
 * Input  : Modul GPS NEO-6M Ublox
 * Output : Webpage
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
static const int RX= D6, TX= D7;
static const uint32_t GPSBaud = 9600;
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
const char* ssid     = "ArdutechWiFi"; // Nama Hotspot/WiFi
const char* password = "12345678";     //  Password
TinyGPSPlus gps;
WiFiClient  client;
WiFiServer server(80);
SoftwareSerial soft(RX, TX);
String latitude_data;
String longitude_data;
//=======================================
void setup()
{ 
  Serial.begin(9600);
  soft.begin(GPSBaud);
  WiFi.begin(ssid, password);
  server.begin();
  while (WiFi.status() != WL_CONNECTED)
  {
   delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("IP address : ");  
  Serial.println(WiFi.localIP());    
  delay(3000);
}
//==================================================
void loop()
{
  while (soft.available() > 0)
    if (gps.encode(soft.read()))
    {
      displaydata();
      displaywebpage();
    }
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("GPS Connection Error!!"));
    while (true);
  }
}
//===================================================
void displaydata()
{
  if (gps.location.isValid())
  {
    double latitude = (gps.location.lat());
    double longitude = (gps.location.lng());
    latitude_data= (String(latitude, 6));
    longitude_data= (String(longitude, 6));   
    delay(20000);
  }
  else
  {
    Serial.println(F("Data error!!!"));
  }
}

//==================================================
void displaywebpage()
{
    WiFiClient client = server.available();
    if (!client)
    {
      return;
    }
    String page = "<html><center><p><h1>GPS Tracker dg NodeMCU & NEO-6M</h1><a style=""color:RED;font-size:125%;"" href=""http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=";
    page += latitude_data;
    page += "+";
    page += longitude_data;
    page += ">Click here For Live Location</a> </p></center></html>";
    
    client.print(page);
    delay(100);
}
