/***************************************
 * Project 2 Ch DS18B20 dg Thinger io
 * Board  : NodeMCU ESP8266 V3
 * Input  : 2 DS18B20
 * Output : thinger.io
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#include <OneWire.h>
#include <DallasTemperature.h>
#include <BlynkSimpleEsp8266.h>
#define BLYNK_PRINT Serial 
#define ONE_WIRE_BUS 14
//---GANTI SESUAI DENGAN TOKEN BLYNK ANDA
char auth[] = "CbS0l3x8agGfefffJ9GJ6b3G5kKE5Q4S"; 
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
char ssid[] = "ArdutechWiFi";  // Nama Hotspot/WiFi
char pass[] = "12345678";      //  Password
BlynkTimer timer;
OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);
WidgetLCD lcd(V0);    
int numberOfDevices;
float temperature1,temperature2;
DeviceAddress tempDeviceAddress; 
//============================
void ReadDS18B20(){
   sensors.requestTemperatures(); 
   for(int i=0;i<numberOfDevices; i++){
    if(sensors.getAddress(tempDeviceAddress, i)){
      float tempC = sensors.getTempC(tempDeviceAddress);
      if(i==0){
        temperature1=tempC;
        Blynk.virtualWrite(1, temperature1); 
        Serial.print("Temperature 1: ");
        Serial.println(temperature1);
      }
      else if(i==1){
        temperature2=tempC;
         Blynk.virtualWrite(2, temperature2); 
        Serial.print("Temperature 2: ");
        Serial.println(temperature2);
      }
     
      }  
}
  lcd.print(0, 0, "Ch 1 =");
  lcd.print(6,0,temperature1);
  lcd.print(0, 1, "Ch 2 =");  
  lcd.print(6,1,temperature2);
}
//=============================
void setup(){
  Serial.begin(9600);
  sensors.begin();
  numberOfDevices = sensors.getDeviceCount();
  Serial.print("Locating devices...");
  Serial.print("Found ");
  Serial.print(numberOfDevices, DEC);
  Serial.println(" devices.");
  for(int i=0;i<numberOfDevices; i++){
    if(sensors.getAddress(tempDeviceAddress, i)){
      Serial.print("Found device ");
      Serial.print(i, DEC);
      Serial.print(" with address: ");
      printAddress(tempDeviceAddress);
      Serial.println();
    } else {
      Serial.print("Found ghost device at ");
      Serial.print(i, DEC);
      Serial.print(" but could not detect address. Check power and cabling");
    }
  }
  delay(10);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(5000L, ReadDS18B20); 
  lcd.clear();
  lcd.print(0, 0, "==2 Ch DS18B20 ==");
  lcd.print(0, 1, "www.ardutech.com");  
  delay(3000);  
  lcd.clear();
}
//===============================================
void loop(){ 
   Blynk.run();
  timer.run();  
}
//==============================================
void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++){
    if (deviceAddress[i] < 16) Serial.print("0");
      Serial.print(deviceAddress[i], HEX);
  }
}
