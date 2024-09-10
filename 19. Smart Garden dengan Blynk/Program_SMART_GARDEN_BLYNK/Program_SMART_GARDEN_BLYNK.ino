/***************************************
 * Project Smart Garden dengan Blynk
 * Board  : NodeMCU ESP8266 V3
 * Input  : Modul Soil Moisture
 *          Modul Raindrops
 *          DHT11
 * Output : Blynk
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#define BLYNK_PRINT Serial    
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

#define RainDrops D2                           
#define Pump D3

#define DHTPIN D1  
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//Ganti dengan Token anda
char auth[] = "-htbXm6E3Lizwp915_No7P516Ywa7nrj";
// Ganti dengan WiFi anda
char ssid[] = "ArdutechWiFi";
char pass[] = "12345678";
                                           
byte humi, temp; 
byte soil;
byte manual;

WidgetLED led(V3);

BLYNK_WRITE(V4){
  int buttonState = param.asInt();
  if(buttonState==HIGH){
    manual=1;
  }
  else{
    manual=0;
  }
}

BLYNK_WRITE(V5){
  int buttonState = param.asInt();
  if (manual==0){
    if(buttonState)digitalWrite(Pump,LOW);//pompa ON
    else  digitalWrite(Pump,HIGH);//pompa OFF
  }
  else Blynk.virtualWrite(V5,LOW); 
}
//======================================
void sendDataDHT(){  
  humi = dht.readHumidity();
  temp = dht.readTemperature();
  if (isnan(humi) || isnan(temp) || temp==255) {
    Serial.println("DHT11 tidak terbaca... !");
  }
  else {
    Serial.println(temp);
    Serial.println(humi);
    Blynk.virtualWrite(1, temp);//virtual input V10 di Blynk (suhu)
    Blynk.virtualWrite(2, humi);//virtual input V11 di Blynk (kelembaban)
  }
}

//================================
void getSoil(){
  soil=map(analogRead(0), 0, 1023, 100, 0);
  if (manual){
    if(soil<40)digitalWrite(Pump,LOW);//pompa ON
    else  digitalWrite(Pump,HIGH);//pompa OFF
  } 
  Blynk.virtualWrite(0, soil);//virtual input V0 di Blynk (kelembaban tanah)
  Serial.print("Kelembaban Tanah:");
  Serial.println(soil);
}

//================================
void getRain(){
  if(digitalRead(RainDrops)==LOW){
    led.on();
    Serial.println("Cuaca Cerah");  
  }
  else {
    led.off();
    Serial.println("Cuaca Hujan");
  }
}
//==========================
void setup(){
  pinMode(RainDrops, INPUT); 
  digitalWrite(RainDrops,HIGH);
  pinMode(Pump, OUTPUT); 
  digitalWrite(Pump,HIGH);
  delay(2000);
  dht.begin();
  Serial.begin(9600);
  Serial.println();
  Serial.println();    
  Blynk.begin(auth, ssid, pass);  
  delay(1000);     
}
//============================
void loop(){
  Blynk.run(); 
  Serial.println();
  Serial.println();   
  sendDataDHT();
  getSoil(); 
  getRain();
  delay(2000);
}
