/***************************************
 * Project Monitoring DHT11 mode by request dg Telegram
 * Board  : NodeMCU ESP8266 V3
 * Input  : DHT11
 * Output : Telegram
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#include "CTBot.h"
#include <DHT.h>
#define DHTPIN D5 
CTBot myBot;
DHT dht(DHTPIN, DHT11); 
float temp,humi;
String str;                                          
TBMessage msg;
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
String ssid  = "Ardutech2"; // Nama Hotspot/WiFi
String pass  = "qwerty12"; //  Password
//---GANTI SESUAI DENGAN TOKEN TELEGRAM BOT ANDA
String token = "1244921165:AAG-v01XAAznvBP6VxEItwdW8jB91nRVM5k"; 
//---GANTI SESUAI DENGAN ID TELEGRAM BOT ANDA
unsigned long int ID = 780527634;

//==================================================
void setup() {	
	Serial.begin(9600);
  dht.begin();    
	Serial.println("Starting TelegramBot...");  
	myBot.wifiConnect(ssid, pass);
	myBot.setTelegramToken(token);	
	if (myBot.testConnection())
		Serial.println("\ntestConnection OK");
	else
		Serial.println("\ntestConnection NOK");
  delay(3000);
}
//=================================================
void loop() {
  humi = dht.readHumidity();
  temp = dht.readTemperature();	
	if (myBot.getNewMessage(msg)) {
    if (msg.text.equalsIgnoreCase("Get temp")) {  
      //humi = dht.readHumidity();
      //temp = dht.readTemperature();
      //if (isnan(humi) || isnan(temp)) {
      Serial.println("Kirim data suhu ke Telegram ...");
      //myBot.sendMessage(ID, "Temperature="+(String)temp+" Humidity="+(String)humi);        
      myBot.sendMessage(msg.sender.id, "Temperature="+(String)temp); 
      }
    else if (msg.text.equalsIgnoreCase("Get humi")) {  
      //humi = dht.readHumidity();
      //temp = dht.readTemperature();
      //if (isnan(humi) || isnan(temp)) {
      Serial.println("Kirim data kelembaban ke Telegram ...");
      //myBot.sendMessage(ID, "Temperature="+(String)temp+" Humidity="+(String)humi);        
      myBot.sendMessage(msg.sender.id, "Humidity="+(String)humi); 
      } 
    else if (msg.text.equalsIgnoreCase("Get all")) {  
      //humi = dht.readHumidity();
      //temp = dht.readTemperature();
      //if (isnan(humi) || isnan(temp)) {
      Serial.println("Kirim data suhu + kelembaban ke Telegram ...");
      //myBot.sendMessage(ID, "Temperature="+(String)temp+" Humidity="+(String)humi);        
      myBot.sendMessage(msg.sender.id,"Temperature="+(String)temp+ " Humidity="+(String)humi); 
      } 
	}
	Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" Celcius Humidity: ");
  Serial.println(humi);
  delay(2000);
}
