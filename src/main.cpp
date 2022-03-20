#include <Arduino.h>
#include "WIFIConnector_MKR1000.h"
#include "MQTTConnector.h" 

//Libraries
#include <Keypad.h>//https://github.com/Chris--A/Keypad




//Constants
#define ROWS 4
#define COLS 4

//Parameters




const int LED_BLUE = 0;
const int LED_ROUGE = 1;
const int LED_JAUNE = 2;
const int LED_VERT = 3;

int ledChoisi, blinkValue, ledIntens ;
char customKey, lastCustKey ;
const char kp4x4Keys[ROWS][COLS]  = {{'1', '2', '3', 'A'}, {'4', '5', '6', 'B'}, {'7', '8', '9', 'C'}, {'*', '0', '#', 'D'}};
byte rowKp4x4Pin [4] = {11, 10, 9, 8};
byte colKp4x4Pin [4] = {7, 6 ,5 ,4};

//Variables
Keypad kp4x4  = Keypad(makeKeymap(kp4x4Keys), rowKp4x4Pin, colKp4x4Pin, ROWS, COLS);

void setup() {

   wifiConnect();                  //Branchement au réseau WIFI
   MQTTConnect(); 

  //Init Serial USB
  Serial.begin(9600);
  Serial.println(F("Initialize System"));

/*
   pinMode(LED_BLUE, OUTPUT);
   pinMode(LED_ROUGE, OUTPUT);
   pinMode(LED_JAUNE, OUTPUT);
   pinMode(LED_VERT, OUTPUT);
*/
}



/*
void readKp4x4() { //function readKp4x4 
  //// Read button states from keypad
  char customKey = kp4x4.getKey();
  if (customKey) {
    Serial.println(customKey);
  }
}
*/


void loop() {
 // readKp4x4();
   customKey = kp4x4.getKey();

   if(customKey == 'A' || customKey == 'B' || customKey == 'C' || customKey == 'D' ){
      lastCustKey = customKey ;
   }


   if(customKey == '*')
   {
      switch (lastCustKey)
      {
         case 'A':
            ledChoisi = LED_BLUE;
            break;
         
         case 'B':
            ledChoisi = LED_ROUGE ;
            break;

         case 'C':
            ledChoisi = LED_JAUNE ;
            break;

         case 'D':
            ledChoisi = LED_VERT ;
            break;

      }

   }


   switch (customKey)
   {
      case '0':
         blinkValue = 0;
         break;
         
      case '1':
         blinkValue = 1 ;
         break;

      case '2':
         blinkValue = 2 ;
         break;

      case '3':
         blinkValue = 3 ;
         break;

      case '4':
         blinkValue = 4;
         break;
         
      case '5':
        blinkValue = 5 ;
         break;

      case '6':
         blinkValue = 6 ;
         break;

      case '7':
         blinkValue = 7 ;
         break;

      case '8':
         blinkValue = 8 ;
         break;

      case '9':
         blinkValue = 9 ;
         break;

   }
   
   if (customKey == '#')
   {
      ledIntens = map(blinkValue, 0, 9, 0, 255);
      analogWrite(ledChoisi, ledIntens);
   }
   

   appendPayload("Led allume : ", ledChoisi); 
   appendPayload("Tention", blinkValue);  
   sendPayload(); 

}

