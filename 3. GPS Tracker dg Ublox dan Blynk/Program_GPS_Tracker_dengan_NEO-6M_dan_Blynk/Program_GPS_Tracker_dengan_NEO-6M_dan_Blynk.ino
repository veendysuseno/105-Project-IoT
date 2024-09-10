/***************************************
 * Project GPS Tracker dg Blynk
 * Board  : NodeMCU ESP8266 V3
 * Input  : Modul GPS NEO-6M Ublox
 * Output : Blynk
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/

#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

static const int RXPin = D6, TXPin = D7;  
static const uint32_t GPSBaud = 9600; 

TinyGPSPlus gps; 
WidgetMap myMap(V0);  

SoftwareSerial ss(RXPin, TXPin);  

BlynkTimer timer;

float spd;      
float sats;      
String bearing;  
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA            
char ssid[] = "ArdutechWiFi";  // Nama Hotspot/WiFi                                     
char pass[] = "12345678";    //  Password   
//---GANTI SESUAI DENGAN TOKEN BLYNK ANDA 
char auth[] = "-htbXm6E3Lizwp915_No7P516Ywa7nrj";  
unsigned int move_index = 1;       
//===================================================
void setup()
{
  Serial.begin(9600);
  Serial.println();
  ss.begin(GPSBaud);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(5000L, checkGPS); 
}

void checkGPS(){
  if (gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
      Blynk.virtualWrite(V4, "GPS ERROR"); 
  }
}

void loop()
{
 
    while (ss.available() > 0) 
    {
      // sketch displays information every time a new sentence is correctly encoded.
      if (gps.encode(ss.read()))
        displayInfo();
  }
  Blynk.run();
  timer.run();
}

void displayInfo()
{ 

  if (gps.location.isValid() ) 
  {
    
    float latitude = (gps.location.lat());     //Storing the Lat. and Lon. 
    float longitude = (gps.location.lng()); 
    
    Serial.print("LAT:  ");
    Serial.println(latitude, 6);  
    Serial.print("LONG: ");
    Serial.println(longitude, 6);
    Blynk.virtualWrite(V1, String(latitude, 6));   
    Blynk.virtualWrite(V2, String(longitude, 6));  
    myMap.location(move_index, latitude, longitude, "GPS_Location");
    spd = gps.speed.kmph();               
       Blynk.virtualWrite(V3, spd);       
       sats = gps.satellites.value();    
       Blynk.virtualWrite(V4, sats);
       bearing = TinyGPSPlus::cardinal(gps.course.value()); 
       Blynk.virtualWrite(V5, bearing);         
    
  }
  

  Serial.println();
}
