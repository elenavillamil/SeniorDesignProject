#include <math.h>

const int MAX_SIZE = 6;
unsigned char toSend[MAX_SIZE];

double stepSize = .366;

const int encoder0PinA = 13;
const int encoder0PinB = 12;
double encoder0Pos = 28*stepSize;

const int encoder1PinA = 20;
const int encoder1PinB = 21;
int encoder1Pos = 0;
int tog=0;
// Motor Controller Pins
int INA = 5;
int INB = 7;

// Each interrupt corresponds to 3 milimiters.
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
int W = 2.5;
double DT = 1; 
double KP = 1;
double KD = 50;
double KI =0.001;

int loopDelay = 0;

int count = 0;

bool robot_status = false;

void setup() { 
  
  //Serial.println(encoder0Pos);

  analogWriteResolution(10);
  
  pinMode(encoder0PinA, INPUT); 
  pinMode(encoder0PinB, INPUT); 
  pinMode(encoder1PinA, INPUT); 
  pinMode(encoder1PinB, INPUT); 
  pinMode(24,OUTPUT);
  // chanel A (encoder 0) interrupts to pin 0
  attachInterrupt(13, doEncoder0ChanelA, CHANGE);
  // chanel B (encoder 0) interrupts to pin 3
  attachInterrupt(12, doEncoder0ChanelB, CHANGE);
  // chanel A (encoder 1) interrupts to pin 4
  attachInterrupt(20, doEncoder1ChanelA, CHANGE);
  // chanel B (encoder 1) interrupts to pin 5
  attachInterrupt(21, doEncoder1ChanelB, CHANGE);

  //pinMode(fiveVolt, OUTPUT);

  // Motor controller
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);

  Serial1.begin (115200);
  Serial.begin(115200);
  // Set the data rate for the SoftwareSerial port
  //mySerial.begin(115200);

  //Serial.println("start");                // a personal quirk
} 

void loop(){

  /*
  if(tog==0){
    digitalWrite(24, LOW);
    tog=1;
  }
  else{
    digitalWrite(24, HIGH); 
    tog=0;
  }
  */
  Serial.println(encoder0Pos);
  
  if (Serial1.available())
  {
    int new_height = (int) Serial1.read();
    
    if (new_height == 200)
    {
      //Serial.println("Turning Off");
      t = 0;
      encoder1Pos = 0; loopDelay=0;
      RC = 0; YC = 0; E = 0; E0 = 0; E1 = 0; E2 = 0; intE = 0;
      duty = 0;
      motorA();
      robot_status = false;
    }
    
    else if (new_height == 0)
    {
      Serial.println("Turning On");
      t = 0;
      encoder1Pos = 0; loopDelay=0;
      RC = 0; YC = 0; E = 0; E0 = 0; E1 = 0; E2 = 0; intE = 0;
      duty = 0;
      robot_status = true;
    }
    
    else
    {
      if (new_height/10 > 0 && new_height/10 < 5)
      {
          Serial.println("Updating W to ");
          Serial.print(new_height);
          W = new_height/10;
      }
    }
  }
  
  // If the user turns off the robot, do not do any of this.
  if (robot_status)
  {  
    //Serial.print("Status On");
    
    // Encoder0 controlls the hight. Thus, its position cannot be negative. 
    if (encoder0Pos > 155)
    {
      encoder0Pos = 155;
    }

    if (encoder0Pos < 0)
    {
      encoder0Pos = 0;
    }
    
    // Sending new height to the arduino UNO to transmit to the iPad
    count += 1;
    if (count == 5)
    {
      count = 0;

      //Serial.println(encoder0Pos);
      toSend[0] = (int) encoder0Pos;
      Serial1.write(toSend[0]);
    }
    
    
    if(loopDelay<=900)
    {
      t = 0;
      loopDelay++;
    }
    
    
    // Controlling motor speed.
    RC = W * t * 1023;
    YC = (encoder1Pos * 1024 )/ 512;
    E = RC - YC;
    intE = intE + E*DT;
    duty = KP*E + KD*(E - (E0 + E1 + E2)/3) / DT + KI*intE;
  
    //Serial.println(encoder1Pos);
    motorA();
  
    E2 = E1;
    E1 = E0;
    E0 = E;
    
    t += 0.005;  
    // Ensure each loop takes 5 miliseconds.
    while (millis() - start < 5) 
    {
        // busy wating
    }
  
    start += 5;
  }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//      FUNCTIONS
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void doEncoder0ChanelA(){
  //Serial.print("Encoder 0 Chanel A");
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
  //Serial.print("Encoder 0 Chanel B");

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
    //Serial.println("Setting chanels to 0");
    analogWrite(INA, 0);
    analogWrite(INB, 0);
  }
}

