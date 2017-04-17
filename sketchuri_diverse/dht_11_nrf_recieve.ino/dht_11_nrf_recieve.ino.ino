#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
RF24 radio(5, 6);

const uint64_t pipe = 0xE8E8F0F0E1LL;
//const uint64_t pipe = 0xE7E7E7E7E7LL;
struct PacketBase{
  int id;
  float hum;
  float temp;
} packet;



void setup() {
  Serial.begin(9600);
  printf_begin();
  radio.begin();
  radio.printDetails();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
}

void loop(void){
 //radio.printDetails();
 if (radio.available()){
   bool done = false;    
   while (!done){
     done = radio.read(&packet, sizeof(packet));        
    }

     Serial.print("id:");
     Serial.print(packet.id);
     Serial.print("\n");
     Serial.print("hum:");
     Serial.print(packet.hum);
     Serial.print("\n");
     Serial.print("temp:");
     Serial.print(packet.temp);
     Serial.print("\n");
    
  }
}
