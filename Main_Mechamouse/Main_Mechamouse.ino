

int led = 13; // test led
const int startOff;
unsigned int startFlag = 0;

void startState(int);//function declaration for start, intilize agorithm

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
//Serial.begin(9600);
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



//start-----------
center = analogRead(centerRec);
if(center > startOff){

  startState(center);
}

while(startFlag){//follow through with rest of agorithm
//Right Forward 
rightFor(150);


//Left Forward
(100);
leftFor(150);
}
}

void startState(int reading){
  startFlag = 0;
  int tempCenterA = analogRead(center);
  unsigned int prevMillis = millis();
  while( millis() - prevMillis > 3){}
  int tempCenterB = analogRead(center);
  if(tempCenterB - tempCenterA < 100){
    startFlag = 1;
  }
}

void rightFor(double rightSpeed){
  digitalWrite(rightMotorEn, HIGH);
  digitalWrite(rightMotorRev, LOW);
  analogWrite(rightMotorFor, rightSpeed);
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


