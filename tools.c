#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>


/*
free un tableau de char*
*/
void free_tab_char(char** tab,unsigned int size_tab)
{
    for(int i=0;i<size_tab;i++)
    {
        //printf("%d\n",i);
        free(tab[i]);
    }
    free(tab);
}

/*
Affiche un tableau de char*
*/
void printf_array(char** array,unsigned int size)
{
    for(int i=0;i<size;i++)
    {
        printf("%s\n",array[i]);
    }

}
