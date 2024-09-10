/***************************************
 * Project Monitoring Volume Tangki dg RemoteXY
 * Board  : NodeMCU ESP8266 V3
 * Input  : Sensor Ultrasonic HC-SR04
 * Output : RemoteXY
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#define REMOTEXY_MODE__ESP8266WIFI_LIB_CLOUD
#include <ESP8266WiFi.h>
#include <RemoteXY.h>

//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
#define REMOTEXY_WIFI_SSID "ArdutechWiFi"  // Nama Hotspot/WiFi
#define REMOTEXY_WIFI_PASSWORD "12345678"  //  Password
#define REMOTEXY_CLOUD_SERVER "cloud.remotexy.com"
#define REMOTEXY_CLOUD_PORT 6376
//---GANTI SESUAI DENGAN TOKEN BLYNK ANDA
#define REMOTEXY_CLOUD_TOKEN "a95f45aa4292ce11414e54ef54181a78"

const int trigP = D6;  
const int echoP = D5; 
long duration;
unsigned int distance;
unsigned int volume,h2,la;
// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
   { 255,0,0,12,0,75,0,10,13,1,
  129,0,17,7,31,6,17,77,111,110,
  105,116,111,114,105,110,103,0,129,0,
  12,16,41,6,17,86,111,108,117,109,
  101,32,84,97,110,103,107,105,0,129,
  0,8,29,18,6,24,86,111,108,117,
  109,101,32,58,0,67,4,35,28,21,
  7,24,13,11,66,1,16,40,32,47,
  204,31 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // output variables
  char text_1[11];  // string UTF8 end zero 
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
  if (distance>100)distance=100;
  h2=100-distance;
  volume=la*h2/1000;
  Serial.print("Volume = ");         
  Serial.print(volume);
  Serial.println(" liter");
}


void setup() 
{
  Serial.begin(9600); 
  pinMode(trigP, OUTPUT);  
  pinMode(echoP, INPUT);    
  RemoteXY_Init (); 
   // tinggi tangki 1 m (100 cm)
  // diameter alas 60 cm
  // Luas alas = 3.14x30x30 = 2826 cm2
  la=2826;   
}

void loop() 
{ 
  RemoteXY_Handler ();
  ReadUltrasonic();
  dtostrf(volume, 0, 0, RemoteXY.text_1); 
  int level=map(volume,0,280,0,100);
  RemoteXY.level_1 = level;  
  delay(1000);
}
