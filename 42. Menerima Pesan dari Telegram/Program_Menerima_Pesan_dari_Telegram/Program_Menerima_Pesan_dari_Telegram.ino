/***************************************
 * Project Menerima Pesan dari Telegram
 * Board  : NodeMCU ESP8266 V3
 * Input  : Command Telegram
 * Output : LCD
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#include "CTBot.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
// alamat I2C LCD : 0x3f
// ukuran LCD : 16x2
LiquidCrystal_I2C lcd(0x27,16,2);  
//================================
CTBot myBot;
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
String ssid  = "ArdutechWiFi";  // Nama Hotspot/WiFi 
String pass  = "12345678";      //  Password
//---GANTI SESUAI DENGAN TOKEN TELEGRAM BOT ANDA
String token = "1095839490:AAFX8luxNzqlqbYpR_iFF0A-NO_R_g5oGQo";
String str;                            							
TBMessage msg;
//int analogValue;
//float millivolts,celsius;

void setup() {
 //pin SCL -- D1
 //pin SDA -- D2
  Wire.begin(D2, D1);   
  lcd.begin(); 
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print(" Terima Pesan");
  lcd.setCursor(0,1);
  lcd.print(" Dari Telegram"); 
	Serial.begin(9600);
	Serial.println("Starting TelegramBot...");	
	myBot.wifiConnect(ssid, pass);
	myBot.setTelegramToken(token);
	if (myBot.testConnection())
		Serial.println("Connection OK");
	else
		Serial.println("Connection Not OK");	
    lcd.clear();
    lcd.print("Halo Ardutech...");  
}
//========================================
void loop() {	
//	if (myBot.getNewMessage(msg)) {
 //   lcd.clear();
  //  lcd.print("Halo Ardutech...");   
//	}
}
