#include <SPI.h>
#include "printf.h"
#include "nRF24L01.h"
#include "RF24.h"
#include <DHT11.h>
#define DHT11_PIN A5

DHT11 dht(DHT11_PIN);
RF24 radio(9, 10);
const uint64_t pipe = 0xE8E8F0F0E1LL;

int id = 1;

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
    if(id < 3)
      ++id;
    else id = 1;
    packet.id = id;
    int err = dht.read(packet.hum, packet.temp);
    if (err == 0){
      radio.write(&packet, sizeof(packet));
    }
  }
