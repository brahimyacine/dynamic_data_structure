#include <stdio.h>
#include <stdlib.h>
#include"utils.h"

int main()
{   Tmaillon *tete1,*tete2,*tete3,*p;
    int llength1=0,llength2=0,occ,pos,nbmaxfreq;
    char c;
    printf("Hello world!\n");

    construire_llc(&tete1,&llength1);
    while(getchar()!='\n');
    construire_llc(&tete2,&llength2);
    p=tete1;

    while(p!=NULL)
    {
        printf("%d ",valeur(p));
        p=suivant(p);
    }
    printf("\n");
    p=tete2;
    while(p!=NULL)
    {
        printf("%d ",valeur(p));
        p=suivant(p);
    }
    interclass(tete1,tete2,&tete3);
    p=tete3;
    printf("\n");
    while(p!=NULL)
    {
        printf("%d ",valeur(p));
        p=suivant(p);
    }

    liberer(&tete3);
    return 0;
}
