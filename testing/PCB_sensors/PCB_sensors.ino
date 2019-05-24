int led = 13;

//Right Emitters and receivers-----------------------------------------------------
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


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
//LED
pinMode(led, OUTPUT);

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

void loop() {
  // put your main code here, to run repeatedly:
//LED 13 ON ALWAYS
digitalWrite(led, HIGH);

//Emitters
digitalWrite(rightEm, HIGH);
//digitalWrite(right45Em, HIGH);
digitalWrite(centerEm, HIGH);
//digitalWrite(left45Em, HIGH);
digitalWrite(leftEm, HIGH);

//Receiver Readings
right = analogRead(rightRec);
right45 = analogRead(right45Rec);
center = analogRead(centerRec);
left45 = analogRead(left45Rec);
left = analogRead(leftRec);

//int newCenter = map(center, 0, 24, 0, 70); //range of reading: 4-24, range want, 0-250*/
int newCenter = map(center, 6, 250, 0, 300); //range of reading: 4-24, range want, 0-250*/
int newright = map(right, 90, 950, 0, 300); 
int newleft = map(left, 30, 80, 0 , 300);
//no mapping

//no mapping ------------------------------------
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

//values we want mapped-------------------------------- 

Serial.print("mappedCenter: ");
Serial.print(newCenter);
Serial.println();

Serial.print("mappeleft: ");
Serial.print(newleft);
Serial.println();

Serial.print("mapperight: ");
Serial.print(newright);
Serial.println();
delay(500);
}
