#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "dicoreduit.h"
#include "load_file.h"
#include "chain.h" 
#include <time.h>
#include "resolve.h"
#include "jeu.h"
#include "tools.h"

int play_alone(char* fname,unsigned int N)
{
    struct Array_and_size* array_and_size = get_word_array(fname,N);
    char** word_array = array_and_size->array;
    unsigned int size_dico = array_and_size->size;
    char** config_array = get_config_array(N);
    int turn = 1;
    char* secret_word = word_select(word_array,size_dico,N);
    //printf("le mot à trouver est : %s\n",secret_word);
    //char* best_word = get_best_word(word_array,config_array,N,size_dico);
    char* best_word;
    //printf("le meilleur mot à jouer est : RAIES\n");
    char* config_answer = analyse("RAIES",secret_word,N);
    //printf("config obtenue: %s\n\n",config_answer);
    struct Array_and_size *new_word_array_and_size = create_new_word_array("RAIES",config_answer,word_array,size_dico,N);
    char ** new_word_array = new_word_array_and_size->array;
    unsigned int new_size = new_word_array_and_size->size;
    //printf_array(word_array,new_size);
    while (new_size!=1 && turn<20)
    {
        //printf("%d\n",new_size);
        if(new_size!=0) best_word=get_best_word(new_word_array,config_array, N, new_size);
        config_answer = analyse(best_word,secret_word,N);
        //printf("mot joué %s\n",best_word);
        //printf("config obtenue : %s\n\n",config_answer);
        //printf_array(word_array,new_size);
        new_word_array_and_size = create_new_word_array(best_word,config_answer,word_array,new_size,N);
        new_size=new_word_array_and_size->size;
        turn++;
        free(new_word_array_and_size);
        free(config_answer);
    }
    
    //printf("le mot était : %s\n",word_array[0]);
    //printf("mot trouvé en %d coups\n",turn);
    return(turn);
}