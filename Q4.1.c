#include "graphics.h"

int width = 600;
int height = 600;
int Oval_x = 100;
int Oval_y = 100;
int wait_time = 25;
int move_distance = 10;




void init(void)
{
    background();
    setColour(green);

}



void update(int x, int y)
{
    clear();
    foreground();

    setColour(green);
    
    fillOval(Oval_x,Oval_y,400,400);

    setColour(white);

    fillOval(Oval_x + 50, Oval_y + 50, 300, 300);

    setColour(blue);
    fillRect(x,y,100,100);


}


void move(void)
{

    int x = 100;
    int y = 100;
    int x_speed = move_distance;
    int y_speed = 0;

    int count = 0;
    int n =0;
    while (n < 240)
    {
        if(count >= 300){

            if (x_speed > 0 && y_speed == 0)
            {
                x_speed = 0;
                y_speed = move_distance;
            } 
            else if (y_speed > 0 && x_speed == 0)
            {
                y_speed = 0;
                x_speed = -move_distance;
            }
            else if (x_speed < 0 && y_speed == 0)
            {
                x_speed = 0;
                y_speed = -move_distance;
            }
            else if (y_speed < 0 && x_speed == 0)
            {
                x_speed = move_distance;
                y_speed = 0;
            }


            count = 0;
        }


        update(x,y);



        x += x_speed;
        y += y_speed;
        count = count + move_distance;
        sleep(wait_time);
        n = n + 1;

    }


}



int main(void)
{
    setWindowSize(width,height);
    init();


    move();
    return 0;
}