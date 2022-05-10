#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

/*
Revoie true si le mot est compatible avec la config et false sinon
*/
bool is_compatible(char* word_ref, char* word_test, char* config)
{
    bool stop=false;
    char* marquage = calloc(5,sizeof(char));

//On test les vert (2)
    for(int i=0;i<5;i++)
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
    for(int i=0;i<5;i++)
    {
        stop=false;
        if (config[i]=='1')
        {
            if(word_test[i]==word_ref[i]) 
            {
                free(marquage);
                return(false);
            }
            for(int j=0;j<5;j++)
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
    for(int i=0;i<5;i++)
    {
        if(config[i]=='0')
        {
            for(int j=0;j<5;j++)
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



int main(int argc, char const *argv[])
{
    bool t1 = is_compatible("ABCDE","FGHIJ","00000");
    if (t1) printf("test 1 ok\n");

    bool t2 = is_compatible("ABCDE","FGHEI","00000");
    if (!t2) printf("test 2 ok\n");

    bool t3 = is_compatible("ABYYY","AZBZZ","21000");
    if (t3) printf("test 3 ok\n");

    bool t4 = is_compatible("AYYYY","ZAZZZ","10000");
    if (t4) printf("test 4 ok\n");

    bool t5 = is_compatible("AAYYY","ZZAZA","11000");
    if (t5) printf("test 5 ok\n");

    bool t6 = is_compatible("AAAYY","ZZAAZ","11000");
    if (t6) printf("test 6 ok\n");

    bool t7 = is_compatible("AAYYY","ZAZZZ","11000");
    if (!t7) printf("test 7 ok\n");

    bool t8 = is_compatible("AYYYY","AZZZZ","10000");
    if (!t8) printf("test 8 ok\n");

    bool t9 = is_compatible("AAYYY","AAZZZ","11000");
    if (!t9) printf("test 9 ok\n");

    bool t10 = is_compatible("AAYYY","ZZZZZ","01000");
    if (!t10) printf("test 10 ok\n");

    bool t11 = is_compatible("AAYYY","ZZAZZ","01000");
    if (!t11) printf("test 11 ok\n");

    bool t12 = is_compatible("AAYYY","ZAZAZ","11000");
    if (!t12) printf("test 12 ok\n");

    return 0;
}
