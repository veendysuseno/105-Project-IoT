/***************************************
 * Project Kontrol Lampu dengan Telegram
 * Board  : NodeMCU ESP8266 V3
 * Input  : Command Telegram
 * Output : Relay
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#include "CTBot.h"
CTBot myBot;
#define RL1 D5
#define RL2 D6
#define RL3 D7
#define RL4 D8
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
String ssid  = "Ardutech2";   // Nama Hotspot/WiFi 
String pass  = "qwerty12";     //  Password
//---GANTI SESUAI DENGAN TOKEN TELEGRAM BOT ANDA
String token = "1244921165:AAG-v01XAAznvBP6VxEItwdW8jB91nRVM5k"   ; // REPLACE myToken WITH YOUR TELEGRAM BOT TOKEN
String str;                            							
TBMessage msg;
//======================================
void setup() {
  pinMode(RL1, OUTPUT);  
  pinMode(RL2, OUTPUT);
  pinMode(RL3, OUTPUT);
  pinMode(RL4, OUTPUT);
  digitalWrite(RL1,HIGH);
  digitalWrite(RL2,HIGH);
  digitalWrite(RL3,HIGH);
  digitalWrite(RL4,HIGH);
	Serial.begin(9600);
	Serial.println("Starting TelegramBot...");	
	myBot.wifiConnect(ssid, pass);
	myBot.setTelegramToken(token);
	if (myBot.testConnection())
		Serial.println("Connection OK");
	else
		Serial.println("Connection Not OK");	
}
//========================================
void loop() {	
	if (myBot.getNewMessage(msg)) {
    //================ Relay 1 =====================
		if (msg.text.equalsIgnoreCase("1 on")) {              
			digitalWrite(RL1, LOW);                               
			myBot.sendMessage(msg.sender.id, "Relay 1 ON");  
		}
		else if (msg.text.equalsIgnoreCase("1 off")) {        
			digitalWrite(RL1, HIGH);                              
			myBot.sendMessage(msg.sender.id, "Relay 1 OFF"); 
		}		
   //================ Relay 2 =====================
    if (msg.text.equalsIgnoreCase("2 on")) {              
      digitalWrite(RL1, LOW);                               
      myBot.sendMessage(msg.sender.id, "Relay 2 ON");  
    }
    else if (msg.text.equalsIgnoreCase("2 off")) {        
      digitalWrite(RL1, HIGH);                              
      myBot.sendMessage(msg.sender.id, "Relay 2 OFF"); 
    }
    //================ Relay 3 =====================
   if (msg.text.equalsIgnoreCase("3 on")) {              
      digitalWrite(RL3, LOW);                               
      myBot.sendMessage(msg.sender.id, "Relay 3 ON");  
    }
    else if (msg.text.equalsIgnoreCase("3 off")) {        
      digitalWrite(RL3, HIGH);                              
      myBot.sendMessage(msg.sender.id, "Relay 3 OFF"); 
    }
    //================ Relay 4 =====================
   if (msg.text.equalsIgnoreCase("4 on")) {              
      digitalWrite(RL4, LOW);                               
      myBot.sendMessage(msg.sender.id, "Relay 4 ON");  
    }
    else if (msg.text.equalsIgnoreCase("4 off")) {        
      digitalWrite(RL4, HIGH);                              
      myBot.sendMessage(msg.sender.id, "Relay 4 OFF"); 
    } 
	}	
	delay(500);
}
