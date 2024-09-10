/***************************************
 * Project Deteksi Manusia dg sensor PIR dan Telegram
 * Board  : NodeMCU ESP8266 V3
 * Input  : PIR sensor
 * Output : Telegram
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#include "CTBot.h"
CTBot myBot;
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
String ssid  = "ArdutechWiFi"; // Nama Hotspot/WiFi
String pass  = "12345678";  //  Password
//---GANTI SESUAI DENGAN TOKEN TELEGRAM BOT ANDA
String token = "1095839490:AAFX8luxNzqlqbYpR_iFF0A-NO_R_g5oGQo";
//---GANTI SESUAI DENGAN ID TELEGRAM BOT ANDA
unsigned long int ID = 242176458;
#define pirPin D6 // sensor PIR
int pirValue; 
//==================================================
void setup() {	
	Serial.begin(9600);
	Serial.println("Starting TelegramBot...");
  pinMode(pirPin, INPUT);
	myBot.wifiConnect(ssid, pass);
	myBot.setTelegramToken(token);	
	if (myBot.testConnection())
		Serial.println("\ntestConnection OK");
	else
		Serial.println("\ntestConnection NOK");
}
//=================================================
void loop() {	
	pirValue = digitalRead(pirPin);
  if (pirValue) 
  { 
     Serial.println("Obyek terdeteksi...");
     myBot.sendMessage(ID, "Obyek terdeteksi sensor ...");
     delay(1000);
	}
	
}
