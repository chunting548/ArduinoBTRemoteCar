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

long ping() { // 超音波感測程式

  digitalWrite(TrigPin, HIGH); // 觸發腳設定成高電位
  delayMicroseconds(5); // 持續 5 微秒
  digitalWrite(TrigPin, LOW); // 觸發腳設定成低電位
  return pulseIn(EchoPin, HIGH); // 測量高電位的持續時間（μs）

  
}

void stopCar() { // 馬達停止
  analogWrite(EA, 0); // 馬達 A 的 PWM 輸出
  analogWrite(EB, 0); // 馬達 B 的 PWM 輸出
}

void forward() { //D7 = 1, D8 = 1
  
  digitalWrite(RM_direction,cardirection);
  digitalWrite(LM_direction,cardirection);
  analogWrite(RM_speed,fspeed);
  analogWrite(LM_speed,fspeed);
  
}

void backward() { //D7 = 0, D8 = 0

  digitalWrite(RM_direction,LOW);
  digitalWrite(LM_direction,LOW);
  analogWrite(RM_speed,fspeed);
  analogWrite(LM_speed,fspeed);

  
}

void turnLeft() { // D7 = 1, D8 = 0
  digitalWrite(RM_direction,cardirection);
  digitalWrite(LM_direction,LOW);
  analogWrite(RM_speed,fspeed);
  analogWrite(LM_speed,fspeed);
}

void turnRight() { //D7 = 0, D8 = 1
  digitalWrite(RM_direction,LOW);
  digitalWrite(LM_direction,cardirection);
  analogWrite(RM_speed,fspeed);
  analogWrite(LM_speed,fspeed);
}

void loop(){
  
  if( BT.avaviable() ){
    val = BT.read();
    swtch(var){
      case '102':
        forward();
      break;
      
      case '98':
        backward();
      break;
      
      case '115':
        stopCar();
      break;
      
      case '114':
        turnRight();
      break;
      
      case '108':
        turnRight();
      break;
      
      default:
      break;
    }
  }
}
