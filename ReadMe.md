# Operating_Systems_Project_2015
Final Project for Operating Systems class in Fall 2015

Tory Yeonas and Ross Harmon

Objectives:

Reliability is a key aspect of a mission critical system. 
Continuous monitoring of failures in the processes and operating system is a crucial, and fault correction
measures can be implemented to ensure reliable operation of the system mission. In this project we will 
design a Monitoring program that will continuously monitor a given user process at user specified monitoring 
interval. We will also design a fault injection program to kill a target process, which will be detected by 
the monitor and restarted by a deployment manager. Finally, we will maintain a logging system of all pertinent 
information. This project will be written in C/C++

Project Components:
Our project contains four different executables that will be used to accomplish our goals. These are for the Launcher, Deployment Manager, Fault Injector, and the Target Process. Launcher will be called from the terminal,  

Target Process – Program to inject fault to (prog1.c)
Fault injection program (fi.cpp)
Deployment Manager (dm_main.cpp, dm_launcher.cpp, dm_launcher.h)
Launcher (Launcher.cpp)

These are compiled into four different executables that encompass the program operation
./Launcher
./DM (Deployment Manager)
./FI (Fauly Injector_
./prog1 (Prog 1)
