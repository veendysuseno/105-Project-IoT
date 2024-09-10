/***************************************
 * Project Monitoring Suhu Kelembaban dengan Thingspeak
 * Board  : NodeMCU ESP8266 V3
 * Input  : DHT11
 * Output : Thingspeak
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#include <DHT.h>
#include <ESP8266WiFi.h>
// GANTI DENGAN  API Keys anda di Thingspeak
String apiKey = "4XYI1SXO9XRXXP74";
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
const char* ssid = "ArdutechWiFi";
const char* password = "12345678";
const char* server = "api.thingspeak.com";
#define DHTPIN D5 // DHT11 terhubung dengan PIN D5 NODEMCU

DHT dht(DHTPIN, DHT11,15); 
WiFiClient client;
//==========================
void setup() {
  Serial.begin(9600);
  delay(10);
  dht.begin();
  WiFi.begin(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}
//================================
void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("DHT11 tidak terbaca... !");
    return;
  }
  if (client.connect(server,80)) { 
    String postStr = apiKey;
    postStr +="&field1=";
    postStr += String(t);
    postStr +="&field2=";
    postStr += String(h);
    postStr += "\r\n\r\n";
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" Celcius Humidity: ");
    Serial.print(h);
    Serial.println(" send to Thingspeak");
  }
  client.stop();
  Serial.println("Waiting…");
  delay(20000);  //minimal nunggu 15 detik update Thingspeak
}
