#include <SPI.h>
#include "printf.h"
#include "nRF24L01.h"
#include "RF24.h"

#include "DHT.h"

#define DHTPIN 2 

#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);


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
    packet.hum = dht.readHumidity();
    packet.temp = dht.readTemperature();
   if (isnan(packet.hum) || isnan(packet.temp) ) {
    Serial.println("Failed to read from DHT sensor!");
    delay(200);
    return;
    
   } else{

    Serial.println(packet.hum);
    Serial.println(packet.temp);
    
    radio.write(&packet, sizeof(packet));
   }

   delay(500);
  }
