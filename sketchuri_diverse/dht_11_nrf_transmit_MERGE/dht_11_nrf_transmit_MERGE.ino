#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
#include <DHT11.h>

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

void(* resetFunc) (void) = 0; 

int err;
float temp, humi;

void loop(void){
  
  packet.id = 1;
  packet.hum = 0;
  packet.temp = 0;


  packet.hum += humi;
  packet.temp += temp;
  
  if((err=dht11.read(humi, temp))==0){
       Serial.print(temp);
       Serial.print(' ');
       Serial.println(humi);
  }
  else{
    Serial.println(err);
  } 

   radio.write(&packet, sizeof(packet));

  
  //delay(200);

 //delay(DHT11_RETRY_DELAY);

 //resetFunc();
 
}
