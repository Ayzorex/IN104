#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"
#include "load_file.h"
#include "resolve.h"
#include "dicoreduit.h"
#include "jeu_auto.h"
#include "jeu_auto_naif.h"

int main()
{
    srand(time(0));
    int number_test = 1;
    char* fname = "dico.txt";
    unsigned int N = 5;
    char* test ="210";
    int list_turn[number_test];
    int turn;
    for(int i = 0;i<number_test;i++)
    {
        turn = play_alone(fname,N,test);
        list_turn[i]=turn;
    }
    for(int i =0;i<number_test;i++)
    {
        printf("%d, ",list_turn[i]);
    }
    printf("\n");
    return(0);
    
}