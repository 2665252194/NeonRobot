#include "graphics.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "robot_background.h"
#include "robot_data.h"


//Welcome to robot.c
//Here you will find some functions about the robot






//Set the number of total markers
int marker_number = 2;



//struct the robot
struct robot
{
    int orientation;
    int robot_x;
    int robot_y;
    int carry;//Return the number of markers the robot is carrying
    int stop;//Whether the game is over
    int Memory_System;//Whether the robot should have memory
    int clash_time;//I will explain this later in the algorithm
    int is_obstacle;//Whether meeting an obstacle

};



//Function used to draw robot and move forward
void forward(struct robot *a)
{
    if(a->orientation == 1)
    {
        //Each time we plus 1 in its abstracted coordinate (from 0,0 to maximum)
        a->robot_y = a->robot_y - 1;
    }
    else if (a->orientation == 2)
    {
        a->robot_x  =  a->robot_x + 1;
    }
    else if (a->orientation == 3)
    {
        a->robot_y = a->robot_y + 1;
    }
    else if (a->orientation == 4)
    {
        a->robot_x = a->robot_x - 1;
    }
    else
    {
        printf("Where's your orientation?\n");
    }


    //Draw the robot
    foreground();
    clear();
    setColour(green);
    fillRect(O_x + unit_size * (a->robot_x) ,O_y + unit_size * (a->robot_y) ,40 ,40);

    //If robot is carrying something, draw a sign on his body
    if(a->carry > 0)
    {
        setRGBColour(148,0,211);
        fillRect(O_x + unit_size * (a->robot_x) + 10,O_y + unit_size * (a->robot_y) + 10, 10, 10);

    }
}

//Let us make the left function
void left(struct robot *a)
{
    if(a->orientation == 1)
    {
        //check the orientation and then change the orientation
        a->orientation = 4;
    }
    else if (a->orientation == 2)
    {
        a->orientation = 1;
    }
    else if (a->orientation == 3)
    {
        a->orientation = 2;
    }
    else if (a->orientation == 4)
    {
        a->orientation = 3;
    }
}
//same as the left function
void right(struct robot *a)
{
    if(a->orientation == 1)
    {
        a->orientation = 2;
    }
    else if (a->orientation == 2)
    {
        a->orientation = 3;
    }
    else if (a->orientation == 3)
    {
        a->orientation = 4;
    }
    else if (a->orientation == 4)
    {
        a->orientation = 1;
    }
}

//Check whether it is in a marker
int atMarker(struct robot *a)
{
    if(unit_array[a->robot_y][a->robot_x] == 1)//Remeber swapping x and y because it is rom and column for 2D array!!
    {
        return 1;
    }
    else
    {
        return -1;
    }
}


void pickUpMarker(struct robot *a)
{
    //First set it back to 0
    unit_array[a->robot_y][a->robot_x] = 0;

    //You are going to find a corner so you don't really need memory anymore
    a->Memory_System = 0;

    //carry should plus one
    a->carry = a->carry + 1;

    //Redraw the arena
    Create_arena();

    //Redraw the markers left
    if(unit_array[marker_y][marker_x] == 1)
    {
        draw_item(marker_x, marker_y, 1);
    }

    if(unit_array[marker_y_2][marker_x_2] == 1)
    {
        draw_item(marker_x_2, marker_y_2, 1);
    }

    if(unit_array[0][0] == 3)
    {
        draw_item(0,0, 3);
    }

    if(unit_array[0][tmp_max_x] == 3)
    {
        draw_item(tmp_max_x,0, 3);
    }

    if(unit_array[tmp_max_y][0] == 3)
    {
        draw_item(0,tmp_max_y, 3);
    }

    if(unit_array[tmp_max_y][tmp_max_x] == 3)
    {
        draw_item(tmp_max_x,tmp_max_y,3);
    }


    //Redraw the obstacle
    draw_item(obs_x,obs_y,2);
    draw_item(obs_x_2,obs_y_2,2);

    
}


void drpoMarker(struct robot *a)
{
    //Drop the marker at corner 
    if((a->robot_x == 0 && a->robot_y == 0) || (a->robot_x == 0 && a->robot_y == max_y) || (a->robot_x == max_x && a->robot_y == 0) || (a->robot_x == max_x && a->robot_y == max_y))
    {
        a->carry = a->carry - 1;
        draw_item(a->robot_x, a->robot_y, 3);
        marker_number = marker_number - 1;

        //If there is no marker left, game is over
        if(marker_number <= 0)
        {
            a->stop = 1;
        }
        else
        {
            //If there is marker left, turn on the memory and keep going
            a->Memory_System = 1;
            a->clash_time = 0;
        }
    }
    
}


int canMoveForward(struct robot *a)
{
    //check the orientation
    if(a->orientation == 1)//North
    {
        //First case, it is a wall
        if(a->robot_y == min_y)
        {
            return -1;
        }
        //Second case, it is a obstacle
        else if (unit_array[a->robot_y - 1][a->robot_x] == -1)//Remeber swapping x and y because it is rom and column for 2D array!!
        {

            //If that is an obstacle, let me know
            a->is_obstacle = 1;
            return -1;
        }
    }else if(a->orientation == 2)//East
    {

        if(a->robot_x >= max_x) 
        {
            return -1;
        }
        else if (unit_array[a->robot_y][a->robot_x + 1] == -1)//Remeber swapping x and y because it is rom and column for 2D array!!
        {   
            a->is_obstacle = 1;
            return -1;
        }
    }else if(a->orientation == 3)
    {
        if(a->robot_y >= max_y)
        {
            return -1;
        }
        else if (unit_array[a->robot_y+1][a->robot_x] == -1)
        {
            a->is_obstacle = 1;
            return -1;
        }   
    }else if(a->orientation == 4)
    {
        if(a->robot_x == min_x)
        {
            return -1;
        }
        else if (unit_array[a->robot_y][a->robot_x - 1] == -1)
        {
            a->is_obstacle = 1;
            return -1;       
        }
    }
    //If we go through every if-sentence successfully
    //We return 1
    return 1;
}





//This function control the memory
void memory_control(struct robot *a)
{
    if( (a->is_obstacle == 0)&&(a->Memory_System == 1) && (a->clash_time > 1) &&(a->robot_x == min_x || a->robot_x == max_x))
    {
        distance_count = distance_count + 1;

        //If the robot successfully goes through min_x or max_x, we can narrow the max_x and min_x
        //Keep narrowing the edge and one day the robot will find the marker
        if( (distance_count >= (max_y) && (a->robot_x == min_x) ))
        {
            min_x = min_x + 1;
            tmp_changing_min_x = min_x;
            distance_count = 0;
            
        }else if( (distance_count >= (max_y)) && (a->robot_x == max_x) )
        {
            max_x = max_x - 1;
            tmp_changing_max_x = max_x;
            distance_count = 0;
        }
    
    //If I turned off the memory, the min_x and max_x should reset to the default
    //So that the robot can find the corner
    }else if(a->Memory_System == 0)
    {
        max_x = tmp_max_x;
        min_x = 0;


        tmp_changing_max_x = max_x;
        tmp_changing_min_x = min_x;
    }
}



//Integrate these functions
int setup_robot(struct robot *a)
{

    //Set up the robot position
    a->robot_x = robot_start_x;
    a->robot_y = robot_start_y;
    a->orientation = robot_start_orientation;
    a->stop = 0;
    a->carry = 0;
    a->Memory_System = 1;
    a->clash_time = 0;
    a->is_obstacle = 0;



    //i stands for running time
    //j stands for the time of stuck
    //if j is over a value we can confirm the robot is stuck
    int i = 0;
    int j = 0;
    int stuck = 0;


    //Go robot!
    while(i<600 && a->stop == 0)
    {
        if(canMoveForward(a) == 1)
        {
            //go forward
            memory_control(a);
            forward(a);
            sleep(50);

            //If robot find an obstacle, keep turning left until it can do so
            if(a->is_obstacle == 1)
            {

                //Change the edge temporialy avoiding stuck 
                if(a->orientation == 1)
                {
                    max_x = a->robot_x + 2;
                }
                else if(a->orientation == 3)
                {
                    min_x = a->robot_x - 2;
                }


                //Try turn left
                left(a);

                //If can not turn left, that's fine we turn back
                if(canMoveForward(a) == -1)
                {
                    right(a);

                    //If still can not move, robot has crossed the obstacle
                    if((canMoveForward(a) == -1) || stuck == 1)
                    {
                        //j can be 0
                        j = 0;
                        //No more obstacle then
                        a->is_obstacle = 0;
                        //distance_count should plus 2
                        distance_count = distance_count + 2;
                        //Set back the edge
                        max_x = tmp_changing_max_x;
                        min_x = tmp_changing_min_x;
                        stuck = 0;
                    }
                    else
                    {
                        //If can move, the robot is going like a cycle around the obstacle
                        j = j + 1;
                    }
                }
                //If robot has done a whole cycle, definitely stuck then
                if(j>4)
                {
                    stuck = 1;
                }
            }
        }
        else//If it is only a wall
        {
            //And make sure is_obstacle is 0
            if(a->is_obstacle == 0)
            {
                //We plus the clash_time
                //If clash_time > 2, the robot is definitely at min_x or max_x
                a->clash_time = a->clash_time + 1;
            }

            right(a);//Then turn right
        }
        if(atMarker(a) == 1)
        {
            pickUpMarker(a);
        }
        if(a->carry > 0)
        {
            drpoMarker(a);
        }

        i = i + 1;





    }

}

int main(void)
{
    //initialize the data
    initialize_arena_dimensions();

    //Then set the window size
    setWindowSize(width, height);

    //Create the arena
    Create_arena();

    //Draw the item
    draw_item(marker_x, marker_y,1);
    draw_item(marker_x_2, marker_y_2,1);
    draw_item(obs_x,obs_y,2);
    draw_item(obs_x_2,obs_y_2,2);

    //Declare a robot
    struct robot *Robot;
    //Allocate meomory to it
    Robot = malloc(sizeof(struct robot));
    //Setup
    setup_robot(Robot);

    return 0;
}