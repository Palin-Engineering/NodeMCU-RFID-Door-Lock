/// ************************ Included Libraries ************************
#include <ESP8266WiFi.h> //Included when the NodeMCU Boards are added
#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266HTTPClient.h>
#include "Adafruit_MCP23017.h"

#include <Keypad_MC17.h>
#include <Wire.h>
#include <Keypad.h>
/// ************************ Included Libraries ************************

/// ************************ KeyPad Stuff ************************


#define I2CADDR 0x20


String code;

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns

char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = {0, 1, 2, 3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 5, 6}; //connect to the column pinouts of the keypad

Keypad_MC17 keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS, I2CADDR );


Adafruit_MCP23017 mcp;

/// ************************ Variables ************************


byte readCard[4]; 

int ID = 0;

String keyCode;

const char* ssid = "";// 
const char* password = "";

const String room = "bed_room";;
//WiFiClient client;

#define SS_PIN  2//FOR RFID SS PIN BECASUSE WE ARE USING BOTH ETHERNET SHIELD AND RS-522
#define RST_PIN 0
#define buzzer 16
#define door 15

 WiFiClient client;

//WiFiServer server(80);
  
MFRC522 rfid(SS_PIN,RST_PIN);
MFRC522::MIFARE_Key key; 


byte i;


void setup()
{
  Serial.begin(9600);

  pinMode(buzzer, OUTPUT);
  
  delay(10);
  pinMode(door, OUTPUT);
  
  digitalWrite(door,LOW);
  
  SPI.begin();
  rfid.PCD_Init();

  for(byte i=0;i<6;i++)
  {
    key.keyByte[i]=0xFF;
  }

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);

  int i = 0;
  while (WiFi.status() != WL_CONNECTED && i < 50) 
  {
    i++;
    delay(500);
    Serial.print(".");
  }



  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  //  server.begin();
  Serial.println("Server started");
  Serial.print(WiFi.localIP());
  delay(1000);
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  delay(200);
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  Serial.println("CONECTED");
}


 
void loop()
{ 

  String sID, check, profile;
 

  getID();
    
  for ( uint8_t i = 0; i < 4; i++) 
  {  //
    sID = sID + readCard[i];
  }
    
  if(sID != "0000")
  {
     
    
      Serial.println("ID Tag: " + sID);
      
      for ( uint8_t i = 0; i < 4; i++) 
      {  //
        readCard[i] = 0;
      }

      if(sID == "443142122")
      {
        Serial.println("Access Granted: Master Failsafe");
        access();
        
      }
      

      
     keyCode = getKeyCode();



      
      Serial.println("Got Keycode: " + keyCode);
      check = checkID(sID, room, keyCode);

      
      
      profile = check.substring(2);
      check = check.substring(0,2);

      Serial.println("Check: " + check + " profile: " + profile);
      
      if(check == "SS")
      {
        Serial.println("Access Granted:" + check);
        access();
        logID(sID, room, profile, "GRANTED");

        
      }else{
        Serial.println("Access Denied: LOCKED" + check + "<- check");
        digitalWrite(buzzer, HIGH);
        delay(200);
        digitalWrite(buzzer, LOW);
        logID(sID, room, profile, "DENIED");
      }
      
      
      check ="";
      sID = "0000";
  }
  
}

void access()
{
  digitalWrite(door, HIGH);

  for (int i = 0; i <= 15; i++) {
    digitalWrite(buzzer, HIGH);
    delay(75);
    digitalWrite(buzzer, LOW);
    delay(75);
  }
  digitalWrite(door, LOW);
}

int getID()
 {
      if ( ! rfid.PICC_IsNewCardPresent()) { //If a new PICC placed to RFID reader continue
        return 0;
      }
      if ( ! rfid.PICC_ReadCardSerial()) {   //Since a PICC placed get Serial and continue
        return 0;
      }
      
      for ( uint8_t i = 0; i < 4; i++) 
      {  
        readCard[i] = rfid.uid.uidByte[i];
        //Serial.print(readCard[i]);
      }
      //Serial.println("");
      rfid.PICC_HaltA(); // Stop reading
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer, LOW);
      
      return 1;

}

String checkID(String ID, String area, String keyCode)
{
  String postData, payload;

 
  //Post Data
  postData = "tag=" + ID + "&area=" + area + "&keyCode=" + keyCode;
  //Serial.println(postData);
 if((WiFi.status() == WL_CONNECTED)) {
       

        HTTPClient http;

        
        // Use posttestserver.com
        http.begin("https://rfid.gpalin.com/check.php", "75 F3 62 E3 65 FC 59 D1 C4 8B B9 8C 86 FE E8 86 E2 C9 A6 7D");
        http.addHeader("Content-Type", "application/x-www-form-urlencoded", false, true);
        
        
        // start connection and send HTTP header
        int httpCode = http.POST(postData);

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                payload = http.getString();
                Serial.println(payload);
                
            }
        } else {
            Serial.printf("[HTTPS] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }
  
  return payload;
}



String logID(String ID, String area, String profile, String access)
{
    String postData, payload;

 
  //Post Data
  if(profile == "")
  {
    profile = "UNKNOWN";
  }
  
  postData = "tag=" + ID + "&area=" + area + "&profile=" + profile + "&access=" + access;
  
  Serial.println(postData);
 if((WiFi.status() == WL_CONNECTED)) {
       
        HTTPClient http;

        
        // Use posttestserver.com
        http.begin("https://rfid.gpalin.com/log.php", "75 F3 62 E3 65 FC 59 D1 C4 8B B9 8C 86 FE E8 86 E2 C9 A6 7D");
        http.addHeader("Content-Type", "application/x-www-form-urlencoded", false, true);
        
        
        // start connection and send HTTP header
        int httpCode = http.POST(postData);

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                payload = http.getString();
                Serial.println(payload);
                
            }
        } else {
            Serial.printf("[HTTPS] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }
  return payload;
}

String getKeyCode()
{
 keypad.begin( );
 char key; 
 int check = 0;
 String code = "";
 
 do{
  key = keypad.getKey();
  switch (key) {
    case '*':
      check = 1;
      return code;
      break;
      
    default:
      if(key){
        digitalWrite(buzzer, HIGH);
        delay(50);
        digitalWrite(buzzer, LOW);
        code = code + key;
      }
      break;
  }
  
  delay(100);
  
 }while(check != 1);
}
