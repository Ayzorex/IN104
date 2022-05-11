#ifndef __LOAD_FILE_H__
#define __LOAD_FILE_H__

#include "chain.h"

struct Array_and_size
{
    char** array;
    unsigned int size;
};

/*
Permet de free une chaine
*/
void free_chain(struct Chain_link* link);

/*
Prend en argument le nom d'un fichier et renvoit le tableau de mot correspondant
ansi que la taille de ce tableau
*/
struct Array_and_size* get_word_array(char* fname);

#endif