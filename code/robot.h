/* 
 * File:   robot.h
 * Author: nana
 *
 * Created on December 24, 2015, 6:18 PM
 */

#ifndef ROBOT_H
#define	ROBOT_H

// robots.hh C++11

#include <list>
#include <map>


namespace My_Robot_Space {

    // Each robot has a unique ID.
    // No robot has ID 0, that number refers to "no robot on this position".
    // Robots with IDs in {1,...,127} are fast robots;
    // robots with IDs in {128,...,255} are slow robots.
    // (Slow robots move at half the speed of fast robots.)

    // Robot ID
    typedef unsigned Robot_ID_t;

    // Everything happens in time intervals, let's think of them as seconds.
    typedef unsigned long time_t;

    // These are the commands which can be sent to the robots: accelerate into a direction, or stop
    // ... plus some extra (idle, moving_E, moving_N, moving_W, moving_S) for sake of implementation of some functions
    // ... NOTE!!! extra command can not be directly sent to robots, we don't put them in other_robots_commands list

    enum class Robot_Command_Type : char {
        acc_E, acc_N, acc_W, acc_S, stop, idle, moving_E, moving_N, moving_W, moving_S
    };

    // These are the types of slot occupancy

    enum class Slot_Occupancy_Type : char {
        full, e_1_2, w_1_2, e_1_4, w_1_4, n_1_4, s_1_4, e_3_4, w_3_4, n_3_4, s_3_4, n_1_8, n_3_8, n_5_8, n_7_8, s_1_8, s_3_8, s_5_8, s_7_8
    };

    struct Slots_Occupancy {
        Robot_ID_t r;
        Robot_Command_Type cmd;
        std::map<std::pair<unsigned, unsigned>, Slot_Occupancy_Type>  slots_occupied;
    };

    struct Robot_Command {
        time_t t;
        Robot_ID_t r;
        Robot_Command_Type cmd;
    };


    // This function must be implemented:

    time_t move_a_robot(unsigned gridsize_NS, unsigned gridsize_EW,
            const std::map<Robot_ID_t, std::pair<unsigned, unsigned>> robot_in_initial_situation,
            const std::list< Robot_Command > & other_robots_commands,
            Robot_ID_t my_robot,
            unsigned x_destination, unsigned y_destination,
            std::list< Robot_Command > *p_my_robots_commands);

    // Everything happens on a NS by EW grid.

    // Before time interval 0, the robot on grid slot with coordinate (x,y) in {0,...,EW-1}x{0,...,NS-1} is:
    //                robot_in_initial_situation[robot_id]]

    // The commands controlling the  robots are in ``other_robots_commands''.
    // Promise 1: This is sorted according to time (non-decreasing).
    // Promise 2: This does not lead to collisions of the other robots among themselves.

    // The robot which must be moved between the other robots is the one with ID ``my_robot''.
    // It should be moved to position  (x_destination, y_destination) as quickly as possible, without colliding with any other robots.

    // Put the commands into the list ``*p_my_robots_commands''.
    // Promise: That list is empty when the function is called. (So you can just append.)

    // The function returns the time when the robot stops at its destination.  (This number should be minimized.)


    //**************************************************************************************
    // HOW ROBOTS MOVE

    // Robot speeds
    // Fast robot EW-movement
    //   - accelerating     takes 1 second and covers 1/2 width of a grid slot.
    //   - stopping         takes 1 second step and covers 1/2 width of a grid slot.
    //   - normal movement  (after acceleration, before stopping) full width of a grid slot

    // Fast robot NS-movement (= Slow robot EW-movement)
    //   - accelerating     takes 1 second and covers 1/4 width of a grid slot.
    //   - stopping         takes 1 second step and covers 1/4 width of a grid slot.
    //   - normal movement  (after acceleration, before stopping) 1/2 width of a grid slot

    // Slow robot NS-movement
    //   - accelerating     takes 1 second and covers 1/8 width of a grid slot.
    //   - stopping         takes 1 second step and covers 1/8 width of a grid slot.
    //   - normal movement  (after acceleration, before stopping) 1/4 width of a grid slot

    // Robot dimensions:
    // We assume that a robot covers the whole space of a grid slot.
    // During movement, it sometimes occupies parts of two grid slots.  
    // Another robot can immediately follow in the same direction and (at most) the same speed so that they are ``bumper-to-bumper''.


    //------------------------------------Main functions-----------------------------------------------------//


    // Function to generate commands and initial positions for other robots
    /* Some guidelines: (IMPORTANT!)
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
    // 
    void generate_other_robots_commands(unsigned number_of_robots, unsigned NS, unsigned EW, std::list<Robot_Command> other_robots_commands,
            const std::map<Robot_ID_t, std::pair<unsigned, unsigned>> robot_in_initial_situation);


    // Function to generate all possible next moves
    void generate_all_possible_next_moves(unsigned NS, unsigned EW, std::pair<unsigned, unsigned> my_current_position,
            std::pair<unsigned, unsigned> my_destinaniton, std::list<My_Robot_Space::Slots_Occupancy> grid_occupancy);


    // Function to generate the occupancy state of the grid for time t
    std::list<Slots_Occupancy> grid_occupancy_t(Robot_ID_t t, std::list<Robot_Command> other_robots_commands, std::list<Slots_Occupancy> previous_occupancy,
            const std::map<Robot_ID_t, std::pair<unsigned, unsigned>> robot_in_initial_situation);


    // Render the whole process
    void render(std::list<Robot_Command> other_robots_commands, std::list< Robot_Command > my_robots_commands,
            std::map<Robot_ID_t, std::pair<unsigned, unsigned>> robot_in_initial_situation);
    
    
    //¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤Additional functions¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤//
    
    bool is_fast(Robot_ID_t r);
    
    std::map<std::pair<unsigned, unsigned>, Slot_Occupancy_Type> apply_command_on_initial_position(Robot_ID_t r, 
            Robot_Command_Type cmd, std::pair<unsigned, unsigned> init_pos);
    

}

#endif	/* ROBOT_H */

