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


char* dechiffre(char* str, int strSize, int key)
{
    char* result = malloc(strSize * sizeof(char));
    int i;
    for(i = 0; i < strSize; i++){
        if(str[i] >= 'A' && str[i] <= 'Z'){
            result[i] = 'A' + MODULO((str[i]-'A')-key,26);
        }
        else{
            result[i] = str[i];
        }
    }
    return result;
}

int main(int argc, char** argv)
{
    if(argc != 3){
        perror("Usage : caesar_encrypt <texte> <cle>");
        exit(-1);
    }
    int fsize = strlen(argv[1]);
    int key = MODULO(atoi(argv[2]),26);

    char* str = argv[1];
    char* result = dechiffre(str,fsize,key);
    displayText(result,fsize);
    free(result);

    return 0;
}
