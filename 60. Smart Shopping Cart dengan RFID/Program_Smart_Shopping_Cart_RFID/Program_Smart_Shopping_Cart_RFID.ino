/***************************************
 * Project Smart Shopping Cart RFID
 * Board  : NodeMCU ESP8266 V3
 * Input  : RFID TAG
 * Output : web page, LCD
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#include<ESP8266WiFi.h> 
#include<LiquidCrystal_I2C.h> 
#include<Wire.h> 
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN D4  //D2
#define RST_PIN D3 //D1
LiquidCrystal_I2C lcd(0x27, 16, 2); 
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
const char* ssid = "ArdutechWiFi";// Nama Hotspot/WiFi 
const char* password = "12345678";//  Password 

char input[12]; 
int count = 0; 
int a; 
int p1=0,p2=0,p3=0,p4=0; 
int c1=0,c2=0,c3=0,c4=0; 
double total = 0; 
int count_prod = 0; 
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int statuss = 0;
int out = 0;
String ID_TAG;
WiFiServer server(80);
//==========================
void readRFID(byte *buffer, byte bufferSize)
{
  ID_TAG="";
  for(byte i = 0;i<bufferSize; i++)
  {
    ID_TAG=ID_TAG+String(buffer[i], HEX);
  }
}
//==============================
void setup() {    
  Serial.begin(9600);  
  SPI.begin();      
  mfrc522.PCD_Init();    
  Wire.begin(D2, D1);   
//  lcd.begin(16, 2);   
  lcd.begin();   
  lcd.backlight();   
  lcd.setCursor(0, 0);   
  lcd.print("   Smart Cart  ");   
  lcd.setCursor(0, 1);   
  lcd.print("  TOKO BERKAH  ");      
  Serial.print("Connecting to: ");
  Serial.println(ssid);
  //connect to your local wi-fi network
  WiFi.begin(ssid, password);
  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(".");
      }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("IP address : ");  
  Serial.println(WiFi.localIP());  
  server.begin(); 
  delay(2000);     
  lcd.clear();  
  lcd.print(" Selamat Belanja ");   
  lcd.setCursor(0, 1);   
  lcd.print(" Semoga Barokah ");  
  server.begin();
  delay(3000);  
  lcd.clear();  
  lcd.print("Item=0");   
  lcd.setCursor(0, 1);   
  lcd.print("Total=Rp0");  
}
//------------
void kirim(){
  WiFiClient client = server.available();
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");  
  client.println("Refresh: 5");  
  client.println();
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");  
  client.println("<title>e-Cart Toko Berkah</title></head><style type=\"text/css\">");     
  client.println("table{border-collapse: collapse;}th {background-color:  #3498db ;color: white;}table,td {border: 4px solid black;font-size: x-large;");     
  client.println("text-align:center;border-style: groove;border-color: rgb(255,0,0);}</style><body><center>");     
  client.println("<h1>Smart Shopping Cart Toko BERKAH</h1><br><br><table style=\"width: 1200px;height: 450px;\">");
  client.println("<tr><th>ITEMS</th><th>QUANTITY</th><th>COST</th></tr>");
  client.println("<tr><td>Gula pasir (1kg)</td><td>"+String(p1)+"</td><td>"+String(c1)+"</td></tr>");     
  client.println("<tr><td>Terigu (1kg)</td><td>"+String(p2)+"</td><td>"+String(c2)+"</td></tr>");
  client.println("<tr><td>Minyak (1L)</td><td>"+String(p3)+"</td><td>"+String(c3)+"</td></tr>");  
  client.println("<tr><td>Wafer Tanggo</td><td>"+String(p4)+"</td><td>"+String(c4)+"</td></tr>");
  client.println("<tr><th>Grand Total</th><th>"+String(count_prod)+"</th><th>"+String(total)+"</th></tr>");     
  client.println("</table><br><input type=\"button\" name=\"Bayar\" value=\"Bayar\" style=\"width: 200px;height: 50px\"></center></body></html>");
  client.println("<meta http-equiv=\"refresh\" content=\"2\">");
  delay(5000);
  lcd.clear();
  lcd.print("Item=");   
  lcd.print(count_prod);  
  lcd.setCursor(0,1);   
  lcd.print("Total= Rp");   
  lcd.print(total);  
  
}
//======================================
void loop(){   
  if(!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()){
    return;    
   } 
  readRFID(mfrc522.uid.uidByte, mfrc522.uid.size);  
  Serial.print("RFID=");
  Serial.println(ID_TAG);  
  //-------------------Gula pasir
  if (ID_TAG== "e745ba19"){ 
      lcd.setCursor(0, 0);
      lcd.print("Gula Pasir 1kg       ");
      lcd.setCursor(0, 1);
      lcd.print("Rp.13.000,-          ");
      p1++;         
      total = total + 13000;
      count_prod++;  
      c1=p1*13000; //Gula pasir 1kg
      kirim();
      }  
    //-----------------------TERIGU-----------
  else if (ID_TAG== "a745ba19"){ 
      lcd.setCursor(0, 0);
      lcd.print("Terigu 1kg           ");
      lcd.setCursor(0, 1);
      lcd.print("Rp.10.000,-          ");
      p2++;  
      total = total + 10000;
      count_prod++; 
      c2=p2*10000; 
      kirim();
      } 
    //-----------------------MINYAK-----------
  else if (ID_TAG== "871a3063"){ //change UID of the card that you want to give access
      lcd.setCursor(0, 0);
      lcd.print("Minyak 1L            ");
      lcd.setCursor(0, 1);
      lcd.print("Rp.11.000,-          ");
      p3++;   
      total = total + 11000;
      count_prod++;        
      c3=p3*11000;
      kirim();
      } 
     //-----------------------BISKUIT----------
  else if (ID_TAG== "a775797b"){ //change UID of the card that you want to give access
      lcd.setCursor(0, 0);
      lcd.print("Wafer Tanggo       ");
      lcd.setCursor(0, 1);
      lcd.print("Rp.7.000,-          ");
      p4++;         
      total = total + 7000;
      count_prod++;       
      c4=p4*7000; 
      kirim();      
      }     
  }
