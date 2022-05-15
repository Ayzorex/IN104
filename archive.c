#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>


/*
Renvoie en entier corespondant au nombre d'occurence de letter dans word
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
Revoie true si le mot est compatible avec la config et false sinon
*/
bool is_compatible(char* word_ref, char* word_test, char* config)
{
    bool stop=false;
    char* list_precense = calloc(5,sizeof(char));
    int cursor = 0;

// on test les vert (2)
    for(int i=0; i<5;i++)
    {
        if(config[i]=='2')
        {
            if(word_ref[i]==word_test[i])
            {
                list_precense[cursor]=word_ref[i];
                cursor++;
            }
            else
            {   
                free(list_precense);
                return(false);
            }
        }
    }
    //printf("on est au test 1 \n");
    //on test les jaune (1)
    for(int i=0;i<5;i++)
    {
        stop = true;
        if(config[i]=='1')
        {
            stop = false;
            for (int j=0;j<5;j++)
            {
                if(! stop)
                {
                    if(word_ref[i]==word_test[j] && i!=j)
                    {
                        //printf("ref : %d list : %d\n",occurences(word_ref,word_ref[i]),occurences(list_precense,word_ref[i]));
                        //printf("c'est i : %d\n",i);
                        //printf("c'est j : %d\n",j);
                        if(occurences(word_ref,word_ref[i])<=occurences(list_precense,word_ref[i]))
                        {
                            list_precense[cursor] = word_ref[i];
                            stop = true;
                        }
                        else
                        {
                            //printf("au premier \n");
                            free(list_precense);
                            return(false);
                        }
                    }
                }
            }
        }
        if (! stop)
        {
            //printf("on est sortit au stop\n");
            free(list_precense);
            return(stop);
        }
    }
    //printf("on est au test 0 \n");
    
    //on test les gris (0)
    for(int i=0;i<5;i++)
    {
        if (config[i]=='0')
        {
            for (int j=0;j<5;j++)
            {
                if(word_ref[i]==word_test[j])
                {
                    if (occurences(list_precense,word_ref[i])>0)
                    {
                        if(occurences(word_ref,word_ref[i])>=occurences(list_precense,word_ref[i]))
                        {
                            free(list_precense);
                            return(false);
                        }
                    }
                    else
                    {
                        free(list_precense);
                        return(false);
                    }
                }
            }
        }
    }
    free(list_precense);
    return(true);
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