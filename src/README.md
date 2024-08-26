Car's Controling codes
====

This directory contains the codes that we used to control the car and the steering wheel by detecting the red and green colors through the camera connected to the Raspberry Pi. When the car approaches this color, the Raspberry Pi sends a message to the Arduino and the Arduino takes the appropriate action.

## This's the code for the open challenge
```py
#include <Servo.h>  // Include the Servo library for controlling the servo motor

Servo myservo;  // Create a servo object to control the servo motor

// Ultrasonic sensor pins for various directions
const byte echo_r = 5;
const byte trig_r = 4;

const byte echo_l = 6;
const byte trig_l = 7;

const byte echo_fl = 9;
const byte trig_fl = 8;

const byte echo_fr = 12;
const byte trig_fr = 13;

//const byte echo_b = 3;  // Uncomment if you want to use the back sensor
//const byte trig_b = 2;  // Uncomment if you want to use the back sensor

// Motor control pins
const byte motor_f = 52;  // Motor forward pin
const byte motor_b = 53;  // Motor backward pin
const byte motor_s = 10;  // Motor speed control pin (PWM)

const byte servo = 11;  // Servo control pin
int counter_rotate = 0;  // Counter for rotations
const byte start_Stop = 18;  // Start/Stop button pin
long long time;  // Variable to keep track of time

bool finish = true;  // Flag to determine if the program should continue running

// Function to calculate distance using ultrasonic sensors
int get_destance(int pin_Trig, int pin_Echo) {
  long Time;
  int Distance;
  digitalWrite(pin_Trig, LOW);  // Ensure the trigger pin is low
  delayMicroseconds(2);  // Wait for 2 microseconds
  digitalWrite(pin_Trig, HIGH);  // Set the trigger pin high
  delayMicroseconds(10);  // Wait for 10 microseconds
  digitalWrite(pin_Trig, LOW);  // Set the trigger pin low again
  Time = pulseIn(pin_Echo, HIGH);  // Measure the time for the echo to return
  Time = Time / 2;  // Divide the time by 2 to get the one-way distance
  Distance = Time * 0.034;  // Convert time to distance (cm)
  return Distance;  // Return the calculated distance
}

// Function to determine the direction based on distance measurements
void right_or_left() {
  int right = get_destance(trig_r, echo_r);  // Measure distance on the right
  int left = get_destance(trig_l, echo_l);  // Measure distance on the left
  if (left + right >= 200) {  // If the total distance is greater than or equal to 200
    analogWrite(motor_s, 120);  // Set motor speed to 120
    if (left > right) {
      myservo.write(25);  // Adjust the servo position to 25 if left distance is greater
    } else {
      myservo.write(80);  // Adjust the servo position to 80 if right distance is greater
    }
    time = millis();  // Record the current time
    while (millis() - time <= 3500) {  // Wait for 3.5 seconds
      corner();  // Call the corner function to handle corners
    }
    myservo.write(55);  // Set the servo to a default position
    analogWrite(motor_s, 80);  // Set motor speed to 80
    counter_rotate++;  // Increment the rotation counter only if the condition is met
  }
}

// Function to handle corner detection and turning
void corner() {
  int fright = get_destance(trig_fr, echo_fr);  // Measure front-right distance
  int fleft = get_destance(trig_fl, echo_fl);  // Measure front-left distance

  // Check front-right distance
  if (fright < 10 && fright > 0) {
    myservo.write(80);  // Move servo to position 80
    time = millis();  // Record the current time
    while (millis() - time <= 1000) {  // Wait for 1 second
      analogWrite(motor_s, 100);  // Set motor speed to 100
      digitalWrite(motor_f, LOW);  // Stop forward motor
      digitalWrite(motor_b, HIGH);  // Start backward motor
    }
    myservo.write(55);  // Move servo to position 55
    delay(300);  // Wait for 300 milliseconds
    digitalWrite(motor_b, LOW);  // Stop backward motor
    digitalWrite(motor_f, HIGH);  // Start forward motor
  }
  // Check front-left distance
  else if (fleft < 10 && fleft > 0) {
    myservo.write(25);  // Move servo to position 25
    time = millis();  // Record the current time
    while (millis() - time <= 1000) {  // Wait for 1 second
      analogWrite(motor_s, 100);  // Set motor speed to 100
      digitalWrite(motor_f, LOW);  // Stop forward motor
      digitalWrite(motor_b, HIGH);  // Start backward motor
    }
    myservo.write(55);  // Move servo to position 55
    delay(300);  // Wait for 300 milliseconds
    digitalWrite(motor_b, LOW);  // Stop backward motor
    digitalWrite(motor_f, HIGH);  // Start forward motor
  }
  analogWrite(motor_s, 80);  // Reset motor speed to 80
}

// Function to initialize pins and settings
void setup() {
  pinMode(motor_f, OUTPUT);  // Set motor forward pin as output
  pinMode(motor_b, OUTPUT);  // Set motor backward pin as output
  pinMode(motor_s, OUTPUT);  // Set motor speed pin as output
  analogWrite(motor_s, 80);  // Set initial motor speed
  myservo.attach(servo);  // Attach the servo to the control pin
  myservo.write(55);  // Set the servo to a default position
  pinMode(trig_l, OUTPUT);  // Set left trigger pin as output
  pinMode(echo_l, INPUT);  // Set left echo pin as input
  pinMode(trig_r, OUTPUT);  // Set right trigger pin as output
  pinMode(echo_r, INPUT);  // Set right echo pin as input
  pinMode(trig_fl, OUTPUT);  // Set front-left trigger pin as output
  pinMode(echo_fl, INPUT);  // Set front-left echo pin as input
  pinMode(trig_fr, OUTPUT);  // Set front-right trigger pin as output
  pinMode(echo_fr, INPUT);  // Set front-right echo pin as input
  //pinMode(trig_b, OUTPUT);  // Uncomment if using back trigger pin
  //pinMode(echo_b, INPUT);  // Uncomment if using back echo pin
  Serial.begin(9600);  // Start serial communication at 9600 baud
  counter_rotate = 0;  // Initialize rotation counter to 0
}

// Function to stop the program and reset settings
void stopProgram() {
    digitalWrite(motor_f, LOW);  // Stop forward motor
    digitalWrite(motor_b, LOW);  // Stop backward motor
    myservo.write(55);  // Set servo to default position
    counter_rotate = 0;  // Reset rotation counter
}

// Function to start the program and initialize settings
void startProgram() {
    digitalWrite(motor_f, HIGH);  // Start forward motor
    digitalWrite(motor_b, LOW);  // Stop backward motor
    myservo.write(55);  // Set servo to default position
}

// Main loop function
void loop() {
    if(counter_rotate < 12 && finish == true){  // Check if rotations are less than 12 and finish flag is true
      startProgram();  // Start the program
      right_or_left();  // Determine direction
      corner();  // Handle corners
    }
    else{
        stopProgram();  // Stop the program if conditions are not met
        finish = false;  // Set finish flag to false
    }
}
```
