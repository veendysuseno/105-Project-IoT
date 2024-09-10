/***************************************
 * Project Deteksi Gas Bocor dg RemoteXY
 * Board  : NodeMCU ESP8266 V3
 * Input  : Sensor gas MQ-2
 * Output : RemoteXY
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP8266WIFI_LIB_CLOUD
#include <ESP8266WiFi.h>

#include <RemoteXY.h>

//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
#define REMOTEXY_WIFI_SSID "ArdutechWiFi"  // Nama Hotspot/WiFi
#define REMOTEXY_WIFI_PASSWORD "12345678"  //  Password
#define REMOTEXY_CLOUD_SERVER "cloud.remotexy.com"
#define REMOTEXY_CLOUD_PORT 6376
//---GANTI SESUAI DENGAN TOKEN RemoteXY Anda
#define REMOTEXY_CLOUD_TOKEN "1198a726c98413e7f60cae35db5c64a3"
#define MQ2Pin D5 


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,0,0,3,0,42,0,10,13,1,
  129,0,4,7,56,6,17,68,101,116,
  101,107,116,111,114,32,71,97,115,32,
  66,111,99,111,114,0,65,4,19,21,
  26,26,69,0,22,51,28,28,1 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // output variables
  uint8_t led_1_r; // =0..255 LED Red brightness 
  int16_t sound_1; // =0 no sound, else ID of sound, =1001 for example, look sound list in app 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

int MQ2Value; 

void setup() 
{
  Serial.begin(9600);
  RemoteXY_Init (); 
  pinMode(MQ2Pin, INPUT);   
  
  // TODO you setup code
  
}
//=================================
void loop() 
{ 
  RemoteXY_Handler ();
  MQ2Value = digitalRead(MQ2Pin);  
  if (!MQ2Value) 
  {     
    RemoteXY.led_1_r = 255;
    RemoteXY.sound_1 = 1001;  
  }
}
