#ifndef BDLIST_H_INCLUDED
#define BDLIST_H_INCLUDED
typedef int typeqq;
typedef struct Tmaillonb Tmaillonb;
struct Tmaillonb
{
    typeqq Val;
    Tmaillonb *prec;
    Tmaillonb *suiv;
};
typeqq valeur(Tmaillonb *p);
Tmaillonb *suivant(Tmaillonb *p);
Tmaillonb *precedent(Tmaillonb *p);
void allouer(Tmaillonb **p);
void aff_val(Tmaillonb *p,typeqq v);
void aff_adrD(Tmaillonb *p,Tmaillonb *q);
void aff_adrG(Tmaillonb *p,Tmaillonb *q);

void Create_llcb(Tmaillonb **head,int *LENGTH);
Tmaillonb *acces_pos_llcb(Tmaillonb *HEAD,int POS,Tmaillonb **Precedent);
void insererb(Tmaillonb **HEAD,int POS,int val);
#endif // BDLIST_H_INCLUDED
