/***************************************
 * Project Kirim pesan ke Telegram
 * Board  : NodeMCU ESP8266 V3
 * Input  : Switch
 * Output : Telegram
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#include "CTBot.h"
CTBot myBot;
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
String ssid  = "Ardutech2"    ; // REPLACE mySSID WITH YOUR WIFI SSID
String pass  = "qwerty12"; // REPLACE myPassword YOUR WIFI PASSWORD, IF ANY
//---GANTI SESUAI DENGAN TOKEN TELEGRAM BOT ANDA
String token = "1244921165:AAG-v01XAAznvBP6VxEItwdW8jB91nRVM5k"   ; // REPLACE myToken WITH YOUR TELEGRAM BOT TOKEN
//---GANTI SESUAI DENGAN ID TELEGRAM BOT ANDA
unsigned long int ID = 780527634;
#define SW D2
//==================================================
void setup() {	
	Serial.begin(9600);
	Serial.println("Starting TelegramBot...");
  pinMode(SW,INPUT_PULLUP);
	myBot.wifiConnect(ssid, pass);
	myBot.setTelegramToken(token);	
	if (myBot.testConnection())
		Serial.println("\ntestConnection OK");
	else
		Serial.println("\ntestConnection NOK");
}
//=================================================
void loop() {	
	
	if((digitalRead(SW)==LOW)) {
     Serial.println("Kirim pesan...");
     myBot.sendMessage(ID, "Tes Kirim Telegram");
     delay(1000);
	}
	
	
}
