#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
char msg;
RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;

struct packet{
  unsigned int nIncercare;
  unsigned long tInceput;
  unsigned long tActual;
  unsigned long tProcesare;
  unsigned long tAnteriorScriere;
  
} actual_packet;


void setup(void){
 Serial.begin(57600);
 radio.begin();
 radio.printDetails();
 radio.openReadingPipe(1,pipe);
 radio.startListening();
}
void loop(void){
 if (radio.available()){
   bool done = false;    
   while (!done){
     done = radio.read(&actual_packet, sizeof(actual_packet));      
   if(actual_packet.nIncercare){
       Serial.print(actual_packet.nIncercare);
       Serial.print("\t");
       Serial.print(actual_packet.tInceput);
       Serial.print("\t");
       Serial.print(actual_packet.tActual);
       Serial.print("\t");
       Serial.print(actual_packet.tProcesare);
       Serial.print("\t");
       Serial.print(actual_packet.tAnteriorScriere);
       Serial.print("\n");
   }
  }
 }
//   else{Serial.println("No radio available");}
 }

