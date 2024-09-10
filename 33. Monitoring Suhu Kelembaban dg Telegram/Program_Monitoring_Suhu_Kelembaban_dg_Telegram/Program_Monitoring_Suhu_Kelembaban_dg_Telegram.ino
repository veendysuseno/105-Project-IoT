/***************************************
 * Project Monitoring Suhu Kelembaban dg Telegram
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
int i = 0;
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
String ssid  = "ArdutechWiFi"; // Nama Hotspot/WiFi
String pass  = "12345678"; //  Password
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
	i++;
  if(i==15){
    i=0;
    humi = dht.readHumidity();
    temp = dht.readTemperature();
    if (isnan(humi) || isnan(temp)) {
        Serial.println("DHT11 tidak terbaca... !");
        return;
        }
    else{     
        Serial.println("Kirim data ke Telegram ...");
        myBot.sendMessage(ID, "Temperature="+(String)temp+" Humidity="+(String)humi);        
        }
  }	
	  Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.print(" Celcius Humidity: ");
    Serial.println(humi);
    delay(2000);
}
