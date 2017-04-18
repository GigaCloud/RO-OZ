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


int err;
float temp, humi;

void loop(void){

  packet.id = 2;
  
  if((err=dht11.read(packet.hum, packet.temp))==0){
       Serial.print(packet.temp);
       Serial.print(' ');
       Serial.println(packet.hum);
  }
  
  radio.write(&packet, sizeof(packet));

  radio.powerDown();
  delay(200);
  radio.powerUp();

 
}
