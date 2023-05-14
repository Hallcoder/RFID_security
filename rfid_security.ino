#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN); 
MFRC522::MIFARE_Key key; 

byte nuidPICC[4];
int buzzerPin = 7;
int redLED = 5;
int greenLED = 6;
int melody[] = {
  100, 262
};
int duration[] = {
  50, 50
};
void setup() { 
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  pinMode(buzzerPin,OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
  
}

void loop(){
  if(Serial.available()>0){
    String data = Serial.readString();
    if(data == "Wow......"){
     digitalWrite(buzzerPin, HIGH);
     digitalWrite(greenLED, HIGH);
    delay(1000);  
    digitalWrite(buzzerPin,LOW);
    digitalWrite(greenLED, LOW);
      }else{
        for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
          digitalWrite(redLED, HIGH);
    tone(buzzerPin, melody[i], duration[i]);
    delay(duration[i]);
  }     
    digitalWrite(redLED, LOW);
      }
    
  }
  if(!rfid.PICC_IsNewCardPresent()){
    return;
  }

  if(!rfid.PICC_ReadCardSerial()){
    return;
  }

    for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = rfid.uid.uidByte[i];
    }

    printHex(rfid.uid.uidByte, rfid.uid.size);


 /* 
  * Halt PICC
  * Stop encryption on PCD
 */

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

void printHex(byte *buffer, byte bufferSize){
  for (byte i = 0; i < bufferSize; i++){
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i],   HEX);
  }
}  