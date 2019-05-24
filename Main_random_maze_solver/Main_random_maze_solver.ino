/* author: Matthew Alaniz
 *  description: expand start state agorithm, to random maze solving logic
 *  data: 5/19/2019
 *  last edit:
*/
//START OF FUNCTION DECLARATIONS

void StartTick();//function declaration for start, intilize agorithm
void output_sensor_reading();
//Motors
void rightFor(double);
void rightRev(double);
void leftFor(double);
void leftRev(double); 

//END OF FUNCTION DECLARATIONS

//LED
int led = 13; // test led
unsigned int startFlag = 0;
unsigned int start_time = 120; // value neccesary to enter maze solving logic



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

digitalWrite(led, HIGH);

//Emitters
digitalWrite(rightEm, HIGH);
digitalWrite(right45Em, HIGH);
digitalWrite(centerEm, HIGH);
digitalWrite(left45Em, HIGH);
digitalWrite(leftEm, HIGH);

//Receiver Readings
right = analogRead(rightRec);
right45 = analogRead(right45Rec);
center = analogRead(centerRec);
left45 = analogRead(left45Rec);
left = analogRead(leftRec);

//int newCenter = map(center, 0, 24, 0, 70); //range of reading: 4-24, range want, 0-250*/
int center = map(center, 6, 250, 0, 300); //range of reading: 4-24, range want, 0-250*/
int right = map(right, 90, 950, 0, 300); 
int left = map(left, 30, 80, 0 , 300);
}









//main loop ----------------------------------------------------------------------------------------------------------------------
void loop(){
  // put your main code here, to run repeatedly:

//LED
digitalWrite(led,HIGH);
output_sensor_reading();

// States
digitalWrite(centerEm, HIGH);
center = analogRead(centerRec);
center = map(center, 6, 250, 0, 300); //range of reading: 4-24, range want, 0-250
Serial.print("Center: ");
Serial.println(center);
StartTick();
mazesolve();
}




int stateSM[] = {0, 1};
int state = stateSM[0];
int startTimer = 0; // this is the timer value to determine whether the value is being held for over 3 seconds

void StartTick(){
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
  if((center > start_time) && (startTimer > 3000)){ // if the value of center to be greater  
  //is less than 3 seconds stay in the Start state, else state = go // the center needs to hold a value over 80 for three seconds
    state = stateSM[1];
    startFlag = 1;
  }
  else{
    if(center > start_time && startTimer < 3000){
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
   //PID function call for two walls
   break;

  default:
  break;
  
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

void output_sensor_reading(){ 
  Serial.print("Right: ");
Serial.println(right);
Serial.println();

/*
Serial.print("Right 45: ");
Serial.println(right45);
Serial.println();
*/

Serial.print("Center: ");
Serial.println(center);
Serial.println();

/*
Serial.print("Left 45: ");
Serial.println(left45);
Serial.println();
*/

Serial.print("Left: ");
Serial.println(left);
Serial.println();

}


//enum dicision_states{dicision, go_straight, turn_left turn_right, };
int Maze_SM[] = {0, 1, 2, 3};
int Dicision_state = stateSM[0];

void mazesolve(){
  
  if ( startFlag == 1){
    switch(Dicision_state){ //transistions---------------------------
      case 0:
        if ( (left > 200) && (right > 200) && ( center < 200)){ // when wall on left and right
         // state = go_straight;
        }
        
       else  if ( (left > 200) && (right < 200) && ( center < 200)){ // when wall on left 
          if(millis()% 2 == 1){
           // state = turn_right; 
          }
          else{
          //state = go_straight;
          }
        }
        
        else if( (left < 200) && (right > 200) && ( center < 200)){ // when wall on right
           if(millis()% 2 == 1){
            //state = turn_left;
          }
          else{
            //state = go_straight;
          }
        }
        
        else if((left < 200) && (right < 200) && ( center > 200)){ // when wall on the front
          if(millis() % 2 == 0){
           //dicision_state = turn_left;
           }
          else{
            //dicision_state_turn_right;
          }
        }
      break;

      case 1: //dicision_ state = dicision;
      break;
      case 2: //dicision_state = dicision;
      break;
      case 3:// dicision_state = dicision;
      break;
    }//transistions
    switch(Dicision_state){// actions---------------
      case 0:
      break;
      case 1:// go straiht
      //call two wall pid
      break;
      case 2:// go left
       //call one wall pid
      break;
      case 3:// 
       //call one wall pid
      break;
    }//actions
  }
}


afterturn {
  unsigned int pid_delay_time = 5000;
  unsigned cnt;
  while(pid_delay_time > cnt){
    if( left> 200 && right < 200){
      //onewallpid_right
    }
    else if( left < 200 && right > 200){
      //onewallpid_left
    }
    else{
    }//two wall pid
    ++cnt;
  }
  }
}

