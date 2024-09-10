/***************************************
 * Project Wireless Weighing dg Loadcell & Android
 * Board  : NodeMCU ESP8266 V3
 * Input  : Loadcell + HX711
 * Output : Android
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <HX711_ADC.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//---GANTI SESUAI DENGAN TOKEN BLYNK ANDA
char auth[] = "-htbXm6E3Lizwp915_No7P516Ywa7nrj";//token
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
char ssid[] = "ArdutechWiFi"; // Nama Hotspot/WiFi
char pass[] = "12345678";   //  Password

WidgetLCD LCD(V0);//lcd blynk

LiquidCrystal_I2C lcd(0x27, 16, 2);//lcd i2c

HX711_ADC LoadCell(D3,D4);//(dout, sck)

long t;

void ukurBerat(){
  LoadCell.update();
  if (millis() > t + 500) {
    long i = LoadCell.getData(); 
    if(i>=0){
      lcd.setCursor(0,0);
      lcd.print("Berat=");
      lcd.print(i);
      lcd.println(" g        ");
      Blynk.virtualWrite(V1,i);//tampil gauge blynk
      t = millis();
    }
  }
}

//==================================
void setup() {  
  lcd.begin();  
  lcd.backlight();
  lcd.backlight();
  lcd.print("   Timbangan");
  lcd.setCursor(0,1);
  lcd.print("digital Wireless");
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
  lcd.clear();
  lcd.print("koneksi WiFi..."); 
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass); 
  lcd.setCursor(0,1);
  lcd.print("Sukses");
  delay(2000);
  lcd.clear();
  LCD.clear();
  LCD.print(4,0,"Timbangan");   
  LCD.print(0,1,"digital Wireless");   
}
//=======================================
void loop() {
  Blynk.run();
  ukurBerat();
}
