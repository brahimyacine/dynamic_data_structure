#include <stdio.h>
#include <stdlib.h>
#include "bdlist.h"

int main()
{   Tmaillonb *tete,*p;
    int longueur,pos,val;
    printf("Liste Bidirectionnelle!\n");
    Create_llcb(&tete,&longueur);
    p=tete;
    while(p!=NULL)
    {
        printf("%d  ",valeur(p));
        p=suivant(p);
    }

    printf("\n Entrez la position o� vous voulez ins�rer le nouvel element :");
    scanf("%d",&pos);
    printf("\n Entrez la valeur du nouvel element:");
    scanf("%d",&val);
    insererb(&tete,pos,val);
    p=tete;
    while(p!=NULL)
    {
        printf("%d  ",valeur(p));
        p=suivant(p);
    }
    return 0;
}
