#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#define MODULO(x,y) ((x%y + y) % y)

char* generateKeyTable(char* init)
{
    char tmp [26];
    int i,j,found;

    for(i = 0; i < strlen(init);++i)
    {
        found = 0;
        for(j = 0; j < 26; ++j)
        {
            if(tmp[j] == init[i])
            {
                found = 1;
                break;
            }
        }
        if(found == 0)
            tmp[i] = init[i];
    }

    int cpt = i;

    char alpha;

    for(i = 0; i < 26; ++i)
    {
        alpha = 'A'+i;
        found = 0;

        for(j = 0; j < 26; ++j)
        {
            if(tmp[j] == alpha)
            {
                found = 1;
                break;
            }
        }

        if(found == 0){
            tmp[cpt] = alpha;
            ++cpt;
        }
    }

    char* result = (char*)malloc(26*sizeof(char));
    for(i = 0; i < 26; ++i)
    {
        for(j = 0; j < 26; ++j)
        {
            if(tmp[j] == 'A'+i)
            {
                result[i] = 'A'+j;
                break;
            }
        }
    }

    return result;
}

char* dechiffre(char* str, int fsize, char* key)
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
        perror("Usage : substitution_encrypt <key> <text>");
        exit(-1);
    }

    int fsize = strlen(argv[2]);//+1;

    char* startKey = (char*)argv[1];

    char* str = argv[2];

    char* key = generateKeyTable(startKey);
    printf("%s\n",key);

    char* result = dechiffre(str,fsize,key);
    printf("%s\n",result);

    free(key);
    free(result);
    return 0;
}

