#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <qbcan.h>
#include <Wire.h>
#include <SPI.h>
#include <TinyGPS.h>
#include <GY80.h>

#include "printf.h"
#include "nRF24L01.h"
#include "RF24.h"

#define NODEID        2    
#define NETWORKID     100
#define GATEWAYID     1    
#define ENCRYPTKEY    "CanSatRoOzCanSat"
#define FREQUENCY     433.60

#define magneto_i2c 0x1E  

RFM69 radio69;
RF24 radio24(5, 6);
TinyGPS gps;
GY80 sensor = GY80(); 

const uint64_t pipe = 0xE8E8F0F0E1LL;

struct PacketBase{
  int id;
  float hum;
  float temp; 
} packet;

char payload[30];

float flat, flon;

int x_magneto, y_magneto, z_magneto;                  
int xCal=0, yCal=0, zCal=0; 
int calValue = 1000;     

void setup(){
  Serial.begin(115200);
  Serial1.begin(9600);
  while(!Serial){;}
  
  Wire.begin();
  printf_begin();
  
  radio24.begin();
  radio24.printDetails();
  radio24.openReadingPipe(1,pipe);
  radio24.startListening();

  radio69.initialize(FREQUENCY,NODEID,NETWORKID);
  radio69.setHighPower(); 
  radio69.encrypt(ENCRYPTKEY);

  magSetting(0x00, B01101000);
  magSetting(0x01, B01100000);
  calibrateMag();
  sensor.begin();
}

///Magnetometer

void magSetting(byte regLoc, byte setting){
  Wire.beginTransmission(magneto_i2c);
  Wire.write(regLoc); 
  Wire.write(setting);
  Wire.endTransmission();
  delay(10);
}

void getMagnetoReadings(){
  magSetting(0x02, 0x01);       
  Wire.requestFrom(magneto_i2c, 6);
  if (Wire.available()>5){
    x_magneto = readValue()- xCal;
    z_magneto = readValue()- zCal;
    y_magneto = readValue()- yCal;    
  } 
  else {
    Serial.println("****Magneto Error: Less than 6 bytes available for reading*****");
  }
}


int readValue(){
  int val = Wire.read()<<8; 
  val |= Wire.read();
  return val;
}


void printMagnetoReadings(){
  Serial.print("x: ");
  Serial.print(x_magneto);
  Serial.print("  y: ");
  Serial.print(y_magneto);
  Serial.print("  z: ");
  Serial.println(z_magneto);
}

void calibrateMag(){
  getMagnetoReadings();
  xCal = x_magneto - calValue;
  yCal = y_magneto - calValue;
  zCal = z_magneto - calValue;
}

///GPS

void readGPS(){
  bool newData = false;

  while (Serial1.available()){
    char c = Serial1.read();
    if (gps.encode(c)){
      newData = true;
      break;
    }
  }

  if (newData){
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    Serial.print("flat: ");
    Serial.print(flat);
    Serial.print("\n");
    Serial.print("flon: ");
    Serial.print(flon);
    Serial.print("\n");
    //Serial.print("flat: ");Serial.print(flat);Serial.print("\n");
    //    alti  = 0; //TO-DO 
  }
}

//NRF
bool readNRF(){
  if (radio24.available()){
    bool done = false;
    while (!done){
      done = radio24.read(&packet, sizeof(packet));        
    }
    return true;
  }
  return false;
}

//RF69 encode packet for smaller size
void encode(int16_t *in, char *encoded, int numbers){
    int poz_in = 0;
    int poz_encoded = 0;
    int16_t x;
    while(poz_in < numbers){
      unsigned char b1, b2;
      x = in[poz_in];
      b1 = x >> 8;
      b2 = (int16_t)(x<<8)>>8;
      encoded[poz_encoded] = b1;
      encoded[poz_encoded + 1] = b2;
      poz_encoded += 2;
      ++poz_in;
    }
}

unsigned long long timeGPS;
unsigned long long lastNRFTime;
int v[17];

void loop(){

/*  readGPS();

  if(readNRF()){
    getMagnetoReadings();
    //printMagnetoReadings();
    GY80_scaled val = sensor.read_scaled();
    sprintf(payload,
    "\nid: %d \nhum: %d \ntemp: %d \nlati: %i \nlongi: %i \na_x: %i \na_y: %i \na_z: %i \ng_x: %i \ng_y: %i \ng_z: %i \nP: %i \nT: %i", 
    (int)packet.id, 
    (int)packet.hum, 
    (int)packet.temp, 
    (int)(flat*100.0),
    (int)(flon*100.0),
    (int)(val.a_x*100.0),
    (int)(val.a_y*100.0),
    (int)(val.a_z*100.0),
    (int)(val.g_x*10.0),
    (int)(val.g_y*10.0),
    (int)(val.g_z*10.0),
    (int)(val.p*10000.0),
    (int)(val.t*10.0)
      );

    Serial.print(payload); 
    lastNRFTime = millis();
  }

  if(millis() - lastNRFTime > 1000){

    //radio24.printDetails();
    
    getMagnetoReadings();
    printMagnetoReadings();
    GY80_scaled val = sensor.read_scaled();
    sprintf(payload,
    "\nid: %d \nlati: %i \nlongi: %i \na_x: %i \na_y: %i \na_z: %i \ng_x: %i \ng_y: %i \ng_z: %i \nP: %i \nT: %i", 
    -1,
    (int)(flat*100.0),
    (int)(flon*100.0),
    (int)(val.a_x*100.0),
    (int)(val.a_y*100.0),
    (int)(val.a_z*100.0),
    (int)(val.g_x*10.0),
    (int)(val.g_y*10.0),
    (int)(val.g_z*10.0),
    (int)(val.p*10000.0),
    (int)(val.t*10.0)
      );

    Serial.println(payload);
  }*/


   readGPS();
   getMagnetoReadings();
   GY80_scaled val = sensor.read_scaled()
   
   if(readNRF()){
      v[0] = packet.id;
      v[1] = packet.hum;
      v[2] = packet.temp;
      lastNRFTime = millis();
   }
   
   if(millis() - lastNRFTime > 1000){
      v[0] = -1;
      v[1] =  0;
      v[2] =  0;
   }
   
   v[3] = val.p;
   v[4] = val.t;
   
   v[5] = flat;
   v[6] = flon;
   v[7] = alti;

   v[8]  = val.a_x; //ax
   v[9]  = val.a_y; //ay
   v[10] = val.a_z; //az

   v[11] = val.g_x; //gx
   v[12] = val.g_y; //gy
   v[13] = val.g_z;//gz

   v[14] = x_magneto; //mx
   v[15] = y_magneto; //my
   v[16] = z_magneto; //mz

   for(int i = 0; i<17; ++i)
        Serial.println(v[i]);

   encode(v, payload, 17); 
    
   radio69.send(GATEWAYID, payload, sizeof(payload));   
}

