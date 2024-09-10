/***************************************
 * Project Kontrol Timer
 * Board  : NodeMCU ESP8266 V3
 * Input  : Blynk (Timer)
 * Output : Relay 1 Ch
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
 
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <TimeLib.h>
#include <WidgetRTC.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//---GANTI SESUAI DENGAN TOKEN BLYNK ANDA
char auth[] = "CbS0l3x8agGfefffJ9GJ6b3G5kKE5Q4S";
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
char ssid[] = "ArdutechWiFi";  // Nama Hotspot/WiFi
char pass[] = "12345678";   //  Password
//==========================================
BlynkTimer timer;

WidgetRTC rtc;
// Digital clock display of the time
// alamat I2C LCD : 0x3f
// ukuran LCD : 16x2
LiquidCrystal_I2C lcd(0x3F,16,2);  
void clockDisplay()
{
  String currentTime = String(hour()) + ":" + minute() + ":" + second();
  String currentDate = String(day()) + " " + month() + " " + year();
  Serial.print("Current time: ");
  Serial.print(currentTime);
  Serial.print(" ");
  Serial.print(currentDate);
  Serial.println();
  lcd.setCursor(5,0);
  lcd.print(currentTime);
  lcd.setCursor(0,1);
  
  if(digitalRead(D5)==LOW){
    lcd.print("Switch OFF");    
  }
  else if(digitalRead(D5)==HIGH){
    lcd.print("Switch ON ");    
  }
  // Send time to the App
  Blynk.virtualWrite(V1, currentTime);
  // Send date to the App
  Blynk.virtualWrite(V2, currentDate);
}

BLYNK_CONNECTED() {
  // Synchronize time on connection
  rtc.begin();
}
//==============================
void setup()
{
  Serial.begin(9600);
  //pin SCL -- D1
  //pin SDA -- D2
  Wire.begin(D2, D1);  
  lcd.init(); 
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Timer Blynk");  
  delay(2000); 
  Blynk.begin(auth, ssid, pass);  
  setSyncInterval(10 * 60); // Sync interval in seconds (10 minutes)

  // Display digital clock every 10 seconds
  timer.setInterval(10000L, clockDisplay);
  lcd.clear();
  lcd.print("Time=");  
}
//==========================
void loop()
{
  Blynk.run(); 
   timer.run();
}
