#include <Servo.h>  // Include the Servo library

Servo myservo;  // Create a servo object to control the servo motor

// Define pins for ultrasonic sensors
const byte echo_r = 5;
const byte trig_r = 4;
const byte echo_l = 6;
const byte trig_l = 7;
const byte echo_f = 9;
const byte trig_f = 8;
const byte echo_b = 12;
const byte trig_b = 13;

// Define pins for motor control
const byte motor_f = 52;  // Forward motor pin
const byte motor_b = 53;  // Backward motor pin
const byte motor_s = 10;  // Speed control pin

String c = "none";  // Initialize a string to store color commands
const byte servo = 11;  // Servo control pin
int cr = 0;  // Counter for some operation (to be explained below)
long long time;  // Variable to store time for delays

// Function to measure distance using ultrasonic sensor
int get_destance(int pin_Trig, int pin_Echo) {
  long Time;  // Variable to store the time of pulse
  int Distance;  // Variable to store the calculated distance

  // Trigger the ultrasonic sensor to send a pulse
  digitalWrite(pin_Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(pin_Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin_Trig, LOW);

  // Measure the duration of the pulse
  Time = pulseIn(pin_Echo, HIGH);
  Time = Time / 2;  // Divide by 2 to account for travel time to and back
  Distance = Time * 0.034;  // Convert time to distance (in cm)
  return Distance;
}

// Function to control the servo based on sensor distances
void b3d() {
  int left = get_destance(trig_l, echo_l);  // Measure distance on the left
  int right = get_destance(trig_r, echo_r);  // Measure distance on the right
  
  // Check if there's an obstacle on the left
  if (left <= 5) {
    myservo.write(80);  // Turn servo to avoid obstacle
    time = millis();
    while (millis() - time <= 500) {}  // Wait for 500 ms
    myservo.write(55);  // Reset servo position
  }
  // Check if there's an obstacle on the right
  else if (right <= 5) {
    myservo.write(25);  // Turn servo to avoid obstacle
    time = millis();
    while (millis() - time <= 500) {}  // Wait for 500 ms
    myservo.write(55);  // Reset servo position
  }
}

// Function to handle commands received from serial input
void alwan() {
  if (Serial.available() > 0) {  // Check if data is available on serial port
    String k = Serial.readStringUntil('\n');  // Read the command until newline character

    // Check for different color commands
    if (k == "Red Left" || k == "Red Center" || k == "Red Right") {
      c = "red";  // Set color to red
      if (k == "Red Right") {
        myservo.write(25);
        digitalWrite(motor_b, HIGH);  // Reverse motor
        digitalWrite(motor_f, LOW);  // Stop forward motor
        time = millis();
        while (millis() - time <= 1000) { b3d(); }  // Perform obstacle avoidance
        myservo.write(55);  // Reset servo
        digitalWrite(motor_f, HIGH);  // Start forward motor
        digitalWrite(motor_b, LOW);  // Stop reverse motor
      }
      else if (k == "Red Center") {
        k = Serial.readStringUntil('\n');
        myservo.write(80);
        time = millis();
        while (millis() - time <= 2000) {
          k = Serial.readStringUntil('\n');
          if (k != "Red Center") { break; }
        }
        myservo.write(55);
      }
    }

    // Check for green color commands
    else if (k == "Green Left" || k == "Green Center" || k == "Green Right") {
      c = "green";  // Set color to green
      if (k == "Green Left") {
        myservo.write(80);
        digitalWrite(motor_b, HIGH);  // Reverse motor
        digitalWrite(motor_f, LOW);  // Stop forward motor
        time = millis();
        while (millis() - time <= 1000) { b3d(); }  // Perform obstacle avoidance
        myservo.write(55);  // Reset servo
        digitalWrite(motor_f, HIGH);  // Start forward motor
        digitalWrite(motor_b, LOW);  // Stop reverse motor
      }
      else if (k == "Green Center") {
        k = Serial.readStringUntil('\n');
        myservo.write(25);
        time = millis();
        while (millis() - time <= 2000) {
          k = Serial.readStringUntil('\n');
          if (k != "Green Center") { break; }
        }
        myservo.write(55);
      }
    }
  }
}

// Function to determine direction and move accordingly
void atjah() {
  int left = get_destance(trig_l, echo_l);  // Measure distance on the left
  int right = get_destance(trig_r, echo_r);  // Measure distance on the right
  
  // Check if combined distance is above a threshold
  if (left + right >= 140) {
    if (c == "red" && cr == 7) {  // Specific check for red color and counter value
      if (left > right) {
        if (right > 30) {
          // Move forward for 3 seconds or until obstacle is detected
          time = millis();
          while (millis() - time <= 3000) {
            int f = get_destance(trig_f, echo_f);
            if (f < 10) { break; }
          }
          digitalWrite(motor_b, HIGH);  // Reverse motor
          digitalWrite(motor_f, LOW);  // Stop forward motor
          myservo.write(80);  // Turn servo to a specific angle
          time = millis();
          while (millis() - time <= 1500) {
            int b = get_destance(trig_b, echo_b);
            if (b < 10) { break; }
          }
          digitalWrite(motor_f, HIGH);  // Start forward motor
          digitalWrite(motor_b, LOW);  // Stop reverse motor
          myservo.write(25);
        }
        // Similar logic for other conditions...
      }
    }
    // More logic for different cases...
  }
}

// Function to start the motors and set servo position
void startProgram() {
  digitalWrite(motor_f, HIGH);  // Start forward motor
  digitalWrite(motor_b, LOW);  // Stop reverse motor
  myservo.write(55);  // Set servo to default position
}

// Function to stop the motors and reset variables
void stopProgram() {
  digitalWrite(motor_f, LOW);  // Stop forward motor
  digitalWrite(motor_b, LOW);  // Stop reverse motor
  myservo.write(55);  // Reset servo position
  cr = 0;  // Reset counter
  c = "none";  // Reset color command
}

// Arduino setup function
void setup() {
  // Configure motor pins as outputs
  pinMode(motor_f, OUTPUT);
  pinMode(motor_b, OUTPUT);
  pinMode(motor_s, OUTPUT);
  analogWrite(motor_s, 80);  // Set motor speed

  myservo.attach(servo);  // Attach servo to control pin
  myservo.write(55);  // Initialize servo position

  // Configure ultrasonic sensor pins
  pinMode(trig_l, OUTPUT);
  pinMode(echo_l, INPUT);
  pinMode(trig_r, OUTPUT);
  pinMode(echo_r, INPUT);
  pinMode(trig_f, OUTPUT);
  pinMode(echo_f, INPUT);
  pinMode(trig_b, OUTPUT);
  pinMode(echo_b, INPUT);

  Serial.begin(9600);  // Start serial communication
  cr = 0;  // Initialize counter
  c = "none";  // Initialize color command
}

// Arduino main loop function
void loop() {
  if (cr < 12) {
    startProgram();  // Start motors and set servo position
    b3d();  // Check for obstacles
    atjah();  // Determine direction
    alwan();  // Process color commands
  }
  else {
    stopProgram();  // Stop motors and reset if counter exceeds limit
  }
}
