#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#define MODULO(x,y) ((x%y + y) % y)

int eFound = 0, aFound = 0;

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
    int j,i,trouve = 0;
    char lettrePossible[7];
    for(i = 0; i < strSize+1; ++i)
    {
        if(str[i] == str[i+1])
        {
            int found = 0;
            for(j = 0; j < trouve; ++j)
            {
                if(str[i] == lettrePossible[j])
                {
                    found = 1;
                    break;
                }
            }
            if(found == 0)
            {
                lettrePossible[trouve] = str[i];
                ++trouve;
            }
        }
    }

    if(trouve == 0)
    {
        printf("Aucune lettre double trouvee");
        return;
    }

    for(i = 0; i < trouve; ++i)
    {

    }
}

void motUneLettre(char* key,char* str,int strSize)
{
    // Soit A soit Y
    char question = ' ',lettre1=' ', lettre2=' ';
    int i;
    for(i = 1; i < strSize-1; ++i)
    {
        if(str[i] != ' ' && str[i-1] == ' ' && str[i+1] == ' ')
        {
            if(lettre1 == ' ')
                lettre1 = str[i];
            else if(lettre1 != str[i]){
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
        permuteKey(tmpKey,'A',lettre1-'A');
        strTmp = dechiffre(str,strSize,tmpKey);
        displayText(strTmp,strSize);
        printf("Lettre : %c remplacee par A\n",lettre1);
        printf("Garder cette lettre ? o/n\n");
        do
        {
            scanf("%c",&question);
        }while(question != 'o' && question != 'O' &&question != 'n' &&question != 'N');

        if(question == 'o' || question == 'O')
        {
            aFound = 1;
            permuteKey(key,'A',lettre1-'A');
        }
        else
        {
            permuteKey(key,'Y',lettre1-'A');
        }
    }
    else
    {
        printf("Deux lettres seules presentes dans le texte : %c et %c\n",lettre1,lettre2);
        permuteKey(tmpKey,'A',lettre1-'A');
        strTmp = dechiffre(str,strSize,tmpKey);
        displayText(strTmp,strSize);
        printf("Lettre : %c remplacee par A\n",lettre1);
        printf("Garder cette lettre ? o/n\n");
        do
        {
            scanf("%c",&question);
        }while(question != 'o' && question != 'O' &&question != 'n' &&question != 'N');
        aFound = 1;
        if(question == 'o' || question == 'O')
        {
            permuteKey(key,'A',lettre1-'A');
            permuteKey(key,'Y',lettre2-'A');
        }
        else
        {
            permuteKey(key,'Y',lettre1-'A');
            permuteKey(key,'A',lettre2-'A');
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
                    break;
                }
            }
        }
    }

    if (nbLettre == 0)
    {
        printf("Aucune lettre suivie d'une apostrophe\n");
        return;
    }
    // T,S,D,J,L,M,C,N
    char* strTmp;
    char* tmpKey;
    int tFound,sFound,dFound,jFound,lFound,mFound,cFound,nFound;
    tFound=sFound=dFound=jFound=lFound=mFound=cFound=nFound=0;
    for(i = 0; i < nbLettre; ++i)
    {
        tmpKey = key;
        if(tFound == 0)
        {
            char question;
            permuteKey(tmpKey,'T',lettrePossible[i]-'A');
            strTmp = dechiffre(str,strSize,tmpKey);
            displayText(strTmp,strSize);
            printf("Lettre : %c remplacee par T\n",lettrePossible[i]);
            printf("Garder cette lettre ? o/n\n");
            do
            {
                scanf("%c",&question);
            }while(question != 'o' && question != 'O' && question != 'n' && question != 'N');
            if(question == 'o' || question == 'O')
            {
                permuteKey(key,'T',lettrePossible[i]-'A');
                tFound = 1;
                continue;
            }
            else
                tmpKey = key;
        }

        if(jFound == 0)
        {
            char question;
            permuteKey(tmpKey,'J',lettrePossible[i]-'A');
            strTmp = dechiffre(str,strSize,tmpKey);
            displayText(strTmp,strSize);
            printf("Lettre : %c remplacee par J\n",lettrePossible[i]);
            printf("Garder cette lettre ? o/n\n");
            do
            {
                scanf("%c",&question);
            }while(question != 'o' && question != 'O' &&question != 'n' &&question != 'N');
            if(question == 'o' || question == 'O')
            {
                permuteKey(key,'J',lettrePossible[i]-'A');
                jFound = 1;
                continue;
            }
            else
                tmpKey = key;
        }

        if(sFound == 0)
        {
            char question;
            permuteKey(tmpKey,'S',lettrePossible[i]-'A');
            strTmp = dechiffre(str,strSize,tmpKey);
            displayText(strTmp,strSize);
            printf("Lettre : %c remplacee par S\n",lettrePossible[i]);
            printf("Garder cette lettre ? o/n\n");
            do
            {
                scanf("%c",&question);
            }while(question != 'o' && question != 'O' &&question != 'n' &&question != 'N');
            if(question == 'o' || question == 'O')
            {
                permuteKey(key,'S',lettrePossible[i]-'A');
                sFound = 1;
                continue;
            }
            else
                tmpKey = key;
        }

        if(dFound == 0)
        {
            char question;
            permuteKey(tmpKey,'D',lettrePossible[i]-'A');
            strTmp = dechiffre(str,strSize,tmpKey);
            displayText(strTmp,strSize);
            printf("Lettre : %c remplacee par D\n",lettrePossible[i]);
            printf("Garder cette lettre ? o/n\n");
            do
            {
                scanf("%c",&question);
            }while(question != 'o' && question != 'O' &&question != 'n' &&question != 'N');
            if(question == 'o' || question == 'O')
            {
                permuteKey(key,'D',lettrePossible[i]-'A');
                dFound = 1;
                continue;
            }
            else
                tmpKey = key;
        }

        if(lFound == 0)
        {
            char question;
            permuteKey(tmpKey,'L',lettrePossible[i]-'A');
            strTmp = dechiffre(str,strSize,tmpKey);
            displayText(strTmp,strSize);
            printf("Lettre : %c remplacee par L\n",lettrePossible[i]);
            printf("Garder cette lettre ? o/n\n");
            do
            {
                scanf("%c",&question);
            }while(question != 'o' && question != 'O' &&question != 'n' &&question != 'N');
            if(question == 'o' || question == 'O')
            {
                permuteKey(key,'L',lettrePossible[i]-'A');
                lFound = 1;
                continue;
            }
            else
                tmpKey = key;
        }

        if(mFound == 0)
        {
            char question;
            permuteKey(tmpKey,'M',lettrePossible[i]-'A');
            strTmp = dechiffre(str,strSize,tmpKey);
            displayText(strTmp,strSize);
            printf("Lettre : %c remplacee par M\n",lettrePossible[i]);
            printf("Garder cette lettre ? o/n\n");
            do
            {
                scanf("%c",&question);
            }while(question != 'o' && question != 'O' &&question != 'n' &&question != 'N');
            if(question == 'o' || question == 'O')
            {
                permuteKey(key,'M',lettrePossible[i]-'A');
                mFound = 1;
                continue;
            }
            else
                tmpKey = key;
        }

        if(cFound == 0)
        {
            char question;
            permuteKey(tmpKey,'C',lettrePossible[i]-'A');
            strTmp = dechiffre(str,strSize,tmpKey);
            displayText(strTmp,strSize);
            printf("Lettre : %c remplacee par C\n",lettrePossible[i]);
            printf("Garder cette lettre ? o/n\n");
            do
            {
                scanf("%c",&question);
            }while(question != 'o' && question != 'O' &&question != 'n' &&question != 'N');
            if(question == 'o' || question == 'O')
            {
                permuteKey(key,'C',lettrePossible[i]-'A');
                cFound = 1;
                continue;
            }
            else
                tmpKey = key;
        }

        if(nFound == 0)
        {
            char question;
            permuteKey(tmpKey,'N',lettrePossible[i]-'A');
            strTmp = dechiffre(str,strSize,tmpKey);
            displayText(strTmp,strSize);
            printf("Lettre : %c remplacee par N\n",lettrePossible[i]);
            printf("Garder cette lettre ? o/n\n");
            do
            {
                scanf("%c",&question);
            }while(question != 'o' && question != 'O' &&question != 'n' &&question != 'N');
            if(question == 'o' || question == 'O')
            {
                permuteKey(key,'N',lettrePossible[i]-'A');
                nFound = 1;
                continue;
            }
            else
                tmpKey = key;
        }
    }
}

void motProbable(char* key,char* str,int strSize)
{

}

void permutation(char* key,char* str,int strSize)
{
    char lettre1 = ' ', lettre2 = ' ';

    printf("Remplacer la lettre : \n");
    do
    {
        scanf("%c",&lettre1);
    }while(lettre1 < 'A' || lettre1 > 'Z');

    printf("\npar la lettre \n");
    do
    {
        scanf("%c",&lettre2);
    }while(lettre2 < 'A' || lettre2 > 'Z');

    int i,indexL1, indexL2;
    for(i = 0; i < 26; ++i)
    {
        if(key[i] == lettre1)
        {
            indexL1 = i;
        }
        if(key[i] == lettre2)
        {
            indexL2 = i;
        }
    }

    key[indexL1] = lettre2;
    key[indexL2] = lettre1;

}

void trouverDeuxLettresApostrophe(char* key,char* str,int fsize)
{
    int i;
    for(i = 0; i < fsize-2; ++i)
    {
        if(str[i+1] != str[i] && str[i+2] == '\'')
        {
            permuteKey(key,'Q',str[i]-'A');
            permuteKey(key,'U',str[i+1]-'A');
            return;
        }
    }
}

int question(char* key,char* str,int strSize)
{
    int result = -1;
    do{
        printf("Texte decode :\n\n");
        displayText(str,strSize);
        printf("\n\nCle : \n");
        displayText(key,26);
        printf("\n\nSelectionne une action a effectuer : \n\t1 : Analyse frequencielle\n\t2 : Traitement des mots de 2 caracteres\n\t3 : Traitement des mots de 1 lettre\n\t4 : Traitement des mots de 1 lettre suivi d'une apostrophe\n\t5 : Utiliser un mot probable\n\t6 : Permuter deux lettres\n\t7 : Trouver les \"QU'\"\n\t0 : Quitter\n");
        scanf("%d",&result);
    }while(result < 0 || result > 7);

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
    displayText(key,26);

    int running = question(key,str,fsize);

    char* tmpStr;

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
        case 6:
            permutation(key,str,fsize);
            break;
        case 7:
            trouverDeuxLettresApostrophe(key,str,fsize);
            break;
        }
        tmpStr = dechiffre(str,fsize,key);
        running = question(key,tmpStr,fsize);
    }
    //printf("%s\n",result);

    free(key);
    return 0;
}
