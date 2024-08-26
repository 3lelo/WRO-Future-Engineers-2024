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
- 
The division by 2 accounts for the round trip of the wave—going to the object and coming back.

And we used the Ultrasonic for calculate the distance on the right, left, back, and front sides. also to make sure if the car will be crash from the front corner sides.
