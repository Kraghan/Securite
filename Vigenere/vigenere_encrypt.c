#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MODULO(x,y) ((x % y + y) % y)

char* chiffre(char* str, int strSize, char* key, int keySize)
{
    char* result = (char*) malloc(sizeof(char) * strSize);
    int i,j = 0;
    for(i = 0; i < strSize; ++i)
    {
        if('A' <= str[i] && str[i] <= 'Z')
        {
            result[i] = 'A' + MODULO((str[i] - 'A') + (key[j] - 'A'),26);
            ++j;
            if(j == keySize)
                j = 0;
        }
        else
            result[i] = str[i];
    }
    return result;
}

void displayString(char* string, int size)
{
    int i;
    for(i = 0; i < size; ++i)
    {
        printf("%c",string[i]);
    }
    printf("\n");
}


int main(int argc, char** argv)
{
    if(argc != 3 ){
        perror("Usage : vigenere_encrypt <texte> <cle>");
        exit(-1);
    }

    int fsize = strlen(argv[1]);
    char* str = argv[1];

    int keysize = strlen(argv[2]);
    char* key = argv[2];

    char* result = chiffre(str,fsize,key,keysize);

    displayString(result,fsize);

    free(result);

    return 0;
}
