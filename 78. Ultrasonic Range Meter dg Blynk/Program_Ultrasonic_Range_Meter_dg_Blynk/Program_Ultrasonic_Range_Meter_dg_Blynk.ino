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
const int trigP = D6;  
const int echoP = D5; 
//---GANTI SESUAI DENGAN TOKEN BLYNK ANDA
char auth[] = "-htbXm6E3Lizwp915_No7P516Ywa7nrj"; 
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
char ssid[] = "ArdutechWiFi";// Nama Hotspot/WiFi
char pass[] = "12345678";  //  Password
BlynkTimer timer;
WidgetLCD lcd(V0);   
long duration;
int distance;
//==============================================
void setup()
{
  Serial.begin(9600); 
  pinMode(trigP, OUTPUT);  
  pinMode(echoP, INPUT);    
  delay(10);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(5000L, ReadUltrasonic);  
  lcd.clear();
  lcd.print(0, 0, "Ultrasonic Range");
  lcd.print(0, 1, "Meter NodeMCU V3");     
}

//=================================================
void ReadUltrasonic()
{  
  digitalWrite(trigP, LOW);   
  delayMicroseconds(2);        
  digitalWrite(trigP, HIGH);  
  delayMicroseconds(10);      
  digitalWrite(trigP, LOW);   
  duration = pulseIn(echoP, HIGH);   
  distance= duration*0.034/2; 
  lcd.clear();
  lcd.print(0, 0, "Range=");
  lcd.print(6,0,distance);
  lcd.print(10,0,"cm"); 
  Blynk.virtualWrite(V1, distance);    
  Serial.print("Distance = ");         
  Serial.print(distance);
  Serial.println(" cm");
}
//==================================================
void loop()
{
  Blynk.run();
  timer.run();
}
