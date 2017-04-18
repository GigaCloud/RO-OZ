#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
#include <DHT11.h>

#define photo A1

int pin=A5;
DHT11 dht11(pin); 

struct PacketBase{
  int id;
  float hum;
  float temp; 
} packet;

RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;

void setup(void){
 Serial.begin(9600);
 radio.begin();
 printf_begin();
 radio.setPALevel(RF24_PA_LOW);
 radio.printDetails();
 radio.openWritingPipe(pipe);
}


int err;
float temp, humi;
int sec;
int lastTimePhoto;
int lastPhoto;
int deltaPhoto;
int timesPhoto;

void loop(void){
  sec = millis() / 1000;
  packet.id = 1;
  
  if((err=dht11.read(packet.hum, packet.temp))==0){
      Serial.print(packet.temp);
       Serial.print(' ');
       Serial.println(packet.hum);
  }

  if(sec - lastTimePhoto > 3){
    deltaPhoto = analogRead(photo) - lastPhoto;
    if (deltaPhoto < 0) deltaPhoto *= -1;
    if(deltaPhoto > 100 && lastPhoto != 0 && timesPhoto < 3){
      packet.id = 4;
     /* packet.hum = 48;
      packet.temp = 57;*/
      Serial.println("We are not in CanSat anymore!");
      ++timesPhoto;
      for(int i=0; i<5; ++i){
         radio.powerUp();
         radio.write(&packet, sizeof(packet));
         radio.powerDown();
      }
    }
    lastPhoto = analogRead(photo);
    lastTimePhoto = sec;
  }
  
  radio.write(&packet, sizeof(packet));

  radio.powerDown();
  delay(200);
  radio.powerUp();

 
}
