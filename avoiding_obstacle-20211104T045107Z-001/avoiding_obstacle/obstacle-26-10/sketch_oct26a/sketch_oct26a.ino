
#include <Servo.h>          //Servo motor library. This is standard library
#include <NewPing.h>        //Ultrasonic sensor function library. You must install this library

//our L298N control pins
const int LeftMotorForward = 11;
const int LeftMotorBackward = 9;
const int RightMotorForward = 6;
const int RightMotorBackward = 3;

//sensor pins
#define trig_pin A1 //analog input 1
#define echo_pin A2 //analog input 2

#define maximum_distance 200
boolean goesForward = false;
int distance = 100;

NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function
Servo servo_motor; //our servo name


void setup(){

  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  
  servo_motor.attach(10); //our servo pin

  servo_motor.write(115);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop(){

  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

  if (distance <= 25){
    moveStop();
    delay(300);
    moveBackward();
    delay(700);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if (distanceRight >= distanceLeft){
      turnRight();
      moveStop();
    }
    else{
      turnLeft();
      moveStop();
    }
  }
  else{
    moveForward(); 
  }
    distance = readPing();
}

int lookRight(){  
  servo_motor.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
}

int lookLeft(){
  servo_motor.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
  delay(100);
}

int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}

void moveStop(){
  
  analogWrite(RightMotorForward, 0);
  analogWrite(LeftMotorForward, 0);
  analogWrite(RightMotorBackward, 0);
  analogWrite(LeftMotorBackward, 0);
}

void moveForward(){

  if(!goesForward){

    goesForward=true;
    
    analogWrite(LeftMotorForward, 150);
    analogWrite(RightMotorForward, 150);
  
    analogWrite(LeftMotorBackward, 0);
    analogWrite(RightMotorBackward, 0); 
  }
}

void moveBackward(){

  goesForward=false;

  analogWrite(LeftMotorBackward, 150);
  analogWrite(RightMotorBackward, 150);
  
  analogWrite(LeftMotorForward, 0);
  analogWrite(RightMotorForward, 0);
  
}

void turnRight(){

  analogWrite(LeftMotorForward, 150);
  analogWrite(RightMotorBackward, 150);
  
  analogWrite(LeftMotorBackward, 0);
  analogWrite(RightMotorForward, 0);
  
  delay(500);
  
  analogWrite(LeftMotorForward, 150);
  analogWrite(RightMotorForward, 150);
  
  analogWrite(LeftMotorBackward, 0);
  analogWrite(RightMotorBackward, 0);
 }

void turnLeft(){

  analogWrite(LeftMotorBackward, 150);
  analogWrite(RightMotorForward, 150);
  
  analogWrite(LeftMotorForward, 0);
  analogWrite(RightMotorBackward, 0);

  delay(500);
  
  analogWrite(LeftMotorForward, 150);
  analogWrite(RightMotorForward, 150);
  
  analogWrite(LeftMotorBackward, 0);
  analogWrite(RightMotorBackward, 0);
}

 
