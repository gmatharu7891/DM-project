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
    robot_in_initial_situation[my_robot_id] = other_robot_init_1;

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
    
    
    
    std::cout << "\nGrid occupancy: " << std::endl;
    // Testing the function
    std::list<Slots_Occupancy> previous_occupancy;
    std::list< Robot_Command > other_robots_commands_testing;

    struct Robot_Command *first_command_testinf;

    first_command_testinf = new Robot_Command;

    first_command_testinf->t = 0;
    first_command_testinf->r = 1;
    first_command_testinf->cmd = Robot_Command_Type::acc_N;

    struct Robot_Command *second_command_testing;

    second_command_testing = new Robot_Command;

    second_command_testing->t = 4;
    second_command_testing->r = 1;
    second_command_testing->cmd = Robot_Command_Type::stop;

    other_robots_commands_testing.push_back(*first_command_testinf);
    other_robots_commands_testing.push_back(*second_command_testing);
    
    std::pair <unsigned, unsigned> other_robot_init_testing (0,0);
        
    std::map<Robot_ID_t, std::pair<unsigned,unsigned>> robot_in_initial_situation_testing;
    
    robot_in_initial_situation_testing[1] = other_robot_init_testing;
    
    // ################## Let's rock ########################## //
    
    std::list<Slots_Occupancy> grid_occupancy_0 = grid_occupancy_t(0, other_robots_commands_testing, previous_occupancy, robot_in_initial_situation_testing);
    
    std::cout << "\nNext move, compute next occupancy\n" << std::endl;
    
    std::list<Slots_Occupancy> grid_occupancy_1 = grid_occupancy_t(1, other_robots_commands_testing, grid_occupancy_0, robot_in_initial_situation_testing);
    
    std::cout << "\nNext move, compute next occupancy\n" << std::endl;
    
    std::list<Slots_Occupancy> grid_occupancy_2 = grid_occupancy_t(2, other_robots_commands_testing, grid_occupancy_1, robot_in_initial_situation_testing);
    
    std::cout << "\nNext move, compute next occupancy\n" << std::endl;
    
    std::list<Slots_Occupancy> grid_occupancy_3 = grid_occupancy_t(3, other_robots_commands_testing, grid_occupancy_2, robot_in_initial_situation_testing);
    
    std::cout << "\nNext move, compute next occupancy\n" << std::endl;
    
    std::list<Slots_Occupancy> grid_occupancy_4 = grid_occupancy_t(4, other_robots_commands_testing, grid_occupancy_3, robot_in_initial_situation_testing);
    
    for (auto& robot:grid_occupancy_4 ){
        std::cout << "Robot with ID: " << robot.r << std::endl;
        std::cout << "Is executing command: " << static_cast<int>(robot.cmd) << std::endl;
        std::cout << "Slots occupied:" << std::endl;
        for (auto& slot: robot.slots_occupied){
            std::cout << "X: " << slot.first.first << "; Y: " << slot.first.second << std::endl;
            std::cout << "Occupancy type: " << static_cast<int>(slot.second) << std::endl;
        }
    }

    
    return 0;
}




