
#include "robot.h"
#include <iostream>

// Function to compute the shortest path
My_Robot_Space::time_t My_Robot_Space::move_a_robot(unsigned gridsize_NS, unsigned gridsize_EW, 
        Robot_ID_t const *const *robot_in_initial_situation, 
        const std::list<Robot_Command>& other_robots_commands, Robot_ID_t my_robot, 
        unsigned x_destination, unsigned y_destination, 
        std::list< Robot_Command > *p_my_robots_commands){
    
    std::cout << "returns the shortest path " << std::endl;
    
    std::cout << "Robot at 0 0 - " << robot_in_initial_situation[0][0] << std::endl;
    
    std::cout << "My robot: " << my_robot << std::endl;
    
    return 12;
}

// Function to generate commands and initial positions for other robots
void My_Robot_Space::generate_other_robots_commands(unsigned NS, unsigned EW, 
        std::list<Robot_Command> other_robots_commands, Robot_ID_t **robot_in_initial_situation){
    
    // ...

}


// Function to generate the occupancy lookup table
int** My_Robot_Space::create_occupancy_lookup(unsigned NS, unsigned EW, std::list<Robot_Command> other_robots_commands, Robot_ID_t **robot_in_initial_situation){
    
    // ...
}


// Function to check if the nodes in the tree are equivalent


// Function to generate all possible next moves
void generate_all_possible_next_moves(unsigned NS, unsigned EW, unsigned my_possition_x, unsigned my_possition_y,
            unsigned destination_x, unsigned destination_y, int **occupancy_table){
    
    // ...
}

