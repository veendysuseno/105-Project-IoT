/***************************************
 * Project Interfacing Dasar NodeMCU dg GPS 
 * Board  : NodeMCU ESP8266 V3
 * Input  : Modul GPS Neo-6M
 * Output : LCD + Webpage
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
TinyGPSPlus gps;  // The TinyGPS++ object
static const int RX= D6, TX= D7;
SoftwareSerial ss(RX, TX); // The serial connection to the GPS device
// alamat I2C LCD : 0x3f
// ukuran LCD : 16x2
LiquidCrystal_I2C lcd(0x3f,16,2);  
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
const char* ssid = "ArdutechWiFi";  // Nama Hotspot/WiFi
const char* password = "12345678";  //  Password

float latitude , longitude;
int year , month , date, hour , minute , second;
String date_str , time_str , lat_str , lng_str;
int pm,f,g;

WiFiServer server(80);
void setup()
{
  //pin SCL -- D1
  //pin SDA -- D2
  Wire.begin(D2, D1);  
  lcd.init(); 
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Interfacing GPS");
  lcd.setCursor(0,1);
  lcd.print("dengan NodeMCU "); 
  delay(2000); 
  Serial.begin(9600);
  ss.begin(9600);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  server.begin();
  Serial.println("Server started");
  // Print the IP address
  Serial.println(WiFi.localIP());
  lcd.clear();
  lcd.print("WiFi Connected");
  lcd.setCursor(0,1);
  lcd.print("IP:");
  lcd.print(WiFi.localIP());
  delay(3000);
  
} 
//========================================
void loop()
{ 
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
    {
      if (gps.location.isValid())
      {
        latitude = gps.location.lat();
        lat_str = String(latitude , 6);
        longitude = gps.location.lng();
        lng_str = String(longitude , 6);       
      }

      if (gps.date.isValid())
      {
        date_str = "";
        date = gps.date.day();
        month = gps.date.month();
        year = gps.date.year();

        if (date < 10)
          date_str = '0';
        date_str += String(date);

        date_str += "/";

        if (month < 10)
          date_str += '0';
        date_str += String(month);

        date_str += "/";

        if (year < 10)
          date_str += '0';
        date_str += String(year);
      }

      if (gps.time.isValid())
      {
        time_str = "";
        hour = gps.time.hour();
        minute = gps.time.minute();
        second = gps.time.second();

        //minute = (minute + 30);
        if (minute > 59)
        {
          minute = minute - 60;
          hour = hour + 1;
        }
        hour = (hour + 7) ;
        if (hour > 23)
          hour = hour - 24;

        if (hour >= 12)
          pm = 1;
        else
          pm = 0;

        hour = hour % 12;

        if (hour < 10)
          time_str = '0';
        time_str += String(hour);

        time_str += ":";

        if (minute < 10)
          time_str += '0';
        time_str += String(minute);

        time_str += ":";

        if (second < 10)
          time_str += '0';
        time_str += String(second);

        if (pm == 1)
          time_str += " PM ";
        else
          time_str += " AM ";

      }

    }
  f++;
  if(f<500){
          g++;
          if(g>100){
          lcd.clear();
          lcd.print("Lat=");
          lcd.print(lat_str);
          lcd.setCursor(0,1);
          lcd.print("Long=");
          lcd.print(lng_str);
          g=0;}
        }
   else if(f<1000){
          g++;
          if(g>100){ 
          lcd.clear();
          lcd.print("Date=");
          lcd.print(date_str);
          lcd.setCursor(0,1);
          lcd.print("Time=");
          lcd.print(time_str);
          g=0;}
        }
   else if(f>=1000){
    f=0;
   }
  delay(10);
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }

  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n"; 
  s += "\r\n"; 
  s += "<!DOCTYPE html> <html> <head> <title>Interfacing NodeMCU dg Modul GPS</title> <style>";
  s += "a:link {background-color: YELLOW;text-decoration: none;}";
  s += "table, th, td {border: 1px solid black;} </style> </head> <body> <h1  style=";
  s += "font-size:250%;";
  s += " ALIGN=CENTER> Interfacing NodeMCU dg Modul GPS</h1>";
  s += "<p ALIGN=CENTER style=""font-size:200%;""";
  s += "> <b>Location Details</b></p> <table ALIGN=CENTER style=";
  s += "width:50%";
  s += "> <tr> <th>Latitude</th>";
  s += "<td ALIGN=CENTER >";
  s += lat_str;
  s += "</td> </tr> <tr> <th>Longitude</th> <td ALIGN=CENTER >";
  s += lng_str;
  
  s += "</td> </tr> <tr>  <th>Date</th> <td ALIGN=CENTER >";
  s += date_str;
  s += "</td></tr> <tr> <th>Time</th> <td ALIGN=CENTER >";
  s += time_str;
  s += "</td>  </tr> </table> ";   
  s += "</body> </html> \n";
  client.print(s);  
  delay(100);
}
