/***************************************
 * Project Early Warning System Stock dg Telegram 
 * Board  : NodeMCU ESP8266 V3
 * Input  : Loadcell
 * Output : Telegram + LCD
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/

#include "CTBot.h"
CTBot myBot;

#include <HX711_ADC.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
String ssid = "ArdutechWiFi";   // Nama Hotspot/WiFi
String pass = "12345678";    //  Password
//---GANTI SESUAI DENGAN TOKEN TELEGRAM BOT ANDA
String token = "1244921165:AAG-v01XAAznvBP6VxEItwdW8jB91nRVM5k";   // TELEGRAM BOT TOKEN
//---GANTI SESUAI DENGAN ID TELEGRAM BOT ANDA
long ID = 780527634;

HX711_ADC LoadCell(D3,D4);//(dout, sck)
// alamat I2C LCD : 0x3f
// ukuran LCD : 16x2
LiquidCrystal_I2C lcd(0x3F,16,2);  

long t;
byte f_notif;

//==================================
void setup() {
  //pin SCL -- D1
  //pin SDA -- D2
  Wire.begin(D2, D1);    
  lcd.init();  
  lcd.backlight();  
  lcd.print("Peringatan dini");
  lcd.setCursor(0,1);
  lcd.print("  Stok Beras");
  delay(2000);
  lcd.clear();
  lcd.print("Kalibrasi.....");
  float calValue; // calibration value
  calValue = 674.2;  //menyesuaikan dengan sensor loadcell, setiap sensor beda beda
  LoadCell.begin();
  long stabilisingtime = 2000;
  LoadCell.start(stabilisingtime);
  LoadCell.setCalFactor(calValue); 
  lcd.setCursor(0,1);
  lcd.print("Sukses");
  delay(2000);
  Serial.begin(115200);
  Serial.println("Starting TelegramBot...");
  // connect the ESP8266 to the desired access point
  myBot.wifiConnect(ssid, pass);
  // set the telegram bot token
  myBot.setTelegramToken(token);
  // check if all things are ok
  if (myBot.testConnection())
    Serial.println("\ntestConnection OK");
  else
    Serial.println("\ntestConnection NOK");
  lcd.clear();   
}

//=======================================
void loop() {
  TBMessage msg;
  LoadCell.update();
  if (millis() > t + 500) {
    long i = LoadCell.getData()/1000; 
    if(i>=0){
      lcd.setCursor(0,0);
      lcd.print("Stok Beras");
      lcd.setCursor(0,1);
      lcd.print("Berat:");
      lcd.print(i);
      lcd.print("Kg        ");
      t = millis();
    }
    if(i<=1){//stok minimum
      if(f_notif==0){
        msg.text="PERINGATAN STOK BERAS MENIPIS, Stok "+String(i)+"Kg";
        Serial.println(msg.text);
        myBot.sendMessage(ID, msg.text);  // notify the sender
        f_notif=1;
      }
    }
    else {
      f_notif=0;
    }
  }
}
