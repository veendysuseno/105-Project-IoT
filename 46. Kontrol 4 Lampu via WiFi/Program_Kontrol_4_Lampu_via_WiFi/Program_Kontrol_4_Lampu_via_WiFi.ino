/***************************************
 * Project Kontrol 4 Lampu via WiFi
 * Board  : NodeMCU ESP8266 V3
 * Input  : -
 * Output : Relay 4 Channels
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#include <ESP8266WiFi.h> 
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
const char* ssid = "ArdutechWiFi"; //Nama Hotspot
const char* password = "12345678"; //Password
#define Relay1 D5
#define Relay2 D6 
#define Relay3 D7 
#define Relay4 D8 

WiFiServer server(80);
//==================================== 
void setup() {
  Serial.begin(9600);
  delay(10);
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  pinMode(Relay4, OUTPUT);
  digitalWrite(Relay1, LOW);
  digitalWrite(Relay2, LOW);
  digitalWrite(Relay3, LOW);
  digitalWrite(Relay4, LOW);   
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
 
  // Start the server
  server.begin();
  Serial.println("Server started"); 
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/"); 
}
//====================================  
void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  if (request.indexOf("/relay1on") > 0)  {
    digitalWrite(Relay1, HIGH);   
  }
  if (request.indexOf("/relay1off") >0)  {
    digitalWrite(Relay1, LOW);   
  }

   if (request.indexOf("/relay2on") > 0)  {
    digitalWrite(Relay2, HIGH);
   
  }
  if (request.indexOf("/relay2off") >0)  {
    digitalWrite(Relay2, LOW);
   
  }
    if (request.indexOf("/relay3on") >0)  {
    digitalWrite(Relay3, HIGH);
   
  }
  if (request.indexOf("/relay3off") > 0)  {
    digitalWrite(Relay3, LOW);
   
  }
   if (request.indexOf("/relay4on") > 0)  {
    digitalWrite(Relay4, HIGH);
   
  }
  if (request.indexOf("/relay4off") > 0)  {
    digitalWrite(Relay4, LOW);
   
  }

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
  client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
  client.println("</head>");
  client.println("<body bgcolor = \"#f7e6ec\">"); 
  client.println("<hr/><hr>");
  client.println("<h3><center> 99 Project IoT : Kontrol 4 Lampu  </center></h3>");
  client.println("<h4><center> www.ardutech.com  </center></h4>");
  client.println("<hr/><hr>");  
  client.println("<br><br>");
  //client.println("<br><br>");
  client.println("<center>");
  client.println("Lampu 1");
  client.println("<a href=\"/relay1on\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/relay1off\"\"><button>Turn Off </button></a><br />");  
  client.println("</center>");   
  client.println("<br><br>");
  client.println("<center>");
  client.println("Lampu 2");
  client.println("<a href=\"/relay2on\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/relay2off\"\"><button>Turn Off </button></a><br />");  
  client.println("</center>"); 
  client.println("<br><br>");
  client.println("<center>");
  client.println("Lampu 3");
  client.println("<a href=\"/relay3on\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/relay3off\"\"><button>Turn Off </button></a><br />");  
  client.println("</center>"); 
  client.println("<br><br>");
  client.println("<center>");
  client.println("Lampu 4");
  client.println("<a href=\"/relay4on\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/relay4off\"\"><button>Turn Off </button></a><br />");  
  client.println("</center>"); 
  client.println("<br><br>");
  client.println("<center>");  
  client.println("<table border=\"5\">");
  client.println("<tr>");
  //=====================
  if (digitalRead(Relay1))
         { 
           client.print("<td>Lampu 1 = ON</td>");        
         }
  else
          {
            client.print("<td>Lampu 1 = OFF</td>");
          }     
  client.println("<br />");
  //======================           
  if (digitalRead(Relay2))
          { 
           client.print("<td>Lampu 2 = ON</td>");
          }
  else
          {
            client.print("<td>Lampu 2 = OFF</td>");
          }
  client.println("</tr>");
  //=======================
  client.println("<tr>");
  
  if (digitalRead(Relay3))
          { 
           client.print("<td>Lampu 3 = ON</td>");
          }
  else
          {
            client.print("<td>Lampu 3 = OFF</td>");
          }
  if (digitalRead(Relay4))
          { 
           client.print("<td>Lampu 4 = ON</td>");
          }
  else
          {
            client.print("<td>Lampu 4 = OFF</td>");
          }
  client.println("</tr>");  
  client.println("</table>");
  client.println("</center>");
  client.println("</html>"); 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println(""); 
}
