#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
#include <DHT11.h>
int pin=A5;

DHT11 dht11(pin); 

//#include <Wire.h>
//#include <SI7021.h>

char msg;

struct PacketBase{
  int id;
  float hum;
  float temp; 
} packet;



RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;

//SI7021 sensor;

void setup(void){
 Serial.begin(9600);
 radio.begin();
 //sensor.begin();
 printf_begin();
 radio.setPALevel(RF24_PA_LOW);
 radio.printDetails();
 radio.openWritingPipe(pipe);

}

void(* resetFunc) (void) = 0; 


int err;
float temp, humi;

void loop(void){
  
 //packet.nIncercare = sensor.getCelsiusHundredths();
 //Serial.println(packet.nIncercare);
 //int topkek = sensor.getCelsiusHundredths();
  packet.id = 1;
  packet.hum = 0;
  packet.temp = 0;


  
  packet.hum += humi;
  packet.temp += temp;
 
  if((err=dht11.read(humi, temp))==0)
  {
       Serial.println(temp);
  
  }

  else{
    Serial.println(err);
   
  }
    Serial.println(temp);
    Serial.println(humi);

   radio.write(&packet, sizeof(packet));

 
}
