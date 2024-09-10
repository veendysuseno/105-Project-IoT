/***************************************
 * Project Cat Food Feeder Online 
 * Board  : NodeMCU ESP8266 V3
 * Input  : Android (Blynk)
 * Output : Motor Servo
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>
Servo myservo;

//---GANTI SESUAI DENGAN TOKEN BLYNK ANDA
char auth[] = "-htbXm6E3Lizwp915_No7P516Ywa7nrj";
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
char ssid[] = "ArdutechWiFi";  // Nama Hotspot/WiFi
char pass[] = "12345678";      //  Password

BLYNK_WRITE(V0){
  int tb = param.asInt();
  if (tb==1){
    myservo.write(0);  //buka pakan
    delay(2000);
    myservo.write(90);  //tutup pakan
    Blynk.virtualWrite(V0,LOW); //ganti tombol menjadi OFF kembali
  }
}
//=================================
void setup()
{
  Serial.begin(9600);
  myservo.attach(D5);
  myservo.write(90);//tutup pakan
  Blynk.begin(auth, ssid, pass);
}
//==================================
void loop()
{
  Blynk.run();
}
