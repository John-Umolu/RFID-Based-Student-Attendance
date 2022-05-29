/*RFID Based Student Attendance System With Android Mobile Application
 * 
 * Android Mobile Application Download Link: https://play.google.com/store/apps/details?id=com.akifagoelectronics.mobilebluetoothattendance
 * 
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno           Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 * 
 */
#include "SPI.h" 
#include "MFRC522.h"
//
#define SS_PIN 10 
#define RST_PIN 9 
//#define SP_PIN 8
int greenLed = 2;
int redLed = 3;
//
MFRC522 rfid (SS_PIN, RST_PIN);
MFRC522 :: MIFARE_Key key;
//
void setup () {
  Serial.begin (9600);
  SPI.begin ();
  rfid.PCD_Init ();
  //
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  //
  digitalWrite(redLed, HIGH);
  digitalWrite(greenLed, LOW);
  //
}

void loop () {
  if (!rfid.PICC_IsNewCardPresent () ||!rfid.PICC_ReadCardSerial ())
     return ;

  // Serial.print (F("PICC type:"));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType (rfid.uid.sak);
  // Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type 
  if(piccType!= MFRC522::PICC_TYPE_MIFARE_MINI&&
    piccType!= MFRC522::PICC_TYPE_MIFARE_1K&&
    piccType!= MFRC522::PICC_TYPE_MIFARE_4K){
    Serial.println(F( "Your tag is not of type MIFARE Classic."));
    return;
  }

  String strID = "" ;
  for (byte i = 0; i < 4; i++) {
    strID +=(rfid.uid.uidByte[i]<0x10?"0":"") + String(rfid.uid.uidByte[i], HEX);
  }
  strID.toUpperCase();
  Serial.println(strID);
  //
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, HIGH);
  delay(2000);
  digitalWrite(redLed, HIGH);
  digitalWrite(greenLed, LOW);
  //
  rfid.PICC_HaltA ();
  rfid.PCD_StopCrypto1();
}
