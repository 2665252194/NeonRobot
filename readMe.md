# COMP0002 Coursework Desgined by Zhouzhou Zhang, Nov 2024

A simple robot that can find the marker in an arena.

Stops when getting all markers to Home.

## Compile And Run
To compile:

    gcc -o robot.exe robot.c graphics.c robot_background.c robot_data.c

To run:

    ./robot.exe | java -jar drawapp-4.0.jar

Command may should be changed depending on your platform

## Feature
At stage 7.

Random size and shape of arena.

Find the markers and take them back to Home(a random filet).

Robot at random position and orientation.

Detailed Comments

## Algorithm

Based on a Score-System.

Whenever passing one filet, increase the score of this filet.

Chooses lower score to go.

The score of obstacle is 100000 so robot will never go there.

## File included

robot.c: Implements the functions about robot

robot_background.c: Implements the functions about the background

robot_data.c: Implements some method used to initiliaze the data.

header files: They are not external libraries. They are all implemented by my .c file.
