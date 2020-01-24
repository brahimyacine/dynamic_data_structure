#ifndef FIFO_H_INCLUDED
#define FIFO_H_INCLUDED
#define MAX 100
typedef struct FILE file;
struct FILE
{   int tab[MAX];
    int tete;
    int queue;
};

typedef struct listeF listeF;
typedef struct filed filed;
struct listeF
{
    int val;
    listeF *adr;
};
struct filed
{
   listeF *tete;
   listeF *queue;
};

void creer_file(file *F);
int file_vide(file F);
int file_pleine(file F);
void enfiler(file *F,int x);
void defiler(file *F,int *x);
void affich_file(filed f);
/*---------------------------------------------DYNAMIQUE---------------------------------------------------------*/
void allouer(listeF **l);

int valeur(listeF *p);

listeF *suivant(listeF *p);

void aff_adr(listeF *p,listeF *q);
void aff_val(listeF *p,int valeur);
void creer_filed(filed *f);
int filed_vide(filed f);
void enfilerd(filed *f,int x);
void defilerd(filed *f,int *x);


#endif // FIFO_H_INCLUDED
