/* 
    qbcan ground station example.

    This sketch receives data from other qbcan that transmit messages and also prints the ground station's tempearture and pressure readings.
*/

//Include the required libraries
#include <qbcan.h>
#include <Wire.h>
#include <SPI.h>

//Pressure sensor object

//Radio Parameters
#define NODEID        1    //unique for each node on same network
#define NETWORKID     100  //the same on all nodes that talk to each other
#define ENCRYPTKEY    "CanSatRoOzCanSat" //exactly the same 16 characters/bytes on all nodes!


//Radio object
RFM69 radio;
bool promiscuousMode = true; //set to 'true' to sniff all packets on the same network

void setup()
{
  //Initialize serial connection for debugging
  Serial.begin(9600);
  Serial.println("REBOOT");


  delay(1000);

  //Initialize radio
  radio.initialize(FREQUENCY,NODEID,NETWORKID);
  radio.setFrequency(433600000);
  radio.setHighPower();
  
  radio.encrypt(ENCRYPTKEY);
  radio.promiscuous(promiscuousMode);
  Serial.println("Listening at 433 Mhz");

}


void decode(char *encoded, int16_t *decoded,  int decoded_size){
    int poz_encoded = 0;
    int poz_decoded = 0;
    int16_t x;
    while(poz_decoded < decoded_size){
      unsigned char e1, e2;
      e1 =  encoded[poz_encoded];
      e2 =  encoded[poz_encoded + 1];
      int16_t e2int = 0;
      x =   (int16_t)(e1<<8)|e2;
    /*  bitset<8> be1(e1);
      bitset<8> be2(e2);
      bitset<16> bx(x);*/
      decoded[poz_decoded] = x;
      ++poz_decoded;
      poz_encoded += 2;
      //cout<<x<<' '<<bx<<' '<<be1<<' '<<be2<<'\n';
    }
}

int cifre(unsigned long x){
    int c = 0;
    while(x > 0){
      x/=10;
      ++c;
    }
    
    return c;
}

void loop()
{
  int v[19];
  if (radio.receiveDone())
  {
     decode(radio.DATA, v, 19); 
     Serial.println("###RO-OZ###");
     Serial.print("id: "); Serial.println(v[0]);
     Serial.print("hum: "); Serial.println(v[1]);
     Serial.print("temp: "); Serial.println(v[2]);
     
     Serial.print("P: "); Serial.println(v[3]);
     Serial.print("T: "); Serial.println(v[4]);

     unsigned long lat = v[5];
     unsigned long lon = v[6];
     unsigned long lat_precision = v[17];
     unsigned long lon_precision = v[18];
     
     Serial.print("lat: "); Serial.print(lat);
     for(int i=0; i < 4 - cifre(lat_precision); ++i){
          Serial.print('0');
        } 
     Serial.println(lat_precision);

     Serial.print("lon: "); Serial.print(lon);
     for(int i=0; i < 4 - cifre(lon_precision); ++i){
          Serial.print('0');
        } 
     Serial.println(lon_precision);
     
   /*  
     Serial.print("lat: "); Serial.println(v[5]);
     Serial.print("lon: "); Serial.println(v[6]);
*/   
     Serial.print("alt: "); Serial.println(v[7]);
     
     Serial.print("a_x: "); Serial.println(v[8]);
     Serial.print("a_y: "); Serial.println(v[9]);
     Serial.print("a_z: "); Serial.println(v[10]);

     Serial.print("g_x: "); Serial.println(v[11]);
     Serial.print("g_y: "); Serial.println(v[12]);
     Serial.print("g_z: "); Serial.println(v[13]);

     Serial.print("m_x: "); Serial.println(v[14]);
     Serial.print("m_y: "); Serial.println(v[15]);
     Serial.print("m_z: "); Serial.println(v[16]);
     Serial.println();
  }
}



