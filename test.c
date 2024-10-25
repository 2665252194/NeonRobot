#include <stdio.h>

int array[13][18] = {0};


int main(void)
{
    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 18; j++)
        {
            printf("%d", array[i][j]);
            
        }
    }

    

}