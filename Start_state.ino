
//START OF FUNCTION DECLARATIONS

void startState(int);//function declaration for start, intilize agorithm

//Motors
void rightFor(double);
void rightRev(double);
void leftFor(double);
void leftRev(double); 

//END OF FUNCTION DECLARATIONS

//LED
int led = 13; // test led
const int startOff = 3;
unsigned int startFlag = 0;



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




//setup, variables, as outputs and endputs etc.  --------------------------------------------------------------------------------------------------------------------------
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

int stateSM[] = {0, 1};
int state = stateSM[0];
int startTimer = 0; // this is the timer value to determine whether the value is being held for over 3 seconds
void Tick(){
  Serial.print("State: ");
  Serial.println(state);
  Serial.print("Timer: ");
  Serial.println(startTimer);
  Serial.print("Center: ");
  Serial.println(center);
 // delay(500);
// Transitions 
 switch(state){

  case 0: 
  delay(1000);
  if((center > 30) && (startTimer > 3000)){ // if the value of center to be greater  
  //is less than 3 seconds stay in the Start state, else state = go // the center needs to hold a value over 80 for three seconds
    state = stateSM[1];
  }
  else{
    if(center > 30 && startTimer < 3000){
      startTimer = millis() + startTimer;
      Serial.print("Timer");
      Serial.println(startTimer);
      state = stateSM[0];
      }
    else{
     startTimer = 0;
     state = stateSM[0];
    }
  }
  break;

  case 1:
  state = stateSM[1];
  break;

  default:
  break;
 }

//States
switch(state){
  case 0: 
  break;

  case 1: 
    rightFor(200);
    leftFor(200);
  break;

  default:
  break;
  
  }
}


//main loop ----------------------------------------------------------------------------------------------------------------------
void loop(){
  // put your main code here, to run repeatedly:

//LED
digitalWrite(led,HIGH);

// States
digitalWrite(centerEm, HIGH);
center = analogRead(centerRec);
Serial.print("Center: ");
Serial.println(center);
Tick();
}
//start-----------
//center = analogRead(centerRec);
//
//  if(center > startOff){
//    startState(center);
//  }
//
//void startState(int reading){
//  unsigned int prevMillis = millis(); // 
//  while( millis() - prevMillis > 3){}
//  if(tempCenterB - tempCenterA < 100){
//    startFlag = 1;
//  }
//}

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


