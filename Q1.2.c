//written by zhouzhou zhang, 1st Oct 2024
//This program displays my name

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void)
{
    char myName[] = "ZHANG ZHOUZHOU";
    char address1[] = " Department of Computer Science";
    char address2[] = "Malet Place Engineering Building";
    char city[] = "London";
    char postcode[] = "WC1E 7JE";



    printf("Hello, my name is %s\nI study at %s, %s, %s, %s\n", myName,address1,address2,city,postcode);
    return 0;
}