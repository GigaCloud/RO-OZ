/* 
    qbcan flight unit example.

    This sketch reads temperature and pressure data on the flight unit and sends it to the Ground station
*/

//Include the required libraries
#include <qbcan.h>
#include <Wire.h>
#include <SPI.h>

//Pressure sensor object
BMP180 bmp;

//Radio Parameters
#define NODEID        2    //unique for each node on same network
#define NETWORKID     100  //the same on all nodes that talk to each other
#define GATEWAYID     1    //Receiving node
#define ENCRYPTKEY    "CanSatRoOzCanSat" //exactly the same 16 characters/bytes on all nodes!


RFM69 radio;

char payload[50];
double T,P;

void setup()
{
  //Initialize serial connection for debugging
  Serial.begin(9600);
  Serial.println("REBOOT");

  // Initialize pressure sensor.
  if (bmp.begin())
    Serial.println("BMP180 init success");
  else
  {
    //In case of error let user know of the problem
    Serial.println("BMP180 init fail (disconnected?)\n\n");
 //   while(1); // Pause forever.
  }

  //Initialize radio
  radio.initialize(FREQUENCY,NODEID,NETWORKID);
  radio.setHighPower(); //To use the high power capabilities of the RFM69HW
  radio.encrypt(ENCRYPTKEY);
  Serial.println("Transmitting at 433 Mhz");

}

void loop()
{
  
  // Get a new pressure reading:
  bmp.getData(T,P);

  //Display data
  Serial.print("Absolute pressure: ");
  Serial.print(P,2);
  Serial.println(" mb.");
  Serial.print("Temperature: ");
  Serial.print(T,2);
  Serial.println(" deg C.");

  sprintf(payload,"T: %d, P: %d", (int)T, (int)P);

  //Send Data
  radio.send(GATEWAYID, payload, sizeof(payload));
  Serial.println("Send complete");
  //delay(500);
}
