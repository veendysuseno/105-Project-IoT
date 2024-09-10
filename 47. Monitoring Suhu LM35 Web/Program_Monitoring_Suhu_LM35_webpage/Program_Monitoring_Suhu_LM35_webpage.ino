/***************************************
 * Project Monitoring Suhu LM35 via Web page
 * Board  : NodeMCU ESP8266 V3
 * Input  : LM35
 * Output : web page
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#include <ESP8266WiFi.h>
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
const char* ssid     = "ArdutechWiFi"; // Nama Hotspot/WiFi
const char* password = "12345678"; //  Password
float C = 0;
float F = 0;
WiFiServer server(80);
//=====================================
void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);   
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
  delay(3000);
}
//=========================================
void loop() {
  C = (analogRead(A0) * 330.0) / 1023.0;
  F = C * 1.8 + 32.0;
  Serial.print("  Temperature = ");
  Serial.print(C);
  Serial.print(" Celsius, ");
  Serial.print(F);
  Serial.println(" Fahrenheit");

  WiFiClient client = server.available();
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");  
  client.println("Refresh: 10");  
  client.println();
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.print("<p style='text-align: center;'><span style='font-size: x-large;'><strong>Digital Thermometer</strong></span></p>");
  client.println("<hr size='5px' color='red' width='30%' align='centre'>");
  client.print("<p style='text-align: center;'><span style='font-size: x-large;'>www.ardutech.com</span></p>");
  client.print("<p style='text-align: center;'><span style='color: #0000ff;'><strong style='font-size: large;'>Temperature (*C)= ");
  client.println(C);
  client.print("<p style='text-align: center;'><span style='color: #0000ff;'><strong style='font-size: large;'>Temperature (F) = ");
  client.println(F);
  client.print("</p>");
  client.println("</html>");
  delay(5000);
}
