#include <math.h>

//SoftwareSerial mySerial(10, 11); // RX, TX

const int MAX_SIZE = 6;
unsigned char toSend[MAX_SIZE];

const int encoder0PinA = 12;
const int encoder0PinB = 13;
int encoder0Pos = 0;

const int encoder1PinA = 21;
const int encoder1PinB = 20;
int encoder1Pos = 0;
int tog=0;
// Motor Controller Pins
int INA = 5;
int INB = 7;

// Each interrupt corresponds to 3 milimiters.
int stepSize = 3;
long start=0;
int timestep = 40;

// Keep track of time.
double t = 0;

signed long RC = 0;
signed long YC = 0;
signed long E = 0;
signed int E0 = 0;
signed int E1 = 0;
signed int E2 = 0;
signed int intE = 0;
signed int duty = 0;

// revolution/second
int W = 1;
double DT = 1; 
double KP = 1;
double KD = 50;
double KI =0.001;

int loopDelay = 0;


void setup() { 
  
  analogWriteResolution(10);
  
  pinMode(encoder0PinA, INPUT); 
  pinMode(encoder0PinB, INPUT); 
  pinMode(encoder1PinA, INPUT); 
  pinMode(encoder1PinB, INPUT); 
  pinMode(24,OUTPUT);
  // chanel A (encoder 0) interrupts to pin 0
  attachInterrupt(12, doEncoder0ChanelA, CHANGE);
  // chanel B (encoder 0) interrupts to pin 3
  attachInterrupt(13, doEncoder0ChanelB, CHANGE);
  // chanel A (encoder 1) interrupts to pin 4
  attachInterrupt(21, doEncoder1ChanelA, CHANGE);
  // chanel B (encoder 1) interrupts to pin 5
  attachInterrupt(20, doEncoder1ChanelB, CHANGE);

  //pinMode(fiveVolt, OUTPUT);

  // Motor controller
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);

  Serial1.begin (57600);
  
  // Set the data rate for the SoftwareSerial port
  //mySerial.begin(115200);

  //Serial.println("start");                // a personal quirk
} 

void loop(){

  if(tog==0){
    digitalWrite(24, LOW);
    tog=1;
  }
  else{
    digitalWrite(24, HIGH); 
    tog=0;
  }
  //Serial.println (velocity, DEC); 
  //Serial.println (encoder0Pos, DEC);     

  // Encoder0 controlls the hight. Thus, its position cannot be negative.
  if (encoder0Pos < 0) 
  {
    encoder0Pos = 0;
  }
  if (encoder0Pos > 162)
  {
    encoder0Pos = 162;
  }
  
  // Sending new height to the arduino UNO to transmit to the iPad
  toSend[0] = encode0Pos;
  Serial1.write(toSend[0]);

  if(loopDelay<=900)
  {
    t = 0;
    loopDelay++;
  }
  // Controlling motor speed.
  RC = 4.5 * t * 1023;
  YC = (encoder1Pos * 1024 )/ 512;
  E = RC - YC;
  intE = intE + E*DT;
  duty = KP*E + KD*(E - (E0 + E1 + E2)/3) / DT + KI*intE;

  //Serial.println(encoder1Pos);
  motorA();

  E2 = E1;
  E1 = E0;
  E0 = E;

  
  //Serial.println (millis()% 5); 
  t += 0.005;  
  // Ensure each loop takes 5 miliseconds.
  // while (fmod(millis(), 5)!=0);
  while (millis() - start < 7) 
  {
        // busy wating
  }
  // do NOT read again as this would cummulate the drift
  // instead add just one second to start
  start += 7;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

void motorA()
{ 
  // Duty has to be between -1023 <= duty >= 1023
  if (duty > 1023)
    duty = 1023;

  if (duty < -1023)
    duty = -1023;

  if (duty < 0)
  {
    //turn counter-clockwise
    analogWrite(INA, -duty);
    analogWrite(INB, 0);
  }
  else if (duty > 0)
  {
    analogWrite(INA, 0);
    analogWrite(INB, duty);
  }
  else
  {
    analogWrite(INA, 0);
    analogWrite(INB, 0);
  }
}

