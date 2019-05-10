int led = 13; // test led

//Emitters and receivers -------------------------------------------------------------------------------------------------------------------------
//Right 
int rightEm = A0; //14 // A1
int rightRec = 15; //15 // A1
int right; // right sensor reading 

//Center 
int centerEm = A4; // 18 
int centerRec = 19; //19 // A5
int center; //center sensor reading

//Left
int leftEm =  A8; // 22
int leftRec = 23; // 23 // A9
int left; //left sensor reading

//motor functions and variable declarations------------------------------------------------------------------------------------------------------------------------
//START OF FUNCTION DECLARATIONS
void rightFor(double);
//void rightRev(double);
void leftFor(double);
//void leftRev(double); 
void PID();
//END OF FUNCTION DECLARATIONS

//Right Motor
int rightMotorEn = 8; // Right Motor Enable
int rightMotorFor = 9; // Right Motor Forward
int rightMotorRev = 10; // Right Motor Reverse 
//int rightMotorA = 11; // Right Motor A reading
//int rightMotorB = 12; // Right Motor B reading

//Left Motor
int leftMotorEn = 2; // Left Motor Enable
int leftMotorFor = 4; // Left Motor Forward
int leftMotorRev = 3; // Left Motor Reverse 
//int leftMotorA = 5; // Left Motor A reading
//int leftMotorB = 6; // Left Motor B reading

// pid variable initialize-----------------------------------------------------
const float kp = 0.2; // proportion constant
const float ki = 0.001; // integral constant
const float kd = 0.001; // derivative constant

float L_setpoint = 50; // value obtain from calibrating
float R_setpoint = 500; // sensors in middle of maze

// function variables:
float curr_runtime = 0; // total program execution time
float prev_runtime = 0; // previous total program execution time
float iteration_time = 0; // time since last iteration

float L_error = 0;
float L_prev_error = 0;
float L_p_error = 0; // p-error
float L_i_error = 0; // i-error
float L_d_error = 0; // d-error

float R_error = 0;
float R_prev_error = 0;
float R_p_error = 0; // p-error
float R_i_error = 0; // i-error
float R_d_error = 0; // d-error

float L_mod = 0;
float R_mod = 0;

int right_speed;
int left_speed;

unsigned int max_speed = 200;

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
//pinMode(right45Rec, INPUT);
pinMode(centerRec, INPUT);
//pinMode(left45Rec, INPUT);
pinMode(leftRec, INPUT);

//Emitters
pinMode(rightEm, OUTPUT);
//pinMode(right45Em, OUTPUT);
pinMode(centerEm, OUTPUT);
//pinMode(left45Em, OUTPUT);
pinMode(leftEm, OUTPUT);
}

//main loop ----------------------------------------------------------------------------------------------------------------------
void loop() {

  // turn on LED
  digitalWrite(led,HIGH);

  // turn on emitters
  digitalWrite(rightEm, HIGH);
  digitalWrite(centerEm, HIGH);
  digitalWrite(leftEm, HIGH);
  
  // read sensors
  right = analogRead(rightRec);
  center = analogRead(centerRec);
  left = analogRead(leftRec);

  // output sensor readings to serial monitor for no reason
  Serial.print("Right: ");
  Serial.println(right);

  Serial.print("Center: ");
  Serial.println(center);

  Serial.print("Left: ");
  Serial.println(left);

/*
  int k = 0;
  int startFlag = 0;
  
 do {
    center = analogRead(centerRec);
    Serial.print("Center: ");
    Serial.println(center);
    Serial.print("k: ");
    Serial.println(k);
    if (center > 40){
      k += 1;
    }
    else {
      k = 0;
    }
    
    if (k > 96000) {
        goto fark;
    }
    
  } while (startFlag == 0);
  
fark:
*/



  // compute PID
  PID();

  // insert serial print diagnostics here
  Serial.print("L: ");
  Serial.println(left_speed);

  Serial.print("R: ");
  Serial.println(right_speed);

  // output to motors
  if (center > 40) { //make motor output 0
    rightFor(0);
    leftFor(0);
    }
  else { //use PID motor values
    rightFor(right_speed);
    leftFor(left_speed);
    }

delay(100);
}
// end main loop ------------------------------------------------------------------------------------------------------------------

void PID() {

  //determine time stuff
  curr_runtime = millis();
  iteration_time = curr_runtime - prev_runtime;
  
  //determine which side needs the output to be modified
  L_error = left / L_setpoint;
  R_error = right / R_setpoint;

  //determine error values
  L_p_error = L_error;
  L_i_error += L_error * iteration_time;
  L_d_error = (L_error - L_prev_error) / iteration_time; 
  
  R_p_error = R_error;
  R_i_error += R_error * iteration_time;
  R_d_error = (R_error - R_prev_error) / iteration_time; 
  
  //assign output
  L_mod = kp * L_p_error;// + kd * L_d_error + ki * L_i_error;
  R_mod = kp * R_p_error;// + kd * R_d_error + ki * R_i_error;

/*
  if ( ((L_mod * max_speed) +160) > 255){ left_speed = 250; }
  else { left_speed = (160 + floor(L_mod * max_speed)); }
  
  if ( ((R_mod * max_speed +160)) > 255){ right_speed = 250; } 
  else { right_speed = (160 + floor(R_mod * max_speed)); }
*/

  if ( ((L_mod * max_speed) +100) > 255){ left_speed = 250; }
  else { left_speed = (100 + floor(L_mod * max_speed)); }
  
  if ( ((R_mod * max_speed +100)) > 255){ right_speed = 250; } 
  else { right_speed = (100 + floor(R_mod * max_speed)); }
  
  //set iterators for next iteration
  L_prev_error = L_error;
  R_prev_error = R_error;
  prev_runtime = curr_runtime;

}

void rightFor(int rightSpeed){
  digitalWrite(rightMotorEn, HIGH);
  digitalWrite(rightMotorRev, LOW);
  analogWrite(rightMotorFor, rightSpeed);
}

void leftFor(int leftSpeed){
  digitalWrite(leftMotorEn, HIGH);
  digitalWrite(leftMotorRev, LOW);
  analogWrite(leftMotorFor, leftSpeed);
}
