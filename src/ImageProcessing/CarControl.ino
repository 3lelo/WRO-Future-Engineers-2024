#include <Servo.h>
Servo myservo;
const byte echo_r = 5;
const byte trig_r = 4;
const byte echo_l = 6;
const byte trig_l = 7;


const byte echo_f = 9;
const byte trig_f = 8;
const byte echo_b = 12;
const byte trig_b = 13;

const byte motor_f = 52;
const byte motor_b = 53;
const byte motor_s = 10;
String c = "none";
const byte servo = 11;
int cr = 0;
long long time;

int get_destance(int pin_Trig, int pin_Echo){
  long Time;
  int Distance;
  digitalWrite(pin_Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(pin_Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin_Trig, LOW);
  Time = pulseIn(pin_Echo, HIGH);
  Time = Time / 2;
  Distance = Time * 0.034;
  return Distance;
}




void b3d(){
  int left = get_destance(trig_l,echo_l);
  int right = get_destance(trig_r,echo_r);
  if(left <= 5){
    myservo.write(80);
    time = millis();
    while(millis() - time <= 500){}
    myservo.write(55);
    }
    else  if(right <= 5){
    myservo.write(25);
    time = millis();
    while(millis() - time <= 500){}
    myservo.write(55);
    }
  }






  void alwan(){
    if (Serial.available() > 0){
     String k=Serial.readStringUntil("\n");
     if(k == "Red Left" || k == "Red Center" || k == "Red Right"){
      c = "red";
      if(k == "Red Right"){
        myservo.write(25);
        digitalWrite(motor_b, HIGH);
        digitalWrite(motor_f, LOW);
        time = millis();
        while(millis() - time <= 1000){b3d();}
        myservo.write(55);
        digitalWrite(motor_f, HIGH);
        digitalWrite(motor_b, LOW);
        }

        else if(k == "Red Center"){
          k=Serial.readStringUntil("\n");
          myservo.write(80);
          time= millis();
          while(millis() - time <= 2000){
            k=Serial.readStringUntil("\n");
            if(k != "Red Center"){break;}
            }
         myservo.write(55);
          }
      }
    

      
     else if(k == "Green Left" || k == "Green Center" || k == "Green Right"){
      c = "green";
        if(k == "Green Left"){
        myservo.write(80);
        digitalWrite(motor_b, HIGH);
        digitalWrite(motor_f, LOW);
        time = millis();
        while(millis() - time <= 1000){b3d();}
        myservo.write(55);
        digitalWrite(motor_f, HIGH);
        digitalWrite(motor_b, LOW);
        }

        
        else if(k == "Green Center"){
          k=Serial.readStringUntil("\n");
          myservo.write(25);
          time= millis();
          while(millis() - time <= 2000){
            k=Serial.readStringUntil("\n");
            if(k != "Green Center"){break;}
            }
         myservo.write(55);
          }
      }
     }
  }


void atjah(){
  int left = get_destance(trig_l,echo_l);
  int right = get_destance(trig_r,echo_r);
  if(left+right >= 140){
    if(c = "red" && cr == 7){
      if(left > right){
        if(right > 30){
        time = millis();
        while(millis() - time <= 3000){
          int f = get_destance(trig_f,echo_f);
          if(f < 10){break;}
          }
        digitalWrite(motor_b, HIGH);
        digitalWrite(motor_f, LOW);
        myservo.write(80);
        time = millis();
        while(millis() - time <= 1500){
          int b = get_destance(trig_b,echo_b);
          if(b < 10){break;}
          }
        digitalWrite(motor_f, HIGH);
        digitalWrite(motor_b, LOW);
        myservo.write(25);
          }
        else{
        time = millis();
        while(millis() - time <= 3000){
          int f = get_destance(trig_f,echo_f);
          if(f < 10){break;}
          }
        digitalWrite(motor_b, HIGH);
        digitalWrite(motor_f, LOW);
        myservo.write(25);
        time = millis();
        while(millis() - time <= 1500){
          int b = get_destance(trig_b,echo_b);
          if(b < 10){break;}
          }
        digitalWrite(motor_f, HIGH);
        digitalWrite(motor_b, LOW);
        myservo.write(80);
            }
        }
      else{
        if(right > 30){
        time = millis();
        while(millis() - time <= 3000){
          int f = get_destance(trig_f,echo_f);
          if(f < 10){break;}
          }
        digitalWrite(motor_b, HIGH);
        digitalWrite(motor_f, LOW);
        myservo.write(25);
        time = millis();
        while(millis() - time <= 1500){
          int b = get_destance(trig_b,echo_b);
          if(b < 10){break;}
          }
        digitalWrite(motor_f, HIGH);
        digitalWrite(motor_b, LOW);
        myservo.write(80);
          }
        else{
        time = millis();
        while(millis() - time <= 3000){
          int f = get_destance(trig_f,echo_f);
          if(f < 10){break;}
          }
        digitalWrite(motor_b, HIGH);
        digitalWrite(motor_f, LOW);
        myservo.write(80);
        time = millis();
        while(millis() - time <= 1500){
          int b = get_destance(trig_b,echo_b);
          if(b < 10){break;}
          }
        digitalWrite(motor_f, HIGH);
        digitalWrite(motor_b, LOW);
        myservo.write(25);
            }
        }
      }

    
    else if(left > right){
      if(right > 30){
        time = millis();
        while(millis() - time <= 3000){
          int f = get_destance(trig_f,echo_f);
          if(f < 10){break;}
          }
        digitalWrite(motor_b, HIGH);
        digitalWrite(motor_f, LOW);
        myservo.write(80);
        time = millis();
        while(millis() - time <= 1500){
          int b = get_destance(trig_b,echo_b);
          if(b < 10){break;}
          }
        digitalWrite(motor_f, HIGH);
        digitalWrite(motor_b, LOW);
        myservo.write(55);
        }
        else{
          myservo.write(25);
          time = millis();
          while(millis() - time <= 2000){alwan();}
          myservo.write(55);
          }
      }







      else {
      if(left > 30){
        time = millis();
        while(millis() - time <= 3000){
          int f = get_destance(trig_f,echo_f);
          if(f < 10){break;}
          }
        digitalWrite(motor_b, HIGH);
        digitalWrite(motor_f, LOW);
        myservo.write(25);
        time = millis();
        while(millis() - time <= 1500){
          int b = get_destance(trig_b,echo_b);
          if(b < 10){break;}
          }
        digitalWrite(motor_f, HIGH);
        digitalWrite(motor_b, LOW);
        myservo.write(55);
        }

        
        else{
          myservo.write(80);
          time = millis();
          while(millis() - time <= 2000){alwan();}
          myservo.write(55);
          }
      }
      cr++;
      c = "none";
  }

    
  }
void startProgram() {
    digitalWrite(motor_f, HIGH);
    digitalWrite(motor_b, LOW);
    myservo.write(55);
}
void stopProgram() {
    digitalWrite(motor_f, LOW);
    digitalWrite(motor_b, LOW);
    myservo.write(55);
    cr = 0;
    c = "none";
}



void setup() {
  pinMode(motor_f, OUTPUT);
  pinMode(motor_b, OUTPUT);
  pinMode(motor_s, OUTPUT);
  analogWrite(motor_s, 80);
  myservo.attach(servo);
  myservo.write(55);
  pinMode(trig_l, OUTPUT);
  pinMode(echo_l, INPUT);
  pinMode(trig_r, OUTPUT);
  pinMode(echo_r, INPUT);
  pinMode(trig_f, OUTPUT);
  pinMode(echo_f, INPUT);
  pinMode(trig_b, OUTPUT);
  pinMode(echo_b, INPUT);
  Serial.begin(9600);
  cr = 0;
  c = "none";
}

void loop() {
  if(cr < 12){
    startProgram();
    b3d();
    atjah();
    alwan();
    }
  else{
    stopProgram();
    }
}
