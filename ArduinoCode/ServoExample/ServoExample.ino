#include <Servo.h>

Servo servo;
void setup()
{
    // Attach my_servo to the pin the Servo Motor is connected to
    servo.attach(9);
}

void loop()
{
  // Moving the servo position form 1 to 179 degrees.
  for(int i = 1; i < 180; i++)
  {
    servo.write(i);
    delay(15);
  }
}
