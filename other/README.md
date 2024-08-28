**We used some UltraSonics, but they burned during the experiments ):, 
And the IRs the same thing, We tried using an algorithm based on the color sensor but it measures incorrectly.**

This's some photos show what I mean:
=========================================
## UltraSonics

<p align="center">
  <img src="https://github.com/user-attachments/assets/317b1b24-3fd6-4d9d-9086-a822926bb834" width="500">
</p>

## IRs, ColorSensor

<p align="center">
  <img src="https://github.com/user-attachments/assets/1521a3a6-c4a5-4144-9fb0-0907f7e61413" width="500">
</p>


The algorithm we used
=====================
## Arduino Code (CarControl.ino):
- Ultrasonic Distance Measurement:
Uses ultrasonic sensors to measure the distance by sending a pulse and calculating the time it takes to receive the echo. This is done in the get_destance function.
The function controls the trigger pin to send a pulse and reads the echo pin to calculate the distance.

- Servo Control Logic:
Controls the servo motor based on distance measurements and specific color commands received from the serial input.
The b3d() function adjusts the servo position based on distance readings from left and right sensors to avoid obstacles.

- Serial Communication:
Reads color commands from the serial input using Serial.readStringUntil().
Depending on the command (e.g., "Red Left", "Green Center"), it executes specific motor and servo actions.


## Python Code (ai.py):
- Serial Communication Setup:
Establishes a serial connection with an Arduino device using pyserial.
Configures the communication port and baud rate, and includes a delay to ensure the connection is ready.

- Color Detection:
Detects specific colors in an image using OpenCV. Applies a Gaussian Blur to reduce noise, and then filters colors within a specified range using cv2.inRange() (partially visible in the code).
