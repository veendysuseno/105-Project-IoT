/***************************************
 * Project Monitoring Suhu LM35 via RemoteXY
 * Board  : NodeMCU ESP8266 V3
 * Input  : LM35
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
#define REMOTEXY_CLOUD_TOKEN "38f2a0cdbd7371a6c6f1cefa9c7be673" 

float C = 0;
float F = 0;
// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,0,0,15,0,61,0,10,13,1,
  129,0,3,6,58,6,17,68,105,103,
  105,116,97,108,32,84,104,101,114,109,
  111,109,101,116,101,114,0,129,0,5,
  20,18,6,94,84,101,109,112,32,58,
  0,67,4,29,21,20,5,2,26,11,
  68,17,3,36,57,42,8,36 }; 
  
// this structure defines all the variables and events of your control interface 
struct {

    // output variables
  float onlineGraph_1;
  char text_1[11];  // string UTF8 end zero 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////



//=====================================
void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);  
  RemoteXY_Init ();  
 //RemoteXY.onlineGraph_1_var1 = float (analogRead(A0)) / 204.8;
}
//=========================================
void loop() {
  RemoteXY_Handler ();
  C = (analogRead(A0) * 330.0) / 1023.0;
  dtostrf(C, 0, 0, RemoteXY.text_1); 
  RemoteXY.onlineGraph_1 = C;
  //F = C * 1.8 + 32.0;
  Serial.print("  Temperature = ");
  Serial.print(C);
  Serial.print(" Celsius, ");
  Serial.print(F);
  Serial.println(" Fahrenheit");
  delay(1000);
}
