#include <Servo.h>
#include <SPI.h>
#include <boards.h>
#include <ble_shield.h>
#include <services.h>
#include <RBL_nRF8001.h>

// char* to send thorugh bluetooth
const int MAX_SIZE = 10;
unsigned char toSend[MAX_SIZE];

const int encoder0PinA = 2;
const int encoder0PinB = 3;
int encoder0Pos = 0;

const int encoder1PinA = 21;
const int encoder1PinB = 20;
int encoder1Pos = 0;

// Motor Controller Pins
int INA = 7;
int INB = 8;

// Each interrupt corresponds to 3 milimiters.
int stepSize = 3;

int servoPin = 9;
Servo servo;

int timestep = 50;

// Keep track of time.
int time = 0;


void setup() { 
 
  // Setting up servo
  servo.attach(servoPin);

  // Setting up bluetooth
  //ble_set_name("BRC");
  //ble_begin();

  // chanel A (encoder 0) interrupts to pin 0
  attachInterrupt(0, doEncoder0ChanelA, CHANGE);
  // chanel B (encoder 0) interrupts to pin 3
  attachInterrupt(1, doEncoder0ChanelB, CHANGE);
  // chanel A (encoder 1) interrupts to pin 4
  attachInterrupt(2, doEncoder1ChanelA, CHANGE);
  // chanel B (encoder 1) interrupts to pin 5
  attachInterrupt(3, doEncoder1ChanelB, CHANGE);
  
  //pinMode(fiveVolt, OUTPUT);
  
  // Motor controller
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);
  
  Serial.begin (9600);
  
  //Serial.println("start");                // a personal quirk
} 

void loop(){
  
  //Serial.println (encoder0Pos, DEC); 
  //Serial.println (velocity, DEC); 
  //Serial.println (encoder0Pos, DEC);     
  
  // Encoder0 controlls the hight. Thus, its position cannot be negative.
  if (encoder0Pos < 0) 
  {
    encoder0Pos = 0;
  }
  
  servo.write(encoder0Pos+5);

  // Controlling motor speed.
  //Serial.println(encoder1Pos);
  motorA(1,encoder1Pos/3);
  
  // Ensure each loop takes 5 miliseconds.
  while(millis() % 5 != 0)
  {
  }
    
  time += 0.005;
  
  //////////////////////  BLE CODE  ////////////////////////////////
  
  // Convert int velocity to char*
  //String velocityString = String(velocity);
  //String positionString = String(encoder0Pos);
  //String stringToSend = velocityString + '-' + positionString + '\n';
  
  //Serial.println(stringToSend);
  
  // Code ot send the position to the iPad
  /*
  for (int i = 0; i < positionString.length() && MAX_SIZE; i++)
  {
    toSend[i] = stringToSend[i];
  }
  
  if (ble_connected())
  {
    ble_write_bytes(toSend, stringToSend.length());
  }
  
  ble_do_events();
  */
}


void doEncoder0ChanelA(){
  if (digitalRead(encoder0PinA) == HIGH) 
  {// Found a low-to-high on channel A
    
    // check channel B to see which way
    if (digitalRead(encoder0PinB) == LOW) 
    {// Clockwise
      encoder0Pos = encoder0Pos + stepSize;        
    } 
    else 
    {//Conterclockwise
      encoder0Pos = encoder0Pos - stepSize;
    }
  }
  else                                        
  { // Found a high-to-low on channel A
  
    // check channel B to see which way
    if (digitalRead(encoder0PinB) == HIGH) 
    { // Clockwise
      encoder0Pos = encoder0Pos + stepSize;
    } 
    else 
    { // Counterclockwise
      encoder0Pos = encoder0Pos - stepSize;   
    }
  }
}

void doEncoder0ChanelB(){
  
  if (digitalRead(encoder0PinB) == HIGH) 
  { // Found a low-to-high on channel A
  
    // Check channel B to see which way
    if (digitalRead(encoder0PinA) == LOW) 
    { // Counterclockwise
      encoder0Pos = encoder0Pos - stepSize;    
    } 
    else 
    { // Clockwise
      encoder0Pos = encoder0Pos + stepSize;  
    }
  }
  
  else   
  { // Found a high-to-low on channel A
  
    // Check channel B to see which way
    if (digitalRead(encoder0PinA) == LOW) 
    { // clockwise  
      encoder0Pos = encoder0Pos + stepSize; 
    } 
    else 
    { // Counterclockwise
      encoder0Pos = encoder0Pos - stepSize;       
    }

  }
}

void doEncoder1ChanelA(){
  if (digitalRead(encoder1PinA) == HIGH) 
  {// found a low-to-high on channel A
    
    // check channel B to see which way
    if (digitalRead(encoder1PinB) == LOW) 
    {// Clockwise
      encoder1Pos += 1;        
    } 
    else 
    {//Conterclockwise
      encoder1Pos -= 1;
    }
  }
  else                                        
  { // Found a high-to-low on channel A
  
    // check channel B to see which way
    if (digitalRead(encoder1PinB) == HIGH) 
    { // Clockwise
      encoder1Pos += 1;
    } 
    else 
    { // Counterclockwise
      encoder1Pos -= 1; 
    }
  }
}

void doEncoder1ChanelB(){
  
  if (digitalRead(encoder1PinB) == HIGH) 
  { // Found a low-to-high on channel A
  
    // check channel B to see which way
    if (digitalRead(encoder1PinA) == LOW) 
    { // Counterclockwise
      encoder1Pos -= 1;    
    } 
    else 
    { // Clockwise
      encoder1Pos += 1;  
    }
  }
  
  else   
  { // Found a high-to-low on channel A
  
    // Check channel B to see which way
    if (digitalRead(encoder1PinA) == LOW) 
    { // Clockwise  
      encoder1Pos += 1; 
    } 
    else 
    { // Counterclockwise
      encoder1Pos -= 1;       
    }

  }
}

void motorA(int mode, int duty)
{ 
  // Duty has to be between -1023 <= duty >= 1023
  if (duty > 1023)
    duty = 1023;
  
  if (duty < -1023)
    duty = -1023;
    
  if (duty < 0)
  {
    //turn counter-clockwise
    analogWrite(INA, 0);
    analogWrite(INB, -duty);
  }
  else if (duty > 0)
  {
    analogWrite(INA, duty);
    analogWrite(INB, 0);
  }
  else
  {
    analogWrite(INA, 0);
    analogWrite(INB, 0);
  }
}


