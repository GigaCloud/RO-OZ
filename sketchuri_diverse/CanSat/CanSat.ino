#include <qbcan.h>
#include <Wire.h>
#include <SPI.h>
#include <TinyGPS.h>
#include <SoftwareSerial.h>
#include "printf.h"
#include "nRF24L01.h"
#include "RF24.h"


#define NODEID        2    
#define NETWORKID     100  
#define GATEWAYID     1    
#define ENCRYPTKEY    "CanSatRoOzCanSat"
#define lati          0
#define longi         1
#define alti          2

RFM69 radio69;
RF24 radio24(6, 5);
TinyGPS gps;


const uint64_t pipe = 0xE8E8F0F0E1LL;

struct PacketBase{
  int id;
  float hum;
  float temp; 
} packet;

char payload[50];
float GPS[3];


void setup(){

  Serial.begin(115200);
  Serial1.begin(9600);

  printf_begin();
  radio24.begin();
  radio24.printDetails();
  radio24.openReadingPipe(1,pipe);
  radio24.startListening();
  
  radio69.initialize(FREQUENCY,NODEID,NETWORKID);
  radio69.setHighPower(); 
  radio69.encrypt(ENCRYPTKEY);
 

}

void readGPS(){
  bool newData = false;

  while (Serial1.available()){
     char c = Serial1.read();
     if (gps.encode(c))
     newData = true;
  }

  if (newData){
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);

    GPS[lati]  = flat;
    GPS[longi] = flon;
    GPS[alti]  = 0; //TO-DO 
    
  }
}

void readNRF(){
  if (radio24.available()){
   bool done = false;    
   while (!done){
     done = radio24.read(&packet, sizeof(packet));        
     Serial.print("id:");
     Serial.print(packet.id);
     Serial.print("\n");
     Serial.print("hum:");
     Serial.print(packet.hum);
     Serial.print("\n");
     Serial.print("temp:");
     Serial.print(packet.temp);
     Serial.print("\n");
      
     sprintf(payload,"id: %d \n hum: %d \n temp: %d \n", (int)packet.id, (int)packet.hum, (int)packet.temp);

     radio69.send(GATEWAYID, payload, sizeof(payload));  
    }
  }
}

unsigned long long gpsTime;

void loop(){

  readGPS();
  if(millis() - gpsTime > 1000){
     if(GPS[lati] != 0.0) 
       Serial.println(GPS[lati]);
       gpsTime = millis();
  }
    
  readNRF();


}
