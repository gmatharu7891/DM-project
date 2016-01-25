
#include "robot.h"
#include <iostream>
#include <unistd.h>
#include <map>
#include <queue>

// Function to compute the shortest path

My_Robot_Space::time_t My_Robot_Space::move_a_robot(unsigned gridsize_NS, unsigned gridsize_EW,
        const std::map<Robot_ID_t, std::pair<unsigned, unsigned>> robot_in_initial_situation,
        const std::list<Robot_Command>& other_robots_commands, Robot_ID_t my_robot,
        std::pair<unsigned, unsigned> my_destination,
        std::list< Robot_Command > *p_my_robots_commands) {

    std::cout << "Returns the shortest path " << std::endl;
    std::cout << "My robot: " << my_robot << std::endl;
    std::cout << "My robot initial position: X: " << robot_in_initial_situation.find(my_robot)->second.first << "; Y: " << robot_in_initial_situation.find(my_robot)->second.second << std::endl;

    if (other_robots_commands.empty()) {
        std::cout << "Grid is empty, path is definitely free" << std::endl;
    } else {
        if (robot_in_initial_situation.find(my_robot)->second.first == my_destination.first
                && robot_in_initial_situation.find(my_robot)->second.second == my_destination.second) {
            std::cout << "Initial position and destination are the same" << std::endl;
            return 0;

        } else { // Need BFS tree to find shortest path

            // Initialize the root of the tree
            struct TreeNode *root;
            root = new TreeNode;
            root->state = Robot_Command_Type::idle;
            root->slots_occupied[robot_in_initial_situation.find(my_robot)->second] = Slot_Occupancy_Type::full;
            root->level = 0;
            root->parent = NULL;

            // Populate the children (build up the tree) every time check if destination is reached
            std::list<Slots_Occupancy> previous_occupancy;
            // Start the navigation
            time_t t = 0;

            // -------------------------------- BFS ------------------------------------------------ //
            std::queue<TreeNode*> bfs_queue;
            bfs_queue.push(root);

            TreeNode* leaf_of_the_shortest_path;

            while (!bfs_queue.empty()) {
                std::cout << "\nDecision tree level (time): " << t << std::endl;
                std::list<Slots_Occupancy> current_occupancy = grid_occupancy_t(t, other_robots_commands, previous_occupancy, robot_in_initial_situation);
                TreeNode *node_to_visit = bfs_queue.front();
                node_to_visit->children = generate_all_possible_next_moves(my_robot, gridsize_NS, gridsize_EW, node_to_visit,
                        my_destination, current_occupancy);

                // Check if any of the children reached the goal, if so break;
                std::cout << "Number of nodes on level " << t << ": " << node_to_visit->children.size() << std::endl;
                bool goal_reached = false;
                for (auto& child : node_to_visit->children) {
                    std::cout << "Node state: " << static_cast<int> (child->state) << std::endl;
                    std::cout << "Node level: " << child->level << std::endl;
                    std::cout << "Node's parent level: " << child->parent->level << std::endl;
                    if (reached_the_goal(child, my_destination)) {
                        leaf_of_the_shortest_path = child;
                        goal_reached = true;
                        break;
                    }
                }
                if (goal_reached) {
                    break;
                }

                // If goal not found in current level build the next level
                t++;
                previous_occupancy = current_occupancy;

                if (!(node_to_visit->children.empty())) {
                    for (auto& child_node : node_to_visit->children) {
                        bfs_queue.push(child_node);
                    }
                }
                sleep(1); // Added for testing
            }

            // Reconstruct the path, populate the list of my robot commands
            std::cout << "Time when reached the goal: " << leaf_of_the_shortest_path->level << std::endl;
            std::cout << "State when reached the goal: " << static_cast<int> (leaf_of_the_shortest_path->state) << std::endl;
        }
    }

    return 12;
}

// Function to generate commands and initial positions for other robots

void My_Robot_Space::generate_other_robots_commands(unsigned number_of_robots, unsigned NS, unsigned EW,
        std::list<Robot_Command> other_robots_commands, std::map<Robot_ID_t, std::pair<unsigned, unsigned>> robot_in_initial_situation) {

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


// Function to generate the occupancy state of the grid for time t
// function assumes the commands in other_robot_commands are legal!

std::list<My_Robot_Space::Slots_Occupancy> My_Robot_Space::grid_occupancy_t(Robot_ID_t t, std::list<Robot_Command> other_robots_commands,
        std::list<Slots_Occupancy> previous_occupancy, const std::map<Robot_ID_t, std::pair<unsigned, unsigned>> robot_in_initial_situation) {

    std::list<Slots_Occupancy> current_occupancy;

    if (t == 0) { // there is no previous_occupancy
        // from other_robots_commands take elements with t=0
        for (auto& el : other_robots_commands) {
            if (el.t == 0) {
                // for every such element get robot ID and it's initial position
                std::pair<unsigned, unsigned> init_pos;
                init_pos.first = robot_in_initial_situation.find(el.r)->second.first;
                init_pos.second = robot_in_initial_situation.find(el.r)->second.second;

                //std::cout << "Robot ID: " << el.r << " X: " << init_pos.first << " Y: " << init_pos.second << std::endl;
                //std::cout << "Command being executed: " << static_cast<int> (el.cmd) << std::endl;

                // apply the command type on the initial position and get the occupancy type and occupied slots after the move is done  
                struct Slots_Occupancy *slots_occupancy;
                slots_occupancy = new Slots_Occupancy;
                slots_occupancy->r = el.r;
                slots_occupancy->cmd = el.cmd;
                slots_occupancy->slots_occupied = apply_command_on_idle_position(el.r, el.cmd, init_pos);

                // (x,y,occupancy_type, ID, cmd) - > add as an element to the current_occupancy 
                current_occupancy.push_back(*slots_occupancy);
            } else {
                break; // since elements are sorted by time, when we hit non zero time element we should stop
            }
        }

    } else { // there is a previous_occupancy
        // for element in previous_occupancy
        for (auto& prev_occupancy : previous_occupancy) {
            // if for element.r there are new command for current t in other_robot_commands
            bool found_new_command = false;
            for (auto& cmd : other_robots_commands) {
                // only interested in current t
                if (cmd.t == t) {
                    // check the robot ID
                    if (cmd.r == prev_occupancy.r) {
                        // new command found for this robot
                        // IMPORTANT: that means that robot can either be stopped or has been stopped before
                        found_new_command = true;

                        struct Slots_Occupancy *slots_occupancy;
                        slots_occupancy = new Slots_Occupancy;
                        slots_occupancy->r = prev_occupancy.r;
                        slots_occupancy->cmd = cmd.cmd;
                        if (cmd.cmd == Robot_Command_Type::stop) {
                            slots_occupancy->slots_occupied = move_robot_normally_or_stop(prev_occupancy.r, cmd.cmd, prev_occupancy.cmd, prev_occupancy.slots_occupied);
                        } else {
                            // Case where robot is idle before (NOT between the slots) and can change direction
                            slots_occupancy->slots_occupied = apply_command_on_idle_position(prev_occupancy.r, cmd.cmd, prev_occupancy.slots_occupied.begin()->first);
                        }
                        current_occupancy.push_back(*slots_occupancy);
                    }
                }
            }
            //else: no new cmds, robot moves normally
            if (!found_new_command) {
                std::cout << "No new command for this robot at this time" << std::endl;
                //apply normal movement to the previous occupancy state to generate a new one  
                struct Slots_Occupancy *slots_occupancy;
                slots_occupancy = new Slots_Occupancy;
                slots_occupancy->r = prev_occupancy.r;
                Robot_Command_Type new_cmd;
                switch (prev_occupancy.cmd) {
                    case Robot_Command_Type::acc_E:
                    case Robot_Command_Type::moving_E:
                        new_cmd = Robot_Command_Type::moving_E;
                        break;
                    case Robot_Command_Type::acc_N:
                    case Robot_Command_Type::moving_N:
                        new_cmd = Robot_Command_Type::moving_N;
                        break;
                    case Robot_Command_Type::acc_S:
                    case Robot_Command_Type::moving_S:
                        new_cmd = Robot_Command_Type::moving_S;
                        break;
                    case Robot_Command_Type::acc_W:
                    case Robot_Command_Type::moving_W:
                        new_cmd = Robot_Command_Type::moving_W;
                        break;
                    case Robot_Command_Type::stop:
                    case Robot_Command_Type::idle:
                        new_cmd = Robot_Command_Type::idle;
                        break;
                }
                slots_occupancy->cmd = new_cmd;
                slots_occupancy->slots_occupied = move_robot_normally_or_stop(prev_occupancy.r, new_cmd, prev_occupancy.cmd, prev_occupancy.slots_occupied);
                current_occupancy.push_back(*slots_occupancy);
            }
        }
    }

    std::cout << "Size of current occupancy list: " << current_occupancy.size() << std::endl;
    return current_occupancy;
}


// Function to check if the nodes in the tree are equivalent (TBA))


// Function to generate all possible next moves
// Basically it outputs nice new level of the decision tree

std::list<My_Robot_Space::TreeNode*> My_Robot_Space::generate_all_possible_next_moves(Robot_ID_t r, unsigned NS, unsigned EW, TreeNode *parent,
        std::pair<unsigned, unsigned> my_destinaniton, std::list<Slots_Occupancy> grid_occupancy) {
    std::list<TreeNode*> children;

    // Determine where can we move next after parent.state (what commands would be legal to execute)
    std::list<Robot_Command_Type> next_possible_states = get_next_possible_states(r, parent->state, parent->slots_occupied);

    // For each legal move, estimate what slots will be occupied after the execution (map of slots occupied)
    for (auto& state : next_possible_states) {
        std::map<std::pair<unsigned, unsigned>, Slot_Occupancy_Type> slots_to_be_occupied;
        if (state == Robot_Command_Type::stop || state == Robot_Command_Type::moving_E
                || state == Robot_Command_Type::moving_N || state == Robot_Command_Type::moving_S
                || state == Robot_Command_Type::moving_W) {
            slots_to_be_occupied = move_robot_normally_or_stop(r, state, parent->state, parent->slots_occupied);
        } else {
            slots_to_be_occupied = apply_command_on_idle_position(r, state, parent->slots_occupied.begin()->first);
        }

        bool collision = false;
        bool outside_the_grid = false;
        // Eliminate the move if it leads outside the grid
        for (auto& slot_to_be_occupied : slots_to_be_occupied) {
            if (slot_to_be_occupied.first.first >= EW || slot_to_be_occupied.first.second >= NS
                    || slot_to_be_occupied.first.first < 0 || slot_to_be_occupied.first.second < 0) {
                // Move outside the grid
                outside_the_grid = true;
                break;
            }

            // Eliminate the move, which leads to collisions with other robots based on the grid_occupancy
            // Check for collisions with every robot one by one
            for (auto& occupancy : grid_occupancy) {
                if (!collision) {
                    for (auto& occupied_slot : occupancy.slots_occupied) {
                        // Smart function to check if robots can be in different parts of the same slot goes here
                        // But we ain't have one yet so ...
                        if (occupied_slot.first.first == slot_to_be_occupied.first.first ||
                                occupied_slot.first.second == slot_to_be_occupied.first.second) {
                            collision = true;
                        }
                    }
                }
            }
        }

        // For each legal move create a TreeNode object add it to the output list
        if (!collision && !outside_the_grid) {
            struct TreeNode *child;
            child = new TreeNode;
            child->state = state;
            child->slots_occupied = slots_to_be_occupied;
            child->level = (parent->level)++;
            child->parent = parent;

            children.push_back(child);
        }

    }

    return children;
}


// Function to check if the goal is reached

bool My_Robot_Space::reached_the_goal(TreeNode* node, std::pair<unsigned, unsigned> goal) {
    // for slots occupied in node check if there are any goal slots
    for (auto& slot : node->slots_occupied) {
        if (slot.first.first == goal.first && slot.first.second == goal.second)
            // Smarter function to check that the slot is occupied fully comes here
            return true;
    }
    return false;
}


// Render the whole process

void My_Robot_Space::render(std::list<Robot_Command> other_robots_commands, std::list< Robot_Command > my_robots_commands,
        std::map<Robot_ID_t, std::pair<unsigned, unsigned>> robot_in_initial_situation) {

    // Initialize grid and fill it with zeros
    char **grid = new char *[10];

    for (int i = 0; i < 10; ++i) {
        grid[i] = new char[10];
        for (int j = 0; j < 10; ++j) {
            grid[i][j] = '0';
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

// Determine type of the robot

bool My_Robot_Space::is_fast(Robot_ID_t r) {
    if (r <= 127)
        return true;
    return false;
}

// Returns slots occupied after robot accelerates

std::map<std::pair<unsigned, unsigned>, My_Robot_Space::Slot_Occupancy_Type> My_Robot_Space::apply_command_on_idle_position(Robot_ID_t r,
        Robot_Command_Type cmd, std::pair<unsigned, unsigned> init_pos) {

    std::map<std::pair<unsigned, unsigned>, Slot_Occupancy_Type> slots_occupied;

    if (is_fast(r)) { // move fast robot
        switch (cmd) {
            case Robot_Command_Type::acc_E:
            {
                // move robot east from init_pos;
                std::cout << "Accelerate fast robot east" << std::endl;
                // init_pos is now occupied 1/2 on the east side of the slot
                // init_pos.x+1, init_pos.y is now occupied 1/2 on the west side of the slot
                std::pair<unsigned, unsigned> new_occupied_slot(init_pos.first + 1, init_pos.second);

                slots_occupied[init_pos] = Slot_Occupancy_Type::e_1_2;
                slots_occupied[new_occupied_slot] = Slot_Occupancy_Type::w_1_2;

                //std::cout << "Should be 3: " << static_cast<int> ((slots_occupied.begin()->first.second)) << std::endl;
            }
                break;
            case Robot_Command_Type::acc_N:
            {
                // move robot north from init_pos;
                std::cout << "Accelerate fast robot north" << std::endl;
                // init_pos is now occupied 3/4 on the north side of the slot
                // init_pos.x, init_pos.y+1 is now occupied 1/4 on the south side of the slot
                std::pair<unsigned, unsigned> new_occupied_slot(init_pos.first, init_pos.second + 1);

                slots_occupied[init_pos] = Slot_Occupancy_Type::n_3_4;
                slots_occupied[new_occupied_slot] = Slot_Occupancy_Type::s_1_4;
            }
                break;
            case Robot_Command_Type::acc_S:
            {
                // move robot south from init_pos;
                std::cout << "Accelerate fast robot south" << std::endl;
                // init_pos is now occupied 3/4 on the south side of the slot
                // init_pos.x+1, init_pos.y is now occupied 1/4 on the north side of the slot
                std::pair<unsigned, unsigned> new_occupied_slot(init_pos.first, init_pos.second - 1);

                slots_occupied[init_pos] = Slot_Occupancy_Type::s_3_4;
                slots_occupied[new_occupied_slot] = Slot_Occupancy_Type::n_1_4;
            }
                break;
            case Robot_Command_Type::acc_W:
            {
                // move robot west from init_pos;
                std::cout << "Accelerate fast robot west" << std::endl;
                // init_pos is now occupied 1/2 on the west side of the slot
                // init_pos.x-1, init_pos.y is now occupied 1/2 on the east side of the slot
                std::pair<unsigned, unsigned> new_occupied_slot(init_pos.first - 1, init_pos.second);

                slots_occupied[init_pos] = Slot_Occupancy_Type::w_1_2;
                slots_occupied[new_occupied_slot] = Slot_Occupancy_Type::e_1_2;
            }
                break;
            case Robot_Command_Type::stop:
            {
                // stop robot, unlikely to happen;
                std::cout << "Fast robot's first command is stop. Really? Why?" << std::endl;
            }
                break;
        }
    } else { // move slow robot
        switch (cmd) {
            case Robot_Command_Type::acc_E:
            {
                // move robot east from init_pos;
                std::cout << "Accelerate slow robot east" << std::endl;
                // init_pos is now occupied 3/4 on the east side of the slot
                // init_pos.x+1, init_pos.y is now occupied 1/4 on the west side of the slot
                std::pair<unsigned, unsigned> new_occupied_slot(init_pos.first + 1, init_pos.second);

                slots_occupied[init_pos] = Slot_Occupancy_Type::e_3_4;
                slots_occupied[new_occupied_slot] = Slot_Occupancy_Type::w_1_4;
            }
                break;
            case Robot_Command_Type::acc_N:
            {
                // move robot north from init_pos;
                std::cout << "Accelerate slow robot north" << std::endl;
                // init_pos is now occupied 7/8 on the north side of the slot
                // init_pos.x, init_pos.y+1 is now occupied 1/8 on the south side of the slot
                std::pair<unsigned, unsigned> new_occupied_slot(init_pos.first, init_pos.second + 1);

                slots_occupied[init_pos] = Slot_Occupancy_Type::n_7_8;
                slots_occupied[new_occupied_slot] = Slot_Occupancy_Type::s_1_8;
            }
                break;
            case Robot_Command_Type::acc_S:
            {
                // move robot south from init_pos;
                std::cout << "Accelerate slow robot south" << std::endl;
                // init_pos is now occupied 7/8 on the south side of the slot
                // init_pos.x, init_pos.y-1 is now occupied 1/8 on the north side of the slot
                std::pair<unsigned, unsigned> new_occupied_slot(init_pos.first, init_pos.second - 1);

                slots_occupied[init_pos] = Slot_Occupancy_Type::s_7_8;
                slots_occupied[new_occupied_slot] = Slot_Occupancy_Type::n_1_8;
            }
                break;
            case Robot_Command_Type::acc_W:
            {
                // move robot west from init_pos;
                std::cout << "Accelerate slow robot west" << std::endl;
                // init_pos is now occupied 3/4 on the west side of the slot
                // init_pos.x-1, init_pos.y is now occupied 1/4 on the east side of the slot
                std::pair<unsigned, unsigned> new_occupied_slot(init_pos.first - 1, init_pos.second);

                slots_occupied[init_pos] = Slot_Occupancy_Type::w_3_4;
                slots_occupied[new_occupied_slot] = Slot_Occupancy_Type::e_1_4;
            }
                break;
            case Robot_Command_Type::stop:
            {
                // stop robot, unlikely to happen;
                std::cout << "Slow robot's first command is stop. Really? Why?" << std::endl;
            }
                break;
        }
    }
    return slots_occupied;
}

// Returns slots occupied after robot moves normally or stops

std::map<std::pair<unsigned, unsigned>, My_Robot_Space::Slot_Occupancy_Type> My_Robot_Space::move_robot_normally_or_stop(Robot_ID_t r, Robot_Command_Type current_cmd,
        Robot_Command_Type previous_cmd, std::map<std::pair<unsigned, unsigned>, Slot_Occupancy_Type> slots_occupied) {

    std::map<std::pair<unsigned, unsigned>, Slot_Occupancy_Type> new_slots_occupied;

    if (is_fast(r)) { // move fast robot
        switch (current_cmd) {
            case Robot_Command_Type::idle:
            {
                std::cout << "Robot was stopped and remains unmoved" << std::endl;
                new_slots_occupied = slots_occupied;
            }
                break;
            case Robot_Command_Type::moving_E:
            {
                std::cout << "Move fast robot normally to the east" << std::endl;
                for (auto& slot : slots_occupied) {
                    if (slot.second == Slot_Occupancy_Type::e_1_2) {
                        std::pair<unsigned, unsigned> new_occupied_slot1(slot.first.first + 1, slot.first.second);
                        std::pair<unsigned, unsigned> new_occupied_slot2(slot.first.first + 2, slot.first.second);
                        new_slots_occupied[new_occupied_slot1] = Slot_Occupancy_Type::e_1_2;
                        new_slots_occupied[new_occupied_slot2] = Slot_Occupancy_Type::w_1_2;
                    }
                }
            }
                break;
            case Robot_Command_Type::moving_N:
            {
                std::cout << "Move fast robot normally to the north" << std::endl;
                for (auto& slot : slots_occupied) {
                    if (slot.second == Slot_Occupancy_Type::n_3_4) {
                        std::pair<unsigned, unsigned> new_occupied_slot1(slot.first.first, slot.first.second + 1);
                        new_slots_occupied[slot.first] = Slot_Occupancy_Type::n_1_4;
                        new_slots_occupied[new_occupied_slot1] = Slot_Occupancy_Type::s_3_4;
                    } else {
                        if (slot.second == Slot_Occupancy_Type::n_1_4) {
                            std::pair<unsigned, unsigned> new_occupied_slot1(slot.first.first, slot.first.second + 1);
                            std::pair<unsigned, unsigned> new_occupied_slot2(slot.first.first, slot.first.second + 2);
                            new_slots_occupied[new_occupied_slot1] = Slot_Occupancy_Type::n_3_4;
                            new_slots_occupied[new_occupied_slot2] = Slot_Occupancy_Type::s_1_4;
                        }
                    }
                }
            }
                break;
            case Robot_Command_Type::moving_S:
            {
                std::cout << "Move fast robot normally to the south" << std::endl;
                for (auto& slot : slots_occupied) {
                    if (slot.second == Slot_Occupancy_Type::s_3_4) {
                        std::pair<unsigned, unsigned> new_occupied_slot1(slot.first.first, slot.first.second - 1);
                        new_slots_occupied[slot.first] = Slot_Occupancy_Type::s_1_4;
                        new_slots_occupied[new_occupied_slot1] = Slot_Occupancy_Type::n_3_4;
                    } else {
                        if (slot.second == Slot_Occupancy_Type::s_1_4) {
                            std::pair<unsigned, unsigned> new_occupied_slot1(slot.first.first, slot.first.second - 1);
                            std::pair<unsigned, unsigned> new_occupied_slot2(slot.first.first, slot.first.second - 2);
                            new_slots_occupied[new_occupied_slot1] = Slot_Occupancy_Type::s_3_4;
                            new_slots_occupied[new_occupied_slot2] = Slot_Occupancy_Type::n_1_4;
                        }
                    }
                }
            }
                break;
            case Robot_Command_Type::moving_W:
            {
                std::cout << "Move fast robot normally to the west" << std::endl;
                for (auto& slot : slots_occupied) {
                    if (slot.second == Slot_Occupancy_Type::e_1_2) {
                        std::pair<unsigned, unsigned> new_occupied_slot1(slot.first.first - 1, slot.first.second);
                        std::pair<unsigned, unsigned> new_occupied_slot2(slot.first.first - 2, slot.first.second);
                        new_slots_occupied[new_occupied_slot1] = Slot_Occupancy_Type::w_1_2;
                        new_slots_occupied[new_occupied_slot2] = Slot_Occupancy_Type::e_1_2;
                    }
                }
            }
                break;
            case Robot_Command_Type::stop:
            {
                std::cout << "Stop the fast robot" << std::endl;
                switch (previous_cmd) {
                    case Robot_Command_Type::acc_E: // Fast robot moving east can be stopped right after acceleration
                    case Robot_Command_Type::moving_E:
                    {
                        for (auto& slot : slots_occupied) {
                            if (slot.second == Slot_Occupancy_Type::w_1_2) {
                                new_slots_occupied[slot.first] = Slot_Occupancy_Type::full;
                            }
                        }
                    }
                        break;
                    case Robot_Command_Type::acc_W: // Fast robot moving west can be stopped right after acceleration
                    case Robot_Command_Type::moving_W:
                    {
                        for (auto& slot : slots_occupied) {
                            if (slot.second == Slot_Occupancy_Type::e_1_2) {
                                new_slots_occupied[slot.first] = Slot_Occupancy_Type::full;
                            }
                        }
                    }
                        break;
                    case Robot_Command_Type::moving_N:
                    {
                        for (auto& slot : slots_occupied) {
                            if (slot.second == Slot_Occupancy_Type::s_3_4) {
                                new_slots_occupied[slot.first] = Slot_Occupancy_Type::full;
                            }
                        }
                    }
                        break;
                    case Robot_Command_Type::moving_S:
                    {
                        for (auto& slot : slots_occupied) {
                            if (slot.second == Slot_Occupancy_Type::n_3_4) {
                                new_slots_occupied[slot.first] = Slot_Occupancy_Type::full;
                            }
                        }
                    }
                        break;
                }
            }
                break;
        }
    } else { // move slow robot
        switch (current_cmd) {
            case Robot_Command_Type::idle:
            {
                std::cout << "Robot was stopped and remains unmoved" << std::endl;
                new_slots_occupied = slots_occupied;
            }
                break;
            case Robot_Command_Type::moving_E:
            {
                std::cout << "Move slow robot normally to the east" << std::endl;
                for (auto& slot : slots_occupied) {
                    if (slot.second == Slot_Occupancy_Type::e_3_4) {
                        std::pair<unsigned, unsigned> new_occupied_slot1(slot.first.first + 1, slot.first.second);
                        new_slots_occupied[slot.first] = Slot_Occupancy_Type::e_1_4;
                        new_slots_occupied[new_occupied_slot1] = Slot_Occupancy_Type::w_3_4;
                    } else {
                        if (slot.second == Slot_Occupancy_Type::e_1_4) {
                            std::pair<unsigned, unsigned> new_occupied_slot1(slot.first.first + 1, slot.first.second);
                            std::pair<unsigned, unsigned> new_occupied_slot2(slot.first.first + 2, slot.first.second);
                            new_slots_occupied[new_occupied_slot1] = Slot_Occupancy_Type::e_3_4;
                            new_slots_occupied[new_occupied_slot2] = Slot_Occupancy_Type::w_1_4;
                        }
                    }
                }
            }
                break;
            case Robot_Command_Type::moving_N:
            {
                std::cout << "Move slow robot normally to the north" << std::endl;
                for (auto& slot : slots_occupied) {
                    switch (slot.second) {
                            // Case 1 
                        case (Slot_Occupancy_Type::n_7_8):
                        {
                            std::pair<unsigned, unsigned> new_occupied_slot1(slot.first.first, slot.first.second + 1);
                            new_slots_occupied[slot.first] = Slot_Occupancy_Type::n_5_8;
                            new_slots_occupied[new_occupied_slot1] = Slot_Occupancy_Type::s_3_8;
                        }
                            break;
                            // Case 2
                        case(Slot_Occupancy_Type::n_5_8):
                        {
                            std::pair<unsigned, unsigned> new_occupied_slot1(slot.first.first, slot.first.second + 1);
                            new_slots_occupied[slot.first] = Slot_Occupancy_Type::n_3_8;
                            new_slots_occupied[new_occupied_slot1] = Slot_Occupancy_Type::s_5_8;
                        }
                            break;
                            // Case 3
                        case(Slot_Occupancy_Type::n_3_8):
                        {
                            std::pair<unsigned, unsigned> new_occupied_slot1(slot.first.first, slot.first.second + 1);
                            new_slots_occupied[slot.first] = Slot_Occupancy_Type::n_1_8;
                            new_slots_occupied[new_occupied_slot1] = Slot_Occupancy_Type::s_7_8;
                        }
                            break;
                            // Case 4
                        case(Slot_Occupancy_Type::n_1_8):
                        {
                            std::pair<unsigned, unsigned> new_occupied_slot1(slot.first.first, slot.first.second + 1);
                            std::pair<unsigned, unsigned> new_occupied_slot2(slot.first.first, slot.first.second + 2);
                            new_slots_occupied[new_occupied_slot1] = Slot_Occupancy_Type::n_7_8;
                            new_slots_occupied[new_occupied_slot2] = Slot_Occupancy_Type::s_1_8;
                        }
                            break;
                    }
                }
            }
                break;
            case Robot_Command_Type::moving_S:
            {
                std::cout << "Move slow robot normally to the south" << std::endl;
                for (auto& slot : slots_occupied) {
                    switch (slot.second) {
                            // Case 1 
                        case (Slot_Occupancy_Type::s_7_8):
                        {
                            std::pair<unsigned, unsigned> new_occupied_slot1(slot.first.first, slot.first.second - 1);
                            new_slots_occupied[slot.first] = Slot_Occupancy_Type::s_5_8;
                            new_slots_occupied[new_occupied_slot1] = Slot_Occupancy_Type::n_3_8;
                        }
                            break;
                            // Case 2
                        case(Slot_Occupancy_Type::s_5_8):
                        {
                            std::pair<unsigned, unsigned> new_occupied_slot1(slot.first.first, slot.first.second - 1);
                            new_slots_occupied[slot.first] = Slot_Occupancy_Type::s_3_8;
                            new_slots_occupied[new_occupied_slot1] = Slot_Occupancy_Type::n_5_8;
                        }
                            break;
                            // Case 3
                        case(Slot_Occupancy_Type::s_3_8):
                        {
                            std::pair<unsigned, unsigned> new_occupied_slot1(slot.first.first, slot.first.second - 1);
                            new_slots_occupied[slot.first] = Slot_Occupancy_Type::s_1_8;
                            new_slots_occupied[new_occupied_slot1] = Slot_Occupancy_Type::n_7_8;
                        }
                            break;
                            // Case 4
                        case(Slot_Occupancy_Type::s_1_8):
                        {
                            std::pair<unsigned, unsigned> new_occupied_slot1(slot.first.first, slot.first.second - 1);
                            std::pair<unsigned, unsigned> new_occupied_slot2(slot.first.first, slot.first.second - 2);
                            new_slots_occupied[new_occupied_slot1] = Slot_Occupancy_Type::s_7_8;
                            new_slots_occupied[new_occupied_slot2] = Slot_Occupancy_Type::n_1_8;
                        }
                            break;
                    }
                }
            }
                break;
            case Robot_Command_Type::moving_W:
            {
                std::cout << "Move slow robot normally to the west" << std::endl;
                for (auto& slot : slots_occupied) {
                    if (slot.second == Slot_Occupancy_Type::w_3_4) {
                        std::pair<unsigned, unsigned> new_occupied_slot1(slot.first.first - 1, slot.first.second);
                        new_slots_occupied[slot.first] = Slot_Occupancy_Type::w_1_4;
                        new_slots_occupied[new_occupied_slot1] = Slot_Occupancy_Type::e_3_4;
                    } else {
                        if (slot.second == Slot_Occupancy_Type::w_1_4) {
                            std::pair<unsigned, unsigned> new_occupied_slot1(slot.first.first - 1, slot.first.second);
                            std::pair<unsigned, unsigned> new_occupied_slot2(slot.first.first - 2, slot.first.second);
                            new_slots_occupied[new_occupied_slot1] = Slot_Occupancy_Type::w_3_4;
                            new_slots_occupied[new_occupied_slot2] = Slot_Occupancy_Type::e_1_4;
                        }
                    }
                }
            }
                break;
            case Robot_Command_Type::stop:
            {
                std::cout << "Stop the slow robot" << std::endl;
                switch (previous_cmd) {
                    case Robot_Command_Type::moving_E:
                    {
                        for (auto& slot : slots_occupied) {
                            if (slot.second == Slot_Occupancy_Type::w_3_4) {
                                new_slots_occupied[slot.first] = Slot_Occupancy_Type::full;
                            }
                        }
                    }
                        break;
                    case Robot_Command_Type::moving_W:
                    {
                        for (auto& slot : slots_occupied) {
                            if (slot.second == Slot_Occupancy_Type::e_3_4) {
                                new_slots_occupied[slot.first] = Slot_Occupancy_Type::full;
                            }
                        }
                    }
                        break;
                    case Robot_Command_Type::moving_N:
                    {
                        for (auto& slot : slots_occupied) {
                            if (slot.second == Slot_Occupancy_Type::s_7_8) {
                                new_slots_occupied[slot.first] = Slot_Occupancy_Type::full;
                            }
                        }
                    }
                        break;
                    case Robot_Command_Type::moving_S:
                    {
                        for (auto& slot : slots_occupied) {
                            if (slot.second == Slot_Occupancy_Type::n_7_8) {
                                new_slots_occupied[slot.first] = Slot_Occupancy_Type::full;
                            }
                        }
                    }
                        break;
                }
            }
                break;
        }
    }
    return new_slots_occupied;
}

std::list<My_Robot_Space::Robot_Command_Type> My_Robot_Space::get_next_possible_states(Robot_ID_t r, Robot_Command_Type prev_state,
        std::map<std::pair<unsigned, unsigned>, Slot_Occupancy_Type> prev_slots_occupied) {

    std::list<Robot_Command_Type> next_legal_states;

    if (is_fast(r)) {
        switch (prev_state) {
            case Robot_Command_Type::stop:
            case Robot_Command_Type::idle:
                next_legal_states.push_back(Robot_Command_Type::acc_E);
                next_legal_states.push_back(Robot_Command_Type::acc_W);
                next_legal_states.push_back(Robot_Command_Type::acc_N);
                next_legal_states.push_back(Robot_Command_Type::acc_S);
                break;
            case Robot_Command_Type::acc_E:
                next_legal_states.push_back(Robot_Command_Type::stop);
                next_legal_states.push_back(Robot_Command_Type::moving_E);
                break;
            case Robot_Command_Type::acc_W:
                next_legal_states.push_back(Robot_Command_Type::stop);
                next_legal_states.push_back(Robot_Command_Type::moving_W);
                break;
            case Robot_Command_Type::acc_N:
                next_legal_states.push_back(Robot_Command_Type::moving_E);
                break;
            case Robot_Command_Type::acc_S:
                next_legal_states.push_back(Robot_Command_Type::moving_S);
                break;
            case Robot_Command_Type::moving_E:
                next_legal_states.push_back(Robot_Command_Type::moving_E);
                next_legal_states.push_back(Robot_Command_Type::stop);
                break;
            case Robot_Command_Type::moving_W:
                next_legal_states.push_back(Robot_Command_Type::moving_W);
                next_legal_states.push_back(Robot_Command_Type::stop);
                break;
            case Robot_Command_Type::moving_N:
                next_legal_states.push_back(Robot_Command_Type::moving_N);
                // Make sure that moving_N was executed odd number of time before stopping
                for (auto& slot : prev_slots_occupied) {
                    if (slot.second == Slot_Occupancy_Type::s_3_4 || slot.second == Slot_Occupancy_Type::n_1_4) {
                        next_legal_states.push_back(Robot_Command_Type::stop);
                        break;
                    }
                }
                break;
            case Robot_Command_Type::moving_S:
                next_legal_states.push_back(Robot_Command_Type::moving_S);
                // Make sure that moving_S was executed odd number of time before stopping
                for (auto& slot : prev_slots_occupied) {
                    if (slot.second == Slot_Occupancy_Type::n_3_4 || slot.second == Slot_Occupancy_Type::s_1_4) {
                        next_legal_states.push_back(Robot_Command_Type::stop);
                        break;
                    }
                }
                break;
        }
    } else {
        switch (prev_state) {
            case Robot_Command_Type::stop:
            case Robot_Command_Type::idle:
                next_legal_states.push_back(Robot_Command_Type::acc_E);
                next_legal_states.push_back(Robot_Command_Type::acc_W);
                next_legal_states.push_back(Robot_Command_Type::acc_N);
                next_legal_states.push_back(Robot_Command_Type::acc_S);
                break;
            case Robot_Command_Type::acc_E:
                next_legal_states.push_back(Robot_Command_Type::moving_E);
                break;
            case Robot_Command_Type::acc_W:
                next_legal_states.push_back(Robot_Command_Type::moving_W);
                break;
            case Robot_Command_Type::acc_N:
                next_legal_states.push_back(Robot_Command_Type::moving_E);
                break;
            case Robot_Command_Type::acc_S:
                next_legal_states.push_back(Robot_Command_Type::moving_S);
                break;
            case Robot_Command_Type::moving_E:
                next_legal_states.push_back(Robot_Command_Type::moving_E);
                // Make sure that moving_E was executed odd number of times before stopping
                for (auto& slot : prev_slots_occupied) {
                    if (slot.second == Slot_Occupancy_Type::w_3_4 || slot.second == Slot_Occupancy_Type::e_1_4) {
                        next_legal_states.push_back(Robot_Command_Type::stop);
                        break;
                    }
                }
                break;
            case Robot_Command_Type::moving_W:
                next_legal_states.push_back(Robot_Command_Type::moving_W);
                // Make sure that moving_W was executed odd number of times before stopping
                for (auto& slot : prev_slots_occupied) {
                    if (slot.second == Slot_Occupancy_Type::e_3_4 || slot.second == Slot_Occupancy_Type::w_1_4) {
                        next_legal_states.push_back(Robot_Command_Type::stop);
                        break;
                    }
                }
                break;
            case Robot_Command_Type::moving_N:
                next_legal_states.push_back(Robot_Command_Type::moving_N);
                // Make sure that moving_N was executed 3*x number of time before stopping
                for (auto& slot : prev_slots_occupied) {
                    if (slot.second == Slot_Occupancy_Type::s_7_8 || slot.second == Slot_Occupancy_Type::n_1_8) {
                        next_legal_states.push_back(Robot_Command_Type::stop);
                        break;
                    }
                }
                break;
            case Robot_Command_Type::moving_S:
                next_legal_states.push_back(Robot_Command_Type::moving_S);
                // Make sure that moving_S was executed 3*x number of time before stopping
                for (auto& slot : prev_slots_occupied) {
                    if (slot.second == Slot_Occupancy_Type::n_7_8 || slot.second == Slot_Occupancy_Type::s_1_8) {
                        next_legal_states.push_back(Robot_Command_Type::stop);
                        break;
                    }
                }
                break;
        }
    }

    return next_legal_states;

}
