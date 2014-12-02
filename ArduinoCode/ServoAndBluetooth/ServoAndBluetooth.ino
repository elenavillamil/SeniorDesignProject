#include <ble_shield.h>
#include <boards.h>
#include <RBL_nRF8001.h>
#include <services.h>
#include <Servo.h>
#include <SPI.h>

#define SERVO_PIN 5
#define MAX_SIZE 4

Servo servo;

void setup()
{
  // Setting the bluetooth name to BRC (basketball robot controller.
  ble_set_name("ev9");
  
  // Init and start BLE library.
  ble_begin();
  
  servo.attach(SERVO_PIN);
  servo.write(90);
  
  //delay(10);
  
  // Using as fast as possible transmission, to keep the real time feedback
  Serial.begin(9600);
}


int height_received = 4;
int old_height = 4;
int counter = 0;
void loop()
{
  unsigned char str[MAX_SIZE];
  
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
  
  /*
  for (int i = 1; i < 180; i++)
  {
    servo.write(i);
    delay(100);
    Serial.write(i);
  }
  */
  /*
  long duration, cm;
  
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(PIN, HIGH);
  delayMicroseconds(5);
  digitalWrite(PIN, LOW);

  pinMode(PIN, INPUT);
  duration = pulseIn(PIN, HIGH);

  cm = microsecondsToCentimeters(duration);
  //char* current_str = to_str(c, 
  String distance = String(cm);
  for (int i = 0; i < distance.length() && MAX_SIZE; i++)
    str[i] = distance[i];
  */
  
  /*
  if(ble_connected())
  {
    ble_write_bytes(str, distance.length());  
  }
  */
  ble_do_events();
  
  delay(10);
}
