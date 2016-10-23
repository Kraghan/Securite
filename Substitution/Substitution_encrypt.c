#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#define MODULO(x,y) ((x%y + y) % y)

void displayText(char* str, int strsize)
{
    int i;
    printf("\n");
    for(i = 0; i < strsize; ++i)
    {
        printf("%c",str[i]);
    }
    printf("\n");
}

char* generateKeyTable(char* init)
{
    char* result = (char*)malloc(26*sizeof(char));
    int i,j,cpt = 0,found;

    for(i = 0; i < strlen(init);++i)
    {
        found = 0;
        for(j = 0; j < cpt; ++j)
        {
            if(result[j] == init[i])
            {
                found = 1;
                break;
            }
        }
        if(found == 0)
        {
            result[cpt] = init[i];
            ++cpt;
        }
    }

    char alpha = 'A';

    for(i = 0; i < 26; ++i)
    {
        found = 0;

        for(j = 0; j < cpt; ++j)
        {
            if(result[j] == alpha)
            {
                found = 1;
                break;
            }
        }

        if(found == 0){
            result[cpt] = alpha;
            ++cpt;
        }
        alpha++;
    }

    return result;
}

char* chiffre(char* str, int fsize, char* key)
{
    char* result = (char*)malloc(fsize*sizeof(char));
    int i;
    for(i = 0; i < fsize; ++i)
    {
        if('A' <= str[i] && str[i] <= 'Z')
        {
            result[i] = key[str[i] - 'A'];
        }
        else
        {
            result[i] = str[i];
        }
    }

    return result;
}

int main(int argc, char** argv)
{
    if(argc != 3){
        perror("Usage : substitution_encrypt <text> <key>");
        exit(-1);
    }

    int fsize = strlen(argv[1]);//+1;

    char* startKey = (char*)argv[2];

    char* str = argv[1];

    char* key = generateKeyTable(startKey);
    printf("Key\n");
    displayText(key,26);
    char* result = chiffre(str,fsize,key);
    printf("Encrypt\n");
    displayText(result,fsize);

    free(key);
    free(result);
    return 0;
}
