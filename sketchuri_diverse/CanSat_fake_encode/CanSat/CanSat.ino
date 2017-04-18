#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <qbcan.h>
#include <Wire.h>
#include <SPI.h>
#include <TinyGPS.h>
#include <GY80.h>

#define NODEID        2    
#define NETWORKID     100
#define GATEWAYID     1    
#define ENCRYPTKEY    "CanSatRoOzCanSat"

#define magneto_i2c 0x1E  

RFM69 radio69;
TinyGPS gps;
GY80 sensor = GY80(); 


const uint64_t pipe = 0xE8E8F0F0E1LL;

struct PacketBase{
  int id;
  float hum;
  float temp; 
} 
packet;

char payload[40];

float flat, flon;


int x_magneto, y_magneto, z_magneto;                  
int xCal=0, yCal=0, zCal=0; 
int calValue = 1000;     


void setup(){
  Serial.begin(9600);

  radio69.initialize(FREQUENCY,NODEID,NETWORKID);
  radio69.setFrequency(433600000);
  radio69.setHighPower(); 
  radio69.encrypt(ENCRYPTKEY);

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

unsigned long long timeGPS;
unsigned long long lastNRFTime;

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
    /*    bitset<16> bx(x);
        bitset<8> bb1(b1);
        bitset<8> bb2(b2);
        cout<<x<<' '<<bx<<' '<<bb1<<' '<<bb2<<'\n';*/
        poz_encoded += 2;
        ++poz_in;
      }
  }




void loop(){
   int v[17];
   packet.id = 2;
   packet.hum = 200;
   packet.temp = 5;
   
   v[0] = packet.id;
   v[1] = packet.hum;
   v[2] = packet.temp;

   v[3] = 1; //P
   v[4] = 2; //T

  flat = 3;
  flon = 4;

   v[5] = flat;
   v[6] = flon;
   v[7] = 5; //alti

   v[8] = 6; //ax
   v[9] = 7; //ay
   v[10] = 8; //az

   v[11] = 9; //gx
   v[12] = 10; //gy
   v[13] = 3356;//gz

   v[14] = 11; //mx
   v[15] = -120; //my
   v[16] = -4500; //mz


  encode(v, payload, 17);
  radio69.send(GATEWAYID, payload, sizeof(payload));   
}

