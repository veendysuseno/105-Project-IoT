/***************************************
 * Project Interfacing I2C LCD dengan NodeMCU
 * Board  : NodeMCU ESP8266 V3
 * Input  : -
 * Output : LCD 16x2 (I2C backpack)
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
// alamat I2C LCD : 0x3f
// ukuran LCD : 16x2
LiquidCrystal_I2C lcd(0x27,16,2);  
//================================
void setup()
{
  //pin SCL -- D1
  //pin SDA -- D2
  Wire.begin(D2, D1);   
  lcd.begin(); 
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("I2C LCD 16x2");
  lcd.setCursor(0,1);
  lcd.print("NodeMCU ESP8266"); 
}
//=================================
void loop()
{
}
