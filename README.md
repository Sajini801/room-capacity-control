# Occupancy Monitoring and Control System (Arduino + IoT)

## Overview
This project implements a real time occupancy monitoring system using an Arduino.  
A tilt sensor is used to detect entry and exit events, allowing the system to track the number of people inside a room. The system controls access using a servo motor and provides visual feedback through an RGB LED.
Sensor data is transmitted via serial communication to Python for logging, visualization in MATLAB, and optional cloud upload using ThingSpeak.

## Features
- Tilt sensor based entry and exit detection(tilt sensor will be placed in the door,a downward tilt generates a HIGH signal representing entry, while an upward tilt generates a LOW signal representing exit)
- Real time people counting (maximum capacity: 10)  
- Servo motor control for door access  
- RGB LED room status indication  
- Serial data transmission for MATLAB / Python  
- IoT cloud integration using ThingSpeak  

## System Logic
- Entry detected → Count increases, LED turns **Blue**, door opens  
- Exit detected → Count decreases, LED turns **Green**, door opens  
- Room full (10 people) → LED turns **Red**, door locks  

## Technologies Used
- Arduino (Embedded C/C++)
- Servo Motor & RGB LED
- Tilt Sensor
- Python (Serial Communication)
- MATLAB (Data Visualization)
- ThingSpeak (IoT Cloud Platform)

## Applications
- Classroom occupancy monitoring  
- Smart buildings  
- Access control systems  


