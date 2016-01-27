#!/bin/bash
g++ -std=c++11 -c -o sample_robot_commands.o sample_robot_commands.cpp
g++ -std=c++11 -c -o rendering.o rendering.cpp
g++ -std=c++11 -c -o path_planning.o path_planning.cpp
g++ -std=c++11 -c -o main.o main.cpp
g++ -std=c++11 -o robots sample_robot_commands.o rendering.o path_planning.o main.o -lm
