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
#define FREQUENCY     433.60
//Radio object
RFM69 radio;
bool promiscuousMode = false; //set to 'true' to sniff all packets on the same network

void setup()
{
  //Initialize serial connection for debugging
  Serial.begin(9600);
  Serial.println("REBOOT");


  //Delay to give time to the radio to power up
  delay(1000);

  //Initialize radio
  radio.initialize(FREQUENCY,NODEID,NETWORKID);
  radio.setHighPower(); //Use the high power capabilities of the RFM69HW
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


void loop()
{
  int v[17];
  if (radio.receiveDone())
  {

     decode(radio.DATA, v, 17); 
     Serial.println("#########################");
     Serial.print("id: "); Serial.println(v[0]);
     Serial.print("hum: "); Serial.println(v[1]);
     Serial.print("temp: "); Serial.println(v[2]);
     
     Serial.print("P: "); Serial.println(v[3]);
     Serial.print("T: "); Serial.println(v[4]);
     
     Serial.print("lat: "); Serial.println(v[5]);
     Serial.print("lon: "); Serial.println(v[6]);
     Serial.print("alt: "); Serial.println(v[7]);

     Serial.print("ax: "); Serial.println(v[8]);
     Serial.print("ay: "); Serial.println(v[9]);
     Serial.print("az: "); Serial.println(v[10]);

     Serial.print("gx: "); Serial.println(v[11]);
     Serial.print("gy: "); Serial.println(v[12]);
     Serial.print("gz: "); Serial.println(v[13]);

     Serial.print("mx: "); Serial.println(v[14]);
     Serial.print("my: "); Serial.println(v[15]);
     Serial.print("mz: "); Serial.println(v[16]);
  }

}



