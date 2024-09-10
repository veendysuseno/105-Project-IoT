/***************************************
 * Project Kontrol LED via Web server
 * Board  : NodeMCU ESP8266 V3
 * Input  : Web
 * Output : LED
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#include <ESP8266WiFi.h>
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
const char* ssid = "ArdutechWiFi";  // Nama Hotspot
const char* password = "12345678";  // Password 

String header;
String L1State = "off";
const int L1 = D5;
WiFiServer server(80);
//===============================================
void setup() {
  Serial.begin(9600);
  pinMode(L1, OUTPUT);
  digitalWrite(L1, LOW);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
   Serial.print(".");
 }
// Print local IP address 
  Serial.println("");
  Serial.println("WiFi connected-->");
  Serial.println("Copy this IP address: ");
  Serial.println(WiFi.localIP());
 //start web server
  server.begin();
  delay(3000);
}
//================================================
void loop(){
  WiFiClient client = server.available();   
  if (client) {                             
    Serial.println("new client connected");          
    String currentLine = "";                
    while (client.connected())
      if (client.available()) {             
        char c = client.read();             
        Serial.write(c);                    
        header += c;
        if (c == '\n') {                    
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            if (header.indexOf("GET /LED1/on") >= 0) {
              Serial.println("LED1 on");
              L1State = "on";
              digitalWrite(L1, HIGH);
            } else if (header.indexOf("GET /LED1/off") >= 0) {
              Serial.println("LED1 off");
              L1State = "off";
              digitalWrite(L1, LOW);
            } 
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Cairo; display: inline; margin: 0px auto; text-align: center; background-color: #ccffb3;}");
            client.println(".button { background-color: #006699; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 35px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            client.println("<body><h1>Kontrol LED Web Server</h1>");
            // Jika LED OFF, tampilkan tombol ON        
            if (L1State=="off") {
              client.println("<p><a href=\"/LED1/on\"><button class=\"button\">ON</button></a></p>");
              client.println("<svg width=\"500\" height=\"300\"><ellipse cx=\"258.5\" cy=\"125.5\" fill=\"#ffffff\" rx=\"47\" ry=\"52\" stroke=\"#ffffaa\" stroke-width=\"5\"/><rect fill=\"#cccccc\" height=\"40\" stroke=\"#ffffaa\" stroke-width=\"5\" transform=\"rotate(-0.485546 261 187.5)\" width=\"39\" x=\"241.5\" y=\"167.5\"/></svg>");

            } else {
              client.println("<p><a href=\"/LED1/off\"><button class=\"button button2\">OFF</button></a></p>");
              client.println("<svg width=\"500\" height=\"300\"><ellipse cx=\"258.5\" cy=\"125.5\" fill=\"#ff7f00\" rx=\"47\" ry=\"52\" stroke=\"#ffffaa\" stroke-width=\"5\"/><rect fill=\"#cccccc\" height=\"40\" stroke=\"#ffffaa\" stroke-width=\"5\" transform=\"rotate(-0.485546 261 187.5)\" width=\"39\" x=\"241.5\" y=\"167.5\"/></svg>");

            }     
            client.println("</body></html>");
            client.println();
            break;
          } else { 
            currentLine = "";
          }
        } else if (c != '\r') {  
          currentLine += c;      
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client disconnected");
    Serial.println("");
  }
