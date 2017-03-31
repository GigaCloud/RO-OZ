#include <SPI.h>
#include "printf.h"
#include "nRF24L01.h"
#include "RF24.h"
#include <DHT11.h>
#define DHT11_PIN A5

DHT11 dht(DHT11_PIN);
RF24 radio(9, 10);

const uint64_t pipe = 0xE8E8F0F0E1LL;

float humi,temp;

void setup(void) {
  Serial.begin(57600);
  printf_begin();
  radio.begin();
  radio.printDetails();
  radio.openWritingPipe(pipe);
}

void loop() {
    int err = dht.read(humi, temp);
    if (err == 0){
      Serial.print(humi);
      Serial.print(" "); 
      Serial.print(temp); 
      Serial.print("\n");
      radio.write(&humi, sizeof(humi));
      delay(200);
    }
  }
