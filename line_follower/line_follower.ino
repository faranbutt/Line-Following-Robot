#define IR_SENSOR_RIGHT 6
#define IR_SENSOR_LEFT 12
#define MOTOR_SPEED 99
//Right motor
int enableRightMotor=3;
int rightMotorPin1=9;
int rightMotorPin2=10;

//Left motor
int enableLeftMotor=11;
int leftMotorPin1=7;
int leftMotorPin2=8;

void setup()
{ Serial.begin(9600);
  //The problem with TT gear motors is that, at very low pwm value it does not even rotate.
  //If we increase the PWM value then it rotates faster and our robot is not controlled in that speed and goes out of line.
  //For that we need to increase the frequency of analogWrite.
  //Below line is important to change the frequency of PWM signal on pin D5 and D6
  //Because of this, motor runs in controlled manner (lower speed) at high PWM value.
  //This sets frequecny as 7812.5 hz.
  TCCR0B = TCCR0B & B11111000 | B00000010 ;
  
  // put your setup code here, to run once:
  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  
  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  pinMode(IR_SENSOR_RIGHT, INPUT);
  pinMode(IR_SENSOR_LEFT, INPUT);
  rotateMotor(0,0);   
}


void loop()
{
  
  int rightIRSensorValue = digitalRead(IR_SENSOR_RIGHT);
  int leftIRSensorValue = digitalRead(IR_SENSOR_LEFT);
  Serial.print("Left");
  Serial.println(leftIRSensorValue);
//  delay(1000);
  Serial.print("Right");
  Serial.println(rightIRSensorValue);
  //If none of the sensors detects black line, then go straight
  if (rightIRSensorValue == 0 && leftIRSensorValue == 0)
  {
    Serial.print("Rokaooooo");
//    rotateMotor(MOTOR_SPEED, MOTOR_SPEED);
rotateMotor(0, 0);
  }
  //If right sensor detects black line, then turn right
  else if (rightIRSensorValue == 0 && leftIRSensorValue == 1 )
  {
      rotateMotor(-(MOTOR_SPEED-15), (MOTOR_SPEED-11)); 
      
  }
  //If left sensor detects black line, then turn left  
  else if (rightIRSensorValue == 1 && leftIRSensorValue == 0 )
  {
      rotateMotor((MOTOR_SPEED-11), -(MOTOR_SPEED-15));
       
  } 
  //If both the sensors detect black line, then stop 
  else 
  {
    rotateMotor((MOTOR_SPEED-5), (MOTOR_SPEED-11));
    delay(125);
  }
}


void rotateMotor(int rightMotorSpeed, int leftMotorSpeed)
{
  
  if (rightMotorSpeed < 0)
  {
    digitalWrite(rightMotorPin1,LOW);
    digitalWrite(rightMotorPin2,HIGH);    
  }
  else if (rightMotorSpeed > 0)
  {
    digitalWrite(rightMotorPin1,HIGH);
    digitalWrite(rightMotorPin2,LOW);      
  }
  else
  {
    digitalWrite(rightMotorPin1,LOW);
    digitalWrite(rightMotorPin2,LOW);      
  }

  if (leftMotorSpeed < 0)
  {
    digitalWrite(leftMotorPin1,LOW);
    digitalWrite(leftMotorPin2,HIGH);
  }
  else if (leftMotorSpeed > 0)
  {
    digitalWrite(leftMotorPin1,HIGH);
    digitalWrite(leftMotorPin2,LOW);      
  }
  else 
  {
    digitalWrite(leftMotorPin1,LOW);
    digitalWrite(leftMotorPin2,LOW);      
  }
  analogWrite(enableRightMotor, abs(rightMotorSpeed));
  analogWrite(enableLeftMotor, abs(leftMotorSpeed));
 ///delay(1000);    
}
