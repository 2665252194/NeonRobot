#include "graphics.h"

const int width = 600;
const int height= 600;
const int wait_time = 25;
const int square_size =60;
const int move_distance = 8;


void draw_bg()
{
    background();
    setColour(green);

}


void update(int x, int y)
{
    clear();
    fillRect(x,y,square_size,square_size);

}


void move()
{
    foreground();
    setColour(blue);
    int x = 20;
    int y = 100;
    for (int i = 0; i < 60; i++)
    {
        update(x,y);

        x += move_distance;
        y += move_distance/2;
        sleep(wait_time);
    }


}

int main(void)
{
    setWindowSize(width,height);
    draw_bg();
    move();


    return 0;


}