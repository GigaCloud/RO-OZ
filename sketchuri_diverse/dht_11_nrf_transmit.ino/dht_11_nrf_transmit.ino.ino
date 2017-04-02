#include <SPI.h>
#include "printf.h"
#include "nRF24L01.h"
#include "RF24.h"


RF24 radio(6, 5);

const uint64_t pipe = 0xE8E8F0F0E1LL;

int humi;

struct PacketBase{
  int id;
  float hum;
  float temp; 
} packet;



void setup(void) {
  Serial.begin(57600);
  printf_begin();
  radio.begin();
  radio.printDetails();
  radio.openWritingPipe(pipe);
}

void loop() {
    packet.id = 1;
    packet.hum = 2;
    packet.temp = 3;
    radio.write(&packet, sizeof(packet));
}

