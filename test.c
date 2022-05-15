#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>



int main()
{
    srand(time(0));
    for (int i = 0; i <10 ; i++)
    {
        int random = rand()%8000;
        printf("%d\n",random);
    }

    return(0);



}