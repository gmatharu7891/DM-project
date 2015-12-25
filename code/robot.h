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

namespace My_Robot_Space {

    // Each robot has a unique ID.
    // No robot has ID 0, that number refers to "no robot on this position".
    // Robots with IDs in {1,...,127} are fast robots;
    // robots with IDs in {128,...,255} are slow robots.
    // (Slow robots move at half the speed of fast robots.)

    typedef  unsigned char  Robot_ID_t;


    // Everything happens in time intervals, let's think of them as seconds.
    typedef  unsigned long   time_t;

    // These are the commands which can be sent to the robots: accelerate into a direction, or stop.
    enum class Robot_Command_Type : char { acc_E, acc_N, acc_W, acc_S, stop };

    struct Robot_Command {
        time_t              t;
        Robot_ID_t          r;
        Robot_Command_Type  cmd;
    };


    // This function must be implemented:

    time_t move_a_robot(unsigned gridsize_NS, unsigned gridsize_EW,
                        Robot_ID_t const *const *robot_in_initial_situation, 
                        const std::list< Robot_Command > & other_robots_commands,
                        Robot_ID_t my_robot,
                        unsigned x_destination, unsigned y_destination);
    // Everything happens on a NS by EW grid.

    // Before time interval 0, the robot on grid slot with coordinate (x,y) in {0,...,EW-1}x{0,...,NS-1} is:
    //                robot_in_initial_situation[y][x]
    // where y is the North-South coordinate, x is the East-West coordinate.

    // The commands controlling the  robots are in ``other_robots_commands''.
    // Promise 1: This is sorted according to time (non-decreasing).
    // Promise 2: This does not lead to collisions of the other robots among themselves.

    // The robot which must be moved between the other robots is the one with ID ``my_robot''.
    // It should be moved to position  (x_destination, y_destination) as quickly as possible, without colliding with any other robots.

    // Put the commands into the list ``*p_my_robots_commands''.
    // Promise: That list is empty when the function is called. (So you can just append.)

    // The function returns the time when the robot stops at its destination.  (This number should be minimized.)


    //**************************************************************************************
    // NOW TO THE JUICY DETAILS

    // Robot speeds
    // Fast robot EW-movement
    //   - accelerating     takes 1 second and covers 1/2 width of a grid slot.
    //   - stopping         takes 1 second step and covers 1/2 width of a grid slot.
    //   - normal movement  (after acceleration, before stopping) full width of a grid slot

    // Fast robot NW-movement (= Slow robot EW-movement)
    //   - accelerating     takes 1 second and covers 1/4 width of a grid slot.
    //   - stopping         takes 1 second step and covers 1/4 width of a grid slot.
    //   - normal movement  (after acceleration, before stopping) 1/2 width of a grid slot

    // Slow robot NW-movement
    //   - accelerating     takes 1 second and covers 1/8 width of a grid slot.
    //   - stopping         takes 1 second step and covers 1/8 width of a grid slot.
    //   - normal movement  (after acceleration, before stopping) 1/4 width of a grid slot

    // Robot dimensions:
    // We assume that a robot covers the whole space of a grid slot.
    // In particular, during movement, it always occupies two grid slots.  Another robot can immediately follow in the same direction and (at most) the same speed so that they are ``bumper-to-bumper''.

}

#endif	/* ROBOT_H */

