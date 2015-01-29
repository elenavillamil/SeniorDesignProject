#include <ble_shield.h>
#include <boards.h>
#include <RBL_nRF8001.h>
#include <services.h>
#include <Servo.h>
#include <SPI.h>

#define SERVO_PIN 5
#define MAX_SIZE 10

Servo servo;
int pulses = 0;
int A_SIG = 0;
String data_to_send;

void setup()
{
  // Attaching interrupt to pin 3, where channel A is connected.
  attachInterrupt(1, A_RISE, RISING);
  
  // Setting the bluetooth name to BRC (basketball robot controller.
  ble_set_name("ev9");
  
  // Init and start BLE library.
  ble_begin();
  
  servo.attach(SERVO_PIN);
  servo.write(90);
    
  // Using as fast as possible transmission, to keep the real time feedback
  Serial.begin(57600);
}


int height_received = 4;
int old_height = 4;
int counter = 0;

void loop()
{
  
  unsigned char chars_to_send[MAX_SIZE];
  memset(chars_to_send, 0, MAX_SIZE * sizeof(char));

  if (ble_available())
  {
    // Getting the new information wrote from the iOS app.
    height_received = ble_read();
    if (old_height != height_received && height_received <=180)
    {
      //counter++;
      //if (counter > 180)
        //counter = 0;
        
      servo.write(height_received);
      
      old_height = height_received;
      
      //Serial.write(counter);
    }  
    Serial.print(height_received);
  }
 
  if(ble_connected())
  {
    data_to_send = String(pulses);
    for (int i = 0; i < data_to_send.length() && MAX_SIZE-1; i++)
      chars_to_send[i] = data_to_send[i];
      
    ble_write_bytes(chars_to_send, data_to_send.length());  
  }
  
  ble_do_events();
  
  delay(10);
}

void A_RISE() {
  detachInterrupt(1);
  A_SIG = 1;
  pulses++;
  
  if (pulses > 50)
    pulses = 0;
  
  //Serial.println(pulses);
  
  // Once A is high, the only option is for it to fall.
  // This way if we miss an interrupt we dont wrongly change direction or miss an extra pulse
  attachInterrupt(1, A_FALL, FALLING);
}


void A_FALL()
{
  detachInterrupt(1);
  A_SIG = 0;
  pulses++;

  if (pulses > 50)
    pulses = 0;
  //Serial.println(pulses);
  attachInterrupt(1, A_RISE, RISING);
}
