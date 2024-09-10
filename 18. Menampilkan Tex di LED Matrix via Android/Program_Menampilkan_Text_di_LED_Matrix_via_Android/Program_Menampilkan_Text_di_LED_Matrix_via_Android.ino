/***************************************
 * Project Menampilkan Text di Dot Matrix via Android (Blynk)
 * Board  : NodeMCU ESP8266 V3
 * Input  : Blynk 
 * Output : LED Matrix 8x32
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
 #define BLYNK_PRINT Serial
//#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
char ssid[] = "ArdutechWiFi";   // Nama Hotspot/WiFi
char pass[] = "12345678";       //  Password
//---GANTI SESUAI DENGAN TOKEN BLYNK ANDA
char auth[] = "-htbXm6E3Lizwp915_No7P516Ywa7nrj";//to
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CLK_PIN   D5  // or SCK
#define DATA_PIN  D7  // or MOSI
#define CS_PIN    D8  // or SS

// SPI hardware interface
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE,CS_PIN, MAX_DEVICES);
#define    CHAR_SPACING    1    // pixels between characters
#define    BUF_SIZE    75
#define UNIT_DELAY       25
#define SCROLL_DELAY     (4 * UNIT_DELAY)
static  boolean bRestart = true;
uint32_t prevTimeAnim = 0;  
  
char charBuf[50]= "Kontrol Running Text";

WidgetTerminal terminal(V0);
BLYNK_WRITE(V0){
  String msg = param.asStr();
  msg.toCharArray(charBuf, 50); 
}

//==============================
bool scrollText(bool bInit, char *pmsg)
// Callback function for data that is required for scrolling into the display
{
  static char    curMessage[BUF_SIZE];
  static char   *p = curMessage;
  static uint8_t  state = 0;
  static uint8_t  curLen, showLen;
  static uint8_t  cBuf[8];
  uint8_t         colData;

  // are we initializing?
  if (bInit)
  {    
    resetMatrix();
    strcpy(curMessage, pmsg);
    state = 0;
    p = curMessage;
    bInit = false;
  }

  // Is it time to scroll the text?
  if (millis()-prevTimeAnim < SCROLL_DELAY)
    return(bInit);

  // scroll the display
  mx.transform(MD_MAX72XX::TSL);  // scroll along
  prevTimeAnim = millis();      // starting point for next time

  // now run the finite state machine to control what we do 
  switch (state)
  {
    case 0: // Load the next character from the font table     
      showLen = mx.getChar(*p++, sizeof(cBuf)/sizeof(cBuf[0]), cBuf);
      curLen = 0;
      state = 1;
    case 1: // display the next part of the character
      colData = cBuf[curLen++];
      mx.setColumn(0, colData);
      if (curLen == showLen)
      {
        showLen = ((*p != '\0') ? CHAR_SPACING : mx.getColumnCount()-1);
        curLen = 0;
        state = 2;
      }
      break;

    case 2: // display inter-character spacing (blank column) or scroll off the display
      mx.setColumn(0, 0);
      if (++curLen == showLen) 
      {
        state = 0;
        bInit = (*p == '\0');
      }
      break;
    default:
      state = 0;
  }
  return(bInit);
}
//==============

void setup()
{
  mx.begin(); 
  delay(1000); 
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);  
  terminal.clear();
}
//=================================
void loop() 
{ 
  Blynk.run();
  bRestart = scrollText(bRestart, charBuf); 
}
//==================================
void resetMatrix(void)
{
  mx.control(MD_MAX72XX::INTENSITY, MAX_INTENSITY/2);
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  mx.clear();
  prevTimeAnim = 0;
}
