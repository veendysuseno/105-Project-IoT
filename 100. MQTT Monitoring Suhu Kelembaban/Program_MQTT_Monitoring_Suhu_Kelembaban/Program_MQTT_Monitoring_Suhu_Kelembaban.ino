/***************************************
 * Project MQTT Monitoring Suhu & Kelembaban
 * Board  : NodeMCU ESP8266 V3
 * Input  : Sensor DHT11
 * Output : MQTT Dash
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
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
#define DHTPIN D5 // DHT11 terhubung dengan PIN D5 NODEMCU
DHT dht(DHTPIN, DHT11); 
float temp,humi;
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
  dht.begin();  
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
  humi = dht.readHumidity();
  temp = dht.readTemperature();
  if (isnan(humi) || isnan(temp)) {
    Serial.println("DHT11 tidak terbaca... !");
    return;
  }
  else{ 
  
  sprintf(msg, "%.2f", temp);
  Serial.print("Publish message: ");
  Serial.println(msg);
  client.publish("DHT11Temp", msg);  
  sprintf(msg, "%.2f", humi);
  Serial.print("Publish message: ");
  Serial.println(msg);
  client.publish("DHT11Humi", msg);
}
}
