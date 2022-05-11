#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chain.h"
#include "load_file.h"
#include "tools.h"

void free_chain(struct Chain_link* link)
{
    struct Chain_link* tmp;
    while (link != NULL)
    {
        tmp = link->next;
        free(link);
        link = tmp;
    }  
}

char **load_file_naif (char *fname, unsigned int size)
{
    char buffer[32];
    char **words_array = malloc(sizeof(char*)*size);
    //printf("all good\n");

    FILE *f ;
    f = fopen (fname, "rb") ;
    if (f== NULL) return (NULL) ;

    printf("%d \n",size);
    for(int i=0;i<size;i++) 
    {
        fscanf (f, "%s", buffer) ;
        words_array[i] = malloc(sizeof(buffer));
        strcpy(words_array[i],buffer);
        //printf("%s\n",words_array[i]);
    }
    fclose(f);
    return(words_array);
}


struct Array_and_size* get_word_array(char* fname, unsigned int N)
{
    unsigned int count_words = 0 ;
    struct Chain_link *link = NULL ;
    char buffer[256] ;
    FILE *in_hd ;
    in_hd = fopen (fname, "rb") ;
    fscanf (in_hd, "%s", buffer) ;
    while (! feof (in_hd)) 
    {
        if(strlen(buffer)==N)
        {
            char *word_cpy ;
            struct Chain_link *new_cell = malloc (sizeof (struct Chain_link)) ;
            word_cpy = malloc ((1 + strlen (buffer)) * sizeof (char)) ;
            strcpy (word_cpy, buffer) ;
            new_cell->word = word_cpy ;
            new_cell->next = link ;
            link = new_cell ;
            count_words++ ;
        }
        fscanf (in_hd, "%s", buffer) ;
    }
    fclose (in_hd) ;
    char ** word_array = malloc (count_words * sizeof (char*)) ;
    unsigned int size = count_words ;
    struct Chain_link * tmp1 = link;
    for(int i=0;i<size;i++)
    {
        struct Chain_link * tmp2 = tmp1->next;
        word_array[size-1-i]=tmp1->word;
        tmp1 = tmp2;
    }
    struct Array_and_size* array_and_size = malloc(sizeof(struct Array_and_size));
    array_and_size->array = word_array;
    array_and_size->size = size;
    free_chain(link);
    return(array_and_size);
}