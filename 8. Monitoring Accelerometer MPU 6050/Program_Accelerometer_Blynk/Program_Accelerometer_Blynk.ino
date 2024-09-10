/***************************************
 * Project Monitoring Accelerometer
 * Board  : NodeMCU ESP8266 V3
 * Input  : Sensor MPU-6050
 * Output : Blynk
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/

#include<Wire.h>
#define BLYNK_PRINT Serial
#include <Blynk.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
char ssid[] = "ArdutechWiFi";  // Nama Hotspot/WiFi                     
char pass[] = "12345678";     //  Password
//---GANTI SESUAI DENGAN TOKEN BLYNK ANDA
char auth[] = "CbS0l3x8agGfefffJ9GJ6b3G5kKE5Q4S";       

const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ;

int minVal=265;
int maxVal=402;

double x;
double y;
double z;
//=============================================
void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  delay(5000); 
}
//=======================================
void loop(){
  Blynk.run();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);
  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
  int xAng = map(AcX,minVal,maxVal,-90,90);
  int yAng = map(AcY,minVal,maxVal,-90,90);
  int zAng = map(AcZ,minVal,maxVal,-90,90);

  x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
  y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
  z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);

  Serial.print("AngleX= ");
  Serial.println(x);

  Serial.print("AngleY= ");
  Serial.println(y);

  Serial.print("AngleZ= ");
  Serial.println(z);
  Serial.println("-----------------------------------------");

  Blynk.virtualWrite(V1, x);
  Blynk.virtualWrite(V2, y);
  Blynk.virtualWrite(V3, z);
  delay(1000);
}
