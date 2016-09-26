#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int getKeySize(char* str, int strSize, float indiceLangue)
{
    int cpt,pureSize = 0;

    char* strPure = malloc(strSize*sizeof(char));

    // On enlève les caractères spéciaux
    for(cpt = 0; cpt < strSize; cpt++)
    {
        if(str[cpt] >= 'A' && str[cpt] <= 'Z'){
            strPure[pureSize] = str[cpt];
            pureSize++;
        }
    }

    int keySizeSaved;

    float ecartSaved = 1.0;

    int keySize = 1;

    while(keySize < pureSize)
    {
        int i;

        for(i = 0; i < keySize; i++)
        {

            int sizeStrRaccourci = pureSize/keySize + pureSize%keySize;
            char* strRaccourci = malloc(sizeStrRaccourci * sizeof(char));

            int j;
            int k = 0;

            for(j = i; j < pureSize; j += keySize)
            {
                strRaccourci[k] = strPure[j];
                k++;
            }

            float indice = calculIndiceCoincidence(strRaccourci,(float)sizeStrRaccourci);

            free(strRaccourci);

            float ecart = indiceLangue - indice;

            if(ecart < 0)
            {
                ecart *= -1;
            }

            if(ecart < ecartSaved)
            {
                ecartSaved = ecart;
                keySizeSaved = keySize;
            }

        }

        keySize++;
    }
    free(strPure);

    return keySizeSaved;
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

    int key = indexMax - 4;
    return key;
}

char* breaker(char* str, int strsize)
{
    int keySize = getKeySize(str,strsize,0.074);
    printf("key size : %d\n",keySize);

    int cpt,pureSize = 0;

    char* strPure = malloc(strsize*sizeof(char));

    // On enlève les caractères spéciaux
    for(cpt = 0; cpt < strsize; cpt++)
    {
        if(str[cpt] >= 'A' && str[cpt] <= 'Z'){
            strPure[pureSize] = str[cpt];
            pureSize++;
        }
    }

    // On divise la chaine en keysize chaine plus petite et on cherche à la façon du code César
    char * key = malloc(keySize*sizeof(char));
    for(cpt = 0; cpt < keySize; cpt++)
    {
        char* strRaccourcie = malloc((pureSize/keySize + 1)*sizeof(char));
        unsigned int i,cursor = 0;
        for(i = cpt; i < pureSize ;i+=keySize)
        {
            strRaccourcie[cursor] = strPure[i];
            cursor++;
        }
        key[cpt] = 'A'+getKeyFrequencielle(strRaccourcie,cursor);
        printf("%c : %d\n",key[cpt],key[cpt]);
        free(strRaccourcie);
    }

    printf("%s\n",key);

    return str;
}

int main(int argc, char** argv)
{

    if(argc < 2){
        perror("Usage : vigenere_break <texte>");
        exit(-1);
    }

    char* result;

    int fsize = strlen(argv[1]);
    printf("strSize : %d\n", fsize);
    char* str = argv[1];
    result = breaker(str,fsize);
    printf("Resultat breaker : %s\n",result);
    free(result);

    return 0;
}
