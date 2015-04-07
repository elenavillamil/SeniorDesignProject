#include <SPI.h>
#include <boards.h>
#include <ble_shield.h>#include <services.h>
#include <RBL_nRF8001.h>

//#include <SoftwareSerial.h>

//SoftwareSerial mySerial(0, 1); // RX, TX

// char* to send thorugh bluetooth
const int MAX_SIZE = 6;
unsigned char toSend[MAX_SIZE];
HardwareSerial com = Serial;

void setup() { 

  // Setting up bluetooth
  ble_set_name("BRC");
  ble_begin();

  Serial.begin (57600);
  
  // Set the data rate for the SoftwareSerial port
  //mySerial.begin(115200);
} 

void loop(){
  /*
  int incoming = Serial.available();
  while (incoming != 0)                 //While there is something to be read
  {
    int val = Serial.parseInt();             //Reads integers as integer rather than ASCI. Anything else returns 0
    val = val + 5;
    Serial.print(val);                  //Send the new val back to the Tx 
    incoming = Serial.available();    
  }
  */
  
  
  if (Serial.available())
  {
    toSend[0] = Serial.read();
    //delay(100);
    //Serial.println((int)toSend[0]);
    
  //////////////////////  BLE CODE  ////////////////////////////////
  
  // Convert int velocity to char*
   //String velocityString = String(velocity);
   //String positionString = String();
   //String stringToSend = velocityString + '-' + positionString + '\n';
   
   //Serial.println(stringToSend);
   
   // Code ot send the position to the iPad
   //for (int i = 0; i < positionString.length() && MAX_SIZE; i++)
   //{
     //toSend[i] = positionString[i];
   //}
   
     if (ble_connected())
     {
       ble_write_bytes(toSend, sizeof(char) * 1);
     }
  }
   
   ble_do_events();
   
}

