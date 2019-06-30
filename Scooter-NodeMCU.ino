#include "ThingSpeak.h"
#include <ESP8266WiFi.h>

//----------------  Fill in your credentails   ---------------------
char ssid[] = "Beinur";     // your network SSID (name) 
char pass[] = "legion96"; // your network password
//------------------------------------------------------------------

WiFiClient  client;

unsigned long counterChannelNumber = 810675;
const char * myCounterReadAPIKey = "1VCLS87C8TDEJX46";
unsigned int counterFieldNumber = 1; 

#define LED D1 // Led in NodeMCU at pin GPIO16 (D0).


void setup() {

  pinMode(LED, OUTPUT); // set the digital pin as output.

 //Initialize serial and wait for port to open:
 Serial.begin(9600);
 while (!Serial) {
   ; // wait for serial port to connect. Needed for native USB port only
 }

 WiFi.mode(WIFI_STA);  
 ThingSpeak.begin(client);
}

void loop() {

 int statusCode = 0;
 
 // Connect or reconnect to WiFi
 if(WiFi.status() != WL_CONNECTED){
   Serial.print("Attempting to connect to SSID: ");
   while(WiFi.status() != WL_CONNECTED){
     WiFi.begin(ssid, pass);
     Serial.print(".");
     delay(5000);     
   } 
   Serial.println("\nConnected");
 }

 // Read in field 1 of the private channel which is a counter  
 long count = ThingSpeak.readLongField(counterChannelNumber, counterFieldNumber, myCounterReadAPIKey);  

if(count == 1){
  digitalWrite(LED, HIGH);// turn the LED off.
  Serial.println("Engine is ON");
} else {
  digitalWrite(LED, LOW);// turn the LED on
  Serial.println("Engine is OFF");
}

  // Check the status of the read operation to see if it was successful
 statusCode = ThingSpeak.getLastReadStatus();
 if(statusCode == 200){
   Serial.println("Counter: " + String(count));
 }
 else{
   Serial.println("Problem reading channel. HTTP error code " + String(statusCode)); 
 }
 
 delay(3000); // No need to read the counter too often.
 
}
