/***************************************
 * Project Kontrol Servo SG90 dengan Web Page
 * Board  : NodeMCU ESP8266 V3
 * Input  : web server
 * Output : Servo SG90
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>
Servo myservo;  

static const int servoPin = D5;

//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
const char *ssid     = "ArdutechWiFi"; // Nama Hotspot/WiFi
const char *password = "12345678";  //  Password
WiFiServer server(80);
String header;
String valueString = String(5);
int pos1 = 0;
int pos2 = 0;
//=======================================
void setup() {
  Serial.begin(9600);
  myservo.attach(servoPin);  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}
//=========================================
void loop(){
  WiFiClient client = server.available();   

  if (client) {                            
    Serial.println("New Client.");          
    String currentLine = "";                 
    while (client.connected()) {            
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
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>body { text-align: center; font-family: \"Trebuchet MS\", Arial; margin-left:auto; margin-right:auto;}");
            client.println(".slider { width: 300px; }</style>");
            client.println("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script>");
            client.println("</head><body><h1>Kontrol Servo SG90</h1>");
            client.println("<p>Position: <span id=\"servoPos\"></span></p>");          
            client.println("<input type=\"range\" min=\"0\" max=\"180\" class=\"slider\" id=\"servoSlider\" onchange=\"servo(this.value)\" value=\""+valueString+"\"/>");
            client.println("<script>var slider = document.getElementById(\"servoSlider\");");
            client.println("var servoP = document.getElementById(\"servoPos\"); servoP.innerHTML = slider.value;");
            client.println("slider.oninput = function() { slider.value = this.value; servoP.innerHTML = this.value; }");
            client.println("$.ajaxSetup({timeout:1000}); function servo(pos) { ");
            client.println("$.get(\"/?value=\" + pos + \"&\"); {Connection: close};}</script>");
            client.println("</body></html>");     
            //GET /?value=180& HTTP/1.1
            if(header.indexOf("GET /?value=")>=0) {
              pos1 = header.indexOf('=');
              pos2 = header.indexOf('&');
              valueString = header.substring(pos1+1, pos2);              
              //Rotate the servo
              myservo.write(valueString.toInt());
              Serial.println(valueString); 
            }         
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
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
