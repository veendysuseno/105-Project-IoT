/***************************************
 * Project Kontrol LED via Web server
 * Board  : NodeMCU ESP8266 V3
 * Input :  
 *  MQ2 ---------- D3
 *  Door sensor -- D2
 *  DHt22 -------- D4
 * Output : 
 *  Buzzzer -- D1
 *  RL1 (lamp1) -- D5
 *  RL3 (Fan)   -- D6
 *  Servo       -- D7
 * 99 Proyek IoT
 * www.ardutech.com
 * ***********************************/

#define BLYNK_PRINT Serial    
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>
#include <TimeLib.h>
#include <DHT.h>
#define doorSensor D2 // sensor jendela
#define MQ2Pin D3 // sensor MQ2
#define DHTPIN D4 // DHT11 terhubung dengan PIN D4 NODEMCU

DHT dht(DHTPIN, DHT22); 
Servo servo;
//Ganti dengan Token Blynk anda
char auth[] = "-htbXm6E3Lizwp915_No7P516Ywa7nrj";
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
char ssid[] = "ArdutechWiFi"; // Nama Hotspot
char pass[] = "12345678";     // Password               
BlynkTimer timer; 
float temp,humi;
int doorValue; 
int MQ2Value; 

//==========================================
BLYNK_WRITE(V3){
  int buttonState = param.asInt();
  if(buttonState==HIGH){
    servo.write(0);
    delay(100);
  }
  else if(buttonState==LOW){
    delay(100);
    servo.write(90);
  }
}

//==============================================
void sendDHT22()
{  
  humi = dht.readHumidity();
  temp = dht.readTemperature();
  if (isnan(humi) || isnan(temp)) {
    Serial.println("DHT22 tidak terbaca... !");
    return;
  }
  else{   
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.print(" Celcius Humidity: ");
    Serial.println(humi);
    Blynk.virtualWrite(0, temp); 
    Blynk.virtualWrite(1, humi); 
  }
  
}
//============================================
void getDoorSensor(void)
{
  doorValue = digitalRead(doorSensor);
  if (doorValue) 
  { 
    Serial.println("==> Jendela Terbuka !!");    
    Blynk.notify("Jendela Terbuka !!!");  
    delay(1000);
  }  
}
//============================================
void getMQ2Value(void)
{
  MQ2Value = digitalRead(MQ2Pin);
  if (!MQ2Value) 
  { 
    Serial.println("==>Gas terdeteksi");    
    Blynk.notify("Kebocoran Gas terdeteksi.....!");  
    delay(1000);
  }  
}
//===========================================
void setup()
{
  pinMode(D1,OUTPUT);
  digitalWrite(D1,LOW);
  pinMode(D5,OUTPUT);
  digitalWrite(D5,HIGH);
  pinMode(D6,OUTPUT);
  digitalWrite(D6,HIGH);
  Serial.begin(9600);
  dht.begin(); 
  servo.attach(D7); // 1 
  delay(50);
  timer.setInterval(1000, sendDHT22);
  Blynk.begin(auth, ssid, pass);  
  delay(1000);  
  pinMode(doorSensor, INPUT);
  digitalWrite(doorSensor,HIGH);
  pinMode(MQ2Pin, INPUT);   
  servo.write(90);  
}
//==========================================
void loop()
{
  Blynk.run();
  timer.run(); 
  getDoorSensor();
  getMQ2Value();
}
