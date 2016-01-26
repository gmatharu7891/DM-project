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

void My_Robot_Space::render_the_process(unsigned NS, unsigned EW) {
    //we need to change this to 7 x 7
    unsigned **grid = new unsigned *[NS];

    // Fill grid with zeros
    for (int i = 0; i < NS; ++i) {
        grid[i] = new unsigned[EW];
        for (int j = 0; j < EW; ++j) {
            grid[i][j] = 0;
        }
    }
    //create commands for fast robot in circular(c)[s=stepwise and initialization=1,1] motion anticlockwise(a)

    std::list<Robot_Command> sample_other_robots_commands = generate_sample_other_robots_commands('a', 130, 'c');
    std::pair <unsigned, unsigned> sample_other_robot_init(0, 0);
    std::map<Robot_ID_t, std::pair<unsigned, unsigned>> sample_robot_in_initial_situation;
    sample_robot_in_initial_situation[130] = sample_other_robot_init;
    //vector to store previous occupancy
    std::vector<std::list < Slots_Occupancy >> occupancy_at_t(100);
    //for t=0 we need empty occupancy
    std::list<Slots_Occupancy> previous_occupancy;
    std::list<Slots_Occupancy> grid_occupancy_0;
    Robot_ID_t robot_id;

    //save the occupancy and print
    for (int t = 0; t < 80; ++t) {
        //Print out time value
        for (int i = 0; i < 10; ++i) {
            grid[i] = new unsigned[10];
            for (int j = 0; j < 10; ++j) {
                grid[i][j] = 0;
            }
        }
        std::cout << "Time:" << t << std::endl;
        //Print out grid state
        //cout << "Grid state:" << std::endl;
        if (t == 0) {
            grid_occupancy_0 = grid_occupancy_t(t, sample_other_robots_commands, previous_occupancy, sample_robot_in_initial_situation);
            occupancy_at_t.at(t) = grid_occupancy_0;
        } else {
            grid_occupancy_0 = grid_occupancy_t(t, sample_other_robots_commands, occupancy_at_t.at(t - 1), sample_robot_in_initial_situation);
            occupancy_at_t.at(t) = grid_occupancy_0;
        }


        for (auto& robot : occupancy_at_t.at(t)) {
            robot_id = robot.r;
            //std::cout << "Robot with ID: " << robot_id << std::endl;
            std::cout << "Is executing command: " << static_cast<int> (robot.cmd) << std::endl;
            //std::cout << "Slots occupied:" << std::endl;
            for (auto& slot : robot.slots_occupied) {
                //save the robot id on grid
                grid[slot.first.first][slot.first.second] = robot_id;
                //std::cout << "X: " << slot.first.first << "; Y: " << slot.first.second << std::endl;
                //std::cout << "Occupancy type: " << static_cast<int>(slot.second) << std::endl;
            }
        }




        //printing loop
        for (int i = NS-1; i >= 0; i--) {
            for (int j = 0; j < EW; j++) {
                std::cout << std::setw(7);
                std::cout << grid[j][i] << " ";
            }
            std::cout << "\n";
        }

        //Let user observe the output for a second before updating console
        usleep(400000);
        // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
        if (t != 79) {
            std::cout << "\x1B[2J\x1B[H";
        }
    }

    std::cout << "Finished" << std::endl;

    return;
}
