/***************************************
 * Project Deteksi Kebocoran Gas dg Telegram
 * Board  : NodeMCU ESP8266 V3
 * Input  : MQ2 sensor
 * Output : Telegram
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#include "CTBot.h"
CTBot myBot;
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
String ssid  = "ArdutechWiFi"; // Nama Hotspot/WiFi
String pass  = "12345678";          //  Password
//---GANTI SESUAI DENGAN TOKEN TELEGRAM ANDA
String token = "1095839490:AAFX8luxNzqlqbYpR_iFF0A-NO_R_g5oGQo";
//---GANTI SESUAI DENGAN ID TELEGRAM ANDA
unsigned long int ID = 242176458;
#define MQ2Pin D5 
int MQ2Value; 
//==================================================
void setup() {	
	Serial.begin(9600);
	Serial.println("Starting TelegramBot...");
  pinMode(MQ2Pin, INPUT);   
	myBot.wifiConnect(ssid, pass);
	myBot.setTelegramToken(token);	
	if (myBot.testConnection())
		Serial.println("\ntestConnection OK");
	else
		Serial.println("\ntestConnection NOK");
}
//=================================================
void loop() {	
	MQ2Value = digitalRead(MQ2Pin);  
   if (!MQ2Value) 
  { 
     Serial.println("Obyek terdeteksi...");
     myBot.sendMessage(ID, "Terjadi kebocoran Gas ...!");     
     while(!digitalRead(MQ2Pin));
     delay(1000);
	}
	
}
