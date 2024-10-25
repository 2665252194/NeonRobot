#include "robot_data.h"
#include "time.h"
#include "stdlib.h"

//Welcome to robot_data.c
//You can Change settings here


//Function to generate random number
int random_num(int min, int max) 
{
    //Remember using srand() before calling
    return rand() % (max - min + 1) + min;
}


//Screen size
const int width = 1000;
const int height = 1000;



//arena size
int arena_width;
int arena_height;

//Fillet size
const int unit_size = 40;

//Position to start drawing the arena
int arena_start_x;
int arena_start_y;


//O_x and O_y means position of the top-left corner of the arena
int O_x;
int O_y;

//max_x and max_y is the maximum number of fillets in column and row 
int max_x;
int max_y;

//The size inside the arena rather than the wall
int inside_width;
int inside_height;


//Use 2D array to store value in each fillet
//Make sure the random number range is smaller than 32
//How much you got, how many fillets you use, leave the rest of fillets
int unit_array[32][32] = {0};


//position of the marker
int marker_x;
int marker_y;

//position of obstacle
int obs_x;
int obs_y;

//Set up the robot
int robot_start_x;
int robot_start_y;
int robot_start_orientation;

float distance_count;

int min_x;
int min_y;
int tmp_max_x;



void initialize_arena_dimensions() {
    //srand the time()
    srand(time(0));

    //Some Simple mathematics
    arena_width = 40* random_num(10,20);
    arena_height = 40* random_num(10,20);
    arena_start_x = (width - arena_width) / 2;
    arena_start_y = (height - arena_height) / 2;
    O_x = arena_start_x + unit_size;
    O_y = arena_start_y + unit_size;
    inside_width = arena_width - unit_size * 2;
    inside_height = arena_height - unit_size * 2;
    max_x = ((arena_width - 2*unit_size) / unit_size) - 1;//Remember taking 0 into account so minus 1
    max_y = ((arena_height - 2*unit_size) / unit_size) - 1;
    tmp_max_x = max_x;
    
    min_x = 0;
    min_y = 0;




    //Generate random number
    do
    {
        do
        {
            marker_x = random_num(0,max_x - 1);
            marker_y = random_num(0,max_y - 1);
            //Can not be at corner
        } while ( (marker_x == 0 && marker_y == 0) || (marker_x == 0 && marker_y == max_y) || (marker_x == max_x && marker_y == max_y || (marker_x == max_x && marker_y == 0)) );
        obs_x = random_num(0,max_x);
        obs_y = random_num(0,max_y);
        robot_start_x = random_num(2,max_x-2);
        robot_start_y = random_num(2,max_y-2);
        robot_start_orientation = random_num(1,4);
        //If some of them overlapped then do it again
    } while ((marker_x == obs_x && marker_y ==obs_y) || (marker_x == robot_start_x && marker_y == robot_start_y) || (robot_start_x == obs_x && robot_start_y ==obs_y));

    distance_count = 0;
}