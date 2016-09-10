#include <stdio.h>
#include <stdlib.h>

char* chiffre(char* str, int strSize, char key, int keySize)
{
    char* result = malloc(strSize * sizeof(char));
    int i;
    for(i = 0; i < strSize; i++){
        if(str[i] >= 'A' && str[i] <= 'Z'){
            result[i] = str[i] + ((key - 'A')%26);
            if(result[i] > 'Z'){
                result[i] = '@' + (result[i] - 'Z');
            }
        }
        else{
            result[i] = str[i];
        }
    }
    return result;
}

char* dechiffreBruteForce(char* str, int strSize, char* key)
{
    char* result = malloc(strSize * sizeof(char));
    char i;

    for(i = 'A'; i <= 'Z'; i++)
    {
        int j;
        for(j = 0; j < strSize; j++){
            if(str[j] >= 'A' && str[j] <= 'Z'){
                result[j] = str[j] - ((i - 'A')%26);
                if(result[j] < 'A'){
                    result[j] ='[' - ('A' - result[j]);
                }
            }
            else{
                result[j] = str[j];
            }
        }

        printf("Cle : %c -> /n %s /n/n Correct ? Y/N",i,result);

        char c = ' ';
        do{
            c = getc(stdin);
        }while(c != 'Y' && c != 'y' && c != 'N' && c != 'n');

        if(c == 'Y' || c == 'y')
        {
            *key = i;
            break;
        }
    }
    return result;
}

char* dechiffreFrequencielle()
{

}

int main()
{
    FILE* fp = fopen("text.txt","r");

    fseek(fp,0,SEEK_END);

    int fsize = ftell(fp)+1;

    char key = 'Z';

    fseek(fp,0,0);

    char * str = malloc(fsize * sizeof(char));

    fgets(str,fsize,fp);

    fclose(fp);

    char* result = chiffre(str,fsize,key,4);

    free(str);

    printf("%s\n",result);

    char resultkey;

    result = dechiffreBruteForce(result,fsize, &resultkey);

    printf("Resultat brutforce : cle : %c %s\n",resultkey,result);

    //result = dechiffreFrequencielle(result,fsize);

    //printf("Resultat frequencielle : %s\n",result);

    free(result);

    return 0;
}
