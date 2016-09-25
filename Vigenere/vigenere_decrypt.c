#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    if(argc != 2){

    }

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
