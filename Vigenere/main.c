#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char* chiffre(char* str, int strSize, char* key, int keySize)
{
    char* result = malloc(strSize * sizeof(char));
    int j = 0;
    int i;
    for(i = 0; i < strSize; i++){
        if(str[i] >= 'A' && str[i] <= 'Z'){
            result[i] = str[i] + ((key[j] - 'A')%26);
            if(result[i] > 'Z'){
                result[i] = '@' + (result[i] - 'Z');
            }
            j++;
        }
        else{
            result[i] = str[i];
        }

        if(j == keySize)
            j = 0;
    }
    return result;
}

int main()
{
    FILE* fp = fopen("text.txt","r");

    fseek(fp,0,SEEK_END);

    int fsize = ftell(fp)+1;

    char* key = "TEST";

    fseek(fp,0,0);

    char * str = malloc(fsize * sizeof(char));

    fgets(str,fsize,fp);

    char* result = chiffre(str,fsize,key,4);

    printf("%s\n",result);

    return 0;
}
