int pulses = 0;
int A_SIG = 0;
int B_SIG = 1;

void setup() {
  attachInterrupt(1, A_RISE, RISING);
  //attachInterrupt(0, B_RISE, RISING);
  
  Serial.begin(57600);
}

void loop()
{
}

void A_RISE() {
  detachInterrupt(1);
  A_SIG = 1;
  
  // Direction detection
  //if (B_SIG = 0)
  //{
    pulses++;
  //}
  //else
  //{
    //pulses--;
  //}
  
  Serial.println(pulses);
  
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
