#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#define MODULO(x,y) ((x%y + y) % y)

int eFound = 0, aFound = 0;

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

void permuteKey(char* key, char alpha, int indexBeta)
{
    if(indexBeta < 0)
        indexBeta += 26;
    int a,i;
    for(i = 0; i < 26; ++i)
    {
        if(key[i] == alpha)
        {
            a = i;
            break;
        }
    }

    key[a] = key[indexBeta];
    key[indexBeta] = alpha;
}

char* generateEmptyKeyTable()
{
    char* result = (char*)malloc(26*sizeof(char));
    int i;

    for(i = 0; i < 26;++i)
    {
        result[i] = 'A'+i;
    }
    return result;
}

void analyseFrequencielle(char* key,char* str,int strSize)
{
    // Trouver le e
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
    eFound = 1;
    permuteKey(key,'E',indexMax);
}

void traiterDoubleLettre(char* key,char* str,int strSize)
{
    // E,M,L,N,F,T,C
}

void motUneLettre(char* key,char* str,int strSize)
{
    // Soit A soit Y
    char question,lettre1=' ', lettre2=' ';
    int i;
    for(i = 1; i < strSize-1; ++i)
    {
        if(str[i] != ' ' && str[i-1] == ' ' && str[i+1] == ' ')
        {
            if(lettre1 == ' ')
                lettre1 = str[i];
            else{
                lettre2 = str[i];
                break;
            }
        }
    }

    char* tmpKey = key;
    char* strTmp;

    if(lettre1 == ' ')
    {
        printf("Aucune lettre seule presente dans le texte\n");
        return;
    }
    else if(lettre1 != ' ' && lettre2 == ' ')
    {
        printf("Une lettre seule presente dans le texte : %c\n",lettre1);
        //Decoder avec les deux lettres possibles et laisser le choix
        permuteKey(tmpKey,'A',lettre1);
        strTmp = dechiffre(str,strSize,tmpKey);
        printf("%s \n\n Garder cette lettre ? o/n",strTmp);
        scanf("%c",&question);
        if(question == 'o' || question == 'O')
        {
            aFound = 1;
            permuteKey(key,'A',lettre1);
        }
        else
        {
            permuteKey(key,'Y',lettre1);
        }
    }
    else
    {
        printf("Deux lettres seules presentes dans le texte : %c et %c\n",lettre1,lettre2);
        permuteKey(tmpKey,'A',lettre1);
        strTmp = dechiffre(str,strSize,tmpKey);
        printf("%s \n\n Garder cette lettre ? o/n",strTmp);
        scanf("%c",&question);
        aFound = 1;
        if(question == 'o' || question == 'O')
        {
            permuteKey(key,'A',lettre1);
            permuteKey(key,'Y',lettre2);
        }
        else
        {
            permuteKey(key,'Y',lettre1);
            permuteKey(key,'A',lettre2);
        }
    }
}

void motUneLettreApostrophe(char* key,char* str,int strSize)
{
    // Detection des lettres seules avec apostrophe.
    char lettrePossible[8];
    int i,j,nbLettre = 0;
    for(j = 0; j < 8;++j)
        lettrePossible[j] = ' ';

    for(i = 1; i < strSize-1; ++i)
    {
        if(str[i] != ' ' && str[i-1] == ' ' && str[i+1] == '\'')
        {
            for(j = 0; j < 8;++j)
            {
                if(lettrePossible[j] == str[i])
                    break;

                if(lettrePossible[j] == ' ')
                {
                    lettrePossible[j] = str[i];
                    nbLettre = j;
                }
            }
        }
    }
    // T,S,D,J,L,M,C,N
}

void motProbable(char* key,char* str,int strSize)
{

}

int question(char* key,char* str,int strSize)
{
    int result = -1;
    do{
        printf("Texte decode :\n\n%s\n\nCle : \n%s\n\nSelectionne une action a effectuer : \n\t1 : Analyse frequencielle\n\t2 : Traitement des mots de 2 caracteres\n\t3 : Traitement des mots de 1 lettre\n\t4 : Traitement des mots de 1 lettre suivi d'une apostrophe\n\t5 : Utiliser un mot probable\n\t0 : Quitter\n",str,key);
        scanf("%d",&result);
    }while(result < 0 || result > 5);

    return result;
}

int main(int argc, char** argv)
{
    if(argc != 2){
        perror("Usage : substitution_encrypt <text>");
        exit(-1);
    }

    int fsize = strlen(argv[1]);

    char* str = argv[1];

    char* key = generateEmptyKeyTable();
    printf("%s\n",key);

    int running = question(key,str,fsize);

    while(running!=0)
    {
        switch(running)
        {
        case 1:
            analyseFrequencielle(key,str,fsize);
            break;
        case 2:
            traiterDoubleLettre(key,str,fsize);
            break;
        case 3:
            motUneLettre(key,str,fsize);
            break;
        case 4:
            motUneLettreApostrophe(key,str,fsize);
            break;
        case 5:
            motProbable(key,str,fsize);
            break;
        }
        str = dechiffre(str,fsize,key);
        running = question(key,str,fsize);
    }
    //printf("%s\n",result);

    free(key);
    return 0;
}
