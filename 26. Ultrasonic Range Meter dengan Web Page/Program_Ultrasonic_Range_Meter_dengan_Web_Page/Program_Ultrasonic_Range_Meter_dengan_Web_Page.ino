/***************************************
 * Project Ultrasonic Range Meter dg Webpage
 * Board  : NodeMCU ESP8266 V3
 * Input  : Sensor Ultrasonik HC-SR04
 * Output : web page
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#include <ESP8266WiFi.h>
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
const char* ssid     = "ArdutechWiFi"; // ssid/hotspot
const char* password = "12345678"; //  Password
const int trigP = D6;  
const int echoP = D5; 

long duration;
int distance;
WiFiServer server(80);
//=====================================
void setup() {
  Serial.begin(9600);
  pinMode(trigP, OUTPUT);  
  pinMode(echoP, INPUT);   
  Serial.println();  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi is connected");
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
  delay(4000);
}
//=========================================
void loop() {
  digitalWrite(trigP, LOW);   
  delayMicroseconds(2);        
  digitalWrite(trigP, HIGH);  
  delayMicroseconds(10);      
  digitalWrite(trigP, LOW);   

  duration = pulseIn(echoP, HIGH);   
  distance= duration*0.034/2;        

  Serial.print("Distance = ");         
  Serial.print(distance);
  Serial.println(" cm");
  WiFiClient client = server.available();
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");  
  client.println("Refresh: 10");  
  client.println();
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.print("<p style='text-align: center;'><span style='font-size: x-large;'><strong>Ultrasonic Range Meter</strong></span></p>");
  client.println("<hr size='5px' color='red' width='20%' align='centre'>");
  client.print("<p style='text-align: center;'><span style='font-size: x-large;'>www.ardutech.com</span></p>");
  client.print("<p style='text-align: center;'><span style='color: #0000ff;'><strong style='font-size: x-large;'>Range = ");
  client.print(distance);
  client.println(" cm");
  client.print("</p>");
  client.println("</html>");
  delay(4000);
}
