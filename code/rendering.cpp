/*
 * File:   main.cpp
 * Author: nana
 *
 * Created on January 4, 2016, 10:40 AM
 */


#include <iostream>
#include <unistd.h>
#include <iomanip>
#include "robot.h"
#include <vector>
#include <typeinfo>

using namespace My_Robot_Space;

void My_Robot_Space::render_the_process(time_t t, Robot_ID_t my_robot, unsigned NS, unsigned EW, std::pair<unsigned, unsigned> my_destination,
        std::vector<std::list<Slots_Occupancy>> other_robots_trajectories, std::map<std::pair<int, int>, Slot_Occupancy_Type> my_position) {

    unsigned **grid = new unsigned *[NS];

    // Fill grid with zeros
    for (int i = 0; i < NS; ++i) {
        grid[i] = new unsigned[EW];
        for (int j = 0; j < EW; ++j) {
            grid[i][j] = 0;
        }
    }

    //Put current positions to the grid
    std::cout << "Grid state:" << std::endl;
    for(auto& my_slot:my_position){
        grid[my_slot.first.first][my_slot.first.second] = my_robot;
    }
    

    for (auto& robot : other_robots_trajectories.at(t)) {
        //std::cout << "Robot with ID: " << robot_id << std::endl;
        //std::cout << "Is executing command: " << static_cast<int> (robot.cmd) << std::endl;
        //std::cout << "Slots occupied:" << std::endl;
        for (auto& slot : robot.slots_occupied) {
            //save the robot id on grid
            grid[slot.first.first][slot.first.second] = robot.r;
            //std::cout << "X: " << slot.first.first << "; Y: " << slot.first.second << std::endl;
            //std::cout << "Occupancy type: " << static_cast<int>(slot.second) << std::endl;
        }
    }

    //printing loop
    for (int i = NS - 1; i >= 0; i--) {
        for (int j = 0; j < EW; j++) {
            if (i == my_destination.second && j == my_destination.first) {
                std::cout << std::setw(8);
                std::cout << "  goal";
            } else {
                std::cout << std::setw(7);
                std::cout << grid[j][i] << " ";
            }
        }
        std::cout << "\n";
    }



    return;
}
