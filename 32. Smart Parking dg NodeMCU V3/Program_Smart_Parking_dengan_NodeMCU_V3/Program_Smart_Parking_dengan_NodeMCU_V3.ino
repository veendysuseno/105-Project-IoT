/***************************************
 * Project Smart Parking 
 * Board  : NodeMCU ESP8266 V3
 * Input  : Infrared Sensor (4)
 * Output : Notifikasi Blynk
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define S1 D1
#define S2 D2
#define S3 D3
#define S4 D4
//---GANTI SESUAI DENGAN TOKEN BLYNK ANDA
char auth[] = "-htbXm6E3Lizwp915_No7P516Ywa7nrj";
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
char ssid[] = "ArdutechWiFi";  // Nama Hotspot/WiFi
char pass[] = "12345678";      //  Password

WidgetLED slot1(V1);
WidgetLED slot2(V2);
WidgetLED slot3(V3);
WidgetLED slot4(V4);

byte send1=0;
byte send2=0;
byte send3=0;
byte send4=0;
//============================
void setup() {
  pinMode(S1, INPUT_PULLUP); 
  pinMode(S2, INPUT_PULLUP); 
  pinMode(S3, INPUT_PULLUP); 
  pinMode(S4, INPUT_PULLUP); 
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  delay(10);
  Blynk.begin(auth, ssid, pass); 
  slot1.off();
  slot2.off();
  slot3.off();
  slot4.off();  
}
//==================================
void loop() {
  Blynk.run();
  //---------------------------
  if(digitalRead(S1) == LOW) {
    sendBlynk();
    send1=0;
  }
  else{
    sendBlynk();
    send1=1;
  }  
 
  //---------------------------
  if(digitalRead(S2) == LOW) {
    sendBlynk();
    send2=0;
  }
  else{
    sendBlynk();
    send2=1;
  }
  //---------------------------  
  if(digitalRead(S3) == LOW) {
    sendBlynk();
    send3=0;
  }
  else{
    sendBlynk();
    send3=1;
  }
  //---------------------------  
  if(digitalRead(S4) == LOW) {
    sendBlynk();
    send4=0;
  }
  else{
    sendBlynk();
    send4=1;
  }
  delay(300);
}

void sendBlynk(){
  if(send1!=digitalRead(S1)){
    if (send1)slot1.on();
    else slot1.off();
    Serial.print("send1:");
    Serial.println(send1);
    delay(500);
  }
  if(send2!=digitalRead(S2)){
    if (send2)slot2.on();
    else slot2.off();
    Serial.print("send2:");
    Serial.println(send2);
    delay(500);
  }
  if(send3!=digitalRead(S3)){
    if (send3)slot3.on();
    else slot3.off();
    Serial.print("send3:");
    Serial.println(send3);
    delay(500);
  }
  if(send4!=digitalRead(S4)){
    if (send4)slot4.on();
    else slot4.off();
    Serial.print("send4:");
    Serial.println(send4);
    delay(500);
  }
}
