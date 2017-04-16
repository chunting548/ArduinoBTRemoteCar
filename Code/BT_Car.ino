#include <SoftwareSerial.h>

SoftwareSerial BT(0, 0);//tx rx

int LM_direction = 8; //左輪方向 
int LM_speed = 6; //左輪速度 
int RM_speed = 5; //右輪速度 
int RM_direction = 7; //右輪方向

const byte trigPin = 2;
const byte echoPin = 3;

int fspeed = 0;
boolean cardirection = 1;

unsigned long distance;

unsigned long var;

unsigned long ping(){
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH);
  
}

void setup(){
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(RM_direction,OUTPUT); //D7
  pinMode(LM_direction,OUTPUT); //D8
  pinMode(RM_speed,OUTPUT); 
  pinMode(LM_speed,OUTPUT);
  
  Serial.begin(9600);
  BT.begin(9600);
  Serial.println("Bluetooth is READY!");
  
}

void stopCar() { // 馬達停止

  analogWrite(RM_speed, fspeed); // 馬達 A 的 PWM 輸出
  analogWrite(LM_speed, fspeed); // 馬達 B 的 PWM 輸出
  
}

void forward() { //D7 = 1, D8 = 1
  
  digitalWrite(RM_direction, HIGH);
  digitalWrite(LM_direction, HIGH);
  analogWrite(RM_speed, 200);
  analogWrite(LM_speed, 200);
  
}

void backward() { //D7 = 0, D8 = 0

  digitalWrite(RM_direction, LOW);
  digitalWrite(LM_direction, LOW);
  analogWrite(RM_speed, 200);
  analogWrite(LM_speed, 200);

}

void turnLeft() { // D7 = 1, D8 = 0

  digitalWrite(RM_direction, HIGH);
  digitalWrite(LM_direction, LOW);
  analogWrite(RM_speed, 200);
  analogWrite(LM_speed, 200);
  
}

void turnRight() { //D7 = 0, D8 = 1

  digitalWrite(RM_direction, LOW);
  digitalWrite(LM_direction, HIGH);
  analogWrite(RM_speed, 200);
  analogWrite(LM_speed, 200);
  
}

void loop(){
   
  distance = ping() / 58;
  BT.write((byte)distance);
  Serial.print(distance);
  Serial.print(" cm");
  Serial.println();
  delay(1000);
  
  if(distance <= 15){
    stopCar();
    Serial.print("Danger!! Stop the Car!\n");
  }
  
  if( BT.available() > 0) {
    
    var = BT.read();
    
    switch(var) {
      case 102: //F, 0
        forward();
      break;
      
      case 98: //B, 1
        backward();
      break;
      
      case 115: //S, 2
        stopCar();
      break;
      
      case 114: //R, 3
        turnRight();
      break;
      
      case 108:
        turnLeft(); //L, 4
      break;
      
      default:
      break;
    }
  }
}
