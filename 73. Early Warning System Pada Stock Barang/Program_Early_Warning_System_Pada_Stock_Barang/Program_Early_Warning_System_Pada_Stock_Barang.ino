/***************************************
 * Project Early Warning System Stock Barang (Beras) 
 * Board  : NodeMCU ESP8266 V3
 * Input  : Loadcell (sensor berat)
 * Output : Notifikasi Blynk
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
char ssid[] = "ArdutechWiFi";  // Nama Hotspot/WiFi
char pass[] = "12345678";  //  Password

WidgetLCD LCD(V0);//lcd blynk
LiquidCrystal_I2C lcd(0x27, 16, 2);//lcd i2c
HX711_ADC LoadCell(D3,D4);//(dout, sck)

long t;
byte f_notif;

void ukurBerat(){
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
      
      LCD.print(0,0,"Stok Beras");   
      LCD.print(0,1,"Berat:"); 
      LCD.print(6,1,i);
      LCD.print(9,1,"Kg");
      t = millis();
    }
    if(i<=1){//stok minimum
      if(f_notif==0){
        Blynk.notify("Beras hampir habis");
        f_notif=1;
      }
    }
    else {
      f_notif=0;
    }
  }
}

//==================================
void setup() {  
  lcd.begin();  
  lcd.backlight();
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
  lcd.clear();
  lcd.print("koneksi WiFi..."); 
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass); 
  lcd.setCursor(0,1);
  lcd.print("Sukses");
  delay(2000);
  lcd.clear(); 
  LCD.clear();
}

//=======================================
void loop() {
  Blynk.run();
  ukurBerat();
}
