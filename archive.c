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