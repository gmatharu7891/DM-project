/* 
 * File:   main.cpp
 * Author: nana
 *
 * Created on December 24, 2015, 6:17 PM
 */
#include <iostream>
#include <cstdlib>
#include "robot.h"


using namespace My_Robot_Space;

/*
 * 
 */
int main(int argc, char** argv) {

    Robot_ID_t my_robot_id = 1;
    Robot_ID_t other_robot_id = 128;
    Robot_ID_t other_robot_id_2 = 3;

    std::cout << "My robot ID: " << my_robot_id << std::endl;

    unsigned NS = 5;
    unsigned EW = 5;

    std::cout << "Grid size: NS - " << NS << "; EW - " << EW << std::endl;
    
    std::pair <unsigned, unsigned> other_robot_init_1 (2,4);
    std::pair <unsigned, unsigned> other_robot_init_2 (6,3);
        
    std::map<Robot_ID_t, std::pair<unsigned,unsigned>> robot_in_initial_situation;
    
    robot_in_initial_situation[other_robot_id] = other_robot_init_2;
    

    std::list< Robot_Command > other_robots_commands;

    struct Robot_Command *first_command;

    first_command = new Robot_Command;

    first_command->t = 0;
    first_command->r = other_robot_id;
    first_command->cmd = Robot_Command_Type::acc_E;

    struct Robot_Command *second_command;

    second_command = new Robot_Command;

    second_command->t = 2;
    second_command->r = other_robot_id_2;
    second_command->cmd = Robot_Command_Type::stop;

    other_robots_commands.push_back(*first_command);
    other_robots_commands.push_back(*second_command);

    unsigned x_destination = 4;
    unsigned y_destination = 4;


    std::list< Robot_Command > *p_my_robots_commands;

    std::cout << "\nCalling move_a_robot...\n" << std::endl;


    My_Robot_Space::time_t the_time = move_a_robot(NS, EW, robot_in_initial_situation,
            other_robots_commands,
            my_robot_id, x_destination, y_destination,
            p_my_robots_commands);

    std::cout << the_time << std::endl;
    
    std::list<Slot_Occupancy> previous_occupancy;

    
    std::cout << "\nGrid occupancy: " << std::endl;
    // Testing the function
    grid_occupancy_t(0, other_robots_commands, previous_occupancy, robot_in_initial_situation);

    
    return 0;
}




