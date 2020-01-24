#ifndef LIFO_H_INCLUDED
#define LIFO_H_INCLUDED
#define MAX 100

typedef struct PILE PILE;
struct PILE
{
    int tab[MAX];
    int sommet;
};

typedef struct ListeP ListeP;
struct ListeP//structure d'un maillon d'une pile
{
    int val;
    ListeP *suiv;
};
typedef struct ListeP PILED;

void creer_pile(PILE p);
int pile_vide(PILE p);
int pile_pleine(PILE p);
void empiler(PILE p,int valeur);
void depiler(PILE p,int *valeur);



void allouerp(ListeP **l);
int valeurp(ListeP *p);
ListeP *suivantp(ListeP *p);
void aff_adrp(ListeP *p,ListeP *q);
void aff_valp(ListeP *p,int valeur);

void creer_piled(PILED **p);
int piled_vide(PILED *p);
void empilerd(PILED **p,int valeur);
void depilerd(PILED **p,int *valeur);

void affich_pile(PILED *p);
#endif // LIFO_H_INCLUDED
