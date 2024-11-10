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

};

int markerCount(struct robot *a)
{
    if(a->carry>0)
    {
        return a->carry;
    }
    else{
        return 0;
    }
}


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
}


//Make the left function
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
    if(unit_array[a->robot_y][a->robot_x] == -1)
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
    //set to zero
    unit_array[a->robot_y][a->robot_x] = 0;

    //carry should plus one
    a->carry = a->carry + 1;
    unit_array[robot_start_y][robot_start_x] = 0;

    //Redraw the arena
    Create_arena();
    shape();

    //Redraw the markers left
    if(unit_array[marker_y][marker_x] == -1)
    {
        draw_item(marker_x, marker_y, 1);
    }

    if(unit_array[marker_y_2][marker_x_2] == -1)
    {
        draw_item(marker_x_2, marker_y_2, 1);
    }



    //Redraw the obstacle
    draw_item(obs_x,obs_y,2);
    draw_item(obs_x_2,obs_y_2,2);

    //Redraw the home
    draw_item(robot_start_x, robot_start_y,4);

    
}


void drpoMarker(struct robot *a)
{
    //Drop the marker at home 
    if(a->robot_x == robot_start_x && a->robot_y == robot_start_y)
    {
        marker_number = marker_number - a->carry;
        a->carry = 0;

        //If there is no marker left, game is over
        if(marker_number <= 0)
        {
            a->stop = 1;
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
        else if (unit_array[a->robot_y - 1][a->robot_x] == 100000)
        {
            return -1;
        }
    }else if(a->orientation == 2)//East
    {

        if(a->robot_x >= max_x) 
        {
            return -1;
        }
        else if (unit_array[a->robot_y][a->robot_x + 1] == 100000)//Remeber swapping x and y because it is rom and column for 2D array!!
        {
            return -1;
        }
    }else if(a->orientation == 3)
    {
        if(a->robot_y >= max_y)
        {
            return -1;
        }
        else if (unit_array[a->robot_y+1][a->robot_x] == 100000)
        {
            return -1;
        }   
    }else if(a->orientation == 4)
    {
        if(a->robot_x == min_x)
        {
            return -1;
        }
        else if (unit_array[a->robot_y][a->robot_x - 1] == 100000)
        {
            return -1;       
        }
    }
    //If we go through every if-sentence successfully
    //We return 1
    return 1;
}





//My Algoritm
void memory_control(struct robot *a)
{
    //Add 1 when passing this filt
    unit_array[a->robot_y][a->robot_x] += 1;
    int lowest = 100;
    int best_orientation = 0;
    int tmp_x = a->robot_x;
    int tmp_y = a->robot_y;

    //Try to find the orientation where the score is lowest
    if(canMoveForward(a) == 1){
        forward(a);
        if(unit_array[a->robot_y][a->robot_x] < lowest){
            lowest = unit_array[a->robot_y][a->robot_x];
            best_orientation = a->orientation;
        }
        a->robot_x = tmp_x;
        a->robot_y = tmp_y;
    }

    //Turn right and try again
    right(a);
    if(canMoveForward(a) == 1)
    {

        forward(a);

        if(unit_array[a->robot_y][a->robot_x] < lowest)
        {
            lowest = unit_array[a->robot_y][a->robot_x];
            best_orientation = a->orientation;
        }

        a->robot_x = tmp_x;
        a->robot_y = tmp_y;

        left(a);
    }else
    {   //If can not move there just turn left directly
        left(a);
    }

    //Turn left and try again
    left(a);
    if(canMoveForward(a) == 1)
    {

        forward(a);

        if(unit_array[a->robot_y][a->robot_x] < lowest)
        {
            lowest = unit_array[a->robot_y][a->robot_x];
            best_orientation = a->orientation;
        }

        a->robot_x = tmp_x;
        a->robot_y = tmp_y;
        right(a);


    }else
    {
        right(a);
    }

    //If we go through 3 cases and nothing happening, that means we are stuck, now get out
    if(best_orientation == 0)
    {
        right(a);
        right(a);
    }else{
        //If something happening, we can move forward
        a->orientation = best_orientation;
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

    int i = 0;


    //Go robot!
    while(i<600 && a->stop == 0)
    {
        if(atMarker(a) == 1)
        {
            pickUpMarker(a);
        }
        if(a->carry > 0)
        {
            drpoMarker(a);
        }



        memory_control(a);
        forward(a);
        sleep(20);



        //Draw the robot
        foreground();
        clear();
        displayImage("neon_rb.jpg",O_x + unit_size * (a->robot_x) , O_y + unit_size * (a->robot_y));

        //If robot is carrying something, draw a sign on his body
        if(a->carry > 0)
        {
            setRGBColour(148,0,211);
            fillRect(O_x + unit_size * (a->robot_x) + 10,O_y + unit_size * (a->robot_y) + 10, 10, 10);

        }
        i = i + 1;
    }

}

int main(void)
{
    //initialize the arena
    initialize_arena_dimensions();

    //Then set the window size
    setWindowSize(width, height);

    //Create the arena
    Create_arena();
    shape();
    //Initiliaze the data of item(robot and markers...)
    initialize_item();

    //Draw the item
    draw_item(marker_x, marker_y,1);
    draw_item(marker_x_2, marker_y_2,1);
    draw_item(obs_x,obs_y,2);
    draw_item(obs_x_2,obs_y_2,2);
    draw_item(robot_start_x, robot_start_y,4);

    //Declare a robot
    struct robot *Robot;
    //Allocate meomory to it
    Robot = malloc(sizeof(struct robot));
    //Setup
    setup_robot(Robot);

    return 0;

}