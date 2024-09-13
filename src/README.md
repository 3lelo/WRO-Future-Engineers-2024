Car's Controling codes
====

This directory contains the codes that we used to control the car and the steering wheel by detecting the red and green colors through the camera connected to the Raspberry Pi. When the car approaches this color, the Raspberry Pi sends a message to the Arduino and the Arduino takes the appropriate action.

## This's the code for the open challenge in C language

```C
#include <Servo.h>

// Servo object
Servo myservo;

// Define ultrasonic sensor pins
const byte echo_r = 13;
const byte trig_r = 12;
const byte echo_l = 9;
const byte trig_l = 8;
const byte echo_f = 5;
const byte trig_f = 4;
const byte echo_b = 3;
const byte trig_b = 2;

// Define motor and servo control pins
const byte motor_f = 52; // Forward motor
const byte motor_b = 53; // Backward motor
const byte motor_s = 10; // Speed control
const byte servo = 11;   // Servo motor control pin

// Global variables
int cr = 0;   // Counter for path correction
long time;    // Variable to store current time

// Function to calculate distance using ultrasonic sensor
int get_distance(int pin_Trig, int pin_Echo) {
  long Time;
  int Distance;
  
  // Triggering the sensor to send an ultrasonic pulse
  digitalWrite(pin_Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(pin_Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin_Trig, LOW);

  // Measure the duration of the echo pulse
  Time = pulseIn(pin_Echo, HIGH);
  Time = Time / 2;  // Time for the pulse to travel to the object and back
  Distance = Time * 0.034;  // Convert time to distance (cm)
  
  return Distance;
}

// Function to correct the path of the robot
void correct_path() {
  int left = get_distance(trig_l, echo_l);   // Get left sensor distance
  int right = get_distance(trig_r, echo_r);  // Get right sensor distance
  int f = get_distance(trig_f, echo_f);      // Get front sensor distance
  
  // If obstacle is detected on the left side
  if (left <= 10 && left != 0) {
    myservo.write(25);   // Turn servo to the left
    digitalWrite(motor_b, HIGH);  // Move backward
    digitalWrite(motor_f, LOW);
    
    // Move backward for 1400 ms or until obstacle is cleared
    time = millis();
    while (millis() - time <= 1400) {
      int b = get_distance(trig_b, echo_b);
      if (b < 10 && b != 0) break;  // Stop if obstacle is detected behind
    }
    
    myservo.write(55);  // Reset servo to center
    digitalWrite(motor_b, LOW);
    digitalWrite(motor_f, HIGH);  // Move forward
  }
  // If obstacle is detected on the right side
  else if (right <= 10 && right != 0) {
    digitalWrite(motor_b, HIGH);
    digitalWrite(motor_f, LOW);
    myservo.write(80);   // Turn servo to the right
    
    time = millis();
    while (millis() - time <= 1400) {
      int b = get_distance(trig_b, echo_b);
      if (b < 10 && b != 0) break;
    }
    
    myservo.write(55);   // Reset servo to center
    digitalWrite(motor_b, LOW);
    digitalWrite(motor_f, HIGH);  // Move forward
  }
  // If obstacle is detected in front
  else if (f <= 10) {
    if (right == 0) {
      digitalWrite(motor_b, HIGH);
      digitalWrite(motor_f, LOW);
      myservo.write(80);  // Turn to right
      time = millis();
      while (millis() - time <= 1400) {
        int b = get_distance(trig_b, echo_b);
        if (b < 10 && b != 0) break;
      }
      myservo.write(55);
      digitalWrite(motor_b, LOW);
      digitalWrite(motor_f, HIGH);
    }
    else if (left == 0) {
      myservo.write(25);  // Turn to left
      digitalWrite(motor_b, HIGH);
      digitalWrite(motor_f, LOW);
      time = millis();
      while (millis() - time <= 1400) {
        int b = get_distance(trig_b, echo_b);
        if (b < 10 && b != 0) break;
      }
      myservo.write(55);
      digitalWrite(motor_b, LOW);
      digitalWrite(motor_f, HIGH);
    } else {
      // Move backward if both sides are blocked
      digitalWrite(motor_b, HIGH);
      digitalWrite(motor_f, LOW);
      time = millis();
      while (millis() - time <= 1400) {
        int b = get_distance(trig_b, echo_b);
        if (b < 10 && b != 0) break;
      }
      myservo.write(55);
      digitalWrite(motor_b, LOW);
      digitalWrite(motor_f, HIGH);
    }
  }
}

// Function to avoid obstacles when left or right sensors detect close objects
void avoid_obstacles() {
  int left1 = get_distance(trig_l, echo_l);
  int right1 = get_distance(trig_r, echo_r);
  
  if (left1 == 0 || right1 == 0) {
    int left = get_distance(trig_l, echo_l);
    int right = get_distance(trig_r, echo_r);
    
    if (left == 0 || right <= 25) {
      myservo.write(25);  // Turn left slightly
      time = millis();
      while (millis() - time <= 500) {}
      myservo.write(55);  // Reset to center
    } 
    else if (right == 0 || left <= 25) {
      myservo.write(80);  // Turn right slightly
      time = millis();
      while (millis() - time <= 500) {}
      myservo.write(55);  // Reset to center
    }
  }
}

// Function to decide between left or right based on distances
void left_right(int left, int right) {
  analogWrite(motor_s, 150);  // Increase speed temporarily

  if (left > right) {
    myservo.write(25);  // Turn left
    time = millis();
    while (millis() - time <= 2000) {
      delay(200);  // Delay for stability
      int f = get_distance(trig_f, echo_f);
      int left = get_distance(trig_l, echo_l);
      int right = get_distance(trig_r, echo_r);
      if (left != 0 && right != 0 && f >= 170) break;  // Break if front is clear
      correct_path();
    }
    myservo.write(55);
  } else {
    myservo.write(80);  // Turn right
    time = millis();
    while (millis() - time <= 2000) {
      delay(200);
      int f = get_distance(trig_f, echo_f);
      int left = get_distance(trig_l, echo_l);
      int right = get_distance(trig_r, echo_r);
      if (left != 0 && right != 0 && f >= 170) break;  // Break if front is clear
      correct_path();
    }
    myservo.write(55);
  }
  
  analogWrite(motor_s, 80);  // Reset speed
  time = millis();
  while (millis() - time <= 2000) { 
    correct_path(); 
    avoid_obstacles();
  }
}

// Function to start the robot's movement
void startProgram() {
  digitalWrite(motor_f, HIGH);  // Move forward
  digitalWrite(motor_b, LOW);
  myservo.write(55);  // Set servo to center
  analogWrite(motor_s, 80);  // Set speed
}

// Function to stop the robot's movement
void stopProgram() {
  digitalWrite(motor_f, LOW);   // Stop moving
  digitalWrite(motor_b, LOW);
  myservo.write(55);   // Reset servo
}

void setup() {
  // Set motor pins as output
  pinMode(motor_f, OUTPUT);
  pinMode(motor_b, OUTPUT);
  pinMode(motor_s, OUTPUT);
  analogWrite(motor_s, 80);   // Set initial speed
  
  // Attach servo to pin and set to center
  myservo.attach(servo);
  myservo.write(55);
  
  // Set ultrasonic sensor pins
  pinMode(trig_l, OUTPUT);
  pinMode(echo_l, INPUT);
  pinMode(trig_r, OUTPUT);
  pinMode(echo_r, INPUT);
  pinMode(trig_f, OUTPUT);
  pinMode(echo_f, INPUT); 
  pinMode(trig_b, OUTPUT);
  pinMode(echo_b, INPUT);
  
  // Initialize serial communication
  Serial.begin(9600);
  cr = 0;
}

void loop() {
  int left = get_distance(trig_l, echo_l);
  int right = get_distance(trig_r, echo_r);
  
  // If combined distance of left and right sensors is large, navigate
  if (left + right >= 150) {
    left_right(left, right);
    cr++;
  }

  // Perform actions based on counter value
  if (cr < 12) {
    startProgram();
    avoid_obstacles();
    correct_path();
  } else if (cr == 11) {
    correct_path();
    avoid_obstacles();
    int left = get_distance(trig_l, echo_l);
    int right = get_distance(trig_r, echo_r);
    if (left + right >= 150) {
      left_right(left, right);
      cr++;
    }
  } else {
    stopProgram();  // Stop if task is complete
  }
}
```
