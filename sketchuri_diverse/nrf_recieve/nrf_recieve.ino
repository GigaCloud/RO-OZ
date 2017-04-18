#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
char msg;
RF24 radio(5,6);
const uint64_t pipe = 0xE8E8F0F0E1LL;

struct PacketBase{
  int id;
  float hum;
  float temp; 
} packet;



void setup(void){
 Serial.begin(57600);
 radio.begin();
 printf_begin();
 radio.printDetails();
 radio.openReadingPipe(1,pipe);
 radio.startListening();
}
void loop(void){
 if (radio.available()){
   bool done = false;    
   while (!done){
     done = radio.read(&packet, sizeof(packet));      
       Serial.print("id: ");
       Serial.print(packet.id);
       Serial.print("\ntemp: ");
       Serial.print(packet.temp);
       Serial.print("\nhum: ");
       Serial.print(packet.hum);
       Serial.print("\n");
  }
 }
   //else{Serial.println("No radio available");}

   //radio.printDetails();
 }

