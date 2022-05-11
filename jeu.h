#ifndef __JEU_H__
#define __JEU_H__

/* 
Cette fonction prend en argument le tableau du dico et sa taille et va renvoyer un mot au hasard du dico
*/
char* word_select(char** dico, int size_dico, unsigned int N);

/*
Renvois le nombre d'occurence d'un char dans un char*
*/
int occurences (char* word, char letter,unsigned int N);

/*
Renvois la config correspondante à jouer current_word 
*/
char*  analyse(char* current_word, char* secret_word,unsigned int N);

/*
Permet de jouer au wordle tranquillou
*/
void play_wordle(unsigned int N,char* fname);

#endif