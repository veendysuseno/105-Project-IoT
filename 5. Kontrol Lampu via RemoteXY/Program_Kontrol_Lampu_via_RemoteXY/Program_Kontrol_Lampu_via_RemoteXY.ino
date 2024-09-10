/***************************************
 * Project Kontrol 4 LED via RemoteXY
 * Board  : NodeMCU ESP8266 V3
 * Input  : -
 * Output : LED
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#define REMOTEXY_MODE__ESP8266WIFI_LIB_CLOUD
#include <ESP8266WiFi.h>
#include <RemoteXY.h>

//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA 
#define REMOTEXY_WIFI_SSID "ArdutechWiFi" // Nama Hotspot/WiFi
#define REMOTEXY_WIFI_PASSWORD "12345678" //  Password
#define REMOTEXY_CLOUD_SERVER "cloud.remotexy.com"
#define REMOTEXY_CLOUD_PORT 6376
//---GANTI SESUAI DENGAN TOKEN RemoteXY ANDA
#define REMOTEXY_CLOUD_TOKEN "1198a726c98413e7f60cae35db5c64a3"


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,4,0,0,0,68,0,10,13,1,
  1,8,5,19,12,12,2,31,76,49,
  0,1,8,19,19,12,12,2,31,76,
  50,0,1,8,33,19,12,12,2,31,
  76,51,0,1,8,46,19,12,12,2,
  31,76,52,0,129,0,11,7,42,6,
  17,75,111,110,116,114,111,108,32,76,
  97,109,112,117,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t button_1; // =1 if button pressed, else =0 
  uint8_t button_2; // =1 if button pressed, else =0 
  uint8_t button_3; // =1 if button pressed, else =0 
  uint8_t button_4; // =1 if button pressed, else =0 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#define PIN_BUTTON_1 D5
#define PIN_BUTTON_2 D6
#define PIN_BUTTON_3 D7
#define PIN_BUTTON_4 D8


void setup() 
{
  RemoteXY_Init (); 
  
  pinMode (PIN_BUTTON_1, OUTPUT);
  pinMode (PIN_BUTTON_2, OUTPUT);
  pinMode (PIN_BUTTON_3, OUTPUT);
  pinMode (PIN_BUTTON_4, OUTPUT);
  
  // TODO you setup code  
}

void loop() 
{ 
  RemoteXY_Handler ();
  
  digitalWrite(PIN_BUTTON_1, (RemoteXY.button_1==0)?LOW:HIGH);
  digitalWrite(PIN_BUTTON_2, (RemoteXY.button_2==0)?LOW:HIGH);
  digitalWrite(PIN_BUTTON_3, (RemoteXY.button_3==0)?LOW:HIGH);
  digitalWrite(PIN_BUTTON_4, (RemoteXY.button_4==0)?LOW:HIGH);
  
  // TODO you loop code
  // use the RemoteXY structure for data transfer


}
