#include "graphics.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "robot_background.h"
#include "robot_data.h"






//Welcome to robot.c!
//Here you will find the functions about the robot

//Design the robot structure
struct robot
{
    int orientation;
    float robot_x;
    float robot_y;
    int carry;//Check whether the robot is carrying marker
    int stop;
    int mark;
    int Memory_System;
    int clash_time;
    int is_obstacle;

};



//Function used to draw robot and move forward
void forward(struct robot *a)
{
    if(a->orientation == 1)
    {
        //Each time we plus 0.2 in its abstracted coordinate (from 0,0 to maximum)
        a->robot_y = a->robot_y - 0.2;
    }
    else if (a->orientation == 2)
    {
        a->robot_x  =  a->robot_x + 0.2;
    }
    else if (a->orientation == 3)
    {
        a->robot_y = a->robot_y + 0.2;
    }
    else if (a->orientation == 4)
    {
        a->robot_x = a->robot_x - 0.2;
    }
    else
    {
        printf("Where's your orientation?\n");
    }


    //Draw the robot, it can be whatever shape
    foreground();
    clear();
    setColour(green);
    fillRect(O_x + unit_size * (a->robot_x) ,O_y + unit_size * (a->robot_y) ,40 ,40);

    //If robot is carrying something, let us draw something on his head!
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
    //Check which unit(fillet) is the robot in
    int int_x, int_y;
    int_x = (int)a->robot_x;
    int_y = (int)a->robot_y;
 
    if(unit_array[int_y][int_x] == 1)//Remeber swapping x and y because it is rom and column for 2D array!!
    {
        //After the robot take the marker, Reset the value to 0, logically the marker is gone
        unit_array[int_y][int_x] = 0;

        return 1;
    }
    else
    {
        return -1;
    }
}


void pickUpMarker(struct robot *a)
{
    //After picking up let us turn on the carry
    a->carry = a->carry + 1;

    //Redraw the arena
    Create_arena();
    
}


void drpoMarker(struct robot *a)
{
    int int_x = 0;
    int int_y = 0;
    int_x = (int)a->robot_x;
    int_y = (int)a->robot_y;

    //Drop the marker at corner 
    if((int_x == 0 && int_y == 0) || (int_x == 0 && int_y == max_y) || (int_x == max_x && int_y == 0) || (int_x == max_x && int_y == max_y))
    {
        a->carry = 0;
        draw_item(int_x, int_y, 3);
        forward(a);
        a->stop = 1;
    }
    
}


int canMoveForward(struct robot *a)
{
    //Check which unit is the robot in
    int int_x = 0;
    int int_y = 0;
    int_x = (int)a->robot_x;
    int_y = (int)a->robot_y;
    //Then check the orientation
    if(a->orientation == 1)//North
    {
        //First case, it is a wall!
        if(a->robot_y - min_y < 0.1)
        {
            a->robot_y = min_y;//Reset the coordinate to integer value
            return -1;
        }
        //Second case, it is a obstacle!
        else if (unit_array[int_y][int_x] == -1)//Remeber swapping x and y because it is rom and column for 2D array!!
        {
            a->robot_y = int_y + 1;
            a->is_obstacle = 1;
            return -1;
        }
    }else if(a->orientation == 2)//East
    {

        if(int_x == max_x) 
        {
            a->robot_x = max_x;

            return -1;
        }
        else if (unit_array[int_y][int_x+1] == -1)//Remeber swapping x and y because it is rom and column for 2D array!!
        {
            a->robot_x = int_x;
            //printf("%d\n %f\n %f\n", a->orientation,a->robot_x,a->robot_y);
            a->is_obstacle = 1;
            return -1;
        }
    }else if(a->orientation == 3)
    {
        if(int_y == max_y)
        {
            a->robot_y = max_y;
            return -1;
        }
        else if (unit_array[int_y+1][int_x] == -1)
        {
            a->robot_y = int_y;
            a->is_obstacle = 1;
            return -1;
        }   
    }else if(a->orientation == 4)
    {
        if(a->robot_x - min_x < 0.1)
        {
            a->robot_x = min_x;
            return -1;
        }
        else if (unit_array[int_y][int_x] == -1)
        {
            a->robot_x = int_x + 1;
            a->is_obstacle = 1;
            return -1;       
        }
    }
    //If we go through every if-sentence successfully
    //We return 1
    return 1;
}

void memory_control(struct robot *a)
{
    int int_x;
    int_x = (int)a->robot_x;
    if( (a->Memory_System == 1) &&(a->clash_time > 1)&&(int_x == min_x || int_x == max_x) && (a->orientation == 1 || a->orientation == 3))
    {
        distance_count = distance_count + 0.1;
        if( (distance_count - (max_y + 1) < -0.5) && (int_x == min_x) )
        {
            min_x = min_x + 1;
            
        }else if( (distance_count - (max_y + 1) < -0.5) && (int_x == max_x) )
        {
            max_x = max_x - 1;
        }
    }else if(a->Memory_System == 0)
    {
        max_x = tmp_max_x;
        min_x = 0;

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



    //Use an index to exit the program in case of bugs
    int i = 0;

    //Write the algorithm here
    while(i<2000 && a->stop == 0)
    {
        if(canMoveForward(a) == 1)
        {
            forward(a);
            memory_control(a);
            sleep(10);
        }
        else if (canMoveForward(a) == -1 && a->is_obstacle == 0)
        {
            a->clash_time = a->clash_time + 1; 
            right(a);

        }
        if(atMarker(a) == 1)
        {
            pickUpMarker(a);
            a->Memory_System = 0;
            memory_control(a);
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

    //Declare a robot
    struct robot *Robot;
    //Allocate meomory to it
    Robot = malloc(sizeof(struct robot));
    //Setup
    setup_robot(Robot);

    return 0;
}