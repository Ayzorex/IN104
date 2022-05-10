#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
int main(int argc, char* argv[])
{
    FILE* dico = fopen(argv[1],"rb");
    FILE* dico_bis = fopen(argv[2],"wb");
    char buffer[128];
    while (! feof(dico))
    {
        fscanf(dico,"%s",buffer);
        if (strlen(buffer)==5)
        {
            fprintf(dico_bis,"%s\n",buffer);
        }
    }
    fclose(dico);
    fclose(dico_bis);
    return(0);
}
*/


unsigned int build_dico(char* word_size)
{
    FILE* dico = fopen("dico.txt","rb");

    char new_name[] = "dico_";
    strcat(new_name,word_size);
    strcat(new_name,".txt");
    FILE* new_dico = fopen(new_name,"wb");
    char buffer[128];

    int N = atoi(word_size);
    unsigned int size_dico = 0;
    
    while (! feof(dico))
    {
        fscanf(dico,"%s",buffer);
        if (strlen(buffer)==N)
        {
            fprintf(new_dico,"%s\n",buffer);
            size_dico++;
        }
    }
    fclose(dico);
    fclose(new_dico);
    return(size_dico);
}