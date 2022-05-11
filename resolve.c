#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "tools.h"
#include "load_file.h"


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


char* get_best_word(char** word_array, char** config_array, int N, unsigned int size_curr_dico)
{
    char* best_word = word_array[0];
    double best_entropy = get_entropy(best_word,word_array,size_curr_dico,config_array,N);
    for(int i=0;i<size_curr_dico;i++)
    {
        if(i%200 == 0) //Pour vérifier que le programme tourne on a mis un système de pourcentage d'avancé (ne marque que si il reste plus de 200 mots dans la liste)
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
    return(best_word);
}


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

int resolve(unsigned int size_dico, char** word_array, char** config_array, int N)
{
    char config_answer[32];
    int turn=0;
    char* best_word = get_best_word(word_array,config_array,N,size_dico);
    printf("le meilleur mot à jouer est : %s\n",best_word);
    printf("entrez la config réponse : ");
    scanf("%s",config_answer);
    printf("\n");
    struct Array_and_size *new_word_array_and_size = create_new_word_array(best_word,config_answer,word_array,size_dico,N);
    char ** new_word_array=new_word_array_and_size->array;
    unsigned int new_size=new_word_array_and_size->size;
    //printf_array(word_array,new_size);
    while (strcmp(config_answer,"22222")!=0)
    {
        
        best_word=get_best_word(new_word_array,config_array, N, new_size);
        printf("le nouveau meilleur mot est : %s\n",best_word);
        printf("entrez la config réponse : ");
        scanf("%s",config_answer);
        printf("\n");
        //printf_array(word_array,new_size);
        new_word_array_and_size = create_new_word_array(best_word,config_answer,word_array,new_size,N);
        new_word_array=new_word_array_and_size->array;
        new_size=new_word_array_and_size->size;
        turn++;
    }
    printf("mot trouvé en %d coups\n",turn);
    return(turn);
}