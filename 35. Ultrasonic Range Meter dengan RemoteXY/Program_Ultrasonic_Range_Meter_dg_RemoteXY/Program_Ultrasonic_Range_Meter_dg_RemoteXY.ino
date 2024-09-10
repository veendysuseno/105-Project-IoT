/***************************************
 * Project Ultrasonic Range Meter dengan RemoteXY
 * Board  : NodeMCU ESP8266 V3
 * Input  : Sensor ultrasonic HC-SR04
 * Output : RemoteXY
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/

#define REMOTEXY_MODE__ESP8266WIFI_LIB_CLOUD
#include <ESP8266WiFi.h>
#include <RemoteXY.h>

//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA 
#define REMOTEXY_WIFI_SSID "ArdutechWiFi"
#define REMOTEXY_WIFI_PASSWORD "12345678"
#define REMOTEXY_CLOUD_SERVER "cloud.remotexy.com"
#define REMOTEXY_CLOUD_PORT 6376
//---GANTI SESUAI DENGAN TOKEN REMOTEXY ANDA
#define REMOTEXY_CLOUD_TOKEN "abb67f472e84cfe41f9c46326126e7e8"

const int trigP = D6;  
const int echoP = D5; 
long duration;
unsigned int distance;
// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,0,0,12,0,72,0,10,13,1,
  129,0,16,9,29,6,94,85,108,116,
  114,97,115,111,110,105,99,0,129,0,
  13,17,36,6,94,82,97,110,103,101,
  32,77,101,116,101,114,0,129,0,4,
  27,18,6,31,82,97,110,103,101,32,
  58,0,67,4,29,26,23,8,31,13,
  11,66,129,5,41,52,8,2,26 };
  
// this structure defines all the variables and events of your control interface 
struct {
  char text_1[11];  // string UTF8 end zero 
    // output variables
  int8_t level_1; // =0..100 level position 
    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 
} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////
void ReadUltrasonic()
{  
  digitalWrite(trigP, LOW);   
  delayMicroseconds(2);        
  digitalWrite(trigP, HIGH);  
  delayMicroseconds(10);      
  digitalWrite(trigP, LOW);   
  duration = pulseIn(echoP, HIGH);   
  distance= duration*0.034/2; 
  
  Serial.print("Distance = ");         
  Serial.print(distance);
  Serial.println(" cm");
}


void setup() 
{
  Serial.begin(9600); 
  pinMode(trigP, OUTPUT);  
  pinMode(echoP, INPUT);    
  RemoteXY_Init ();   
  // TODO you setup code  
}

void loop() 
{ 
  RemoteXY_Handler ();
  ReadUltrasonic();
  dtostrf(distance, 0, 0, RemoteXY.text_1); 
  // TODO you loop code
  // use the RemoteXY structure for data transfer
  int level=map(distance,0,300,0,100);
  RemoteXY.level_1 =level ;

}
