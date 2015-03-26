#include <Servo.h>
//#include <SPI.h>
//#include <boards.h>
//#include <ble_shield.h>
//#include <services.h>
//#include <RBL_nRF8001.h>

// char* to send thorugh bluetooth
const int MAX_SIZE = 10;
unsigned char toSend[MAX_SIZE];

const int encoder0PinA = 2;
const int encoder0PinB = 3;
int encoder0Pos = 0;

const int encoder1PinA = 51;
const int encoder1PinB = 47;
int encoder1Pos = 0;

// Encoder Pins
int INA = 7;
int INB = 8;
//int fiveVolt = 6;

int stepSize = 3;
int servoPin = 9;
Servo servo;

int timestep = 50;


void setup() { 
 
  // Setting up servo
  servo.attach(servoPin);

  // Setting up bluetooth
  //ble_set_name("BRC");
  //ble_begin();

  // chanel A (encoder 0) interrupts to pin 0
  attachInterrupt(2, doEncoder0ChanelA, CHANGE);
  // chanel B (encoder 0) interrupts to pin 3
  attachInterrupt(3, doEncoder0ChanelB, CHANGE);
  // chanel A (encoder 1) interrupts to pin 4
  attachInterrupt(51, doEncoder1ChanelA, CHANGE);
  // chanel B (encoder 1) interrupts to pin 5
  attachInterrupt(47, doEncoder1ChanelB, CHANGE);
  
  //pinMode(fiveVolt, OUTPUT);
  
  // Motor controller
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);
  
  Serial.begin (9600);
  
  //Serial.println("start");                // a personal quirk
} 

void loop(){
  
  // Get velocity
  //position1=encoder0Pos;
  delay(timestep);
  //position2 = encoder0Pos;
  //velocity = (position2-position1)/(timestep*.001*3);
  
  //Serial.println (encoder0Pos, DEC); 
  //Serial.println (velocity, DEC); 
  //Serial.println (encoder0Pos, DEC);     
  
  // Encoder0 controlls the hight. Thus, it position cannot be negative.
  if (encoder0Pos < 0) 
  {
    encoder0Pos = 0;
  }
  
  servo.write(encoder0Pos+5);

  // Controlling safts speed.
  Serial.println(encoder1Pos);
  motorA(1,encoder1Pos/3);
  
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
      encoder1Pos = encoder1Pos + stepSize;        
    } 
    else 
    {//Conterclockwise
      encoder1Pos = encoder1Pos - stepSize;
    }
  }
  else                                        
  { // Found a high-to-low on channel A
  
    // check channel B to see which way
    if (digitalRead(encoder1PinB) == HIGH) 
    { // Clockwise
      encoder1Pos = encoder1Pos + stepSize;
    } 
    else 
    { // Counterclockwise
      encoder1Pos = encoder1Pos - stepSize; 
    }
  }
}

void doEncoder1ChanelB(){
  
  if (digitalRead(encoder1PinB) == HIGH) 
  { // Found a low-to-high on channel A
  
    // check channel B to see which way
    if (digitalRead(encoder1PinA) == LOW) 
    { // Counterclockwise
      encoder1Pos = encoder1Pos - stepSize;    
    } 
    else 
    { // Clockwise
      encoder1Pos = encoder1Pos + stepSize;  
    }
  }
  
  else   
  { // Found a high-to-low on channel A
  
    // Check channel B to see which way
    if (digitalRead(encoder1PinA) == LOW) 
    { // Clockwise  
      encoder1Pos = encoder1Pos + stepSize; 
    } 
    else 
    { // Counterclockwise
      encoder1Pos = encoder1Pos - stepSize;       
    }

  }
}

void motorA(int mode, int duty)
{ 
  if (duty > 1023)
    duty = 1023;
  
  // TODO: Not too sure what is the difference between switch case 0 and 3
  switch(mode)
  {
    case 0:  //disable/coast
      //digitalWrite(fiveVolt, LOW);  //set enable low to disable A
      analogWrite(INA, 0);
      analogWrite(INB, 0);
      break;
      
    case 1:  //turn clockwise?
      analogWrite(INA, duty);
      analogWrite(INB, 0);
            
      break;
      
    case 2:  //turn counter-clockwise
      analogWrite(INA, 0);
      analogWrite(INB, duty);
            
      break;
      
    case 3:  //brake motor
      //setting IN1 low connects motor lead 1 to ground
      //digitalWrite(INA, LOW);   
      analogWrite(INA, 0);
      analogWrite(INB, 0);
      //setting IN2 high connects motor lead 2 to ground
      //digitalWrite(INB, LOW);  
      
      //use pwm to control motor braking power 
      //through enable pin
      //analogWrite(fiveVolt, duty);  
      
      break;
  }
}


