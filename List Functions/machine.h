#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

typedef int typeqq;
typedef struct Tmaillon Tmaillon;
struct Tmaillon
{
    typeqq Val;
    Tmaillon *suiv;
};
typeqq valeur(Tmaillon *p);//retourne la valeur qui est dans le champ valeur du maillon p
void allouer(Tmaillon **p);//allouer un espace m�moire pour p
Tmaillon *suivant(Tmaillon *p);//retourne la valeur qui est dans le champ adresse du maillon p(l'adresse de l'�l�ment suivant)
void aff_val(Tmaillon *p,typeqq v);//affecter la valeur V au champ valeur de p
void aff_adr(Tmaillon *p,Tmaillon *q);//affecter l'adresse q au champ d'adresse de p
void liberer(Tmaillon *tete);
void construire_llc(Tmaillon **tete,int *llength); //Construire une llc � partir de n donn�es lues
int longueur (Tmaillon *tete);
int max_freq(Tmaillon *tete,int *occ);//retourne le nombre ayant la plus grand occurence dans une liste
int frequence(Tmaillon *tete,int nb);//retourne le frequence de nb dans la liste
Tmaillon *acces_pos_llc(Tmaillon *tete,int pos,Tmaillon **precedent);//retourne l'adresse du maillon ayant la position pos
Tmaillon *acces_val_llc(Tmaillon *tete,int val,Tmaillon **precedent);
void sup_val(Tmaillon **tete,int val);
void sup_val2(Tmaillon **tete,int val);
void inserer(Tmaillon **tete,int pos,int val); //inserer l'element val à la position pos
void sup_pos(Tmaillon **tete,int position);//supprimer l'element qui se trouve à la position p
void interclass(Tmaillon *t1,Tmaillon *t2,Tmaillon **t3);//interclasser  les deux liste t1 et t2 et retourner le résultat dans t3
void print_llc(Tmaillon *tete);
void invert_llc(Tmaillon **tete,Tmaillon **p,Tmaillon **q,Tmaillon **s,int n);
#endif // MACHINE_H_INCLUDED
