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
int blackThresh = 300;  //Threshold for photoresistors
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
  sensorValueL = analogRead(Photo1); // read the values from the photoresistors
  sensorValueC = analogRead(Photo2);
  sensorValueR = analogRead(Photo3); // read the value from the sensor
  //distanceValue = analogRead(Dist);
  Serial.print(analogRead(Photo1));
  Serial.print("\t");
  Serial.print(analogRead(Photo2));
  Serial.print("\t");
  Serial.print(analogRead(Photo3));
  Serial.println();
  //Serial.println(analogRead(Dist));

  if(sensorValueL < blackThresh || lastMove == 3)
  {
    TurnRight();
    lastMove = 3;
  }
  if(sensorValueR < blackThresh || lastMove == 1)
  {
    TurnLeft();
    lastMove = 1;
  }
  if(sensorValueC < blackThresh || lastMove == 2)
  {
    Forward();
    lastMove = 2;
  }
//  if(distanceValue < distThresh || lastMove == 4)
//  {
//    Break();
//    lastMove = 4;
//  }
 }
/*setting pwm of the motor to 255
we can change the speed of rotaion
by chaning pwm input but we are only
using arduino so we are using higest
value to driver the motor  */

void Forward(){
  //For Clock wise motion , in_1 = High , in_2 = Low
  digitalWrite(in_1,HIGH) ;
  digitalWrite(in_2,LOW) ;
  digitalWrite(in_3,HIGH) ;
  digitalWrite(in_4,LOW) ;
  analogWrite(pwm,100) ;
}

void Backward(){
  //For Clock wise motion , in_1 = High , in_2 = Low
  digitalWrite(in_1,LOW) ;
  digitalWrite(in_2,HIGH) ;
  digitalWrite(in_3,LOW) ;
  digitalWrite(in_4,HIGH) ;
  analogWrite(pwm,125) ;
}

void TurnLeft(){
  digitalWrite(in_1,LOW) ;
  digitalWrite(in_2,HIGH) ;
  digitalWrite(in_3,HIGH) ;
  digitalWrite(in_4,LOW) ;
  analogWrite(pwm,100) ;
}

void TurnRight(){
  digitalWrite(in_1,HIGH) ;
  digitalWrite(in_2,LOW) ;
  digitalWrite(in_3,LOW) ;
  digitalWrite(in_4,HIGH) ;
  analogWrite(pwm,100) ;
}

void Break(){
  digitalWrite(in_1,HIGH) ;
  digitalWrite(in_2,HIGH) ;
  digitalWrite(in_3,HIGH) ;
  digitalWrite(in_4,HIGH) ;
}

