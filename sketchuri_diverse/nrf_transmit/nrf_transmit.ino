#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
char msg;

struct packet{
  unsigned int nIncercare;
  unsigned long tInceput;
  unsigned long tActual;
  unsigned long tProcesare;
  unsigned long tAnteriorScriere;
  
} actual_packet;

int nIncercare = 1;
unsigned long tInceput;
unsigned long t3;
RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
unsigned long timpActual, timpAnterior;

void setup(void){
 Serial.begin(57600);
 radio.begin();
 radio.printDetails();
 radio.openWritingPipe(pipe);
 tInceput = micros();
}

void loop(void){
 timpAnterior = micros();
 
 actual_packet.nIncercare = nIncercare;
 actual_packet.tInceput = tInceput;
 actual_packet.tActual  = micros();
 actual_packet.tProcesare =  micros() - timpAnterior; 
 actual_packet.tAnteriorScriere = t3;

 t3 = micros();
 nIncercare += 1;
 radio.write(&actual_packet, sizeof(actual_packet));
 t3 = micros() - t3;
}
