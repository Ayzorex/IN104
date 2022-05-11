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

int play_alone_naif(char* fname,unsigned int N)
{
    char* test = "210";
    struct Array_and_size* array_and_size = get_word_array(fname,N);
    char** word_array = array_and_size->array;
    unsigned int size_dico = array_and_size->size;
    int turn = 1;
    char* secret_word = word_select(word_array,size_dico,N);
    //char* random_word = get_random_word(word_array,config_array,N,size_dico);
    char* random_word = word_select(word_array,size_dico,N);
    printf("le mot joué est : %s\n",random_word);
    char* config_answer = analyse(random_word,secret_word,N);
    printf("config obtenue: %s\n\n",config_answer);
    struct Array_and_size *new_word_array_and_size = create_new_word_array(random_word,config_answer,word_array,size_dico,N,test);
    char ** new_word_array = new_word_array_and_size->array;
    unsigned int new_size = new_word_array_and_size->size;
    //printf_array(word_array,new_size);
    while (new_size!=1 && turn<100)
    {
        random_word = word_select(new_word_array,size_dico,N);
        config_answer = analyse(random_word,secret_word,N);
        printf("mot joué %s\n",random_word);
        printf("config obtenue : %s\n\n",config_answer);
        //printf_array(word_array,new_size);
        new_word_array_and_size = create_new_word_array(random_word,config_answer,new_word_array,new_size,N,test);
        new_word_array=new_word_array_and_size->array;
        new_size=new_word_array_and_size->size;
        turn++;
        free(new_word_array_and_size);
        free(config_answer);
    }
    printf("le mot était : %s\n",random_word);
    printf("mot trouvé en %d coups\n",turn);
    return(turn);
}