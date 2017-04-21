#include <SoftwareSerial.h>

SoftwareSerial BT(0, 0);//tx rx

int LM_direction = 8; //左輪方向 
int LM_speed = 6; //左輪速度 
int RM_speed = 5; //右輪速度 
int RM_direction = 7; //右輪方向

//Sensors:
int D1 = A0;
int D2 = A1;
int D3 = A2;
int D4 = A3;
int D5 = A4;

int sensorValue = 0; // 儲存感測值

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

  digitalWrite(RM_direction, LOW);
  digitalWrite(LM_direction, LOW);
  analogWrite(RM_speed, cardirection);
  analogWrite(LM_speed, cardirection);
  
}

void forward() { //D7 = 1, D8 = 1
  
  digitalWrite(RM_direction, HIGH);
  digitalWrite(LM_direction, HIGH);
  analogWrite(RM_speed, fspeed);
  analogWrite(LM_speed, fspeed);
  
}

void backward() { //D7 = 0, D8 = 0

  digitalWrite(RM_direction, LOW);
  digitalWrite(LM_direction, LOW);
  analogWrite(RM_speed, 255);
  analogWrite(LM_speed, 255);

}

void turnLeft() { // D7 = 1, D8 = 0

  digitalWrite(RM_direction, HIGH);
  digitalWrite(LM_direction, LOW);
  analogWrite(RM_speed, fspeed);
  analogWrite(LM_speed, fspeed);
  
}

void turnRight() { //D7 = 0, D8 = 1

  digitalWrite(RM_direction, LOW);
  digitalWrite(LM_direction, HIGH);
  analogWrite(RM_speed, fspeed);
  analogWrite(LM_speed, fspeed);
  
}

void loop(){
   
  distance = ping() / 58;
  BT.write((byte)distance);
  Serial.print(distance);
  Serial.print(" cm");
  Serial.println();
  delay(1000);
  
  if(distance <= 20){
    stopCar();
    Serial.print("Danger!! Stop the Car!\n");
  }
  
  if( BT.available() > 0) {
    
    var = BT.read();

    switch(var) {
      case 102: //f
       
        forward(); 
             
      break;
      
      case 98: //b
      
        backward();
 
      break;
      
      case 115: //s
      
        stopCar();
        
      break;
      
      case 114: //r
      
        turnRight();
    
      break;
      
      case 108: //l
      
        turnLeft();

      break;
      
      default:
      
      break;
      
    }
  } 

  //-------Line Follow--------
  Serial.println("-------------");
  
  sensorValue = analogRead(D1); 
  Serial.print("D1 = "); 
  Serial.println(sensorValue, OCT); 
  
  sensorValue = analogRead(D2); 
  Serial.print("D2 = "); 
  Serial.println(sensorValue, OCT); 
  
  sensorValue = analogRead(D3); 
  Serial.print("D3 = "); 
  Serial.println(sensorValue, OCT); 
  
  sensorValue = analogRead(D4); 
  Serial.print("D4 = "); 
  Serial.println(sensorValue, OCT);
   
  sensorValue = analogRead(D5); 
  Serial.print("D5 = "); 
  Serial.println(sensorValue, OCT); 
  
  Serial.println("-------------"); 
  
}
