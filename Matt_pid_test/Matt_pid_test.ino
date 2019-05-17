/*
 * this code for main mechmouse by Rat pack 
 * main contributers: Matthew Alaniz, Stephanie Cabrera
 */

int led = 13; // test led


//Right Emitters and receivers -------------------------------------------------------------------------------------------------------------------------
int rightEm = A0; //14 // A1
int rightRec = 15; //15 // A1
int right; // right sensor reading 

// Right45
int right45Em = A2; //16
int right45Rec = 17; //17 //A3
int right45; //right45 sensor reading

// Center 
int centerEm = A4; // 18 
int centerRec = 19; //19 // A5
int center; //center sensor reading

// Left 45 
int left45Em = A6; //20
int left45Rec = 21; //21 // A7
int left45; //left45 sensor reading

//Left
int leftEm =  A8; // 22
int leftRec = 23; // 23 // A9
int left; //left sensor reading


//motor functions and variable declarations------------------------------------------------------------------------------------------------------------------------
//START OF FUNCTION DECLARATIONS
void rightFor(double);
void rightRev(double);
void leftFor(double);
void leftRev(double); 
//END OF FUNCTION DECLARATIONS


//Right Motor
int rightMotorEn = 8; // Right Motor Enable
int rightMotorFor = 9; // Right Motor Forward
int rightMotorRev = 10; // Right Motor Reverse 
//int rightMotorA = 11; // Right Motor A reading
//int rightMotorB = 12; // Right Motor A reading


//Left Motor
int leftMotorEn = 2; // Left Motor Enable
int leftMotorFor = 4; // Left Motor Forward
int leftMotorRev = 3; // Left Motor Reverse 
//int leftMotorA = 5; // Left Motor A reading
//int leftMotorB = 6; // Left Motor B reading

//pid function declaration--------------------------------

void two_wall_pid(int leftIr, int rightIr);

unsigned int leftset = 68, rightSet = 900;
unsigned int leftError = 0, rightError = 0;
unsigned int leftOutput = 0, rightOutput = 0;
unsigned int leftSet = 0, righSet = 0;
unsigned int right_errorsum = 0, left_errorsum = 0;
unsigned int left_errorOutput = 0;
unsigned int right_errorOutput = 0;  
unsigned int  right_DError = 0, left_DError = 0;
unsigned int left_lastError = 0, right_lastError = 0;
unsigned int preTime = millis();


//setup, varaiables, as outputs and endputs etc.  --------------------------------------------------------------------------------------------------------------------------
void setup() {
 // put your setup code here, to run once:
//sensor,output--------------------------------------------------------------
//Right Motor
pinMode(rightMotorEn, OUTPUT);
pinMode(rightMotorFor, OUTPUT);
pinMode(rightMotorRev, OUTPUT);
//pinMode(rightMotorA, INPUT);
//pinMode(rightMotorB, INPUT);



//Left Motor
pinMode(leftMotorEn, OUTPUT);
pinMode(leftMotorFor, OUTPUT);
pinMode(leftMotorRev, OUTPUT);
//pinMode(leftMotorA, INPUT);
//pinMode(leftMotorB, INPUT);

//LED
pinMode(led, OUTPUT); // test led

// sensors setup---------------------------------------------------------------
Serial.begin(9600);
//Receivers
pinMode(rightRec, INPUT);
pinMode(right45Rec, INPUT);
pinMode(centerRec, INPUT);
pinMode(left45Rec, INPUT);
pinMode(leftRec, INPUT);

//Emitters
pinMode(rightEm, OUTPUT);
pinMode(right45Em, OUTPUT);
pinMode(centerEm, OUTPUT);
pinMode(left45Em, OUTPUT);
pinMode(leftEm, OUTPUT);




}

//main loop ----------------------------------------------------------------------------------------------------------------------
void loop() {
  // put your main code here, to run repeatedly:

//LED
digitalWrite(led,HIGH);
//Emitters
digitalWrite(rightEm, HIGH);
digitalWrite(right45Em, HIGH);
digitalWrite(centerEm, HIGH);
digitalWrite(left45Em, HIGH);
digitalWrite(leftEm, HIGH);

rightFor(150);
leftFor(150);

unsigned int currentMillis = millis();
while((millis() - currentMillis) > 1500){}

while(1){
//Receiver Readings
right = analogRead(rightRec);
//right45 = analogRead(right45Rec);
center = analogRead(centerRec);
//left45 = analogRead(left45Rec);
left = analogRead(leftRec);

Serial.print("Right: ");
Serial.println(right);
Serial.println();


Serial.print("Center: ");
Serial.println(center);
Serial.println();



Serial.print("Left: ");
Serial.println(left);
Serial.println();


two_wall_pid( left, right);

analogWrite(rightMotorFor, right_errorOutput);
analogWrite(leftMotorFor, left_errorOutput);

Serial.print("leftOutput: ");
Serial.println(left_errorOutput);
Serial.println(leftMotorFor, left_errorOutput);

Serial.print("rightOutput: ");
Serial.println(right_errorOutput);
Serial.println(rightMotorFor, right_errorOutput);




//start-----------
//follow through with rest of agorithm
//Right Forward 
//rightFor(150);


//Left Forward
//(100);
//leftFor(150);

preTime = millis();
}

}



void rightFor(double rightSpeed){
  digitalWrite(rightMotorEn, HIGH);
  digitalWrite(rightMotorRev, LOW);
  analogWrite(rightMotorFor, rightSpeed);bn  
}

void leftFor(double leftSpeed){
  digitalWrite(leftMotorEn, HIGH);
  digitalWrite(leftMotorRev, LOW);
  analogWrite(leftMotorFor, leftSpeed);
}


void rightRev(double rightSpeed){
  digitalWrite(rightMotorEn, HIGH);
  digitalWrite(rightMotorFor, LOW);
  analogWrite(rightMotorRev, rightSpeed);
}

void leftRev(double leftSpeed){
  digitalWrite(leftMotorEn, HIGH);
  digitalWrite(leftMotorFor, LOW);
  analogWrite(leftMotorRev, leftSpeed);
}



void two_wall_pid(int leftIr,int rightIr){
  unsigned int kp;
  unsigned int kd;
  unsigned int ki;
  //proportional error--------------------------
  if(leftIr > leftSet){
    leftError = leftIr - leftSet;
  }
  else if(leftIr < leftSet){
    leftError = leftSet - leftIr;
  }
  if(rightIr > rightSet){
    rightError = rightIr - rightSet;
  }
  else if(rightIr < rightSet){
    leftError = rightSet - rightIr;
  }
  
 //derivative error----------------------------------------------
unsigned int  timeChange = millis()  - preTime;
  if(leftError > rightError){
      left_DError = (leftError - left_lastError)/timeChange;
  }
 if(leftError < rightError){
  right_DError = (rightError - right_lastError)/timeChange;
 }
//integrl error-----------------------------------------------
  if(leftError > rightError){
  left_errorsum += ( leftError * timeChange);
  }
 if(leftError < rightError){
  right_errorsum += (rightError * timeChange);
 }
 //
//outputing as motor value----------------------------------------
  left_errorOutput = kp*leftError + kd * left_DError + ki*left_errorsum;
  right_errorOutput = kp * rightError + kd * left_DError + ki*left_errorsum;

  left_lastError = leftError;
  right_lastError = rightError;
  
  }

