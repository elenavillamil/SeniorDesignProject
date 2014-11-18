#include <ble_shield.h>
#include <boards.h>
#include <RBL_nRF8001.h>
#include <services.h>
#include <Servo.h>
#include <SPI.h>

#define SERVO_PIN 9

Servo servo;

void setup()
{
  // Setting the bluetooth name to BRC (basketball robot controller.
  ble_set_name("BRC");
  
  // Init and start BLE library.
  ble_begin();
  
  servo.attach(SERVO_PIN);
  
  // Using as fast as possible transmission, to keep the real time feedback
  Serial.begin(115200);
}

void loop()
{
  int height_received;
  
  if (ble_available())
  {
    // Getting the new information wrote from the iOS app.
    height_received = ble_read();
    servo.write(height_received);
    Serial.write(height_received);    
  }
}
