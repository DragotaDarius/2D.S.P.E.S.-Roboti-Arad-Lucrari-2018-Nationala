#include <QTRSensors.h>
#include <Servo.h>

#define Kp 0.3 // experiment to determine this, start by something small that just makes your bot follow the line at a slow speed
#define Kd 2.2 // experiment to determine this, slowly increase the speeds and adjust this value. ( Note: Kp < Kd) 
#define rightMaxSpeed 150  // max speed of the robot
#define leftMaxSpeed 150 // max speed of the robot
#define rightBaseSpeed 110 // this is the speed at which the motors should spin when the robot is perfectly on the line
#define leftBaseSpeed 110  // this is the speed at which the motors should spin when the robot is perfectly on the line
#define NUM_SENSORS  6
#define TIMEOUT       2500
#define EMITTER_PIN   2

#define rightMotor1 3
#define rightMotor2 4
#define rightMotorPWM 5
#define leftMotor1 12
#define leftMotor2 13
#define leftMotorPWM 11
#define motorPower 8
int lastError = 0;

bool Collecting = false;
int currentColor = 0;

#define rosu 1
#define galben 2
#define albastru 3

int senzor10cm = 30;
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;
int S2 = 9;
int S3 = 8;
int sout = 7;



Servo servo;
QTRSensorsRC qtrrc((unsigned char[]) {14,15,16,17,18,19} ,NUM_SENSORS, TIMEOUT, EMITTER_PIN); // sensor connected through analog pins A0 - A5 i.e. digital pins 14-19

unsigned int sensorValues[NUM_SENSORS];

void setup(){
  servo.attach(10);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(rightMotorPWM, OUTPUT);
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(leftMotorPWM, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sout, INPUT);
  servo.write(1);
  delay(500);
  
  int i;
for (int i = 0; i < 100; i++)
   qtrrc.calibrate();   
   delay(20);
   delay(2000);
  } 

void loop(){

}
void Line(){
  unsigned int sensors[6];
  int position = qtrrc.readLine(sensors); // get calibrated readings along with the line position, refer to the QTR Sensors Arduino Library for more details on line position.
  int error = position - 2500;


  int motorSpeed = Kp * error + Kd * (error - lastError);
  lastError = error;

  int rightMotorSpeed = rightBaseSpeed + motorSpeed;
  int leftMotorSpeed = leftBaseSpeed - motorSpeed;
  
  
  if (rightMotorSpeed > rightMaxSpeed ) rightMotorSpeed = rightMaxSpeed; // prevent the motor from going beyond max speed
  if (leftMotorSpeed > leftMaxSpeed ) leftMotorSpeed = leftMaxSpeed; // prevent the motor from going beyond max speed
  if (rightMotorSpeed < 0) rightMotorSpeed = 0; // keep the motor speed positive
  if (leftMotorSpeed < 0) leftMotorSpeed = 0; // keep the motor speed positive
    {
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
  analogWrite(rightMotorPWM, rightMotorSpeed);
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  analogWrite(leftMotorPWM, leftMotorSpeed);}
  }

void DeployProcedure()
{

  switch (currentColor)
  {
  case rosu:
    delay(2000);
    servo.write(1);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    analogWrite(rightMotorPWM, 200);   
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    analogWrite(leftMotorPWM, 90);
    delay(1000);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    analogWrite(rightMotorPWM, 200);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
    analogWrite(leftMotorPWM, 0);
    delay(400);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
    analogWrite(leftMotorPWM, 150);
    delay(300);
  
  case galben:
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, HIGH);
    analogWrite(rightMotorPWM, 100);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
    analogWrite(leftMotorPWM, 100);
    servo.write(1);
     digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    analogWrite(rightMotorPWM, 200);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
    analogWrite(leftMotorPWM, 0);
    delay(300);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, HIGH);
    analogWrite(rightMotorPWM, 100);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
    analogWrite(leftMotorPWM, 160);
    break;
    
   case albastru:
    delay(2000);
    servo.write(3);
    delay(700);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, HIGH);
    analogWrite(rightMotorPWM, 100);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
    analogWrite(leftMotorPWM, 100);
    delay(1600);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, HIGH);
    analogWrite(rightMotorPWM, 150);
    delay(550);
    boolean nott = true;
    delay(400);
    while(nott)
    {
      delay(30);
      unsigned int sensors[8];
      
      qtrrc.read(sensors);
    }
    break;
  }
}
int Culoare(int r, int g, int b){
    if (b > g && b > r)
    {
    Serial.println("Blue");
        return albastru;

    }
    
    if(g < 0){
    Serial.println("Red");
        return rosu;
    }

  Serial.println("Yello");
return galben;
}
