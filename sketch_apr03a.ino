//#include <Boards.h>
//#include <Firmata.h>
//#include <FirmataConstants.h>
//#include <FirmataDefines.h>
//#include <FirmataMarshaller.h>
//#include <FirmataParser.h>


int led = 13;
// Motor #1
int motorEN1 = 8; // Enable
int motorLogic1F = 9; //Forward9
int motorLogic1R = 10; // Reverse10
double motorSpeed1 = 50; // Speed

//// Motor #2
int motorEN2 = 2; // Enable
int motorLogic2F = 3;  //Forward3
int motorLogic2R = 4;  //Reverse4
double motorSpeed2 = 75; // Speed

//  Numbers
const double pi = 3.1415926;

// Analog Pins

//LEFT:
int leftSenEn = A6; // black neg for the receiver
int leftSen = 22; //A8;// black pos for the receiver
int leftEm = A7; // blue Emitter enable
int left;        // For the value from the receiver

//RIGHT:

int rightSen = A2;  // black neg for the receiver
int rightSenEn = A1; // black pos this enables the sensor
int rightEm = A0; // blue (this is the emitter)
int right;            // For the value from the receiver

//FRONT:
int frontSen = A5; //black neg    // For the receiver
int frontSenEn = A4; // black pos A4
int frontEm = A3; //blue this is the emitter 
int front;            // For the value from the receiver

void forwardMotor1(double motorSpeed) {
  digitalWrite(motorEN1, HIGH);
  digitalWrite(motorLogic1F, HIGH);
  digitalWrite(motorLogic1R, LOW);
  analogWrite(motorLogic1F, motorSpeed);
}

void reverseMotor1(double motorSpeed) {
  digitalWrite(motorEN1, HIGH); 
  digitalWrite(motorLogic1F, LOW);
  digitalWrite(motorLogic1R, HIGH);
  analogWrite(motorLogic1R, motorSpeed);
 
}

void forwardMotor2(double motorSpeed) {
  digitalWrite(motorEN2, HIGH);
  digitalWrite(motorLogic2F, HIGH);
  digitalWrite(motorLogic2R, LOW);
  analogWrite(motorLogic2F, motorSpeed);
}

void reverseMotor2(double motorSpeed) {
  digitalWrite(motorEN2, HIGH);
  digitalWrite(motorLogic2F, LOW);
  digitalWrite(motorLogic2R, HIGH);
  analogWrite(motorLogic2R, motorSpeed);
}

void halt() {
  
  digitalWrite(motorEN1, LOW);
  digitalWrite(motorLogic1F, LOW);
  digitalWrite(motorLogic1R, LOW);
  
  digitalWrite(motorEN2, LOW);
  digitalWrite(motorLogic2F, LOW);
  digitalWrite(motorLogic2R, LOW);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);

  //Motor 1
  pinMode(motorEN1, OUTPUT);
  pinMode(motorLogic1F, OUTPUT);
  pinMode(motorLogic1R, OUTPUT);
  digitalWrite(motorEN1, LOW);

  //Motor 2
  pinMode(motorEN2, OUTPUT);
  pinMode(motorLogic2F, OUTPUT);
  pinMode(motorLogic2R, OUTPUT);
  digitalWrite(motorEN2, LOW);
  
  //LED
  pinMode(led, OUTPUT);
  
  Serial.begin(9600);
  //LEFT:
  pinMode(leftSen, INPUT);
   pinMode(leftSenEn, OUTPUT);
  pinMode(leftEm, OUTPUT);
  
  //RIGHT:
  pinMode(rightSen, INPUT);
  pinMode(rightSenEn, OUTPUT);
  pinMode(rightEm, OUTPUT);
  
  //FRONT:
  pinMode(frontSen, INPUT);
   pinMode(frontSenEn, OUTPUT);
  pinMode(frontEm, OUTPUT);

  
}

void loop() {
  // put your main code here, to run repeatedly:
  //while loop for the receivers
  
  forwardMotor2(150);
  forwardMotor1(125);
  //digitalWrite(led,HIGH);
  //delay(1000);
  
  //halt();
  
  //delay(1000);
  
  //reverseMotor2(100);
  //reverseMotor1(100);
  
  delay(500);
  
//  digitalWrite(led, HIGH);
//  delay(1000);
//  digitalWrite(led,LOW);
//  delay(1000);

  left = analogRead(leftSen);
  right = analogRead(rightSen);
  front = analogRead(frontSen);
    
  //LEFT:
   digitalWrite(leftSenEn, HIGH);
  digitalWrite(leftEm, HIGH);
  Serial.print("Left: ");
  Serial.println(left);
  Serial.println();

  //right:
  digitalWrite(rightSenEn, HIGH);
  digitalWrite(rightEm, HIGH);
  Serial.print("Right: ");
  Serial.println(right);
  Serial.println();

  //Front:
   digitalWrite(frontSenEn, HIGH);
  digitalWrite(frontEm, HIGH);
  Serial.print("Front: ");
  Serial.println(front);
  Serial.println();
  
  
//  while (abs(left-right) < 100) {
//  
//  left = analogRead(leftSen);
//  right = analogRead(rightSen);
//  front = analogRead(frontSen);
//      //LEFT:
//   digitalWrite(leftSenEn, HIGH);
//  digitalWrite(leftEm, HIGH);
//  Serial.print("Left: ");
//  Serial.println(left);
//  Serial.println();
//
//  //right:
//  digitalWrite(rightSenEn, HIGH);
//  digitalWrite(rightEm, HIGH);
//  Serial.print("Right: ");
//  Serial.println(right);
//  Serial.println();
//
//  //Front:
//   digitalWrite(frontSenEn, HIGH);
//  digitalWrite(frontEm, HIGH);
//  Serial.print("Front: ");
//  Serial.println(front);
//  Serial.println();
//  
//    if (/*(abs(left - right) < 50) &&*/ ((left - right) > 0)) {
//      Serial.print("Left is greater\n");
//      rightFix(left - right);
//    }
//    else if (/*(abs(right - left) < 250) && */((right -left) > 30)){
//      Serial.print("Right is greater\n");
//      leftFix(right - left);
//    }
//  }
  
}

//double radius() {
//  //Read the distance away from the wall and return that value as r.
//  //r = analogReading;
//  return 1.0;
//}

//void rightForward() {
//  //Turn off the receivers?
//  //right turn forward
//  // move a certain distance forward;
//  //Turn the speeds for each wheel respectively
//}
//double r = radius();
//  //double vR = distance(r)/5 //FIX ME SOON !!!!!!!!!!
//  //double vL = motorSpeed(vR,r);
//  //  motorSpeed1 = vR;
//  //  motorSpeed2 = vL;
//}

//void leftForward(){} //COMPLETE ME
//void rightReverse(){} // COMPLETE ME
//void leftReverse(){} // COMPLETE ME

//void halt() {
//  digitalWrite(motorLogic1F, LOW);
//  digitalWrite(motorLogic1R, LOW);
//  digitalWrite(motorLogic2F, LOW);
//  digitalWrite(motorLogic2R, LOW);
//  motorSpeed1 = 0;
//  motorSpeed2 = 0;
//}

/*
Rover Forward(){
digitalWrite(M1, HIGH);
digitalWrite(M2, HIGH);
analogWrite(S1, maxSpeed);
analogWrite(S2, maxSpeed);
}

*/

//double motorSpeed(double v, double r){
//  //this will calculate the speed for the farther wheel
//   return ((r+8)*v)/r;
// }

//double radius(){
//  //Read the distance away from the wall and return that value as r.
//  //r = analogReading;
//  //return 1;
// }
//double distance(r){
//  //this returns the distance for turns
//  // return (0.25)*pi*sq(r);
// }


//void rightFix(int error) {
//  // will make it go right
//  delay(1000);
//  motorSpeed1 = 50+ error;
//  motorSpeed2 = 50 - error + 25;
//  forwardMotor1(motorSpeed1);
//  forwardMotor2(motorSpeed2);
//}
//void leftFix(int error) {
//  delay(1000);
//  //will make it go left
//  motorSpeed1 = 50 - error;
//  motorSpeed2 = 50 + error + 25;
//  forwardMotor1(motorSpeed1);
//  forwardMotor2(motorSpeed2);
//}


/*
 WEEK 4 Winter SLIDES 
  
  pinMode(motorVar,OUTPUT);
  pinMode(motorEn, LOW);
*/
