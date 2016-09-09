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

float calculIndiceCoincidence(char* str, float strSize)
{
    int i;

    float* tab[26];

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
    */

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

    printf("%s\n",strPure);

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

            for(j = i; j < strSize; j += keySize)
            {
                strRaccourci[k] = strPure[j];
                k++;
            }

            float indice = calculIndiceCoincidence(strRaccourci,(float)sizeStrRaccourci);

            free(strRaccourci);

            /*
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
            */

        }

        keySize++;
    }
    free(strPure);

    return keySizeSaved;
}

char* dechiffre(char* str,int strSize)
{
    // Déterminer longueur clé
    int keySize =  getKeySize(str,strSize,0.0746);


    //Déterminer la clé

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

    dechiffre(result,fsize);

    return 0;
}
