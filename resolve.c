#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "tools.h"
#include "load_file.h"


char** get_config_array(unsigned int N)
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



/*Teste uniquement les 2 (verts)*/

bool is_compatible_verts(char* word_ref, char* word_test, char* config, int N)
{

    for(int i=0;i<N;i++)
    {
        if(config[i]=='2')
        {
            if(word_ref[i]!=word_test[i])
            {
                return(false);
            }
        }
    }   
    return(true);
}




/*Teste uniquement les 1 (jaune)*/

bool is_compatible_jaune(char* word_ref, char* word_test, char* config, int N)
{
    bool stop=false;
    char* marquage = calloc(N,sizeof(char));

//On test les vert pour créer la liste marquage(2)
    for(int i=0;i<N;i++)
    {
        if(config[i]=='2')
        {
            if(word_ref[i]==word_test[i])
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
    free(marquage);
    return(true);
}

/*Teste uniquement les 0 (gris)*/

bool is_compatible_gris(char* word_ref, char* word_test, char* config, int N)
{
    char* marquage = calloc(N,sizeof(char));

//On test les vert (2)
    for(int i=0;i<N;i++)
    {
        if(config[i]=='2')
        {
            if(word_ref[i]==word_test[i])
            {
                marquage[i]='1';
            }
        }
    }
//On test les jaunes (1)
    for(int i=0;i<N;i++)
    {
        if (config[i]=='1')
        {
            for(int j=0;j<N;j++)
            {
                if (word_ref[i]==word_test[j] && marquage[j]!='1')
                {
                    marquage[j]='1';
                }
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


bool is_compatible(char* word_ref, char* word_test, char* config, int N, char* test)
{
    if (strcmp(test, "2")==0)
    {
        return is_compatible_verts(word_ref,word_test,config,N);
    }
    if (strcmp(test, "1")==0)
    {
        return is_compatible_jaune(word_ref,word_test,config,N);
    }
    if (strcmp(test, "0")==0)
    {
        return is_compatible_gris(word_ref,word_test,config,N);
    }
    if (strcmp(test, "21")==0)
    {
        if (is_compatible_verts(word_ref,word_test,config,N))
        {
            if (is_compatible_jaune(word_ref,word_test,config,N))
            {
                return true;
            }
        }else{
            return false;
        }
    }
    if (strcmp(test, "20")==0)
    {
        if (is_compatible_verts(word_ref,word_test,config,N)&&is_compatible_gris(word_ref,word_test,config,N))
        {
            return true;
        }else{
            return false;
        }
    }
    if (strcmp(test, "10")==0)
    {
        if (is_compatible_jaune(word_ref,word_test,config,N) && is_compatible_gris(word_ref,word_test,config,N))
        {
            return true;
        }else{
            return false;
        }
    }
    if (strcmp(test,"210")==0)
    {
        if (is_compatible_verts(word_ref,word_test,config,N) && is_compatible_jaune(word_ref,word_test,config,N) && is_compatible_gris(word_ref,word_test,config,N))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return true;
}

int get_number_compatible(char* config,char* word_ref,unsigned int size_curr_dico, char** word_array,char* marquage_word_ref,unsigned int N,char* test)
{
    int count = 0;
    for(int i=0;i<size_curr_dico;i++)
    {
        char* word_test = word_array[i];
        if(marquage_word_ref[i]!='1')
        {
            if(is_compatible(word_ref,word_test,config,N,test))
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

double get_entropy(char* word_ref, char** word_array, unsigned int size_curr_dico, char** config_array,unsigned int N,char* test)
{
    char* marquage_word_ref = calloc(size_curr_dico,sizeof(char));
    double entropy = 0;
    int number_tot = 0;
    double size_f = size_curr_dico;
    for(int i=0; i<pow(3,N) ; i++) //pour toute les config (3^N config)
    {
        char* config = config_array[i];
        int number_compatible = get_number_compatible(config,word_ref,size_curr_dico,word_array,marquage_word_ref,N,test);
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


char* get_best_word(char** word_array, char** config_array,unsigned int N, unsigned int size_curr_dico, char* test)
{
    char* best_word = word_array[0];
    double best_entropy = get_entropy(best_word,word_array,size_curr_dico,config_array,N,test);
    for(int i=0;i<size_curr_dico;i++)
    {
        if(i%200 == 0) //Pour vérifier que le programme tourne on a mis un système de pourcentage d'avancé (ne marque que si il reste plus de 200 mots dans la liste)
        {
            double ii = i;
            double nn = size_curr_dico;
            printf("%f pourcent\n",(ii*100)/nn);
        }
        char* curr_word = word_array[i];
        double curr_entropy = get_entropy(curr_word,word_array,size_curr_dico,config_array,N,test);
        if(curr_entropy>best_entropy)
        {
            best_entropy=curr_entropy;
            best_word = curr_word;
        }
    }
    return(best_word);
}


struct Array_and_size* create_new_word_array(char* word_ref, char* config, char** word_array, unsigned int size_dico,unsigned int N,char* test)
{
    struct Array_and_size* new_array_and_size=malloc(sizeof(struct Array_and_size));
    int curseur_compatible=0;
    for (int i=0; i<size_dico; i++)
    {
        if (is_compatible(word_ref,word_array[i],config,N,test))
        {
            word_array[curseur_compatible]=word_array[i];
            curseur_compatible++;
        }
    }
    new_array_and_size->array=word_array;
    new_array_and_size->size=curseur_compatible;
    return(new_array_and_size);
}

int resolve(char* fname,unsigned int N, char* test)
{
    struct Array_and_size* array_and_size = get_word_array(fname,N);
    char** word_array = array_and_size->array;
    unsigned int size_dico = array_and_size->size;
    char** config_array = get_config_array(N);
    char config_answer[32];
    int turn=0;
    char* best_word = get_best_word(word_array,config_array,N,size_dico,test);
    printf("le meilleur mot à jouer est : %s\n",best_word);
    printf("entrez la config réponse : ");
    scanf("%s",config_answer);
    printf("\n");
    struct Array_and_size *new_word_array_and_size = create_new_word_array(best_word,config_answer,word_array,size_dico,N,test);
    char ** new_word_array=new_word_array_and_size->array;
    unsigned int new_size=new_word_array_and_size->size;
    //printf_array(word_array,new_size);
    while (new_size!=1)
    {
        
        best_word=get_best_word(new_word_array,config_array, N, new_size, test);
        printf("le nouveau meilleur mot est : %s\n",best_word);
        printf("entrez la config réponse : ");
        scanf("%s",config_answer);
        printf("\n");
        //printf_array(word_array,new_size);
        new_word_array_and_size = create_new_word_array(best_word,config_answer,word_array,new_size,N,test);
        new_word_array=new_word_array_and_size->array;
        new_size=new_word_array_and_size->size;
        turn++;
    }
    printf("mot trouvé en %d coups\n",turn);
    return(turn);
}