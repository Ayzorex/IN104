#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "dicoreduit.h"
#include "load_file.h"
#include "chain.h" 
#include <time.h>

/*
Cette fontion ouvre le fichier et renvois le tableau de mot associé
*/
char **load_file (char *fname, unsigned int size)
{
    char buffer[32];
    char **words_array = malloc(sizeof(char*)*size);
    //printf("all good\n");

    FILE *f ;
    f = fopen (fname, "rb") ;
    if (f== NULL) return (NULL) ;

    //printf("%d \n",size);
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

/*
Renvoie la liste des char correspondant aux config possibles et prend en arguments la taille du mot
*/
char** get_config_array(int N)
{
    int n = pow(3,N);
    char** config_array = malloc(sizeof(char*)*n);
    char* config;
    for(int i=0;i<n;i++)
    {
        config = malloc(N*sizeof(char));
        int I = i;
        for(int e=0;e<N;e++)
        {
            int r = I%3;
            I=I/3;
            if(r==0)
            {
                config[e] = '0';
            }
            if(r==1)
            {
                config[e] = '1';
            }
            if(r==2)
            {
                config[e] = '2';
            }
        }
        config_array[i] = malloc(sizeof(config));
        config_array[i] = config;
    }
    return(config_array);
}

/*
Afficher un double tableau d'entier
*/
void super_print(char** tab, int N)
{
    for(int i=0;i<pow(3,N);i++)
    {
        printf("%s\n",tab[i]);
    }
}

/*
Revoie true si le mot est compatible avec la config et false sinon
*/
bool is_compatible(char* word_ref, char* word_test, char* config, int N)
{
    bool stop=false;
    char* marquage = calloc(N,sizeof(char));

//On test les vert (2)
    for(int i=0;i<N;i++)
    {
        if(config[i]=='2')
        {
            if(word_ref[i]!=word_test[i])
            {
                free(marquage);
                return(false);
            }
            else
            {
                marquage[i]='1';
            }
        }
    }
//On test les jaunes (1)
    for(int i=0;i<N;i++)
    {
        stop=false; 
        if (config[i]=='1')
        {
            if(word_test[i]==word_ref[i]) 
            {
                free(marquage);
                return(false);
            }
            for(int j=0;j<N;j++)
            {
                if (word_ref[i]==word_test[j] && marquage[j]!='1')
                {
                    stop = true;
                    marquage[j]='1';
                }
            }
            if (!stop)
            {
                free(marquage);
                return(stop);
            }
        }
    }
//On test les gris (0)
    for(int i=0;i<N;i++)
    {
        if(config[i]=='0')
        {
            for(int j=0;j<N;j++)
            {
                if(word_ref[i]==word_test[j] && marquage[j]!='1')
                {
                    free(marquage);
                    return(false);
                }
            }
        }
    }
    free(marquage);
    return(true);
}

/*
Renvoie le nombre de mot du dico compatible avec word_ref et la config choisie
*/
int get_number_compatible(char* config,char* word_ref,unsigned int size_curr_dico, char** word_array,char* marquage_word_ref, int N)
{
    int count = 0;
    for(int i=0;i<size_curr_dico;i++)
    {
        char* word_test = word_array[i];
        if(marquage_word_ref[i]!='1')
        {
            if(is_compatible(word_ref,word_test,config,N))
            {
                //printf("%s (test) est compatible avec %s (ref) suivant la config %s\n",word_test,word_ref,config);
                count++;
                marquage_word_ref[i]='1';
            }
            else
            {
            //printf("%s (test) n'esst pas compatible avec %s (ref) suivant la config %s\n",word_test,word_ref,config);
            }
        }
    }
    return(count);
}

/*
Renvoie l'entropie de word_ref
*/
double get_entropy(char* word_ref, char** word_array, unsigned int size_curr_dico, char** config_array, int N)
{
    char* marquage_word_ref = calloc(size_curr_dico,sizeof(char));
    double entropy = 0;
    int number_tot = 0;
    double size_f = size_curr_dico;
    for(int i=0; i<pow(3,N) ; i++) //pour toute les config (3^N config)
    {
        char* config = config_array[i];
        int number_compatible = get_number_compatible(config,word_ref,size_curr_dico,word_array,marquage_word_ref,N);
        double number_f = number_compatible;
        number_tot+=number_compatible;
        //printf("%d\n",number_tot);
        //printf("%s donne : %d \n",config,number_compatible);
        double p = number_f/size_f;
        double P = 0;
        if(p!=0)
        {
            //printf("%s donne : %f\n",config,p);
            P = (-p)*(log2(p));
            entropy+=P;
        }
        //printf("%s donne proba : %f et entropie : %f\n",config,p,P);
    }
    //printf("%s a %d mot compatible\n",word_ref,number_tot);
    //printf("%s a pour entropie %f\n",word_ref,entropy);
    free(marquage_word_ref);
    return(entropy);
}
/*
Renvoie le mot avec la plus grande entropie
*/
char* get_best_word(char** word_array, char** config_array, int N, unsigned int size_curr_dico)
{
    char* best_word = word_array[0];
    double best_entropy = get_entropy(best_word,word_array,size_curr_dico,config_array,N);
    for(int i=0;i<size_curr_dico;i++)
    {
        
        if(i%100 == 0)
        {
            double ii = i;
            double nn = size_curr_dico;
            printf("%f pourcent\n",(ii*100)/nn);
        }
        
        char* curr_word = word_array[i];
        double curr_entropy = get_entropy(curr_word,word_array,size_curr_dico,config_array,N);
        if(curr_entropy>best_entropy)
        {
            best_entropy=curr_entropy;
            best_word = curr_word;
        }
    }
    printf("le meilleur mot est %s\n l'entropie espéré est de %f\n",best_word,best_entropy);
    return(best_word);
}
/*
Permet de créer le nouveau tableau de mot sur l'ancien en prenant une config et un mot ref
*/
struct Array_and_size* create_new_word_array(char* word_ref, char* config, char** word_array, unsigned int size_dico,int N)
{
    struct Array_and_size* new_array_and_size=malloc(sizeof(struct Array_and_size));
    int curseur_compatible=0;
    for (int i=0; i<size_dico; i++)
    {
        if (is_compatible(word_ref,word_array[i],config,N))
        {
            word_array[curseur_compatible]=word_array[i];
            curseur_compatible++;
        }
    }
    new_array_and_size->array=word_array;
    new_array_and_size->size=curseur_compatible;
    return(new_array_and_size);
}

void printf_array(char** array,unsigned int size)
{
    for(int i=0;i<size;i++)
    {
        printf("%s\n",array[i]);
    }
}

/*
Renvois le nombre d'occurence d'un char dans un char*
*/
int occurences (char* word, char letter)
{
    int occurence=0;
    for (int i=0; i<5; i++)
    {
        if (word[i]==letter)
        {
            occurence++;
        }
    }
    return(occurence);
}

/* 
Cette fonction prend en argument le tableau du dico et sa taille et va renvoyer un mot au hasard du dico
*/
char* word_select(char** dico, int size_dico, char* secret_word)
{
    int id = rand()%size_dico;
    strcpy(secret_word,dico[id]);
    return(secret_word);
}


char*  analyse(char* current_word, char* secret_word,int N)
{
    bool presence=false;
    char* list_presents = calloc(5,sizeof(char));
    int cursor=0;
    char* config=malloc((N+1)*sizeof(char));
    for (int i=0; i<5; i++)
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
            for (int j=0; j<5; j++)
            {
                if ( j!=i && current_word[i]==secret_word[j])
                {
                    if (occurences(secret_word,current_word[i])>occurences(list_presents,current_word[i]))
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
    config[5] = '\0';
    //printf("%s\n",config);
    //printf_list(list_presents);
    free(list_presents);
    return(config);
}

/*
Fonction dans laquelle le jeu tourne
*/
void play_alone(unsigned int size_dico, int N, char* fname)
{
    char** word_array = load_file("dico_test.txt",size_dico);
    char** config_array = get_config_array(N);
    int turn=1;
    char word[16];
    char* secret_word=word_select(word_array,size_dico,word);
    //char* best_word = get_best_word(word_array,config_array,N,size_dico);
    char* best_word;
    printf("le meilleur mot à jouer est : RAIES\n");
    char* config_answer=analyse("RAIES",secret_word,N);
    printf("config obtenue: %s\n\n",config_answer);
    struct Array_and_size *new_word_array_and_size = create_new_word_array("RAIES",config_answer,word_array,size_dico,N);
    char ** new_word_array=new_word_array_and_size->array;
    unsigned int new_size=new_word_array_and_size->size;
    //printf_array(word_array,new_size);
    while (strcmp(config_answer,"22222")!=0)
    {
        
        best_word=get_best_word(new_word_array,config_array, N, new_size);
        config_answer=analyse(best_word,secret_word,N);
        printf("config obtenue : %s\n\n",config_answer);
        //printf_array(word_array,new_size);
        new_word_array_and_size = create_new_word_array(best_word,config_answer,word_array,new_size,N);
        new_word_array=new_word_array_and_size->array;
        new_size=new_word_array_and_size->size;
        turn++;
        free(new_word_array_and_size);
        free(config_answer);
    }
    printf("mot trouvé en %d coups\n",turn);
}





/*
free un tableau de char*
*/
void free_tab_char(char** tab,unsigned int size_tab)
{
    for(int i=0;i<size_tab;i++)
    {
        //printf("%d\n",i);
        free(tab[i]);
    }
    free(tab);
}




int main(int argc, char* argv[])
{
    srand(time(0));
    unsigned int size_dico = 7645;
    unsigned int N = 5;
    char* fname = "dico_5.txt";
    play_alone(size_dico,N,fname);
    return(0);
}