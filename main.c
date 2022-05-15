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

void get_data()
{
    srand(time(NULL));
    int number_test = 1000;
    char* fname = "dico.txt";
    unsigned int N = 5;
    double time_spent;
    //int list_turn[number_test];
    int turn;
    FILE* fd=fopen("data_turn.txt","wb");
    FILE* ft = fopen("data_time.txt","wb");
    for(int i = 0;i<number_test;i++)
    {
        time_spent = 0.0;
        clock_t begin = clock();
        turn = play_alone(fname,N);
        clock_t end = clock();
        time_spent += (double) (end - begin)/ CLOCKS_PER_SEC;
        //printf("%f\n",time_spent);
        if(turn!=20)
        {
            fprintf(fd,"%d\n",turn);
            fprintf(ft,"%f\n",time_spent);
        }
    }
    fclose(fd);
    fclose(ft);
}

int main()
{
    srand(time(NULL));
    double time_spent;
    char** word_array;
    unsigned int size;
    char** config_array;
    char* best_word;
    struct Array_and_size* array_and_size ;
    unsigned int N = 6;
    //FILE* ft = fopen("data_first_word_time.txt","wb");
    clock_t begin = clock();
    array_and_size = get_word_array("dico.txt",N);
    word_array = array_and_size->array;
    size = array_and_size->size;
    config_array = get_config_array(N);
    best_word = get_best_word(word_array,config_array,N,size);
    clock_t end = clock();
    time_spent = (double)(end - begin)/CLOCKS_PER_SEC;
    printf("%f\n",time_spent);
    printf("%s\n",best_word);

    return(0);

}