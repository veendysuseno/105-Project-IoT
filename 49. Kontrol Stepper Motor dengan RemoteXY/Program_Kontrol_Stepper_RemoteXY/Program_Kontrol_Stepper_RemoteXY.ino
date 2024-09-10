/***************************************
 * Project Kontrol Motor Stepper dg RemoteXY
 * Board  : NodeMCU ESP8266 V3
 * Input  : RemoteXY
 * Output : Stepper Motor
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/

#define REMOTEXY_MODE__ESP8266WIFI_LIB_CLOUD
#include <ESP8266WiFi.h>
#include <RemoteXY.h>

//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
#define REMOTEXY_WIFI_SSID "ArdutechWiFi"   // Nama Hotspot/WiFi
#define REMOTEXY_WIFI_PASSWORD "12345678"   //  Password
#define REMOTEXY_CLOUD_SERVER "cloud.remotexy.com"
#define REMOTEXY_CLOUD_PORT 6376
//---GANTI SESUAI DENGAN TOKEN RemoteXY Anda
#define REMOTEXY_CLOUD_TOKEN "1198a726c98413e7f60cae35db5c64a3"

// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,2,0,0,0,53,0,10,13,1,
  129,0,9,5,45,6,17,75,111,110,
  116,114,111,108,32,83,116,101,112,112,
  101,114,0,1,0,6,19,17,17,2,
  31,75,73,82,73,0,1,0,37,19,
  17,17,2,31,75,65,78,65,78,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t button_1; // =1 if button pressed, else =0 
  uint8_t button_2; // =1 if button pressed, else =0 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#define PIN_BUTTON_1 D4
uint8_t IN1 = D5;
uint8_t IN2 = D6;
uint8_t IN3 = D7;
uint8_t IN4 = D8;
const uint16_t _delay = 5;
//====================
void sequence(bool a, bool b, bool c, bool d){  /* four step sequence to stepper motor */
  digitalWrite(IN1, a);
  digitalWrite(IN2, b);
  digitalWrite(IN3, c);
  digitalWrite(IN4, d);
  delay(_delay);
}
void CW(){
    sequence(HIGH, LOW, LOW, LOW);
    sequence(HIGH, HIGH, LOW, LOW);
    sequence(LOW, HIGH, LOW, LOW);
    sequence(LOW, HIGH, HIGH, LOW);
    sequence(LOW, LOW, HIGH, LOW);
    sequence(LOW, LOW, HIGH, HIGH);
    sequence(LOW, LOW, LOW, HIGH);
    sequence(HIGH, LOW, LOW, HIGH);
}
void CCW(){
    sequence(LOW, LOW, LOW, HIGH);
    sequence(LOW, LOW, HIGH, HIGH);
    sequence(LOW, LOW, HIGH, LOW);
    sequence(LOW, HIGH, HIGH, LOW);
    sequence(LOW, HIGH, LOW, LOW);
    sequence(HIGH, HIGH, LOW, LOW);
    sequence(HIGH, LOW, LOW, LOW);
    sequence(HIGH, LOW, LOW, HIGH);
}
void setup() 
{
  RemoteXY_Init (); 
  pinMode (PIN_BUTTON_1, OUTPUT);
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}
//=====================================
void loop() 
{ 
  RemoteXY_Handler ();
  if (RemoteXY.button_1==1) {
    CCW();
  }
  else if (RemoteXY.button_2==1){
    CW();
  }
}
