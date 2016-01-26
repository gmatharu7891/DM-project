/* 
 * File:   main.cpp
 * Author: nana
 *
 * Created on December 24, 2015, 6:17 PM
 */
#include <iostream>
#include <cstdlib>
#include "robot.h"
#include <unistd.h>

using namespace My_Robot_Space;

/*
 * 
 */
int main(int argc, char** argv) {

    Robot_ID_t my_robot_id = 1, other_robot_id = 2;
    std::cout << "My robot ID: " << my_robot_id << std::endl;

    unsigned NS = 10, EW = 10;
    std::cout << "Grid size: NS - " << NS << "; EW - " << EW << std::endl;

    std::pair <unsigned, unsigned> my_robot_init(1, 1), other_robot_init(0, 6);
    std::map<Robot_ID_t, std::pair<unsigned, unsigned>> robot_in_initial_situation;
    robot_in_initial_situation[my_robot_id] = my_robot_init;
    robot_in_initial_situation[other_robot_id] = other_robot_init;

    std::list< Robot_Command > other_robots_commands;
    Robot_Command first_command = {0, other_robot_id, Robot_Command_Type::acc_E};
    Robot_Command second_command = {4, other_robot_id, Robot_Command_Type::stop};
    other_robots_commands.push_back(first_command);
    other_robots_commands.push_back(second_command);

    std::pair <unsigned, unsigned> my_destination(1, 2);

    std::list< Robot_Command > *p_my_robots_commands = new std::list< Robot_Command >;

    std::vector<std::list < Slots_Occupancy>> *other_robots_trajectories = new std::vector<std::list < Slots_Occupancy>>;

    std::list<std::map<std::pair<int, int>, Slot_Occupancy_Type>> *my_robot_trajectory = new std::list<std::map<std::pair<int, int>, Slot_Occupancy_Type>>;

    std::cout << "\nCalling move_a_robot...\n" << std::endl;

    My_Robot_Space::time_t the_time = move_a_robot(NS, EW, robot_in_initial_situation,
            other_robots_commands, my_robot_id, my_destination, p_my_robots_commands,
            other_robots_trajectories, my_robot_trajectory);

    std::cout << "The time returned by move_a_robot: " << the_time << std::endl;

    std::cout << "\n" << std::endl;
    sleep(1);
    //std::cout << "Size of other robots trajectory: " << other_robots_trajectories->size() << std::endl;

    My_Robot_Space::time_t time_for_rendering = 0;
    for (auto& grid_state : *my_robot_trajectory) {
        std::cout << "Time: " << time_for_rendering << std::endl;
        render_the_process(time_for_rendering, my_robot_id, NS, EW, my_destination, *other_robots_trajectories, grid_state);
        
        //Let user observe the output for a second before updating console
        sleep(1);
        // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
        if (time_for_rendering != the_time) {
            std::cout << "\x1B[2J\x1B[H";
        }
        time_for_rendering++;
    }



    return 0;
}



