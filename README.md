# 2DOF-ESP32-RobotArm

Inverse kinematics controlled 2-DOF robotic arm using ESP32 and servo motors, with smooth coordinated motion and MATLAB simulation for trajectory visualization.


## Overview

This project demonstrates a 2-degree-of-freedom (2-DOF) planar robotic arm controlled via an ESP32 microcontroller.  
It includes:

- Arduino code to control two servo motors based on target X, Y coordinates.
- Smooth, synchronized servo movement using linear interpolation.
- MATLAB simulation to visualize arm motion and verify inverse kinematics calculations.

## Features

- Real-time X, Y coordinate input via Serial.
- Inverse kinematics calculations for 2-link robotic arm.
- Smooth motion between positions with adjustable speed.
- MATLAB simulation for trajectory testing and visualization.

## Hardware Required

- ESP32 development board
- 2x Servo motors (compatible with 0–180° range)
- Power supply for ESP32 and servos
- Jumper wires
- Breadboard or custom arm assembly

## Software Required

- Arduino IDE or PlatformIO
- MATLAB (for simulation)
- ESP32 board libraries for Arduino
- ESP32Servo library

## Arduino Usage

1. Connect your ESP32 and attach the servo motors to pins 32 and 33.
2. Upload `ESP32_RobotArm.ino` to the board.
3. Open the Serial Monitor at 115200 baud.
4. Send X and Y coordinates as floats separated by a space or newline.
5. The robotic arm will move smoothly to the target position if reachable.

## MATLAB Simulation

1. Open `IKTesting.m` in MATLAB.
2. Set the start and end positions as desired.
3. Run the script to visualize arm movement.

## Notes

- Ensure target positions are within the reachable workspace:  
  `|l1 - l2| <= r <= l1 + l2`
- Adjust the `steps` variable in both Arduino and MATLAB code to change motion smoothness.
- The `smoothMoveTogether` function allows synchronized motion of both servos.


## License

This project is open-source. Feel free to use and modify


## Contact

For questions or suggestions, please contact me via GitHub.
