## World Robot Olympiad (WRO)
<p align="center">
  <img src="https://github.com/user-attachments/assets/4c95deb0-fc7f-4303-b52d-3bfd13346ee3" width="500">
</p>The World Robot Olympiad (WRO) is a prestigious international robotics competition that ignites the imaginations of students worldwide. It challenges participants to showcase their creativity, problem-solving skills, and technical prowess in designing and programming robots for a variety of tasks and challenges.

One of the most dynamic categories within WRO is the Future Engineers category. Here, participants are tasked with developing innovative solutions to real-world problems using robotics and automation. This category serves as a breeding ground for future innovators, encouraging students to think critically and creatively, laying the groundwork for a new generation of engineers and technologists.

This year, the Future Engineers category presents an exciting challenge: creating a self-driving car. This challenge pushes participants to explore the cutting edge of robotics, adding layers of complexity and innovation to an already thrilling competition.

Content
=======
- `t-photos` contains 2 photos of the team (an _official_ one and one _funny_ photo with all team members)
- `v-photos` contains 6 photos of the vehicle (from every side, from top and bottom)
- `video` contains the `video.md` file with the link to a video where driving demonstration exists
- `schemes` contains one schematic diagram in form of `JPEG, PNG or PDF` of the electronic components and motors that used in the vehicle and how they connect to each other.
- `src` contains code of control software for all components which were programmed
- `other` is for other files which can be used to understand how to prepare the vehicle for the competition. It may include documentation how to connect to a SBC/SBM and upload files there, datasets, hardware specifications, communication protocols descriptions etc.

How Ultrasonic Technology Works:
================================
## Generation of Ultrasonic Waves:
Ultrasonic waves are generated using an ultrasonic transducer.
This device converts electrical energy into mechanical vibrations using materials like piezoelectric crystals.
When an electrical signal is applied to the crystal, it vibrates at a high frequency, producing ultrasonic sound waves.

## Transmission of Waves:
The ultrasonic waves are transmitted into a medium, such as air, water, or a solid material. 
The choice of medium depends on the application.
For example, in medical imaging, waves travel through body tissues, while in 
industrial applications, they may pass through metals or other materials.

## Interaction with Objects:
As ultrasonic waves move through the medium, they interact with objects or boundaries they encounter.
This interaction can result in reflection (echo), refraction, or absorption, depending on the 
material's properties and the angle at which the waves strike the object.

## Reception of Echoes:
When the ultrasonic waves encounter an object, part of the wave is reflected back towards the source.
The ultrasonic receiver, often the same device as the transmitter, detects these echoes.
The time it takes for the echo to return is measured.

## Processing of Data:
The time delay between the emission of the ultrasonic pulse and the reception of the echo is used 
to calculate the distance to the object.
This is based on the known speed of sound in the medium and is calculated using the formula:
- Distance = (Speed of Sound × Time Delay) / 2

The division by 2 accounts for the round trip of the wave—going to the object and coming back.

And we used the Ultrasonic for calculate the distance on the right, left, back, and front sides. also to make sure if the car will be crash from the front corner sides.


#### Components of an H-Bridge:
1. **Switches (Transistors or MOSFETs)**: These act as the electronic switches that control the flow of current through the motor.
2. **DC Motor**: This is the load whose direction and speed you want to control.
3. **Power Supply**: Provides the necessary voltage and current for the motor.

#### Basic Operation:

1. **Forward Direction**: To drive the motor forward, you close switches S1 and S4 (top-left and bottom-right) and open switches S2 and S3 (top-right and bottom-left). This allows current to flow from the positive supply, through S1, through the motor from one terminal to the other, and finally through S4 to the ground. This sets up a voltage across the motor in one direction.

2. **Reverse Direction**: To drive the motor in reverse, you close switches S2 and S3 and open switches S1 and S4. This allows current to flow from the positive supply, through S2, through the motor in the opposite direction, and finally through S3 to the ground. This sets up a voltage across the motor in the opposite direction.

3. **Stop (Brake)**: To stop the motor, you can do one of two things:
   - Open all switches (S1, S2, S3, S4) so no current flows through the motor (coast to stop).
   - Close both top switches (S1 and S2) or both bottom switches (S3 and S4). This will short-circuit the motor, causing it to quickly brake (dynamic braking).

4. **Speed Control**: The speed of the motor can be controlled using Pulse Width Modulation (PWM). By rapidly turning the switches on and off, you can control the average voltage and current supplied to the motor, thereby controlling its speed.

#### Safety Considerations:

- **Shoot-through Condition**: Care must be taken to never close both switches on the same side (e.g., S1 and S2 simultaneously or S3 and S4 simultaneously) as this would create a direct short circuit across the power supply, causing a large current that could damage the components. This is known as a "shoot-through" condition.
  
- **Flyback Diodes**: When a motor is suddenly switched off or reversed, it can generate a back EMF (electromotive force) due to its inductance. Flyback diodes are often added across each switch to protect against voltage spikes caused by this back EMF.

### Applications:

- **Motor Control**: The primary use of an H-bridge is in DC motor control for applications such as robotics, drones, conveyor belts, and other automated systems.
- **Bidirectional Current Flow**: They can be used in any application where bidirectional current flow is needed.

In summary, an H-bridge circuit enables the direction and speed control of a DC motor by allowing current to flow in both directions and managing the switching of the motor's power.

