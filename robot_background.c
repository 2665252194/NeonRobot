#include "graphics.h"
#include "stdio.h"
#include "stdlib.h"
#include "robot_data.h"


//Welcome to robot_background.c
//Here are some functions used to draw the arena , marker and obstacle



void Create_arena ()
{
    //Fill the Background with black colour
    background();
    //setColour(black);
    displayImage("neon_bg.jpg", 0,0);


    //Pink
    setRGBColour(255,20,147);
    // Create a big rectangle
    fillRect(arena_start_x,arena_start_y,arena_width,arena_height);
    setColour(black);
    drawRect(arena_start_x-1,arena_start_y-1,arena_width,arena_height); //Just a stroke!
    //Then create a black small rectangle inside the big one
    setColour(black);
    fillRect(arena_start_x + unit_size, arena_start_y + unit_size, inside_width, inside_height);
    //Now we have the frame


    //Draw lines
    setColour(blue);
    int i = 0;
    int j = 0;
    //Let us use a double loop, the outer loop is for height and the inner is for width
    int inner_x = O_x;
    int inner_y = O_y;
    int outer_x = O_x;
    int outer_y = O_y;
    for (i; i<=max_y; i++)
    {
        //horizontal lines
        drawLine(outer_x, outer_y, outer_x + inside_width, outer_y);
        outer_y = outer_y + unit_size;
        for(j; j<=max_x; j++)
        {
            //vertical lines
            drawLine(inner_x, inner_y, inner_x, inner_y + inside_height);
            inner_x = inner_x + unit_size;
        }
    }
}


//Draw obstacle or marker
void draw_item(int x, int y, int item_type)
{
    //First we need to find out the real value of the coordinate!
    int real_x = O_x + unit_size * (x);
    int real_y = O_y + unit_size * (y);
    background();

    
    if (item_type == 1)//marker
    {

        //Neon purple
        setRGBColour(148, 0 ,211);
        //Fill that fillet
        fillRect(real_x, real_y, unit_size, unit_size);

        //Set the value to be -1 meanning there is a marker
        unit_array[y][x] = -1;
    }
    else if (item_type == 2)//obstruction
    {
        //Neon yellow
        setRGBColour(255,165,0);
        fillRect(real_x, real_y, unit_size, unit_size);

        //Set the value to be 100000 meaning there is a obstacle or wall
        unit_array[y][x] = 100000;
   
    }
    else if (item_type == 3)//Wall
    {
        //Pink
        setRGBColour(255,20,147);
        fillRect(real_x, real_y, unit_size, unit_size);
        unit_array[y][x] = 100000;
   
    }
    else if (item_type == 4)//Home
    {
        //Green
        setColour(green);
        fillRect(real_x, real_y, unit_size, unit_size);
        unit_array[y][x] = 0;
   
    }
}


void shape(void)
{

    //Draw the shape of the arena
    for(int i=0; i<max_x+1; i++)
    {
        draw_item(i,max_y,3);
    }
    for(int i=2; i<max_x-1; i++)
    {
        draw_item(i,max_y-1,3);
        draw_item(i,max_y-2,3);
        draw_item(i,max_y-3,3);
    }
    for(int i=4; i<max_x-3; i++)
    {
        draw_item(i,max_y-4,3);
        draw_item(i,max_y-5,3);
        draw_item(i,max_y-6,3);
    }
}