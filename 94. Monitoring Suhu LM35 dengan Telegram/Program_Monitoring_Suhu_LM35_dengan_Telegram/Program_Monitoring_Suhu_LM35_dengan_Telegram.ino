/***************************************
 * Project Monitoring Suhu LM35 dg Telegram
 * Board  : NodeMCU ESP8266 V3
 * Input  : LM35
 * Output : Telegram
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#include "CTBot.h"
CTBot myBot;
float C = 0;
int i = 0;
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
String ssid  = "Ardutech2"; // Nama Hotspot/WiFi 
String pass  = "qwerty12";   //  Password
//---GANTI SESUAI DENGAN TOKEN TELEGRAM BOT ANDA
String token = "1244921165:AAG-v01XAAznvBP6VxEItwdW8jB91nRVM5k"; 
//---GANTI SESUAI DENGAN ID TELEGRAM BOT ANDA
unsigned long int ID = 780527634;

//==================================================
void setup() {	
	Serial.begin(9600);
  pinMode(A0, INPUT);     
	Serial.println("Starting TelegramBot...");  
	myBot.wifiConnect(ssid, pass);
	myBot.setTelegramToken(token);	
	if (myBot.testConnection())
		Serial.println("\ntestConnection OK");
	else
		Serial.println("\ntestConnection NOK");
  delay(3000);
myBot.sendMessage(ID, "Obyek terdeteksi sensor ...");
}
//=================================================
void loop() {	
	i++;
  if(i==10){
    i=0;
    C = (analogRead(A0) * 330.0) / 1023.0;
    Serial.println("Kirim data ke Telegram ...");
    myBot.sendMessage(ID, "Temperature="+(String)C);        
   }
  Serial.print("Temperature: ");
  Serial.println(C);
    
  delay(2000);
}
