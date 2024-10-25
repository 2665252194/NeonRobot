#include <stdio.h>

int main(void)
{
    int num;
    scanf("%i",&num);
    for (int i = 2; i < num - 1; i++)
    {
        if (num % i == 0)
        {
            printf("Not Prime number\n");
            return 0;
        }
    }

    printf("Prime number\n");
    return 0;
}