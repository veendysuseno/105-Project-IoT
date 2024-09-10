/***************************************
 * Project Membaca Input Digital dg thinger.io
 * Board  : NodeMCU ESP8266 V3
 * Input  : Switch
 * Output : Text (Thinger.io)
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
 
#include <ThingerESP8266.h>
//---GANTI SESUAI DENGAN USER NAME Thinger.io  ANDA
#define USERNAME "Ardutech"
//---GANTI SESUAI DENGAN DEVICE ID Thinger.io  ANDA
#define DEVICE_ID "Digital_Input"
//---GANTI SESUAI DENGAN TOKEN Thinger.io  ANDA
#define DEVICE_CREDENTIAL "EzewcQWXpz#9"
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
#define SSID "ArdutechWiFi"    // Nama Hotspot/WiFi
#define SSID_PASSWORD "12345678"   //  Password
#define buttonPin D5
ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);
//================================================
int buttonState = 0;
bool buttonOut=false;
String str; 
void setup() {
  pinMode(buttonPin, INPUT_PULLUP);  
  Serial.begin(9600);
  thing.add_wifi(SSID, SSID_PASSWORD);  
  thing["PUSH1"] >> [](pson& out) { 
      out = str;
  };
}
//=================================================
void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == 0) {    //button is pressed
    str = "Switch ON";
  }
  else {
    str = "Switch OFF";
  }
  thing.handle();
}
