#ifndef __RESOLVE_H__
#define __RESOLVE_H__
#include "load_file.h"
#include <stdbool.h>

/*
Renvoie la liste des char correspondant aux config possibles et prend en arguments la taille du mot
*/
char** get_config_array(unsigned int N);

/*
Revoie true si le mot est compatible avec la config et false sinon
*/
bool is_compatible(char* word_ref, char* word_test, char* config, unsigned int N);

/*
Renvoie le nombre de mot du dico compatible avec word_ref et la config choisie
*/
int get_number_compatible(char* config,char* word_ref,unsigned int size_curr_dico, char** word_array,char* marquage_word_ref,unsigned int N);

/*
Renvoie l'entropie de word_ref
*/
double get_entropy(char* word_ref, char** word_array, unsigned int size_curr_dico, char** config_array,unsigned int N);

/*
Renvoie le mot avec la plus grande entropie
*/
char* get_best_word(char** word_array, char** config_array,unsigned int N, unsigned int size_curr_dico);

/*
Permet de créer le nouveau tableau de mot sur l'ancien en prenant une config et un mot ref
*/
struct Array_and_size* create_new_word_array(char* word_ref, char* config, char** word_array, unsigned int size_dico,unsigned int N);

/*
Résout le jeu avec la méthoqde de la théorie de l'information
*/
int resolve(char* fname,unsigned int N);

#endif
