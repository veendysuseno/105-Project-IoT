/***************************************
 * Project Monitoring Suhu Kelembaban DHT11 via RemoteXY
 * Board  : NodeMCU ESP8266 V3
 * Input  : DHT11
 * Output : RemoteXY
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#define REMOTEXY_MODE__ESP8266WIFI_LIB_CLOUD
#include <ESP8266WiFi.h>
#include <RemoteXY.h>
#include <DHT.h>
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
#define REMOTEXY_WIFI_SSID "ArdutechWiFi" // Nama Hotspot/WiFi
#define REMOTEXY_WIFI_PASSWORD "12345678"  //  Password
#define REMOTEXY_CLOUD_SERVER "cloud.remotexy.com"
#define REMOTEXY_CLOUD_PORT 6376
//---GANTI SESUAI DENGAN TOKEN RemoteXY ANDA
#define REMOTEXY_CLOUD_TOKEN "1198a726c98413e7f60cae35db5c64a3"
#define DHTPIN D5 // DHT11 terhubung dengan PIN D5 NODEMCU
DHT dht(DHTPIN, DHT11); 
float temp,humi;

// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,0,0,30,0,68,0,10,13,1,
  129,0,5,7,31,6,96,84,101,109,
  112,32,40,67,41,32,32,58,0,129,
  0,6,17,31,6,96,72,117,109,105,
  32,40,37,41,32,58,32,0,67,4,
  39,6,21,8,96,13,11,67,4,39,
  16,21,8,96,13,11,68,18,2,28,
  59,51,8,36,135 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // output variables
  char text_1[11];  // string UTF8 end zero 
  char text_2[11];  // string UTF8 end zero 
  float onlineGraph_1_var1;
  float onlineGraph_1_var2;

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
  dht.begin();  
  RemoteXY_Init ();  
 
}
//=========================================
void loop() {
  RemoteXY_Handler ();
  humi = dht.readHumidity();
  temp = dht.readTemperature();
  if (isnan(humi) || isnan(temp)) {
    Serial.println("DHT11 tidak terbaca... !");
    return;
  }
  else{ 
    dtostrf(temp, 0, 0, RemoteXY.text_1); 
    dtostrf(humi, 0, 0, RemoteXY.text_2); 
    RemoteXY.onlineGraph_1_var1 = temp;
    RemoteXY.onlineGraph_1_var2 = humi;
  
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.print(" Celcius Humidity: ");
    Serial.println(humi);
  }
  delay(1000);
}
