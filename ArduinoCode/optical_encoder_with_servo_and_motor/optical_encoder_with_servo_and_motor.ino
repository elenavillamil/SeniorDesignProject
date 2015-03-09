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
int INA = 6;
int INB = 7;
int fiveVolt = 5;




void setup() { 


  pinMode(encoder0PinA, INPUT); 
  //digitalWrite(encoder0PinA, HIGH);     // turn on pullup resistor
  pinMode(encoder0PinB, INPUT); 
  //digitalWrite(encoder0PinB, HIGH);       // turn on pullup resistor
  pinMode(fiveVolt, OUTPUT);
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);



  attachInterrupt(0, doEncoderA, CHANGE);  // encoder pin on interrupt 0 - pin 2
  attachInterrupt(1, doEncoderB, CHANGE);  // encoder pin on interrupt 1 - pin 3
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
  if (encoder0Pos <0) {encoder0Pos=0;}
  if (encoder0Pos > 162) {encoder0Pos = 162;}
  servo.write(angle);
  motorA(1,encoder0Pos)
  
  
  //position1=encoder0Pos;
  delay(timestep);
  //position2 = encoder0Pos;
  //velocity = (position2-position1)/(timestep*.001*3);
  //Serial.println (encoder0Pos, DEC); 
  //Serial.println (velocity, DEC); 
    
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
 //number = number + 1;
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
//  number = number + 1;
// Serial.println (encoder0Pos, DEC);       
}



void motorA(int mode, int percent)
{
  
  //change the percentage range of 0 -> 100 into the PWM
  //range of 0 -> 255 using the map function
  int duty = map(percent, 0, 162, 0, 255);
  
  switch(mode)
  {
    case 0:  //disable/coast
      digitalWrite(fiveVolt, LOW);  //set enable low to disable A
      break;
      
    case 1:  //turn clockwise
      //setting IN1 high connects motor lead 1 to +voltage
      digitalWrite(INA, HIGH);   
      
      //setting IN2 low connects motor lead 2 to ground
      digitalWrite(INB, LOW);  
      
      //use pwm to control motor speed through enable pin
      analogWrite(fiveVolt, duty);  
      
      break;
      
    case 2:  //turn counter-clockwise
      //setting IN1 low connects motor lead 1 to ground
      digitalWrite(INA, LOW);   
      
      //setting IN2 high connects motor lead 2 to +voltage
      digitalWrite(INB, HIGH);  
      
      //use pwm to control motor speed through enable pin
      analogWrite(fiveVolt, duty);  
      
      break;
      
    case 3:  //brake motor
      //setting IN1 low connects motor lead 1 to ground
      digitalWrite(INA, LOW);   
      
      //setting IN2 high connects motor lead 2 to ground
      digitalWrite(INB, LOW);  
      
      //use pwm to control motor braking power 
      //through enable pin
      analogWrite(fiveVolt, duty);  
      
      break;
  }
}


