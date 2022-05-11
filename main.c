#include <stdio.h>

#include "tools.h"
#include "load_file.h"
#include "resolve.h"
#include "dicoreduit.h"

int main()
{
    char* fname = "dico.txt";
    unsigned int N = 3;
    struct Array_and_size* array_and_size = get_word_array(fname,N);
    char** word_array = array_and_size->array;
    unsigned int size = array_and_size->size;
    char** config_array = get_config_array(N);
    int turn = resolve(size,word_array,config_array,N);
    printf("%d\n",turn);
}