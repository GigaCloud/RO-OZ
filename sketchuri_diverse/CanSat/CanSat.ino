#include <Adafruit_BMP280.h>
#include <qbcan.h>
#include <Wire.h>
#include <SPI.h>
#include <TinyGPS.h>
#include <SoftwareSerial.h>
#include <GY80.h>

#include "printf.h"
#include "nRF24L01.h"
#include "RF24.h"

#define NODEID        2    
#define NETWORKID     100
#define GATEWAYID     1    
#define ENCRYPTKEY    "CanSatRoOzCanSat"

#define magneto_i2c 0x1E  

RFM69 radio69;
RF24 radio24(6, 5);
TinyGPS gps;
GY80 sensor = GY80(); 


const uint64_t pipe = 0xE8E8F0F0E1LL;

struct PacketBase{
  int id;
  float hum;
  float temp; 
} packet;

char payload[200];

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
  } else {
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


/* How to read the GY-80
           //get values from all sensors
    // print out values

  Serial.print("\n\nAcc:");                       
  Serial.print(val.a_x,3);
  Serial.print(' ');
  Serial.print(val.a_y,3);
  Serial.print(' ');
  Serial.print(val.a_z,3);
  Serial.print('\n');
  Serial.print("Gyro:");                      
  Serial.print(val.g_x,1);
  Serial.print(' ');
  Serial.print(val.g_y,1);
  Serial.print(' ');
  Serial.print(val.g_z,1);
  Serial.print('\n');
  Serial.print("P:");                         
  Serial.print(val.p,5);
  Serial.print('\n');
  Serial.print("T:");                         
  Serial.println(val.t,1);
  Serial.print("\n\n");
*/




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
    Serial.print("flat: ");Serial.print(flat);Serial.print("\n");
    Serial.print("flon: ");Serial.print(flon);Serial.print("\n");
  //Serial.print("flat: ");Serial.print(flat);Serial.print("\n");
//    alti  = 0; //TO-DO 
  }
}

bool readNRF(){
  if (radio24.available()){
   bool done = false;
   while (!done){
     done = radio24.read(&packet, sizeof(packet));        
   /*  Serial.print("id:");
     Serial.print(packet.id);
     Serial.print("\n");
     Serial.print("hum:");
     Serial.print(packet.hum);
     Serial.print("\n");
     Serial.print("temp:");
     Serial.print(packet.temp);
     Serial.print("\n");*/
    }
    return true;
  }
  return false;
}

unsigned long long timeGPS;
unsigned long long lastNRFTime;

void loop(){

    readGPS();
  
    if(readNRF()){
        getMagnetoReadings();
        printMagnetoReadings();
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
    }
    radio69.send(GATEWAYID, payload, sizeof(payload));   
}
