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


//byte ackCount=0;
//uint32_t packetCount = 0;
void loop()
{

  if (radio.receiveDone())
  {
    
    for (byte i = 0; i < radio.DATALEN; i++)
      Serial.print((char)radio.DATA[i]);
  
    Serial.println();
  }

}



