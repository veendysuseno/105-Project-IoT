/***************************************
 * Project Monitoring Accelerometer
 * Board  : NodeMCU ESP8266 V3
 * Input  : Sensor MPU-6050
 * Output : Blynk
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#include<Wire.h>
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
#define WLAN_SSID       "ArdutechWiFi"
#define WLAN_PASS       "12345678"
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
//---GANTI SESUAI DENGAN USER NAME ADAFRUIT  ANDA
#define AIO_USERNAME    "ArdutechJogja"
//---GANTI SESUAI DENGAN IO KEY ADAFRUIT ANDA
#define AIO_KEY         "aio_mAXJ90DJnEIBVj0IDmG6BIMZqMAW"

const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ;
int16_t temp;
int minVal=265;
int maxVal=402;

double x;
double y;
double z;

WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Publish temperature = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temperature");
Adafruit_MQTT_Publish angle_x = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/accel_x");
Adafruit_MQTT_Publish angle_y = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/accel_y");
Adafruit_MQTT_Publish angle_z = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/accel_z");

void MQTT_connect();
//=============================================
void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  delay(5000); 
}
//=======================================
void loop(){
  MQTT_connect();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);
  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
  temp = Wire.read()<<8 | Wire.read(); //
  int xAng = map(AcX,minVal,maxVal,-90,90);
  int yAng = map(AcY,minVal,maxVal,-90,90);
  int zAng = map(AcZ,minVal,maxVal,-90,90);

  x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
  y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
  z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);
  temp=temp/340.00+36.53;

  if (! temperature.publish(temp)) {
      Serial.println(F("Publish Temperature Failed"));
      } else {
      Serial.println(F("Publish Temperature OK!"));
    }    
    
  if (! angle_x.publish(x)) {
      Serial.println(F("Publish Angle X Failed"));
      } else {
      Serial.println(F("Publish Angle X OK!"));
    }
    
  if (! angle_y.publish(y)) {
      Serial.println(F("Publish Angle Y Failed"));
      } else {
      Serial.println(F("Publish Angle Y OK!"));
    }
    
  if (! angle_z.publish(z)) {
      Serial.println(F("Publish Angle Z Failed"));
      } else {
      Serial.println(F("Publish Angle Z OK!"));
    }

  Serial.print("Temperature= ");
  Serial.println(temp);
  
  Serial.print("AngleX= ");
  Serial.println(x);

  Serial.print("AngleY= ");
  Serial.println(y);

  Serial.print("AngleZ= ");
  Serial.println(z);
  Serial.println("-----------------------------------------");  
  delay(5000);
}
//===============================================
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
