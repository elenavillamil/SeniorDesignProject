// messing with git

#include <SPI.h>
#include <boards.h>
#include <ble_shield.h>
#include <services.h>
#include <RBL_nRF8001.h>

const int MAX_SIZE = 4;
int pulses = 0;
int A_SIG = 0;
int B_SIG = 1;

unsigned char str[MAX_SIZE];

void setup() {
  attachInterrupt(1, A_RISE, RISING);
  //attachInterrupt(0, B_RISE, RISING);
  
  // Setting up bluetooth
  ble_set_name("BRC");
  ble_begin();
  
  Serial.begin(57600);
}

void loop()
{
  
  unsigned char str[MAX_SIZE];
  String num_string = String(pulses);
  
  for (int i = 0; i < num_string.length() && MAX_SIZE; i++)
      str[i] = num_string[i];
  
  if (ble_connected())
  {
    //Serial.println(pulses);
    ble_write_bytes(str, num_string.length());
  }

  delay(20);
  ble_do_events();
}

void A_RISE() {
  detachInterrupt(1);
  A_SIG = 1;
  if (pulses > 150)
  {
    pulses = 0;
  }
  // Direction detection
  //if (B_SIG = 0)
  //{
    pulses++;
  //}
  //else
  //{
    //pulses--;
  //}
  
  //Serial.println(pulses);
  
  // Once A it is a 5v, the only option is for it to fall
  // This way if we miss an interrupt we dont wrongly change direction
  attachInterrupt(1, A_FALL, FALLING);
}

void A_FALL()
{
  detachInterrupt(1);
  A_SIG = 0;
  
  //if(B_SIG == 1)
  //{
     pulses++;
  //}
  //else
  //{
    //pulses--;
  //} 
  
  Serial.println(pulses);
  attachInterrupt(1, A_RISE, RISING);
}
/*
void B_RISE()
{
  detachInterrup(0);
  B_SIG = 1;
  
  if (A_SIG == 1)
  {
    pulses++;
  }
  else
  {
    pulses--;
  }
  
  Serial.println(pulses);
  attachInterrupt(0, B_FALL, FALLING);
}

void B_FALL()
{
  dettachInterrupt(0);
  B_SIG = 0;
  
  if (A_SIG == 0)
  {
    pulses++;
  }
  else
  {
    pulses--;
  }
  
  Serial.println(pulses);
  attachInterrupt(0, B_RISE, RISING);
}
*/
