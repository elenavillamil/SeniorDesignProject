#include <RBL_nRF8001.h>
#include <boards.h>
#include <ble_shield.h>
#include <SPI.h>
#include <services.h>

#define PIN 7
#define MAX_SIZE 14

void setup()
{
  ble_set_name("BRC");
  
  // Init. and start BLE library.
  ble_begin();
  
  Serial.begin(9600);
}

void loop()
{
  int distance_received;

  if (ble_available())
  {  
    //distance_received = ble_read();
    
    Serial.write(ble_read());
  }
  
  ble_do_events(); 
}
