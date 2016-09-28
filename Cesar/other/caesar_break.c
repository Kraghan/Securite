
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO(x,y) ((x % y + y) % y)

char* dechiffre(char* str, int strSize,char key)
{
    char* result = malloc(strSize * sizeof(char));
    int j;
    for(j = 0; j < strSize; j++){
        if(str[j] >= 'A' && str[j] <= 'Z'){
            result[j] = str[j] - MODULO((key - 'A'),26);
            if(result[j] < 'A'){
                result[j] ='[' - ('A' - result[j]);
            }
        }
        else{
            result[j] = str[j];
        }
    }
    return result;
}

char* dechiffreInt(char* str, int strSize,int key)
{
    printf("%d",strSize);
    char* result = malloc(strSize * sizeof(char));
    int j;
    for(j = 0; j < strSize; j++){
        if(str[j] >= 'A' && str[j] <= 'Z'){
            result[j] = str[j] - key;
            if(result[j] < 'A'){
                result[j] ='[' - ('A' - result[j]);
            }
        }
        else{
            result[j] = str[j];
        }
    }
    return result;
}

char* dechiffreBruteForce(char* str, int strSize)
{
    char* result = "Erreur : non déchiffré";
    char* strDechiffre;
    char i;

    for(i = 'A'; i <= 'Z'; i++)
    {
        strDechiffre = dechiffre(str,strSize,i);

        printf("Cle : %c -> /n %s /n/n Correct ? Y/N",i,strDechiffre);

        char c = ' ';
        do{
            c = getc(stdin);
        }while(c != 'Y' && c != 'y' && c != 'N' && c != 'n');

        if(c == 'Y' || c == 'y')
        {
            result = strDechiffre;
            break;
        }
    }
    return result;
}

char* dechiffreFrequencielle(char* str, int strSize)
{

    int tab[26];

    memset(tab,0,26*sizeof(int));

    int i,j = 0;
    for(i = 0; i < strSize; i++)
    {
        if(str[i] >= 'A' && str[i] <= 'Z')
        {
            tab[str[i] - 'A']++;
            j++;
        }
    }

    float frequence[26];
    int indexMax = -1;

    for(i = 0; i < 26; i++)
    {
        frequence[i] = (float)tab[i]/(float)j;
        if(indexMax == -1 || frequence[indexMax] < frequence[i]){
            indexMax = i;
        }
    }

    int key = indexMax - 4;
    return dechiffreInt(str,strSize,key);
}

int main(int argc, char** argv)
{

    if(argc < 2 || argc > 3){
        perror("Usage : caesar_encrypt [-B] <texte>");
        exit(-1);
    }

    if(argc == 3 && (strcmp(argv[1],"-B") != 0)){
        perror("Paramètre inconnu : -B pour méthode bruteforce");
        exit(-2);
    }

    char* result;

    if(argc == 3){

        int fsize = strlen(argv[2]);
        char* str = argv[2];
        result = dechiffreBruteForce(str,fsize);
        printf("Resultat brutforce : %s\n",result);
    }
    else{
        int fsize = strlen(argv[1]);
        char* str = argv[1];
        result = dechiffreFrequencielle(str,fsize);
        printf("Resultat frequencielle : %s\n",result);
    }

    free(result);
    return 0;
}
