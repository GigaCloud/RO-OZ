#include <SPI.h>
#include "printf.h"
#include "nRF24L01.h"
#include "RF24.h"
#include <DHT11.h>
#define DHT11_PIN A5

DHT11 dht(DHT11_PIN);
RF24 radio(9, 10);
const uint64_t pipe = 0xE8E8F0F0E1LL;

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
    packet.id = 2;
    int err = dht.read(packet.hum, packet.temp);
    if (err == 0){
      radio.write(&packet, sizeof(packet));
 //     delay(10);
    }
  }
