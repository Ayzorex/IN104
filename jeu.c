#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "load_file.h"


char* word_select(char** dico, int size_dico, unsigned int N)
{
    int id = rand()%size_dico;
    char* secret_word = malloc((N+1)*sizeof(char*));
    strcpy(secret_word,dico[id]);
    secret_word[N]='\0';
    return(secret_word);
}

/*
Cette fonction prend en argument le tablau trié par ordre alphabétique, sa taille et un mot et renvois si il est dans le dico ou pas
*/
bool recherche_dichoto(char **tab, char *word, unsigned int size)
{
	int a = 0;
	int b = size; 
	int n = size;
	int mid = (a+b)/2;
	while (strcmp(tab[mid],word)!=0 && n!=0)
	{
		if (strcmp(tab[mid],word)<0)
		{
			a = mid;
			mid=(a+b)/2;
		}
		if (strcmp(tab[mid],word)>0)
		{
			b=mid;
			mid=(a+b)/2;
		}
		n=n/2;
		//printf("%d,%d,%d\n",a,b,n);
	}
	if (n==0)
	{
		//printf("PAS dans le dico\n");
		return(false);
	}
	else
	{
		//printf("dans le dico\n");
		return(true);
	}
}

/*
Cette fonction prend en argument le dico et sa taille, demande à l'utilisateur un mot et vérifie si il est valide et le renvois une fois le mot rentré valide
*/
void get_word(char** dico,unsigned int size_dico, char* current_word,unsigned int N)
{
    bool stop = false;
    char buffer[16];
    while (! stop)
    {   
        printf("entrez un mot de %d lettres svp\n",N);
        scanf(" %s",buffer);
        if (strlen(buffer)!=N)
        {
            printf("le mot ne fait pas %d lettres\n",N);
        }
        if (! recherche_dichoto(dico,buffer,size_dico))
        {
            printf("le mot choisi n'est pas dans le dictionnaire\n");
        }
        if (strlen(buffer)==N && recherche_dichoto(dico,buffer,size_dico))
        {
            stop = true;
        }
    }
    strcpy(current_word,buffer);
}


int occurences (char* word, char letter,unsigned int N)
{
    int occurence=0;
    for (int i=0; i<N; i++)
    {
        if (word[i]==letter)
        {
            occurence++;
        }
    }
    return(occurence);
}

char*  analyse(char* current_word, char* secret_word,unsigned int N)
{
    bool presence=false;
    char* list_presents = calloc(N,sizeof(char));
    int cursor=0;
    char* config=malloc((N+1)*sizeof(char));
    for (int i=0; i<N; i++)
    {
        if (current_word[i]==secret_word[i])
        {
            config[i]='2';
            list_presents[cursor]=current_word[i];
            cursor++;
        }
        else
        {
            presence=false;
            for (int j=0; j<N; j++)
            {
                if ( j!=i && current_word[i]==secret_word[j])
                {
                    if (occurences(secret_word,current_word[i],N)>occurences(list_presents,current_word[i],N))
                    {
                        presence=true;
                        list_presents[cursor]=current_word[i];
                    }
                }
            }
            if (presence)
            {
                config[i]='1';
            }
            else
            {
                config[i]='0';
            }
        }
        
    }
    config[N]='\0';
    //printf("%s\n",config);
    //printf_list(list_presents);
    free(list_presents);
    return(config);
}



void play_wordle(unsigned int N,char* fname)
{ 
    srand(time(0));
    struct Array_and_size* array_and_size = get_word_array(fname,N);
    unsigned int size_dico = array_and_size->size;
    char** dico = array_and_size->array;
    
    char* secret_word = word_select(dico,size_dico,N);
    
    //printf("%s\n",secret_word);
    //fin de l'initialisation du jeu, début de la boucle
    int turn = 1;
    bool game = true;
    char current_word[16];
    while (game && turn<=6)
    {
        //on entre un mot et on vérifie qu'il est valide
        get_word(dico,size_dico,current_word,N);
        if (strcmp(current_word,secret_word)==0)
        {
            game = false;
            printf("Gagnée !! en %d coups\n",turn);
        }
        else
        {
            analyse(current_word,secret_word,N);
        }
        turn++;
    }
    if (turn>6)
    {
        printf("Vous avez perdu! Le mot était %s\n",secret_word);
    }
}