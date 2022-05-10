#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "dicoreduit.h"
#include "load_file.h"
#include "chain.h" 


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

    printf("%d \n",size);
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
        if(i%200 == 0)
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
Fonction dans laquelle le jeu tourne
*/
void play(unsigned int size_dico, char** word_array, char** config_array, int N)
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
    printf_array(word_array,new_size);
    while (strcmp(config_answer,"22222")!=0)
    {
        
        best_word=get_best_word(new_word_array,config_array, N, new_size);
        printf("le nouveau meilleur mot est : %s\n",best_word);
        printf("entrez la config réponse : ");
        scanf("%s",config_answer);
        printf("\n");
        printf_array(word_array,new_size);
        new_word_array_and_size = create_new_word_array(best_word,config_answer,word_array,new_size,N);
        new_word_array=new_word_array_and_size->array;
        new_size=new_word_array_and_size->size;
        turn++;
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
    
    // char* word_size = "5";
    // unsigned int N = atoi(word_size);
    /*
    struct Array_and_size* array_and_size = malloc(sizeof(struct Array_and_size));
    printf("ok");
    array_and_size = get_word_array("dico.txt");
    char** word_array = array_and_size->array;
    unsigned int size = array_and_size->size;
    printf("%s\n",word_array[0]);
    printf("%d\n",size);
    */

    /*
    unsigned int size_dico = build_dico(word_size);
    printf("%d\n",size_dico);
    printf("%d\n",N);
    
    char fname[] = "dico_";
    strcat(fname,word_size);
    //strcat(fname,".txt");
    printf("%s\n",fname);
    printf("on a éxécuté toutes les taches du programme !\n");
    */
    unsigned int size_dico = 135;
    char** word_array = load_file("dico_test.txt",size_dico);
    unsigned int N = 5;
    char** config_array = get_config_array(N);
    play(size_dico,word_array,config_array,N);
    //bool t = is_compatible("ALALA","ALALA","02000");
    //printf("%d\n",t);
    //double entropie = get_entropy("MANGERA",word_array,size_dico,config_array,N);
    //int number = get_number_compatible("11111","ALALA",size_dico,word_array);
    //printf("%f \n",entropie);
    //free_tab_char(word_array,size_dico);
    //free_tab_char(config_array,pow(3,N));

    return(0);
}