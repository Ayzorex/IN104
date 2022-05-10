#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "chain.h"
#include "load_file.h"


void free_chain(struct Chain_head* chain_head)
{
    struct Chain_link* tmp = chain_head->chain_first;
    printf("%s\n",tmp->word);
    struct Chain_link* tmp2;
    while (tmp != NULL)
    {
        tmp = tmp2->next;
        free(tmp);
        tmp2 = tmp;
    }  
}



int main()
{
    FILE* file;
    file = fopen("dico.txt","rb");
    if (file == NULL) printf("pb pour ouvrir le fichier");

    char buffer[32];
    fscanf(file, " %s",buffer);
    //printf("fichier ouvert\n");
    
    struct Chain_head* chain_head = malloc(sizeof(struct Chain_head));
    printf("%d\n",chain_head->size);
    struct Chain_link* tmp = malloc(sizeof(struct Chain_link));
    chain_head->chain_last = tmp;
    chain_head->chain_first = tmp;
    tmp->word = buffer;
    
    //printf("on a bien init les chaines\n");
    while (!feof(file))
    {
        fscanf(file, " %s",buffer);
        struct Chain_link* lst = malloc(sizeof(struct Chain_link));
        chain_head->size++;
        tmp->next = lst;
        lst->word = buffer;
        tmp = lst;
        //printf("%s\n",tmp->word);
    }
    printf("%s\n",chain_head->chain_first->word);
    printf("%d\n",chain_head->size);
    fclose(file);
    /*
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
    */
    free_chain(chain_head);
    printf("tout a été correctement free");
    return(0);



}