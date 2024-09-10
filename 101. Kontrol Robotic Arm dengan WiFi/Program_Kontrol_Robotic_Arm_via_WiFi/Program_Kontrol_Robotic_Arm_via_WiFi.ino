/***************************************
 * Project Kontrol Robotic Arm dengan WiFi
 * Board  : NodeMCU ESP8266 V3
 * Input  : Web page
 * Output : Robotic Arm (4 Servo)
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#include <ESP8266WiFi.h>
#include <Servo.h>
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
const char* ssid     = "ArdutechWiFi";  // Nama Hotspot/WiFi
const char* password = "12345678";      //  Password

WiFiServer server(80);
String header;
String valueString = String(5);
int pos1 = 0;
int pos2 = 0;
const int SERVOS = 4;
int PIN[SERVOS], value[SERVOS], INITANGLE[SERVOS];
Servo myservo[SERVOS];
int DELAYTIME = 200;
int bt_servo;
int bt_move;
byte str;
String inString="";
String in_serial="";
int i,j;
int movef;
//======================================
void setup() {  
  PIN[0] = D4;
  INITANGLE[0] = 90;//MIDDLE
  PIN[1] = D3;
  INITANGLE[1] = 90;//LEFT
  PIN[2] = D2;
  INITANGLE[2] = 70;//RIGHT
  PIN[3] = D1;
  INITANGLE[3] = 25;//CLAW
  for (int i = 0; i < SERVOS; i++){
    myservo[i].attach(PIN[i]);
    myservo[i].write(INITANGLE[i]);
  }
  Serial.begin(9600);
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
  Serial.println("192.168.43.229");
  server.begin();
}
//=======================================
void loop() {
  WiFiClient client = server.available();   
  if (client) {                            
    Serial.println("New Client.");          
    String currentLine = "";                
    boolean currentLineIsBlank = true;
    while (client.connected()) {           
      if (client.available()) {             
        char c = client.read();             
        Serial.write(c);                    
        header += c;
        if (c == '\n' && currentLineIsBlank) {    
          Serial.println("Sending response");  
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><title>Robotic Arm controller</title>");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>body { text-align: center; font-family: \"Trebuchet MS\", Arial; margin-left:auto; margin-right:auto;}");
            client.println("#servoPosR{color: red;}");
            client.println("#servoPosG{color: green;}");
            client.println("#servoPosB{color: blue;}");
            client.println(".slider { width: 300px; }</style>");
            client.println("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script>");
            client.println("</head><body><h1>Kontorl Robotic Arm via WiFi</h1>");
            //ServoA slide bar
            client.println("<p>Claw Pos: <span id=\"servoPosA\"></span></p>");
            client.println("<input type=\"range\" min=\"20\" max=\"50\" class=\"slider\" id=\"servoSliderA\" onchange=\"servo(this.value,'A')\" value=\"" + valueString + "\"/>");
            //ServoB slide bar
            client.println("<p>Left Pos: <span id=\"servoPosB\"></span></p>");
            client.println("<input type=\"range\" min=\"1\" max=\"60\" class=\"slider\" id=\"servoSliderB\" onchange=\"servo(this.value,'B')\" value=\"" + valueString + "\"/>");
            //ServoC slide bar
            client.println("<p>Right Pos: <span id=\"servoPosC\"></span></p>");
            client.println("<input type=\"range\" min=\"1\" max=\"60\" class=\"slider\" id=\"servoSliderC\" onchange=\"servo(this.value,'C')\" value=\"" + valueString + "\"/>");
            //ServoD slide bar
            client.println("<p>Middle Pos: <span id=\"servoPosD\"></span></p>");
            client.println("<input type=\"range\" min=\"1\" max=\"60\" class=\"slider\" id=\"servoSliderD\" onchange=\"servo(this.value,'D')\" value=\"" + valueString + "\"/>");
            client.println("<script>");
            //send A value
            client.println("var sliderA = document.getElementById(\"servoSliderA\");");
            client.println("var servoPA = document.getElementById(\"servoPosA\"); servoPA.innerHTML = sliderA.value;");
            client.println("sliderA.oninput = function() { sliderA.value = this.value; servoPA.innerHTML = this.value; }");
            //send B value
            client.println("var sliderB = document.getElementById(\"servoSliderB\");");
            client.println("var servoPB = document.getElementById(\"servoPosB\"); servoPB.innerHTML = sliderB.value;");
            client.println("sliderB.oninput = function() { sliderB.value = this.value; servoPB.innerHTML = this.value; }");
            //send C value
            client.println("var sliderC = document.getElementById(\"servoSliderC\");");
            client.println("var servoPC = document.getElementById(\"servoPosC\"); servoPC.innerHTML = sliderC.value;");
            client.println("sliderC.oninput = function() { sliderC.value = this.value; servoPC.innerHTML = this.value; }");
            //send D value
            client.println("var sliderD = document.getElementById(\"servoSliderD\");");
            client.println("var servoPD = document.getElementById(\"servoPosD\"); servoPD.innerHTML = sliderD.value;");
            client.println("sliderD.oninput = function() { sliderD.value = this.value; servoPD.innerHTML = this.value; }");
            client.println("$.ajaxSetup({timeout:1000}); function servo(pos,color) { ");
            client.println("$.get(\"/?value\" + color + \"=\" + pos + \"&\"); {Connection: close};}</script>");
            client.println("</body></html>");
            if (header.indexOf("GET /?valueA=") >= 0) {
              pos1 = header.indexOf('=');
              pos2 = header.indexOf('&');
              valueString = header.substring(pos1 + 1, pos2);
                myservo[0].write(INITANGLE[valueString.toInt()]);//claw
                Serial.println(valueString);
            }
            if (header.indexOf("GET /?valueB=") >= 0) {
              pos1 = header.indexOf('=');
              pos2 = header.indexOf('&');
              valueString = header.substring(pos1 + 1, pos2);
              myservo[1].write(INITANGLE[valueString.toInt()]);//left
              Serial.println(valueString);
            }

            if (header.indexOf("GET /?valueC=") >= 0) {
              pos1 = header.indexOf('=');
              pos2 = header.indexOf('&');
              valueString = header.substring(pos1 + 1, pos2);
              myservo[2].write(INITANGLE[valueString.toInt()]);//right
              Serial.println(valueString);
            }

            if (header.indexOf("GET /?valueD=") >= 0) {
              pos1 = header.indexOf('=');
              pos2 = header.indexOf('&');
              valueString = header.substring(pos1 + 1, pos2);
              myservo[3].write(INITANGLE[valueString.toInt()]);//Middle
              Serial.println(valueString);
            }
            client.println();
            // Break out of the while loop
            break;
        }
        if (c == '\n') {
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
         // currentLine += c;
          currentLineIsBlank = false;
        }
      }
    }
    // Clear the header variable
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
