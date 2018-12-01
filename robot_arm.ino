#include <Servo.h>
 
// joystick variables
const int SW_pin = 2;
const int X1_pin = 0;
const int Y1_pin = 1;
const int X2_pin = 2;
const int Y2_pin = 3;

// Claw servo variables
Servo claw;  
const int clawPin = 9; 
const int clawMin = 90;
const int clawMax = 135;
const int clawInt = 135;  // initial claw servo position in degrees
int clawAngle = clawInt;   

// Rotate servo varaibles
Servo rotate;  
const int rotatePin = 6; 
const int rotateMin = 0;
const int rotateMax = 180;
const int rotateInt = 90;  // initial rotate servo position in degrees
int rotateAngle = rotateInt;   

// Extend servo varaibles
Servo extend;  
const int extendPin = 5; 
const int extendMin = 50;
const int extendMax = 160;
const int extendInt = 80;  // initial extend servo position in degrees
int extendAngle = extendInt;  

// Angle servo varaibles
Servo height;  
const int heightPin = 3; 
const int heightMin = 40;
const int heightMax = 135;
const int heightInt = 90;   // initial extend servo position in degrees
int heightAngle = heightInt;   

void setup() {
  // setup code, to run once:
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(115200);  

  claw.attach(clawPin);
  rotate.attach(rotatePin);
  extend.attach(extendPin);
  height.attach(heightPin);
}

void loop() {
  // loop code, to repeat:
  
  // Claw positioning
  if (analogRead(X1_pin) < 50 ) {
    clawAngle++;
    if (clawAngle > clawMax) clawAngle = clawMax;
    
  } else if (analogRead(X1_pin) > 900 ) {
    clawAngle--;
    if (clawAngle < clawMin) clawAngle = clawMin;
  }

  // Rotate positioning
  if (analogRead(Y1_pin) < 250 ) {
    rotateAngle--;
    if (rotateAngle < rotateMin) rotateAngle = rotateMin;
  } else if (analogRead(Y1_pin) > 750 ) {
    rotateAngle++;
    if (rotateAngle > rotateMax) rotateAngle = rotateMax;
  }

  // Height positioning
  if (analogRead(X2_pin) < 250 ) {
    heightAngle++;
    if (heightAngle > heightMax) heightAngle = heightMax;
    
  } else if (analogRead(X2_pin) > 750 ) {
    heightAngle--;
    if (heightAngle < heightMin) heightAngle = heightMin;
  }

  // Extend positioning
  if (analogRead(Y2_pin) < 250 ) {
    extendAngle--;
    if (extendAngle < extendMin) extendAngle = extendMin;
  } else if (analogRead(Y2_pin) > 750 ) {
    extendAngle++;
    if (extendAngle > extendMax) extendAngle = extendMax;
  }

  // Reset Click - return to home position
  if(digitalRead(SW_pin) == LOW) {
    clawAngle = clawInt;
    rotateAngle = rotateInt; 
    extendAngle = extendInt; 
    heightAngle = heightInt;       
  }
  
  // servo position writes
  claw.write(clawAngle);  
  rotate.write(rotateAngle); 
  height.write(heightAngle);  
  extend.write(extendAngle);       
  delay(12); // controls the speed of the arm, higher the number, slower the movement
}
