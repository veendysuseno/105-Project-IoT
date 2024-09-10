/***************************************
 * Project MQTT Monitoring Suhu
 * Board  : NodeMCU ESP8266 V3
 * Input  : Sensor LM35
 * Output : MQTT Dash
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
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

float C = 0;
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
  pinMode(A0, INPUT);  
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
  C = (analogRead(A0) * 330.0) / 1023.0;
  sprintf(msg, "%.2f", C);
  Serial.print("Publish message: ");
  Serial.println(msg);
  client.publish("ARDU2", msg);  
}
