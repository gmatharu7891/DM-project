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
    
    Robot_ID_t my_robot_id = '1';
    Robot_ID_t other_robot_id = '2';
    
    std::cout << "My robot ID: " << my_robot_id << std::endl;
    
    unsigned NS = 5;
    unsigned EW = 5;
    
    std::cout << "Grid size: NS - " << NS << "; EW - " << EW << std::endl;
    
    Robot_ID_t **robot_in_initial_situation = new Robot_ID_t *[NS];
    
    robot_in_initial_situation[0] = new Robot_ID_t[EW];
    
    robot_in_initial_situation[0][0] = my_robot_id;
    
    robot_in_initial_situation[2] = new Robot_ID_t[EW];
    
    robot_in_initial_situation[2][2] = other_robot_id;
    
    std::cout << "Robot at 2 2 - " << robot_in_initial_situation[2][2] << std::endl;
    
    std::list< Robot_Command > other_robots_commands;
    
    struct Robot_Command first_command;
    
    
    first_command.t = 0;
    first_command.r = other_robot_id;
    first_command.cmd = Robot_Command_Type::acc_E;
    
    struct Robot_Command second_command;
    
    second_command.t = 2;
    second_command.r = other_robot_id;
    second_command.cmd = Robot_Command_Type::stop;
    
    other_robots_commands.push_back(first_command);
    other_robots_commands.push_back(second_command);
    
    unsigned x_destination = 4;
    unsigned y_destination = 4;
    
    
    std::list< Robot_Command > *p_my_robots_commands;
    
    std::cout << "\nCalling move_a_robot...\n" << std::endl;
    

    My_Robot_Space::time_t the_time = move_a_robot(NS, EW, robot_in_initial_situation,  
            other_robots_commands, 
            my_robot_id, x_destination, y_destination,
            p_my_robots_commands);
    
    std::cout << the_time << std::endl;
    

    return 0;
}




