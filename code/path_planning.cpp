
#include "robot.h"
#include <iostream>
#include <unistd.h>

// Function to compute the shortest path
My_Robot_Space::time_t My_Robot_Space::move_a_robot(unsigned gridsize_NS, unsigned gridsize_EW,
        Robot_ID_t const *const *robot_in_initial_situation,
        const std::list<Robot_Command>& other_robots_commands, Robot_ID_t my_robot,
        unsigned x_destination, unsigned y_destination,
        std::list< Robot_Command > *p_my_robots_commands) {

    std::cout << "returns the shortest path " << std::endl;

    std::cout << "Robot at 0 0 - " << robot_in_initial_situation[0][0] << std::endl;

    std::cout << "My robot: " << my_robot << std::endl;
    
    return 12;
}

// Function to generate commands and initial positions for other robots
void My_Robot_Space::generate_other_robots_commands(unsigned number_of_robots, unsigned NS, unsigned EW,
        std::list<Robot_Command> other_robots_commands, Robot_ID_t **robot_in_initial_situation) {

    // ...

}


// Function to generate the occupancy lookup table
int** My_Robot_Space::create_occupancy_lookup(std::list<Robot_Command> other_robots_commands, Robot_ID_t **robot_in_initial_situation) {
    int **occupancy_lookup;
    // TODO: Assign each robot its initial position
    // TODO: Fill in the occupancy_lookup
    
    for (auto& it : other_robots_commands) {
        std::cout << it.t << std::endl;
    }

    return occupancy_lookup;
}


// Function to check if the nodes in the tree are equivalent (TBA))


// Function to generate all possible next moves
void generate_all_possible_next_moves(unsigned NS, unsigned EW, unsigned my_possition_x, unsigned my_possition_y,
        unsigned destination_x, unsigned destination_y, int **occupancy_table) {

    // ...
}


// Render the whole process
void My_Robot_Space::render(int **occupancy_table, std::list< Robot_Command > my_robots_commands) {

    // Initialize grid and fill it with zeros
    char **robot_in_initial_situation = new char *[10];

    for (int i = 0; i < 10; ++i) {
        robot_in_initial_situation[i] = new char[10];
        for (int j = 0; j < 10; ++j) {
            robot_in_initial_situation[i][j] = '0';
        }
    }

    for (int t = 0; t < 10; ++t) {
        //Print out time value
        std::cout << "Time:" << t << std::endl;
        //Print out grid state
        std::cout << "Grid state:" << std::endl;

        // TODO: update grid according to occupancy table and my_robots_commands
        //       render updated grid for current value of t

        //Let user observe the output for a second before updating console
        sleep(1);
        // CSI[2J clears the screen, CSI[H moves the cursor to top-left corner
        if (t != 9) {
            std::cout << "\x1B[2J\x1B[H";
        }
    }

    std::cout << "Finished" << std::endl;

}


