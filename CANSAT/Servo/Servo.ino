/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo SL,SR;  // create servo object to control a servo
// twelve servo objects can be created on most boards
void setup() {
  SL.attach(11);
  SR.attach(10);
  SL.write(0);  
  SR.write(0);
  delay(2000);
  SL.write(55);  
  SR.write(55);
  delay(10000);
  SL.write(0);  
  SR.write(0);
}

void loop() {
  
}
