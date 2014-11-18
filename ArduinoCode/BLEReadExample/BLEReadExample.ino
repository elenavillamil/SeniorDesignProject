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
  
  // Usnig as fast as possible transmission, to keep the real time feedback
  Serial.begin(115200);
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
