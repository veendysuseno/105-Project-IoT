/***************************************
 * Project Deteksi Kebakaran dg Telegram
 * Board  : NodeMCU ESP8266 V3
 * Input  : Flame sensor
 * Output : Telegram
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#include "CTBot.h"
CTBot myBot;
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
String ssid  = "ArdutechWiFi"; // Nama Hotspot/WiFi
String pass  = "12345678"; //  Password
//---GANTI SESUAI DENGAN TOKEN TELEGRAM BOT ANDA
String token = "1095839490:AAFX8luxNzqlqbYpR_iFF0A-NO_R_g5oGQo";
//---GANTI SESUAI DENGAN ID TELEGRAM BOT ANDA
unsigned long int ID = 242176458;
#define FlameSensor D5 
int FlameStatus; 
//==================================================
void setup() {	
	Serial.begin(9600);
	Serial.println("Starting TelegramBot...");
  pinMode(FlameSensor, INPUT);   
	myBot.wifiConnect(ssid, pass);
	myBot.setTelegramToken(token);	
	if (myBot.testConnection())
		Serial.println("\ntestConnection OK");
	else
		Serial.println("\ntestConnection NOK");
}
//=================================================
void loop() {	
	FlameStatus = digitalRead(FlameSensor);  
   if (!FlameStatus) 
  { 
     Serial.println("Terjadi kebakaran...");
     myBot.sendMessage(ID, "Terjadi kebakaran ...!");     
     while(!digitalRead(FlameSensor));
     delay(1000);
	}
}
