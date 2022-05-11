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
Ouvre le fichier SANS AVOIR SA TAILLE, récupère les mots de taille N à travers une chaine puis crée un char** pour stocker les mots
Renvois un struct avec le tableau et sa taille
*/
struct Array_and_size* get_word_array(char* fname, unsigned int N);

/*
Cette fontion ouvre le fichier et renvois le tableau de mot associé
*/
char **load_file_naif (char *fname, unsigned int size);

#endif