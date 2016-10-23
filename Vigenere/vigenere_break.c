#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MODULO(x,y) ((x % y + y) % y)

struct key
{
    int size;
    char* key;
};

char* dechiffre(char* str, int strSize, char* key, int keySize)
{
    char* result = (char*) malloc(sizeof(char) * strSize);
    int i,j = 0;
    for(i = 0; i < strSize; ++i)
    {
        if('A' <= str[i] && str[i] <= 'Z')
        {
            result[i] = 'A' + MODULO((str[i] - 'A') - (key[j] - 'A'),26);
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

char** stringDivider(char* string,int strSize,int nbString)
{
    char** resultat;
    int i;
    resultat = (char**) malloc(nbString*sizeof(char*));

    for(i = 0; i < nbString; ++i)
        resultat[i] = (char*) malloc((strSize/nbString+1)*sizeof(char));

    for(i = 0; i < strSize; ++i)
    {
        resultat[i%nbString][i/nbString] = string[i];
    }
    return resultat;
}

float calculIndiceCoincidence(char* str, float strSize)
{
    int i;

    float tab[26];

    // correct juste parce que je rempli de 0
    memset((void *)tab,0,26*sizeof(int));

    // On compte le nombre de char
    for(i = 0; i < strSize; i++)
    {
        int index = str[i] - 'A';
        tab[index]++;
    }

    float indice = 0;
    // on calcule l'indice
    for(i = 0; i < 26; i++)
    {
        indice += (tab[i]*(tab[i]-1.0))/(strSize * (strSize - 1.0));
    }
    return indice;

}

int getKeySize(char* str, int strSize)
{
    int keySize = 1;

    while(keySize < 16)
    {
        char** stringDivided = stringDivider(str,strSize,keySize);
        int i;

        float sum = 0.0f;

        for(i = 0; i < keySize; ++i)
        {
            float strDividedSize = strSize/keySize;
            if(i < strSize%keySize)
                ++strDividedSize;

            sum += calculIndiceCoincidence(stringDivided[i],strDividedSize);
            free(stringDivided[i]);
        }
        free(stringDivided);

        float moyenne = sum/keySize;
        if(moyenne > 0.074)
            return keySize;

        keySize++;
    }

    return keySize;
}

char getKeyFrequencielle(char* str, int strSize)
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

    int key = MODULO(indexMax - 4,26);
    return key;
}

struct key getKey(char* str, int strsize)
{
    struct key k;

    int keySize = getKeySize(str,strsize);
    printf("key size : %d\n",keySize);

    int i;

    // On divise la chaine en keysize chaine plus petite et on cherche à la façon du code César
    char * key = malloc(keySize*sizeof(char));
    char** stringDivided = stringDivider(str,strsize,keySize);

    for(i = 0; i < keySize; i++)
    {
        int strDividedSize = strsize/keySize;
            if(i < strsize%keySize)
                ++strDividedSize;

        key[i] = 'A'+getKeyFrequencielle(stringDivided[i],strDividedSize);
        free(stringDivided[i]);
    }
    free(stringDivided);

    k.key = key;
    k.size = keySize;

    return k;
}

int main(int argc, char** argv)
{

    if(argc < 2){
        perror("Usage : vigenere_break <texte>");
        exit(-1);
    }

    // On purifie la chaine
    int fsize = strlen(argv[1]);
    char* str = argv[1];

    int i,pureSize = 0;
    char* strPure = malloc(fsize*sizeof(char));
    for(i = 0; i < fsize; ++i)
    {
        if(str[i] >= 'A' && str[i] <= 'Z')
        {
            strPure[pureSize] = str[i];
            ++pureSize;
        }
    }
    printf("Chaine chiffree : \n");
    displayString(str,fsize);
    printf("Chaine pure : \n");
    displayString(strPure,pureSize);

    // On brise le chiffrement
    struct key key = getKey(strPure,pureSize);
    printf("Cle : \n");
    displayString(key.key,key.size);

    char* result = dechiffre(str,fsize,key.key,key.size);

    printf("Chaine dechiffree : \n");
    displayString(result,fsize);

    free(key.key);
    free(result);
    free(strPure);
    //free(result);*/

    return 0;
}
