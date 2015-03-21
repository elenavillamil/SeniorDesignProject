#include <Servo.h>

const int encoder0PinA = 2;
const int encoder0PinB = 3;

int encoder0Pos = 0;
const int statusOutA = 4;
const int statusOutB = 5;
const int directionUp = 6;
int stepSize = 3;
int servoPin = 9;
Servo servo;
int number = 0;
int position1 = 0;
int position2 = 0;
int velocity=0;
int timestep = 50;


void setup() { 


  pinMode(encoder0PinA, INPUT); 
  //digitalWrite(encoder0PinA, HIGH);     // turn on pullup resistor
  pinMode(encoder0PinB, INPUT); 
  //digitalWrite(encoder0PinB, HIGH);       // turn on pullup resistor
 
  attachInterrupt(2, doEncoderA, CHANGE);  // encoder pin on interrupt 0 - pin 2
  attachInterrupt(3, doEncoderB, CHANGE);  // encoder pin on interrupt 1 - pin 3
  Serial.begin (9600);
  Serial.println("start");                // a personal quirk
  pinMode(statusOutA, OUTPUT);
  pinMode(statusOutB, OUTPUT);
  pinMode(directionUp, OUTPUT);
  servo.attach(servoPin);
} 

void loop(){
  int angle = encoder0Pos+5;
  servo.write(angle);
  
  //position1=encoder0Pos;
  delay(timestep);
  //position2 = encoder0Pos;
  //velocity = (position2-position1)/(timestep*.001*3);
  //Serial.println (encoder0Pos, DEC); 
  //Serial.println (velocity, DEC); 
  Serial.println (encoder0Pos, DEC);     
  if (encoder0Pos <0) {encoder0Pos=0;}
}


void doEncoderA(){
  if (digitalRead(encoder0PinA) == HIGH) {   // found a low-to-high on channel A
    if (digitalRead(encoder0PinB) == LOW) {  // check channel B to see which way
                                             // encoder is moving
      encoder0Pos = encoder0Pos + stepSize;   // up
      //  digitalWrite(statusOutA, HIGH);
        //digitalWrite(statusOutB, LOW); 
       // digitalWrite(directionUp, HIGH);     
    } 
    else {
      encoder0Pos = encoder0Pos - stepSize; //down 
       // digitalWrite(statusOutA, HIGH);
       // digitalWrite(statusOutB, HIGH);      
       // digitalWrite(directionUp, LOW);
    }
  }
  else                                        // found a high-to-low on channel A
  { 
    if (digitalRead(encoder0PinB) == HIGH) {   // check channel B to see which way
                                              // encoder is turning  
      encoder0Pos = encoder0Pos + stepSize;   // up
      //  digitalWrite(statusOutA, LOW);
      //  digitalWrite(statusOutB, HIGH);
      //  digitalWrite(directionUp, HIGH);      
    } 
    else {
      encoder0Pos = encoder0Pos - stepSize;   // down
     //  digitalWrite(statusOutA, LOW);
     //  digitalWrite(statusOutB, LOW);  
     //  digitalWrite(directionUp, LOW);     
    }

  }
 // Serial.println (encoder0Pos, DEC);          // debug - remember to comment out
  number = number + 1;
                                              // before final program run
  // you don't want serial slowing down your program if not needed
}



void doEncoderB(){
  if (digitalRead(encoder0PinB) == HIGH) {   // found a low-to-high on channel A
    if (digitalRead(encoder0PinA) == LOW) {  // check channel B to see which way
                                             // encoder is moving
      encoder0Pos = encoder0Pos - stepSize;   // down
      //  digitalWrite(statusOutB, HIGH);
      //  digitalWrite(statusOutA, LOW); 
      //  digitalWrite(directionUp, LOW);     
    } 
    else {
      encoder0Pos = encoder0Pos + stepSize; //up 
      //  digitalWrite(statusOutB, HIGH);
      //  digitalWrite(statusOutA, HIGH);      
      //  digitalWrite(directionUp, HIGH);
    }
  }
  else                                        // found a high-to-low on channel A
  { 
    if (digitalRead(encoder0PinA) == LOW) {   // check channel B to see which way
                                              // encoder is turning  
      encoder0Pos = encoder0Pos + stepSize;   // up
      //  digitalWrite(statusOutA, LOW);
      //  digitalWrite(statusOutB, LOW);
      //  digitalWrite(directionUp, HIGH);      
    } 
    else {
      encoder0Pos = encoder0Pos - stepSize;   // down
      // digitalWrite(statusOutA, HIGH);
      // digitalWrite(statusOutB, LOW);  
      // digitalWrite(directionUp, LOW);     
    }

  }
  number = number + 1;
// Serial.println (encoder0Pos, DEC);       
}

