/***************************************
 * Project Kontrol RGB via RemoteXY
 * Board  : NodeMCU ESP8266 V3
 * Input  : RemoteXY
 * Output : RGB LED
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP8266WIFI_LIB_CLOUD
#include <ESP8266WiFi.h>
#include <RemoteXY.h>
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
#define REMOTEXY_WIFI_SSID "ArdutechWiFi" // Nama Hotspot/WiFi
#define REMOTEXY_WIFI_PASSWORD "12345678" //  Password
#define REMOTEXY_CLOUD_SERVER "cloud.remotexy.com"
#define REMOTEXY_CLOUD_PORT 6376
//---GANTI SESUAI DENGAN TOKEN RemoteXY Anda
#define REMOTEXY_CLOUD_TOKEN "1198a726c98413e7f60cae35db5c64a3"

// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
    { 255,3,0,0,0,34,0,10,13,1,
    129,0,7,6,50,6,17,75,111,110,
    116,114,111,108,32,76,69,68,32,82,
    71,66,0,6,0,7,22,49,49,2,
    26 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t rgb_1_r; // =0..255 Red color value 
  uint8_t rgb_1_g; // =0..255 Green color value 
  uint8_t rgb_1_b; // =0..255 Blue color value  
    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

void setup() 
{
  RemoteXY_Init ();   
  // TODO you setup code  
}

void loop() 
{ 
   RemoteXY_Handler ();
   analogWrite(D5 , RemoteXY.rgb_1_r ); 
   analogWrite(D6 , RemoteXY.rgb_1_g ); 
   analogWrite(D7 , RemoteXY.rgb_1_b );  
  // TODO you loop code
  // use the RemoteXY structure for data transfer
}
