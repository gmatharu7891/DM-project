
#include "robot.h"
#include <iostream>

My_Robot_Space::time_t My_Robot_Space::move_a_robot(unsigned gridsize_NS, unsigned gridsize_EW, 
        Robot_ID_t **robot_in_initial_situation, 
        const std::list<Robot_Command>& other_robots_commands, Robot_ID_t my_robot, 
        unsigned x_destination, unsigned y_destination){
    
    std::cout << "returns the shortest path " << robot_in_initial_situation[0][0] << std::endl;
    std::cout << "My robot: " << my_robot << std::endl;
    
    return 12;
}
