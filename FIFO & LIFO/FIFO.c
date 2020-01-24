#include "FIFO.h"
#include <stdlib.h>
#include <stdio.h>
/*Circular FIFO*/
typedef struct FILE file;
typedef struct listeF listeF;
typedef struct filed filed;
void creer_file(file *F)
{
    F->tete=MAX-1;
    F->queue=MAX-1;
}
int file_vide(file F)
{
    return(F.queue==F.tete);
}
int file_pleine(file F)
{
    return(F.tete==((F.queue+1)%(MAX)));

}
void enfiler(file *F,int x)
{
    if (!file_pleine(*F))
    {
    (F->queue=(F->queue+1)%(MAX));
    F->tab[F->queue]=x;
    }
    else
        printf("FILE PLEINE \n");
}
void defiler(file *F,int *x)
{
 if (!file_vide(*F))
 {
     *x=(F->tab[(F->tete+1)%(MAX)]);
     (F->tete=(F->tete+1)%(MAX));
 }
 else
    printf("FILE vide \n");
}
void affich_file(filed f)
{   listeF *p;
    if(!filed_vide(f))
    {   p=f.tete;
        printf("\n");
        while(p)
        {
            printf("%d  ",valeur(p));
            p=suivant(p);
        }
        printf("\n");
    }
    else
        printf("\n File vide \n");
}
/*Dynamic FIFO*/
/*---------------------------------------------DYNAMIQUE---------------------------------------------------------*/

void allouer(listeF **l)
{
*l=malloc(sizeof(listeF));
}
int valeur(listeF *p)
{
    return(p->val);
}
listeF *suivant(listeF *p)
{
    return(p->adr);
}
void aff_adr(listeF *p,listeF *q)
{
    p->adr=q;
}
void aff_val(listeF *p,int valeur)
{
    p->val=valeur;
}
void creer_filed(filed *f)
{
    f->tete=NULL;
    f->queue=NULL;
}
int filed_vide(filed f)
{
    return(f.tete==NULL);
}
void enfilerd(filed *f,int x)
{
    listeF *p;
    allouer(&p);aff_adr(p,NULL);
    aff_val(p,x);
    if (filed_vide(*f))
    {
    f->tete=p;f->queue=p;
    }
    else
    {
        aff_adr(f->queue,p);
        f->queue=p;
    }
}
void defilerd(filed *f,int *x)
{
    listeF *sauv;
    if(!filed_vide(*f))
    {
     sauv=f->tete;
     *x=valeur(f->tete);
     f->tete=suivant(f->tete);
     free(sauv);
    }
    else
        printf("File vide \n");
}
