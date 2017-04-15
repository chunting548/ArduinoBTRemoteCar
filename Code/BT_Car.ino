#include <SoftwareSerial.h>

SoftwareSerial BT(0, 0);//tx rx

int LM_direction = 8; //左輪方向 
int LM_speed = 6; //左輪速度 
int RM_speed = 5; //右輪速度 
int RM_direction = 7; //右輪方向

int fspeed = 0;
boolean cardirection = 1;

unsigned long var;

void setup(){
  
  pinMode(RM_direction,OUTPUT); //D7
  pinMode(LM_direction,OUTPUT); //D8
  pinMode(RM_speed,OUTPUT); 
  pinMode(LM_speed,OUTPUT);

  BT.begin(9600);
  Serial.println("Bluetooth is READY!");
  
}

void stopCar() { // 馬達停止

  analogWrite(RM_speed, fspeed); // 馬達 A 的 PWM 輸出
  analogWrite(LM_speed, fspeed); // 馬達 B 的 PWM 輸出
  
}

void forward() { //D7 = 1, D8 = 1
  
  digitalWrite(RM_direction, cardirection);
  digitalWrite(LM_direction, cardirection);
  analogWrite(RM_speed, fspeed);
  analogWrite(LM_speed, fspeed);
  
}

void backward() { //D7 = 0, D8 = 0

  digitalWrite(RM_direction, LOW);
  digitalWrite(LM_direction, LOW);
  analogWrite(RM_speed, 200);
  analogWrite(LM_speed, 200);

}

void turnLeft() { // D7 = 1, D8 = 0

  digitalWrite(RM_direction, cardirection);
  digitalWrite(LM_direction, LOW);
  analogWrite(RM_speed, fspeed);
  analogWrite(LM_speed, fspeed);
  
}

void turnRight() { //D7 = 0, D8 = 1

  digitalWrite(RM_direction, LOW);
  digitalWrite(LM_direction, cardirection);
  analogWrite(RM_speed, fspeed);
  analogWrite(LM_speed, fspeed);
  
}

void loop(){
  
  if( BT.available() > 0) {
    
    var = BT.read();
    
    switch(var) {
      case 70: //F
        forward();
      break;
      
      case 66: //B
        backward();
      break;
      
      case 83: //S
        stopCar();
      break;
      
      case 82: //R
        turnRight();
      break;
      
      case 76:
        turnLeft(); //L
      break;
      
      default:
      break;
    }
  }
}
