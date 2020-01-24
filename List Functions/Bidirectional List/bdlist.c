#include<stdio.h>
#include<stdlib.h>
#include"bdlist.h"

typeqq valeur(Tmaillonb *p)
{
    return(p->Val);
}
Tmaillonb *suivant(Tmaillonb *p)
{
    return(p->suiv);
}
Tmaillonb *precedent(Tmaillonb *p)
{
    return(p->prec);
}
void allouer(Tmaillonb **p)
{
    *p=(Tmaillonb *)malloc(sizeof(Tmaillonb));
}
void aff_val(Tmaillonb *p,typeqq v)
{
    p->Val=v;

}
void aff_adrD(Tmaillonb *p,Tmaillonb *q)
{
    p->suiv=q;
}
void aff_adrG(Tmaillonb *p,Tmaillonb *q)
{
    p->prec=q;
}


void Create_llcb(Tmaillonb **head,int *LENGTH)
{
    int NBdonnees,val,i;
    Tmaillonb *p,*q;
    printf("Entrez la taille de la liste bidirectionnelle :: ");
    scanf("%d",&NBdonnees);
    *head=NULL;
    *LENGTH=NBdonnees;
    for(i=0;i<NBdonnees;i++)
    {   allouer(&p);
        if(*head==NULL)
        {
            *head=p;aff_adrG(p,NULL);
        }
        else
        {
            aff_adrD(q,p);aff_adrG(p,q);
        }
        printf("Entrez la valeur %i :: ",i);
        scanf("%d",&val);
        aff_val(p,val);
        q=p;
    }
    aff_adrD(p,NULL);
}
Tmaillonb *acces_pos_llcb(Tmaillonb *HEAD,int POS,Tmaillonb **Precedent)
{

    int cpt=0;

    while(HEAD!=NULL && cpt<POS)
    {   *Precedent=HEAD;
        HEAD=suivant(HEAD);
        cpt++;
    }

    if (cpt==POS)

     return(HEAD);

    else
        return(NULL);
}
void insererb(Tmaillonb **HEAD,int POS,int val)
{
Tmaillonb *p,*q,*prec;

allouer(&q);
aff_val(q,val);
p=acces_pos_llcb(*HEAD,POS,&prec);
if(POS==0)
{
    aff_adrG(q,NULL);aff_adrD(q,*HEAD);aff_adrG(*HEAD,q);*HEAD=q;
}
else
{
  if(p==NULL)
    {
        aff_adrG(q,prec);aff_adrD(q,NULL);aff_adrD(prec,q);
    }
else
{
   aff_adrD(q,p);aff_adrG(q,precedent(p));aff_adrD(precedent(p),q);aff_adrG(p,q);
}
 }
}
