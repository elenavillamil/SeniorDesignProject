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

int count = 0;

void setup() { 

  // Setting up bluetooth
  ble_set_name("BRC");
  ble_begin();

  Serial.begin (115200);
  
  // Set the data rate for the SoftwareSerial port
  //mySerial.begin(115200);
} 

void loop(){
    
  if (Serial.available())
  {
    toSend[0] = Serial.read();
    //delay(100);
    Serial.println((int)toSend[0]);
   
    count += 1;
   
    if (count == 5)
    {
      count = 0;
     
      if (ble_connected())
      {
        ble_write_bytes(toSend, sizeof(char) * 1);
      }
    }
     
  }

  //while (fmod(millis(), 50)!=0);
   
  ble_do_events();
   
}

