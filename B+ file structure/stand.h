
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#define maxnbbuf 255
#define maxnode 126
#define nbcle 4
#define chang 10
#define MAX_pile 500000
#define nbofbloc 4 //392157


///*  variable global   *///
struct tbloc
{
    int donne[maxnbbuf];
    int suiv;
};

struct entete
{
    int head;
    int tail;
    int nb_bloc;
} ;
typedef struct entete header;
typedef struct tbloc buff;
int size_entete=sizeof(header);
int size_bloc=sizeof(buff);
header Header;
buff Buff;
///*  fin variable global  *///
typedef struct bloc0
{
    int root;
    int nbnode;
    int nb_val;
    int prof;
}Entete;
int tail_entt=sizeof(Entete);
typedef struct noeud
{
    int nb;
    int donn [maxnode];
    int fils [maxnode+1];
    int suiv;
}node;
int tail_node=sizeof(node);

typedef struct pile
{
    int sommet;
    int adr [MAX_pile];
    node Noeud [MAX_pile];
}Pile;

typedef struct bps_tree
{
    FILE* arb;
    Entete entt;
    Pile pila;
}bplustree;

int nbvl;

void Init_pile(Pile *p);
void Empiler(Pile *p, int i, node n);
void Depiler(Pile *p, int *i, node *n);
bplustree *Ouvrir_bplstree(char *nom, char mode); // mode ='A' ou 'N'
void Fermer_bplstree(bplustree *bt);
int allocbloc_bplstree ( bplustree* bst);
void ecrirbloc_bplstree (bplustree* bt,node* buf,int i);
int rech_node( int v, int *i, const node *n );
void ins_node (int valeur,int fd,node* n);
void lirebloc_bplstree (bplustree* tree,node* buf,int i);
int rech_bplstree(bplustree *btt, int vl, int *i, int *j, node *buf);
void ins_bplstree (bplustree *bst,int val);
void ecrirdir (FILE* f,int i , buff buf);
void aff_entete (int k ,int val,header* entt);
void ecrir_header (FILE* f,header entt);
void lirdir (FILE* f,int i,buff* buf);
void init_file (char nam[],FILE* f,buff buf);
void init_file2 (char nam[],FILE* f,buff buf);
void init_bplstree (bplustree* bst,FILE* f,buff buf,header entt);
void affich_arbre (bplustree* bst);
void Inordre_bplstree(bplustree *bt, int i, int avec_affichage );

