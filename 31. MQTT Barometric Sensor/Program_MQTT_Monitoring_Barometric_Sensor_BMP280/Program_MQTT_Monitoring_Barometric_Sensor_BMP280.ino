/***************************************
 * Project MQTT Monitoring Barometric Sensor BMP280
 * Board  : NodeMCU ESP8266 V3
 * Input  : Sensor BMP280
 * Output : MQTT Dash
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#define SEALEVELPRESSURE_HPA (1013.25)
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
const char* ssid = "ArdutechWiFi";
const char* password = "12345678";
const char* mqtt_server = "broker.mqtt-dashboard.com";

WiFiClient espClient;
PubSubClient client(espClient);

#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];
int value = 0;
Adafruit_BMP280 bmp;
float temperature, pressure, altitude;
//========================================
void setup_wifi() {
  delay(10);  
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  //randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
//===========================================
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");    
      // ... and resubscribe
      client.subscribe("ARDU1");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
//========================================
void setup() {
   bmp.begin(0x76);     
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);  
  delay(3000);
}
//===========================================
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  pressure = bmp.readPressure()/100.0F;
  temperature = bmp.readTemperature();
  altitude = bmp.readAltitude(SEALEVELPRESSURE_HPA);
  
  sprintf(msg, "%.2f", temperature);
  Serial.print("Publish message: ");
  Serial.println(msg);  
  client.publish("BMPTemp", msg);
    
  sprintf(msg, "%.2f", pressure);
  Serial.print("Publish message: ");
  Serial.println(msg);
  client.publish("BMPPress", msg);

   sprintf(msg, "%.2f", altitude);
  Serial.print("Publish message: ");
  Serial.println(msg);
  client.publish("BMPAlti", msg);
    //Print values to serial monitor:
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" hPa");
 
  Serial.print(("Temp: "));
  Serial.print(temperature);
  Serial.println(" C");
 
  Serial.print("Altimeter: ");
  Serial.print(altitude); 
  Serial.println(" m");    
  delay(1000);
}
