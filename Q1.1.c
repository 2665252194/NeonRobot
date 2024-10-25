//written by zhouzhou zhang, 1st Oct 2024
//This program displays my name

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void)
{
    char myName[] = "ZHOUZHOU ZHANG";
    printf("Hello, my name is %s\n", myName);

    int index = strlen(myName) - 1;

    while(index > -1)
    {
        printf("%c",myName[index]);
        index = index -1;

    }

    printf("\n");
    return 0;
}