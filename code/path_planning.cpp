
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

    /* Some guidelines:
     * 
     * First the robots IDs and initial positions should be assigned to all the robots (no collisions!)
     * Then each robot is processed one by one, i.e. first "come up" with commands for the first robot.
     * Then take the next robot and generate command for it so that it doesn't collide with the first one.
     * And so it goes until commands for all robots are generated.
     * 
     * 
     * Important! (some notes about the legal commands (due to the specifics in how robots are supposed to move))
     * 
     * IF fast robot accelerates east or west, ...
     * ... it can be stopped at any time (1/2 + 1 + 1/2 = 2; 1/2 + 1 + 1 + ... + 1/2 = int - no problem, robot occupies full slot).
     * 
     * IF fast robot accelerates south or north OR slow robot accelerates east or west, ...
     * ... it has to move normally for ODD number of seconds before it can be stopped (1/4 + 1/2 + 1/2 + 1/4 = 1,5 - robot between slots).
     * 
     * IF slow robot accelerates south or north, ...
     * ... it has to move normally for 3*x seconds before being stopped (1/8 + 1/4 + 1/4 + 1/4 + 1/8 = 1 - no problem, robot occupies full slot).
     * 
    */
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


