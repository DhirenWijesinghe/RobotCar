const int pwm = 9 ;  //initializing pin 2 as pwm
const int in_1 = 3 ; //motor 1 pin
const int in_2 = 4 ; //motor 1 pin
const int in_3 = 5 ; //motor 2 pin
const int in_4 = 6 ; //motor 2 pin

int LEDpin = 13;
int Photo1 = A0; //Input pins for the photoresistors
int Photo2 = A1;
int Photo3 = A2;
//int Dist = A3;
int sensorValueL = 0; //Variables for the photoresistor values
int sensorValueC = 0;
int sensorValueR = 0;
//int distanceValue = 0; //Distance sensor variablle value
int blackThresh = 50;  //Threshold for photoresistors
//int distThresh = 1.2; //Threshold for distance sensor
int lastMove = 2; //1-Left 2-Forward 3-Right 4-Break


//For providing logic to L298 IC to choose the direction of the DC motor 

void setup()
{
  Serial.begin(9600);     //Starts reading data from photoresistors
  pinMode(pwm,OUTPUT) ;  //we have to set PWM pin as output
  pinMode(in_1,OUTPUT) ;  //Logic pins are also set as output
  pinMode(in_2,OUTPUT) ;
  pinMode(in_3,OUTPUT) ;
  pinMode(in_4,OUTPUT) ;
  pinMode(LEDpin,OUTPUT) ;
}

void loop()
{
  sensorValueL = analogRead(Photo1) - 45; // read the values from the photoresistors
  sensorValueC = analogRead(Photo2);
  sensorValueR = .95 * analogRead(Photo3) - 60; // read the value from the sensor
//  sensorValueL = analogRead(Photo1) * 2; // read the values from the photoresistors
//  sensorValueC = analogRead(Photo2) * 2 + 40;
//  sensorValueR = analogRead(Photo3) * 2; // read the value from the sensor
  //distanceValue = analogRead(Dist);
  int sum = sensorValueL + sensorValueC + sensorValueR;
  int smallest = min(sensorValueL, sensorValueC);
  smallest = min(smallest, sensorValueR);
  sum = sum - smallest;
  int averageWhite = sum / 2;
  Serial.print(sensorValueL);
  Serial.print("\t");
  Serial.print(sensorValueC);
  Serial.print("\t");
  Serial.print(sensorValueR);
  Serial.print("\t");
  Serial.print(averageWhite);
  Serial.println();
  //Serial.println(analogRead(Dist));

   if(averageWhite - sensorValueC > blackThresh)
  {
    if (lastMove != 2)
    {
      Serial.println("Found Line, going forward");
    } else {
      Serial.println("Going Forward");
    }
    forward();
    lastMove = 2;
  } else if((averageWhite - sensorValueR > blackThresh && lastMove == 2 || lastMove == 3))
  {
    if (lastMove != 3)
    {
      Serial.println("Turning Left until line found");
    } else {
      Serial.println("Going Right");
    }
    turnRight();
    lastMove = 3;
  } else if((averageWhite - sensorValueL > blackThresh && lastMove == 2 || lastMove == 1))
  {
    if (lastMove != 1)
    {
      Serial.println("Turning Left until line found");
    } else {
      Serial.println("Going Left");
    }
    turnLeft();
    lastMove = 1;
  } else {
    if (lastMove == 1) {
      turnLeft();
    } else if (lastMove == 2) {
      forward();
    } else {
      turnRight();
    }
  }
//  if(distanceValue < distThresh || lastMove == 4)
//  {
//    brake();
//    lastMove = 4;
//  }
 }
/*setting pwm of the motor to 255
we can change the speed of rotaion
by chaning pwm input but we are only
using arduino so we are using higest
value to driver the motor  */

void forward(){
  //For Clock wise motion , in_1 = High , in_2 = Low
  digitalWrite(in_1,HIGH) ;
  digitalWrite(in_2,LOW) ;
  digitalWrite(in_3,HIGH) ;
  digitalWrite(in_4,LOW) ;
  analogWrite(pwm,50) ;
}

void backward(){
  //For Clock wise motion , in_1 = High , in_2 = Low
  digitalWrite(in_1,LOW) ;
  digitalWrite(in_2,HIGH) ;
  digitalWrite(in_3,LOW) ;
  digitalWrite(in_4,HIGH) ;
  analogWrite(pwm,125) ;
}

void turnLeft(){
  digitalWrite(in_1,LOW) ;
  digitalWrite(in_2,HIGH) ;
  digitalWrite(in_3,HIGH) ;
  digitalWrite(in_4,LOW) ;
  analogWrite(pwm,50) ;
}

void turnRight(){
  digitalWrite(in_1,HIGH) ;
  digitalWrite(in_2,LOW) ;
  digitalWrite(in_3,LOW) ;
  digitalWrite(in_4,HIGH) ;
  analogWrite(pwm,50) ;
}

void brake(){
  digitalWrite(in_1,HIGH) ;
  digitalWrite(in_2,HIGH) ;
  digitalWrite(in_3,HIGH) ;
  digitalWrite(in_4,HIGH) ;
}

