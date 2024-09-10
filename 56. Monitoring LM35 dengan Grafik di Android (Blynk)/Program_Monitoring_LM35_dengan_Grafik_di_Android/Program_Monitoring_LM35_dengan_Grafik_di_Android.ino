/***************************************
 * Project Ultrasonic Range Meter dengan Blynk
 * Board  : NodeMCU ESP8266 V3
 * Input  : Sensor ultrasonic HC-SR04
 * Output : Blynk
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#define BLYNK_PRINT Serial 
#include <BlynkSimpleEsp8266.h>
//---GANTI SESUAI DENGAN TOKEN BLYNK ANDA
char auth[] = "CbS0l3x8agGfefffJ9GJ6b3G5kKE5Q4S"; 
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
char ssid[] = "ArdutechWiFi"; // Nama Hotspot/WiFi
char pass[] = "12345678";     //  Password
BlynkTimer timer;
WidgetLCD lcd(V0);   
int analogValue;
float millivolts,celsius;
//==============================================
void setup()
{
  Serial.begin(9600);  
  delay(10);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(5000L, ReadLM35);  
  lcd.clear();
  lcd.print(0, 0, "Monitoring LM35 ");
  lcd.print(0, 1, "Tampilan Grafik");     
}

//=================================================
void ReadLM35()
{  
  analogValue = analogRead(A0);
  millivolts = (analogValue/1024.0) * 3300; 
  celsius = millivolts/10; 
  lcd.clear();
  lcd.print(0, 0, "Temp=");
  lcd.print(5,0,celsius);
  lcd.print(10,0,"C"); 
  Blynk.virtualWrite(V1, celsius);    
  Serial.print("Temperature = ");         
  Serial.print(celsius);
  Serial.println(" C");
}
//==================================================
void loop()
{
  Blynk.run();
  timer.run();
}
