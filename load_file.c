#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chain.h"
#include "load_file.h"

void free_chain(struct Chain_head chain_head)
{
    struct Chain_link* tmp = chain_head.chain_first;
    struct Chain_link* tmp2;
    while (tmp != NULL)
    {
        tmp = tmp2->next;
        free(tmp);
        tmp2 = tmp;
    }  
}



struct Array_and_size* get_word_array(char* fname)
{
    printf("on rentre dans get_word_array");
    FILE* file;
    file = fopen(fname,"rb");
    if (file == NULL) return(NULL) ;

    char buffer[32];
    fscanf(file, " %s",buffer);
    printf("fichier ouvert");
    struct Chain_head chain_head = {1,NULL,NULL};
    struct Chain_link* tmp = malloc(sizeof(struct Chain_link));
    chain_head.chain_last = tmp;
    chain_head.chain_first = tmp;
    strcpy(tmp->word,buffer);

    while (feof(file))
    {
        fscanf(file, " %s",buffer);
        struct Chain_link* tmp = malloc(sizeof(struct Chain_link));
        chain_head.size++;
        chain_head.chain_last->next = tmp;
        chain_head.chain_last = tmp;
        strcpy(tmp->word,buffer);
    }
    fclose(file);
    
    struct Array_and_size* array_and_size = malloc(sizeof(struct Array_and_size));
    array_and_size->size = chain_head.size;
    char** word_array = malloc(chain_head.size*sizeof(char*));
    
    tmp = chain_head.chain_first;
    unsigned int cursor = 0;
    while(tmp!=NULL)
    {
        word_array[cursor] = malloc(sizeof(tmp->word));
        strcpy(word_array[cursor],tmp->word);
        cursor++;
        tmp = tmp->next;
    }
    array_and_size->array = word_array;
    free_chain(chain_head);
    return(array_and_size);
}