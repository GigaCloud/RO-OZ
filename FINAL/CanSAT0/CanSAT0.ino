#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <qbcan.h>
#include <Wire.h>
#include <SPI.h>
#include <TinyGPS.h>
#include <GY80.h>
//NRF
#include "printf.h"
#include "nRF24L01.h"
#include "RF24.h"
//RF69
#define NODEID        1    
#define NETWORKID     42
#define GATEWAYID     1
#define ENCRYPTKEY    "CanSatRoOzCanSat" //FFF creativ
#define Buzzer        4

//Chestii magneto
#define magneto_i2c 0x1E 

int x_magneto, y_magneto, z_magneto;
int xCal = 0, yCal = 0, zCal = 0;
int calValue = 1000;

TinyGPS gps; //Cam evident

RFM69 radio69; //CanSat -> Ground
char payload[50]; //50char chiar daca tre' numa' 38

RF24 radio24(5, 6); //Sonde -> CanSat
const uint64_t pipe = 0xE8E8F0F0E1LL; //hex reg magic

struct PacketBase //floaturile is degeaba acolo
{                 //dar n-am sa reprogramez sondele pt asta
        int id;
        float hum;
        float temp;
}
packet;

GY80 sensor = GY80(); //10DOF fara magneto

int sec;
unsigned int init_pressure; //o prima masura a press
bool afterAscend; //daca am inceput sa urcam

void setup() 
{
        pinMode(Buzzer, OUTPUT);

        Serial.begin(9600);
        Serial1.begin(9600); //GPS
        delay(1000);

        printf_begin();

        radio24.begin();
        radio24.printDetails();
        radio24.openReadingPipe(1, pipe);
        radio24.startListening();

        radio69.initialize(FREQUENCY, NODEID, NETWORKID);
        radio69.setFrequency(433600000); //433.6 MHz
        radio69.setHighPower(); //over 9000, kek
        radio69.encrypt(ENCRYPTKEY); //doamne fereste sa se fure datele

        Wire.begin();
        magSetting(0x00, B01101000);
        magSetting(0x01, B01100000);
        calibrateMag();

        sensor.begin(); //10 DOF

        GY80_scaled val = sensor.read_scaled();
        init_pressure = val.p * 1000;

}

void magSetting(byte regLoc, byte setting) 
{
        Wire.beginTransmission(magneto_i2c);
        Wire.write(regLoc);
        Wire.write(setting);
        Wire.endTransmission();
        delay(10);
}

void getMagnetoReadings() 
{
        magSetting(0x02, 0x01);
        Wire.requestFrom(magneto_i2c, 6);
        if (Wire.available() > 5) {
                x_magneto = readValue() - xCal;
                z_magneto = readValue() - zCal;
                y_magneto = readValue() - yCal;
        } else {
                Serial.println("****Magneto Error: Less than 6 bytes available for reading*****");
        }
}

int readValue() 
{
        int val = Wire.read() << 8;
        val |= Wire.read();
        return val;
}

void printMagnetoReadings() 
{
        Serial.print("x: ");
        Serial.print(x_magneto);
        Serial.print("  y: ");
        Serial.print(y_magneto);
        Serial.print("  z: ");
        Serial.println(z_magneto);
}

void calibrateMag() 
{
        getMagnetoReadings();
        xCal = x_magneto - calValue;
        yCal = y_magneto - calValue;
        zCal = z_magneto - calValue;
}

//GPS vars
float flat, flon, alti;
unsigned long long lat_long;
unsigned long long lon_long;
unsigned int lat_prec;
unsigned int lon_prec;
unsigned int lat;
unsigned int lon;

void readGPS() 
{
        bool newData = false;

        for (unsigned long start = millis(); millis() - start < 200;) {
                while (Serial1.available()) {
                        char c = Serial1.read();
                        if (gps.encode(c)) {
                                newData = true;
                                break;
                        }
                }
        }

        if (newData) {
                unsigned long age;
                gps.f_get_position( & flat, & flon, & age);
                alti = gps.f_altitude();
                Serial.print("flat: ");
                Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
                Serial.print("\n");
                Serial.print("flon: ");
                Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
                Serial.print("\n");
                Serial.print("alti: ");
                Serial.print(alti);
                Serial.print("\n");

                lat_long = flat * 1000000;
                lon_long = flon * 1000000;
                lat_prec = lat_long % 10000;
                lon_prec = lon_long % 10000;
                lat = lat_long / 10000;
                lon = lon_long / 10000;

                //Serial.print("flat: ");Serial.print(flat);Serial.print("\n");
                //    alti  = 0; //TO-DO 
        }
}

bool readNRF() 
{
        if (radio24.available()) {
                bool done = false;
                while (!done) {
                        done = radio24.read( & packet, sizeof(packet));

                }
                Serial.println("Citit NRF");
                return true;
        }
        return false;
}

void encode(int16_t * in , char * encoded, int numbers) 
{       //Ceva functie simpla de care-s oleaca mandru ca reduce packet size
        int poz_in = 0;
        int poz_encoded = 0;
        int16_t x;
        while (poz_in < numbers) { //separa fiecare int_16 din vec
                unsigned char b1, b2; //in doua charuri, in alt vector
                x = in [poz_in];
                b1 = x >> 8;
                b2 = (int16_t)(x << 8) >> 8;
                encoded[poz_encoded] = b1;
                encoded[poz_encoded + 1] = b2;
                poz_encoded += 2;
                ++poz_in;
        }
}

void buzz()//SOS beep
{
        digitalWrite(Buzzer, HIGH);
        delay(100);
        digitalWrite(Buzzer, LOW);
        delay(100);
        digitalWrite(Buzzer, HIGH);
        delay(100);
        digitalWrite(Buzzer, LOW);
        delay(100);
        digitalWrite(Buzzer, HIGH);
        delay(100);
        digitalWrite(Buzzer, LOW);
        delay(300);
        digitalWrite(Buzzer, HIGH);
        delay(300);
        digitalWrite(Buzzer, LOW);
        delay(100);
        digitalWrite(Buzzer, HIGH);
        delay(300);
        digitalWrite(Buzzer, LOW);
        delay(100);
        digitalWrite(Buzzer, HIGH);
        delay(300);
        digitalWrite(Buzzer, LOW);
        delay(300);
        digitalWrite(Buzzer, HIGH);
        delay(100);
        digitalWrite(Buzzer, LOW);
        delay(100);
        digitalWrite(Buzzer, HIGH);
        delay(100);
        digitalWrite(Buzzer, LOW);
        delay(100);
        digitalWrite(Buzzer, HIGH);
        delay(100);
        digitalWrite(Buzzer, LOW);

}

void nobuzz() //STFU
{ 
        digitalWrite(Buzzer, LOW);
}

int lastP = 0; //var buzzer
int lastTimeP;
int deltaP = 100;
bool buzz_flip;

void loop() //impachetare in v, encoding, chestii trestii
{
        sec = millis() / 1000;
        Serial.println(sec);
        int v[19]; //payload fara encode
        if (readNRF()) {
                v[0] = packet.id;
                v[1] = packet.hum;
                v[2] = packet.temp;
        } else {
                v[0] = -1;
        }
        readGPS();
        
        v[5] = lat;
        v[6] = lon;
        v[7] = alti;
        v[17] = lat_prec;
        v[18] = lon_prec;

        GY80_scaled val = sensor.read_scaled(); //10DOF
        v[3] = val.p * 1000;
        v[4] = val.t * 1000;

        v[8] = (val.a_x) * 1000;
        v[9] = (val.a_y) * 1000;
        v[10] = (val.a_z) * 1000;

        v[11] = (val.g_x) * 1000;
        v[12] = (val.g_y) * 1000;
        v[13] = (val.g_z) * 1000;

        getMagnetoReadings();
        v[14] = x_magneto;
        v[15] = y_magneto;
        v[16] = z_magneto;

        encode(v, payload, 19); //int_16 -> unsigned char

        if (sec - lastTimeP > 30) {
                /*Am inceput sa urc, sper*/

                int deltaInit = v[3] - init_pressure;
                
                if (deltaInit < 0) deltaInit *= -1;

                if (deltaInit > 10) { //dupa vreo +85m
                        afterAscend = true;
                }

                Serial.print("deltaInit: ");Serial.println(deltaInit);

                /*Presiune stabilizata*/

                lastTimeP = sec;
                deltaP = v[3] - lastP;
                lastP = v[3];
                if (deltaP < 0) deltaP *= -1;

                if (deltaP < 3 && afterAscend) {
                        buzz();
                }

        }

        radio69.send(GATEWAYID, payload, 50);

        delay(200); //merge bine asa, mare sincronizare, csz
}
