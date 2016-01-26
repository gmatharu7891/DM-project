#include "robot.h"
#include <iostream>

//create commands for fast robot in circular(c)[s=stepwise and initialization=1,1] motion anticlockwise(a)
std::list<My_Robot_Space::Robot_Command> My_Robot_Space::generate_sample_other_robots_commands(char direction, int robot_id, char movement)
{
    std::list<Robot_Command> other_robots_commands;
    
    //std::cout<<direction<<" "<<robot_id<<" "<<movement<<" "<<std::endl;
    Robot_Command cmd;
    //fast robot moving anti clockwise circular motion
    if(robot_id<128 and direction =='a' and movement=='c')
    {
        cmd.t=0;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_E;
        other_robots_commands.push_back(cmd);

        cmd.t=6;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);

        cmd.t=7;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_N;
        other_robots_commands.push_back(cmd);

        cmd.t=19;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);

        cmd.t=20;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_W;
        other_robots_commands.push_back(cmd);

        cmd.t=26;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);

        cmd.t=27;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_S;
        other_robots_commands.push_back(cmd);

        cmd.t=39;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);
    }
    //slow robot moving anticlockwise and with circular movement starting at 1,1 or 0,0
    else if(robot_id>=128 and direction =='a' and movement=='c')
    {
        cmd.t=0;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_E;
        other_robots_commands.push_back(cmd);

        cmd.t=12;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);

        cmd.t=13;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_N;
        other_robots_commands.push_back(cmd);

        cmd.t=37;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);

        cmd.t=38;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_W;
        other_robots_commands.push_back(cmd);

        cmd.t=50;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);

        cmd.t=51;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_S;
        other_robots_commands.push_back(cmd);

        cmd.t=75;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);
    }
    //slow robot moving anticlockwise and with step movement starting at 2,2
    else if(robot_id>=128 and direction =='a' and movement=='s')
    {
        cmd.t=0;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_E;
        other_robots_commands.push_back(cmd);

        cmd.t=4;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);

        cmd.t=5;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_N;
        other_robots_commands.push_back(cmd);

        cmd.t=9;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);

        cmd.t=10;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_E;
        other_robots_commands.push_back(cmd);

        cmd.t=12;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);

        cmd.t=13;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_N;
        other_robots_commands.push_back(cmd);

        cmd.t=17;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);

        cmd.t=18;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_E;
        other_robots_commands.push_back(cmd);

        cmd.t=20;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);

        cmd.t=21;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_N;
        other_robots_commands.push_back(cmd);

        cmd.t=25;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);

        cmd.t=26;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_E;
        other_robots_commands.push_back(cmd);

        cmd.t=28;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);

        cmd.t=29;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_N;
        other_robots_commands.push_back(cmd);

        cmd.t=33;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);

        cmd.t=34;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_W;
        other_robots_commands.push_back(cmd);

        cmd.t=36;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);

        cmd.t=37;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_S;
        other_robots_commands.push_back(cmd);

        cmd.t=41;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);

        cmd.t=42;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_W;
        other_robots_commands.push_back(cmd);

        cmd.t=44;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);

        cmd.t=45;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_S;
        other_robots_commands.push_back(cmd);

        cmd.t=48;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);

        cmd.t=49;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_W;
        other_robots_commands.push_back(cmd);

        cmd.t=51;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);

        cmd.t=52;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_S;
        other_robots_commands.push_back(cmd);

        cmd.t=56;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);

        cmd.t=57;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_W;
        other_robots_commands.push_back(cmd);

        cmd.t=59;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);

        cmd.t=60;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_S;
        other_robots_commands.push_back(cmd);

        cmd.t=64;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);
    }
    // fast robot step movement
    else if(robot_id<128 && direction =='a' && movement=='s')
    {
        cmd.t=0;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_E;
        other_robots_commands.push_back(cmd);

        cmd.t=1;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);

        cmd.t=2;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_N;
        other_robots_commands.push_back(cmd);

        cmd.t=4;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);

        cmd.t=5;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_E;
        other_robots_commands.push_back(cmd);

        cmd.t=6;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);

        cmd.t=7;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_N;
        other_robots_commands.push_back(cmd);

        cmd.t=9;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);

        cmd.t=10;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_E;
        other_robots_commands.push_back(cmd);

        cmd.t=11;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);

        cmd.t=12;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_N;
        other_robots_commands.push_back(cmd);

        cmd.t=14;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);

        cmd.t=15;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_E;
        other_robots_commands.push_back(cmd);

        cmd.t=16;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);

        cmd.t=17;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_N;
        other_robots_commands.push_back(cmd);

        cmd.t=19;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);

        cmd.t=20;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_W;
        other_robots_commands.push_back(cmd);

        cmd.t=21;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);

        cmd.t=22;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_S;
        other_robots_commands.push_back(cmd);

        cmd.t=24;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);

        cmd.t=25;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_W;
        other_robots_commands.push_back(cmd);

        cmd.t=26;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);

        cmd.t=27;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_S;
        other_robots_commands.push_back(cmd);

        cmd.t=29;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);

        cmd.t=30;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_W;
        other_robots_commands.push_back(cmd);

        cmd.t=31;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);

        cmd.t=32;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_S;
        other_robots_commands.push_back(cmd);

        cmd.t=34;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);

        cmd.t=35;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_W;
        other_robots_commands.push_back(cmd);

        cmd.t=36;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);

        cmd.t=37;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::acc_S;
        other_robots_commands.push_back(cmd);

        cmd.t=39;
        cmd.r=robot_id;
        cmd.cmd=Robot_Command_Type::stop;
        other_robots_commands.push_back(cmd);
    }


    /*for(std::list<Robot_Command>::iterator list_iter = other_robots_commands.begin();list_iter != other_robots_commands.end(); list_iter++)
    {
        Robot_Command cm=*list_iter;
        std::cout<< static_cast<int>(cm.t)<<" ";
        if(static_cast<int>(cm.cmd) == 0)
            std::cout<< "acc_E"<<" ";
        if(static_cast<int>(cm.cmd) == 1)
            std::cout<< "acc_N"<<" ";
        if(static_cast<int>(cm.cmd) == 2)
            std::cout<< "acc_W"<<" ";
        if(static_cast<int>(cm.cmd) == 3)
            std::cout<< "acc_S"<<" ";
        if(static_cast<int>(cm.cmd) == 4)
            std::cout<< "stop"<<" ";
    }*/
    
    return other_robots_commands;
}
