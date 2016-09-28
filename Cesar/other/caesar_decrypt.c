#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#define MODULO(x,y) ((x%y + y) % y)

char* dechiffre(char* str, int strSize, int key)
{
    char* result = malloc(strSize * sizeof(char));
    int i;
    for(i = 0; i < strSize; i++){
        if(str[i] >= 'A' && str[i] <= 'Z'){
            result[i] = str[i] + (MODULO(key - 'A',26));
            if(result[i] > 'Z')
                result[i] = '@' + (result[i] - 'Z');
        }
        else
            result[i] = str[i];
    }
    return result;
}

int main(int argc, char** argv)
{
    if(argc != 3){
        perror("Usage : caesar_encrypt <decalage> <texte>");
        exit(-1);
    }

    int fsize = strlen(argv[2]);
    int numKey = MODULO(-atoi(argv[1]),26);
    char key = 'A';
    int i;
    for(i = 0; i < numKey; i ++)
        key++;
    char* str = argv[2];
    char* result = dechiffre(str,fsize,key);
    printf("%s\n",result);
    free(result);
    return 0;
}