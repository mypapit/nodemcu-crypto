/****
 * 
 *  Simple code to Display Crypto Currency to 1602 i2c LCD on NodeMCU
 *  Copyright (c) 2021 Mohammad Hafiz bin Ismail <mypapit@gmail.com)
 * 
 *  Original Post: https://www.youtube.com/watch?v=bMO5UzgfTi0
 * 
 *  If you use this as a reference for your project, please cite this as (APA-Style):
 *
 *  Ismail, M. H. (2021). Simple code to Display Crypto Currency to 1602 i2c LCD on NodeMCU. Coding Malaya. 
 *  Retrieved December 16, 2021, from https://github.com/mypapit/nodemcu-crypto
 *   
 *   The currency displayed is in Malaysian Ringgit (MYR)
 *   
 *   Required parts:
 *      1. NodeMCU V2 Amica (V3 Lolin not recommended as it lacks internal LED)
 *      2. i2c 1602 LCD 
 *      3. Some jumper wires
 * 
 *     Estimated Project cost: 
 *     1. USD 5 + USD 3 = USD 8
 *     2. MYR 20 + MYR 12 = MYR 32
 *     
 *     This project uses internal LED to indicate the WiFi status. You are free to use external LED, if you want.
 *     All configurable parameters are listed on the top section of the code.
 *     
 *     ===  NOTE: DO NOT FORGET TO CHANGE WiFI SSID and PASSWORD CONFIGURATION ====
 *     
 *     
 *  TERMS
 *  You are free to use this code in your work and your project as long as:
 *    1. You attribute and cite this work in your project or your project documentation.
 *    2. Provide a link to this source code or its original website URL.
 *
*/


#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <LiquidCrystal_I2C.h>


// XRP Crypto currency valu API, change this to ETH.json for Ethereum, or XBT for Bitcoin
const char* CRYPTO_URL = "http://insecure.mypapit.net/api/XRP.json";

const char* ssid     = " ";         // WiFi AP Station Name 
const char* password = "  ";     // WiFi password

const int I2C_ADDRESS = 0x27; //change this i2c address if necessary.
const int LEDPIN = 2; // LED PIN ADDRESS


LiquidCrystal_I2C lcd(I2C_ADDRESS, 16, 2);

void setup() {

  pinMode(LEDPIN, OUTPUT);   //blue built in LED in NodeMCU v2 Amica
  
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(500);
  Serial.println('\n');
  
  WiFi.begin(ssid, password);             // Connect to the network
  

  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(2000);
   // Serial.print(++i); Serial.print(' ');
    blinkfast(); // blink fast to indicate that the WiFi is still connecting
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
  lcd.init();
  lcd.setCursor(0,0);
  lcd.print(WiFi.localIP());
  lcd.setCursor(0,1);
  lcd.print("Retrieving...");
  lcd.backlight();
  blinksuccess();  // blink slowly to indicate the wifi has already connected..

  
  delay(2000); // Pause for 2 seconds
  
}


void loop() {
  
   HTTPClient client;
   WiFiClient wifiClient;
   String payload;

  // XRP Crypto currency valu API, change this to ETH.json for Ethereum, or XBT for Bitcoin
  client.begin(wifiClient,CRYPTO_URL); 
  int code=client.GET();
  Serial.println("Code : " + code);
  
  

  if (code >0) {
    payload = client.getString();
  } else {
    const char* failedmsg = "Failed to get URL";
    lcd.setCursor(0,1);
    lcd.print(failedmsg);
    Serial.println(failedmsg);
  }

  //Serial.println(payload);
  Serial.println("Successfully retrieved data");

  client.end();

  DynamicJsonDocument doc(1600);

  deserializeJson(doc,payload);
 
  
  double bid = doc["bid"];
  const char* pair = doc["pair"];
  const char* timestamp = doc["tzkl"];
 
  
  //DEBUG ONLY
  //const char* ask = doc["ask"];
  //Serial.println(ask);
 // Serial.println(bid);
 //timestamp = timestamp/1000;
 //Serial.print(pair);
 //Serial.print(": ");
 //Serial.println(bid);
  
  
  lcd.setCursor(0,0);
  lcd.print("                "); // old hack to clear LCD
  lcd.setCursor(0,0);
  lcd.print(pair);
  lcd.print(":");
  lcd.print(bid);
  lcd.setCursor(0,1);
  lcd.print(timestamp);

 /// DELAY
 Serial.print("Delaying..." );
  
 //Serial.println(pair);  
  delay(900000); // update every 15 minutes

  
  }


void blinkfast(){
  int c;
  for (c=0;c<5;c++){
      digitalWrite(LEDPIN,LOW);
      delay(100);
      digitalWrite(LEDPIN,HIGH);
      delay(100);
      digitalWrite(LEDPIN,LOW);
      delay(100);
      digitalWrite(LEDPIN,HIGH);
      delay(100);
  }
}


void blinksuccess(){
  int c;
  for (c=0;c<3;c++){

      digitalWrite(LEDPIN,LOW);
      delay(2000);
      digitalWrite(LEDPIN,HIGH);
      delay(500);
      digitalWrite(LEDPIN,LOW);
      delay(2000);
      digitalWrite(LEDPIN,HIGH);
  }

}
  
      
