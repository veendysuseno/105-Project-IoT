/***************************************
 * Project MQTT Kontrol Lampu
 * Board  : NodeMCU ESP8266 V3
 * Input  : MQTT Dash
 * Output : LED
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
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];
int value = 0;
#define L1 D5
#define L2 D6
#define L3 D7
#define L4 D8
//======================================
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
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
//===========================================
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  if ((char)payload[0] == 'A') {
    digitalWrite(L1,HIGH);   // Turn the LED 1 on 
  } 
  else if ((char)payload[0] == 'a') {
    digitalWrite(L1, LOW);  // Turn the LED 1 off 
  }
  else if ((char)payload[0] == 'B') {
    digitalWrite(L2,HIGH);   // Turn the LED 2 on 
  } 
  else if ((char)payload[0] == 'b') {
    digitalWrite(L2, LOW);  // Turn the LED 2 off 
  }
   else if ((char)payload[0] == 'C') {
    digitalWrite(L3,HIGH);   // Turn the LED 3 on 
  } 
  else if ((char)payload[0] == 'c') {
    digitalWrite(L3, LOW);  // Turn the LED 3 off 
  }
   else if ((char)payload[0] == 'D') {
    digitalWrite(L4,HIGH);   // Turn the LED 4 on
  } 
  else if ((char)payload[0] == 'd') {
    digitalWrite(L4, LOW);  // Turn the LED 4 off 
  }
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
//==========================================
void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  pinMode(L4, OUTPUT);
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}
//=========================================
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
