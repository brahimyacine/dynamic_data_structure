#include <stdlib.h>
#include <stdio.h>
#include "LIFO.h"
/*---------------Impelémantation des PILES-------------*/
/*----------------------STATIQUE------------------------*/

void creer_pile(PILE p)
{
    p.sommet=0;
}
int pile_vide(PILE p)
{
   return(p.sommet==0);
}
int pile_pleine(PILE p)
{
    return(p.sommet==MAX-1);
}
void empiler(PILE p,int valeur)
{
    if(!pile_pleine(p))
    {
        p.sommet++;
        p.tab[p.sommet]=valeur;
    }
    else
        printf("Pile pleine \n");
}
void depiler(PILE p,int *valeur)
{
    if(!pile_vide(p))
    {
       *valeur=p.tab[p.sommet];
       p.sommet--;
    }
    else printf("Pile vide \n");
}
/*--------------------DYNAMIQUE-------------------------*/


void allouerp(ListeP **l)
{
*l=malloc(sizeof(ListeP));
}
int valeurp(ListeP *p)
{
    return(p->val);
}
ListeP *suivantp(ListeP *p)
{
    return(p->suiv);
}
void aff_adrp(ListeP *p,ListeP *q)
{
    p->suiv=q;
}
void aff_valp(ListeP *p,int valeur)
{
    p->val=valeur;
}

void creer_piled(PILED **p)
{
   *p=NULL;
}
int piled_vide(PILED *p)
{
    return(p==NULL);
}
void empilerd(PILED **p,int valeur)
{
    ListeP *l;
allouerp(&l);
if(*p==NULL)//la pile est vide
    aff_adrp(l,NULL);

else //la pile n'est pas vide
{
    aff_adrp(l,*p);
}
*p=l;
aff_valp(*p,valeur);
}
void depilerd(PILED **p,int *valeur)
{   ListeP *l;
    if(!piled_vide(*p))
    {
    *valeur=valeurp(*p);
    l=*p;
    *p=suivantp(*p);
    free(l);
    }
    else
        printf("Pile vide");
}

void affich_pile(PILED *p)
{   ListeP *q;
    if(!piled_vide(p))
    {   q=p;
        printf("\n");
        while(q!=NULL)
        {
            printf("%d  ",valeurp(q));

            q=suivantp(q);
        }
        printf("\n");
    }
    else
        printf("\n Pile vide \n");
}
