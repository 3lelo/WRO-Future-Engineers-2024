#include <Servo.h>
Servo myservo;
const byte echo_r = 5;
const byte trig_r = 4;

const byte echo_fl = 9;
const byte trig_fl = 8;

const byte echo_fr = 12;
const byte trig_fr = 13;

const byte echo_l = 6;
const byte trig_l = 7;

const byte motor_f = 52;
const byte motor_b = 53;
const byte motor_s = 10;

const byte servo = 11;
int counter_rotate = 0;
const byte start_Stop = 18;
long long time;

bool finish = true;


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





// Function to determine the direction based on distance measurements
void right_or_left() {
  int right = get_destance(trig_r, echo_r);  // Measure distance on the right
  int left = get_destance(trig_l, echo_l);  // Measure distance on the left
  if (left + right >= 200) {  // If the total distance is greater than or equal to 200
    analogWrite(motor_s, 120);  // Set motor speed to 140
    if (left > right) {
      myservo.write(25);  // Adjust the servo position based on distance
    } else {
      myservo.write(80);  // Adjust the servo position based on distance
    }
    time = millis();  // Record the current time
    while (millis() - time <= 3500) {  // Wait for 3.5 seconds
      corner();  // Call the IR function
    }
    myservo.write(55);  // Set the servo to a default position
    analogWrite(motor_s, 80);  // Set motor speed to 80
    counter_rotate++;  // Increment the rotation counter only if the condition is met
  }
}




  void corner() {
  int fright = get_destance(trig_fr, echo_fr);
  int fleft = get_destance(trig_fl, echo_fl);

  // Check front-right distance
  if (fright < 10 && fright > 0) {
    myservo.write(80);  // Move servo to position 80
    time = millis();
    while (millis() - time <= 1000) {
      analogWrite(motor_s, 100);
      digitalWrite(motor_f, LOW);
      digitalWrite(motor_b, HIGH);
    }
    myservo.write(55);  // Move servo to position 55
    delay(300);
    digitalWrite(motor_b, LOW);
    digitalWrite(motor_f, HIGH);
  }
  // Check front-left distance
  else if (fleft < 10 && fleft > 0) {
    myservo.write(25);  // Move servo to position 25
    time = millis();
    while (millis() - time <= 1000) {
      analogWrite(motor_s, 100);
      digitalWrite(motor_f, LOW);
      digitalWrite(motor_b, HIGH);
    }
    myservo.write(55);  // Move servo to position 55
    delay(300);
    digitalWrite(motor_b, LOW);
    digitalWrite(motor_f, HIGH);
  }
  analogWrite(motor_s, 80);  // Reset motor speed
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
  Serial.begin(9600);
  counter_rotate = 0;
}








void stopProgram() {
    digitalWrite(motor_f, LOW);
    digitalWrite(motor_b, LOW);
    myservo.write(55);
    counter_rotate = 0;
}


void startProgram() {
    digitalWrite(motor_f, HIGH);
    digitalWrite(motor_b, LOW);
    myservo.write(55);
}
void loop() {
    if(counter_rotate < 12 && finish == true){
      startProgram();
      right_or_left();
      corner();
    }
    else{stopProgram(); finish = false;}
}
