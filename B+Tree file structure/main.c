#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conio2.h"
#include <time.h>

#define maxnbbuf 254
#define maxnode 126
#define nbcle 4
//#define nbofbloc 392157 //392157

#define bool char
#define false 0
#define true 1
#define MAX_pile 10
#define chang 10
#define MAX_K 127


 int nbofbloc=0;
 int nb_acc=0,nb_node=0,nb_leaf=1,sizetree=0,nb_split=0;
 float charg=0;

typedef int Tval;
typedef struct BlocE{
    int Root;//pointeur vers la racine
    int Nb_Node;//nombre de noeuds de l'arbre
    int Height;//la profondeur de l'arbre
    int Nb_Leaf;//le nombre de feuille
}TEntete;
typedef struct bptree{
TEntete tentete;
}BpTree;
typedef struct Node {

int nb; //le Nombre de valeurs dans le noeuds
int key[MAX_K];//tableau des valeurs
int child[MAX_K+1];//tableau des fils

} Tnode;
typedef struct tbloc
{
    int donne[maxnbbuf];
    int nb;
    int suiv;
}buff;

typedef struct entete
{
    int head;
    int tail;
    int nb_bloc;
} header;
typedef struct pile2
{
    int sommet;
    Tnode Noeud [MAX_pile];
    int   indice [MAX_pile];
}Pile2;
header Header;
buff Buff;
Tnode buft,buft2,buft3,pere;

char *nom;
int NbA           =  0             ;//Nombre d'accés mémoire
long BTF          =  0             ;//Begin of Tree File
long EDF          =  0             ;//End of Data File
int size_entete   =  sizeof(header);
int size_bloc     =  sizeof(buff)  ;
int size_tentete  =  sizeof(TEntete);
int size_Tnode    =  sizeof(Tnode);
int I             =  0;// l'adresse du nouveau noeud crée
int ipere         = -1;
int boolean       =  0;//Un booleen
int N             = MAX_K  +1         ;
Pile2 *P1,*P2;

///*  fin variable global  *///

///*  variable global   *///

typedef struct entete header;
typedef struct tbloc buff;
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
    int prec;
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

int nbvl=0;
/////////////////// test ///////////////////////////////////
///*  Modules concernants la Pile *///
void Creer_pile(Pile2 *p)
{
   p->sommet = -1;
}
// Empiler le num de bloc (i) et son contenu (n)
void Empiler(Pile2 *p, Tnode n,int k)
{
   p->sommet++;
   p->Noeud[p->sommet] = n;
   p->indice[p->sommet]= k;
}
// Depiler le num de bloc dans i et son contenu dans n
void Depiler(Pile2 *p,  Tnode *n,int *k)
{
  // *i = p->adr[p->sommet];
   *n = p->Noeud[p->sommet];
   *k = p->indice[p->sommet];
   p->sommet--;
}
void Empiler2(Pile2 *p1,Pile2 *p2)
{
    int continu=0,k=-1;
    if(p2->sommet != -1)//Pile Non Vide
        continu =   1   ;
    while(continu)
    {
        Depiler(p2,&buft2,&k);
        Empiler(p1,buft2,k);
        if(p2->sommet ==    -1)
            continu =   0   ;
    }


}
////////////////////
/////////////////////
///*  Fin Des modules de la Pile  *///
void Init_pile(Pile *p)
{
   p->sommet = -1;
}

//////////////////////////////////////////////////////////////
// Empiler le num de bloc (i) et son contenu (n)

void Empiler1(Pile *p, int i, node n)
{
    p->sommet++;
   p->adr[(p->sommet)] = i;
   p->Noeud[p->sommet] = n;
}


// Depiler le num de bloc dans i et son contenu dans n

void Depiler1(Pile *p, int *i, node *n)
{
   *i = p->adr[p->sommet];
   *n = p->Noeud[p->sommet];
   p->sommet--;
}

 bplustree *Ouvrir_bplstree(char *nom, char mode) // mode ='A' ou 'N'
{
   bplustree *bt = malloc( sizeof(bplustree) );

   if (mode == 'N') {			// Nouveau fichier
      bt->arb = fopen(nom,"wb+");
      bt->entt.root = -1;			// Racine = -1
      bt->entt.nbnode = 0;			// Nb de noeud = 0
      bt->entt.prof = 0;			// Hauteur = 0
      bt->entt.nb_val = 0;			// Nb de valeurs initiales
      fwrite( &(bt->entt),sizeof(Entete),1, bt->arb );
   }
   else {				// Ancien fichier (mode = 'A')
      bt->arb = fopen(nom,"rb+");
      if (bt->arb != NULL)	// s'il existe recuperer ses caract.
      	fread( &(bt->entt),sizeof(Entete),1, bt->arb );
      else {			// sinon le creer...
       	bt->arb = fopen(nom,"wb+");
      	bt->entt.root = -1;
      	bt->entt.nbnode = 0;
	    bt->entt.nb_val= 0;
	    bt->entt.prof = 0;
      	fwrite( &(bt->entt),sizeof(Entete),1, bt->arb );
      }
   }
   return bt;
}
////////////////////////////////////////////////////////////////////////
void Fermer_bplstree(bplustree *bt)
{
   fseek(bt->arb, 0, 0);				// Sauver l'entete
   fwrite( &(bt->entt), size_entete, 1, bt->arb );	//  et
   fclose(bt->arb);					// Fermer le fichier
   free(bt);
}
////////////////////////////////////////////////////////////////////////
int allocbloc_bplstree ( bplustree* bst)
{
    int i;
    i = bst->entt.nbnode;
    bst->entt.nbnode++;
    return i;
}
/////////////////////////////////////////////////////////////////////////
void ecrirbloc_bplstree (bplustree* bt,node* buf,int i)
{
    fseek(bt->arb,tail_entt+(i)*tail_node,SEEK_SET);
    fwrite(buf,tail_node,1,bt->arb);
    nb_acc++;
}
/////////////////////////////////////////////////////////////////////////

int rech_node( int v, int *i, const node *n )
{
   int bi = 0, bs = n->nb-1, trouv = 0;
   while ( !trouv && bi <= bs )  {
	*i = (bi +bs) / 2;
	if ( v < n->donn[*i] )
		bs = *i - 1;
	else
	   if ( v >= n->donn[*i] )
		{bi = *i + 1;
		if (v==n->donn[*i])trouv = 1;}
   }
   if ( !trouv )
	*i = bi;

   return trouv;

}
///////////////////////////////////////////////////////////////////////////
void ins_node (int valeur,int fd,node* n)
{
    if (n->nb<maxnode)
    {
        int i=0,j;
       // while ((i<n->nb)&&(n->donn[i]<valeur)){i++;}
       rech_node(valeur,&i,n);
        for (j=n->nb;j>i;j--)
        {
            n->donn[j]=n->donn[j-1];
            n->fils[j]=n->fils[j-1];
        }
        n->donn[j]=valeur;
        n->fils[j+1]=fd;
        n->nb++;
    }
}
//////////////////////////////////////////////////////////
void lirebloc_bplstree (bplustree* tree,node* buf,int i)
{
    fseek(tree->arb, tail_entt + (i)*tail_node, SEEK_SET);
    fread(buf, tail_node, 1, tree->arb);
    nb_acc++;
}
///////////////////////////////////////////////////////////////////////////
int rech_bplstree(bplustree *btt, int vl, int *i, int *j, node *buf)
{
   // printf("la merdaaaaa!");
   *i = btt->entt.root;
   *j = -1;
   Init_pile (&(btt->pila) );
   int trouv = 0;
   while (*i != -1 ) {
     lirebloc_bplstree(btt, buf, *i);
     //printf("here1\n");
     trouv = rech_node(vl, j, buf);
     //printf("trouve : %d %d \n",trouv,*j);
      	Empiler1( &(btt->pila), *i, *buf );
      	if (!trouv) {
	*i = buf->fils[*j];
	//printf(" %d ",*i);
	//getch();
     }else *i= buf->fils[*j+1];

   }
   if (btt->pila.sommet >= 0)
	  {Depiler1( &(btt->pila), i, buf );}
   	  //printf("hahahahahahahahaahahah\n");

   return trouv;
}
/////////////////////////////////////////////////////////////////////////
/*void init_buffer (node* n)
{
    int i=0;
    for (i=0;i<maxnbbuf;i++)
    {
        n->donn[i]=0;
        n->fils[i]=-1;
    }
    n->fils[i]=-1;
    n->nb=0;
    n->suiv=-1;

}*/
////////////////////////////////////////////////////////////////////////
void ins_bplstree (bplustree *bst,int val)
{
    node BUFFER;
    //init_buffer(&BUFFER);
    BUFFER.nb=0;
    int which_leaf=0,pos_in_leaf=0;
    if (!rech_bplstree(bst,val,&which_leaf,&pos_in_leaf,&BUFFER))
        //printf("this is recherche   %d \n",which_leaf);
    {
        if (which_leaf==-1)
        {
            bst->entt.root = allocbloc_bplstree(bst);	// nouvelle racine
           // init_buffer(&BUFFER);
	        ins_node(val, -1, &BUFFER);
	        BUFFER.suiv=-1;
            BUFFER.fils[0] =-1;
            ecrirbloc_bplstree(bst, &BUFFER, bst->entt.root);
	        //bst->entt.nb_val++;
	        //lirebloc_bplstree(bst,&BUFFER,bst->entt.root);
	        //printf( " voici le noeud %d   %d\n",BUFFER.donn[0],BUFFER.donn[1]);
	      //printf(" voici les fils %d   %d %d\n",BUFFER.fils[0],BUFFER.fils[1],BUFFER.fils[2]);
	      //getch();

        }
        else {
        int continu = 1, fd = -1;
        while (continu) 	// Boucle Principale...
	   // Si le bloc n'est pas plein ...
	   if (BUFFER.nb < maxnode) {
	      ins_node(val, fd, &BUFFER);	// inserer dans le bloc
	      ecrirbloc_bplstree(bst,&BUFFER,which_leaf);// et
	      //lirebloc_bplstree(bst,&BUFFER,which_leaf);
	      //printf( " voici le noeud %d  %d  %d %d\n",BUFFER.donn[0],BUFFER.donn[1],BUFFER.donn[2],BUFFER.donn[3]);
	      //printf(" voici les fils %d %d %d %d %d\n",BUFFER.fils[0],BUFFER.fils[1],BUFFER.fils[2],BUFFER.fils[3],BUFFER.fils[4]);
	      //getch();
	      continu = 0;	// sortir de la boucle
	   }
	   else {
            nb_split++;
	   // Sinon : le bloc est plein ...
	   	// Eclatement du noeud courant
	     // int c[maxnbbuf+1]; // tableau temporaire de cles
	      //int f[maxnbbuf];  // tableau temporaire de fils

	   	// Construction de la seq ordonnee dans c et f
              int k = 0; int temp=0,son=0;
              //f[dep]=fd;
              son=fd;
	     /* f[0] = BUFFER.fils[0];
	      while (k<maxnbbuf )//&& BUFFER.donn[k] < val)
            {
		c[k] = BUFFER.donn[k];//printf(" donner yeh %d \n",c[k]);
		f[k+1] = BUFFER.fils[k+1];
		k++;
	      }
	      c[k] = val;
	      f[k+1] = fd;
	      //printf("  %d     fd %d ",c[k],fd);
	      k++;*/
	      /*while (k < maxnbbuf+1) {
		c[k] = BUFFER.donn[k-1];
		f[k+1] = BUFFER.fils[k];
		k++;
	      }*/
	      temp=BUFFER.suiv;
	     // printf("temp %d ",temp);

	   fd = allocbloc_bplstree(bst); // un nouveau noeud pour l'eclatement
	   //printf(" new fd %d ",fd);

	      // 1ere moitie de la sequence
	     // init_buffer(&BUFFER);
  	      /*BUFFER.fils[0] = f[0];
	      for (k=0; k <= ((maxnbbuf-1) / 2); k++) {
		BUFFER.donn[k] = c[k];
		BUFFER.fils[k+1] =f[k+1];
              }*/
              //k++;
	      BUFFER.nb = (maxnode+1)/2;
	      k=(maxnode+1)/2;
	      if ((BUFFER.fils[0]==-1)){BUFFER.suiv=fd; }
	      else BUFFER.suiv=-1;
	      ecrirbloc_bplstree(bst, &BUFFER, which_leaf);
	      //lirebloc_bplstree(bst,&BUFFER,which_leaf);
	      //printf( " jabo voici le noeud %d  %d  %d %d\n",BUFFER.donn[0],BUFFER.donn[1],BUFFER.donn[2],BUFFER.donn[3]);
	      //printf(" voici les fils %d %d %d %d %d le suiv est : %d \n",BUFFER.fils[0],BUFFER.fils[1],BUFFER.fils[2],BUFFER.fils[3],BUFFER.fils[4],fd);
	      //getch();


	      	// 2e moitie dans un nouveau bloc ...
	      	int sauv=0;
	      	sauv=BUFFER.donn[k];

  	     if ((BUFFER.fils[0]==-1)){
                nb_leaf++;
                //printf (" nb_leaf %d ",nb_leaf);
                //getch();
                //init_buffer(&BUFFER);
                //BUFFER.fils[0] = -1;
                //printf(" hadi hiya la valeur  %d ",c[k]);
	      while (k < (maxnode)) {
		BUFFER.donn[k-((maxnode+1)/2)] =BUFFER.donn[k];
		BUFFER.fils[k-((maxnode-1)/2)] = -1;
		k++;
              }
        BUFFER.donn[k-((maxnode+1)/2)] =val;
		BUFFER.fils[k-((maxnode-1)/2)] = -1;
		//k++;
	      BUFFER.nb = k - ((maxnode-1)/2) ;
	      BUFFER.suiv=temp;
	      ecrirbloc_bplstree(bst, &BUFFER, fd);
	      //lirebloc_bplstree(bst,&BUFFER,fd);
	      //printf( " jabo voici le noeud %d  %d  %d %d\n",BUFFER.donn[0],BUFFER.donn[1],BUFFER.donn[2],BUFFER.donn[3]);
	      //printf(" voici les fils %d %d %d %d %d le suiv est : %d \n",BUFFER.fils[0],BUFFER.fils[1],BUFFER.fils[2],BUFFER.fils[3],BUFFER.fils[4],fd);
	      //getch();
	      }
	      else
          {
             // init_buffer(&BUFFER);
              k++;
             // BUFFER.fils[0] = f[k];
	      while (k < (maxnode)) {
		BUFFER.donn[k-((maxnode+1)/2)-1] =BUFFER.donn[k];
		BUFFER.fils[k-((maxnode+1)/2)-1] = BUFFER.donn[k];
		k++;
              }
              BUFFER.fils[k-((maxnode+1)/2)-1] = BUFFER.donn[k];
	      BUFFER.nb = k - ((maxnode+1)/2) - 1;
	      ins_node(val,son,&BUFFER);
//BUFFER.suiv=temp;
	      ecrirbloc_bplstree(bst, &BUFFER, fd);
	      //lirebloc_bplstree(bst,&BUFFER,fd);
	      //printf( "  cas de merde  jabo voici le noeud %d  %d  %d %d \n",BUFFER.donn[0],BUFFER.donn[1],BUFFER.donn[2],BUFFER.donn[3]);
	      //printf(" voici les fils %d %d %d %d %d  \n",BUFFER.fils[0],BUFFER.fils[1],BUFFER.fils[2],BUFFER.fils[3],BUFFER.fils[4]);
	      //getch();

          }

     	  	 // le separateur dans le pere ...
	      val = sauv;
	      if (bst->pila.sommet >= 0) {
		// si le pere existe,le depiler
		  Depiler1( &(bst->pila), &which_leaf,&BUFFER );
		  //printf(" la pile fiha ! \n");
   	      }
	      else  {
		// si le pere n'existe pas : donc nouvelle racine
		//init_buffer(&BUFFER);
		  bst->entt.prof++;
		  bst->entt.root = allocbloc_bplstree(bst);
		  BUFFER.donn[0] = val;
		  BUFFER.fils[0] = which_leaf; // le 1er fils est l'ancienne racine
		  BUFFER.fils[1] = fd;// le 2e = noeud de l'eclatement
		  BUFFER.nb = 1;
		  ecrirbloc_bplstree(bst, &BUFFER, bst->entt.root);
		  continu = 0;  // sortir de la boucle
	      }
  	   } //  Fin sinon (le bloc est plein...) et Fin boucle (while (continu)...)
	   bst->entt.nb_val++;
     } // Fin : si arbre non vide.
    }
} // Fin Ins
////////////////////////////////////////////////////////////

void ecrirdir (FILE* f,int i , buff buf)
{
    fseek(f,(i-1)*size_bloc+size_entete,SEEK_SET);
    fwrite(&buf,size_bloc,1,f);NbA++;
}

//////////////////////////////////////////////////////////
void aff_entete (int k ,int val,header* entt)
{
    switch(k)
    {
    case 1 :
        (*entt).head=val;
        break;
    case 2 :
        (*entt).tail=val;
        break;
    case 3 :
        (*entt).nb_bloc=val;
        break;
    default :
        break;
    }

}
///////////////////////////////////////////////////
void ecrir_header (FILE* f,header entt)
{
    fseek(f,0,SEEK_SET);
    fwrite(&entt,size_entete,1,f);NbA++;
}
//////////////////////////////////////////////////
void lirdir (FILE* f,int i,buff* buf)
{
    fseek(f,size_entete+(i-1)*size_bloc,0);
    fread(buf,size_bloc,1,f);NbA++;
}
///////////////////////////////////////////////////////////
void init_file (char nam[],FILE* f,buff buf)
{
    f=fopen(nam,"wb+");
    int i=0,j=0,nbbloc=0,val=1 ;
    for (j=1;j<=nbofbloc;j++)
    {
        for(i=0;i<maxnbbuf;i++)
        {
            buf.donne[i]=val;
            val++;//j+i+nbbloc;
            printf("  %d wtf donner %d \n",i,buf.donne[i]);
        }
        getch();
        if (j!=nbofbloc){buf.suiv=j+1;}
        else  buf.suiv=-1;
        nbbloc=buf.donne[i-1];
        ecrirdir(f,j,buf);
        //lirdir(f,j,&buf);
        //printf("3      donner1 = %d  donner2 = %d   donner3 = %d donner4 = %d  suiv = %d\n",buf.donne[0],buf.donne[1],buf.donne[2],buf.donne[3],buf.suiv);
        //getch();
    }
    aff_entete(1,1,&Header);
    aff_entete(2,nbofbloc,&Header);
    aff_entete(3,nbofbloc,&Header);
    ecrir_header(f,Header);
    fclose(f);
}

////////////////////////////////////////////////////////////
void init_file2 (char nam[],FILE* f,buff buf)
{
    f=fopen(nam,"wb+");
    int i=0,j=0,nbbloc=0;
   // for (j=1;j<=nbofbloc;j++)
    //{
    printf(" entrer le nombre de valeur a inserer : ");
        scanf("%d",&nbvl);

    while(nbvl<=0)
    {

      printf(" entrer une valeur positive ! \n");
      getch();
    printf(" entrer le nombre de valeur a inserer : ");
        scanf("%d",&nbvl);

    }
     for (j=0;j<nbvl;j++)
    {
        if (i<maxnbbuf)
        {
            buf.donne[i]=j+1;
            //printf("  %d wtf donner %d \n",i,buf.donne[i]);
            i++;
        }
        //getch();

        if (j!=nbvl-1){buf.suiv=j+1;}
        else  {buf.suiv=-1;}
        if ((i==maxnbbuf)||(j==nbvl-1)){buf.nb=i;i=0; nbbloc++;  ecrirdir(f,nbbloc,buf);}

        //nbb=buf.donne[i-1];

    }

    EDF=ftell(f);
    BTF=EDF+1;
    I=nbbloc;
    nbofbloc=nbbloc;

        //lirdir(f,j,&buf);
        //printf("3      donner1 = %d  donner2 = %d   donner3 = %d donner4 = %d  suiv = %d\n",buf.donne[0],buf.donne[1],buf.donne[2],buf.donne[3],buf.suiv);
        //getch();
    aff_entete(1,1,&Header);
    aff_entete(2,nbbloc,&Header);
    aff_entete(3,nbbloc,&Header);
    ecrir_header(f,Header);
    NbA=0;
    fclose(f);
}
//////////////////////////////////////////////////////////////////////////////////////////////
void init_bplstree (bplustree* bst,FILE* f,buff buf,header entt)
{
    int bcl=0,i=0,cpt=0;//node test;
    FILE* ecr=NULL;
    float deb=0,fin=0,duration=0;
    ecr=fopen(" donner.txt","w+");
    rewind(f);
    deb=clock();
    fprintf(ecr," valeurs;temps;prof;accee; noeud ajouter;feuille;taille;eclatements\n");
    for(bcl=1;bcl<=entt.nb_bloc;bcl++)
    {
        lirdir(f,bcl,&buf);
        i=0;
        while ((i<maxnbbuf) && (cpt!=nbvl))
        {
            //printf(" houla %d \n",buf.donne[i]);
            ins_bplstree(bst,buf.donne[i]);
            i++;cpt++;
            if (cpt%999998==0){
                    fin=clock();
                    duration= (double)(fin-deb)/CLOCKS_PER_SEC;

                 fprintf (ecr," %d;",cpt);
                fprintf( ecr," %f;",duration);
                          fprintf(ecr," %d;",bst->entt.prof);
                          fprintf ( ecr,"  %d;",nb_acc);
                          nb_node=(bst->entt.nbnode)-nb_leaf;
                          fprintf (ecr," %d;",nb_node);
                          fprintf (ecr," %d;",nb_leaf);
                          sizetree=bst->entt.nbnode;
                          fprintf (ecr," %d;",sizetree);
                          fprintf (ecr,"%d;\n",nb_split);
            }

            //printf( " cpt %d ",cpt);
            //lirebloc_bplstree(bst,&test,bst->entt.root);
            //printf("  %d   c'est notre racin %d %d %d %d \n",bst->entt.root,test.donn[0],test.donn[1],test.donn[2],test.donn[3]);
            //printf(" c'est les fils de notre racine %d %d %d %d %d\n",test.fils[0],test.fils[1],test.fils[2],test.fils[3],test.fils[4]);
            //getch();
            //printf("wtf is this \n");
        }
        //printf( " bloc %d \n",bcl);

    }
    fclose(ecr);
    //fclose(bst->arb);

}
//////////////////////////////////////////////////////////////////////
void affich_arbre (bplustree* bst)
{
    node buf;
    int temp=0,stop=0,i=0;
    temp=bst->entt.root;
    if (temp!=-1)
    {
     while (!stop)
    {
        lirebloc_bplstree(bst,&buf,temp);
        if (buf.fils[0]==-1){stop=1; }
        else temp=buf.fils[0];
            //lirebloc_bplstree(bst,&buf,temp);
    }
    while (temp!=-1)
    {
        for(i=0;i<buf.nb;i++)
        {
            printf(" %d ",buf.donn[i]);
        }
        printf("\n");
        //printf("  arbre :%d:   donner1 : %d  donner2 : %d donner3 : %d  donner4: %d  \n ",buf.suiv,buf.donn[0],buf.donn[1],buf.donn[2],buf.donn[3]);
        getch();
        temp=buf.suiv;
        if (temp!=-1) lirebloc_bplstree(bst,&buf,temp);
    }

    }

}
//////////////////////////////////////////////////////////////////////
void Inordre_bplstree(bplustree *bt, int i, int avec_affichage )
{
   node localBuf;
   int j;
   if (i != -1) {
      lirebloc_bplstree(bt, &localBuf, i);
      Inordre_bplstree(bt, localBuf.fils[0], avec_affichage);
      for (j=0; j<localBuf.nb; j++) {
	if ( avec_affichage )
      	   printf("%d ", localBuf.donn[j]);

	//if (val_prec > localBuf.cle[j])
		//Erreur = 1;		// pour vérification de l'ordre
	//nbvaleurs++;			// pour vérification du nombre total de valeurs insérées
	//val_prec = localBuf.cle[j];
	Inordre_bplstree(bt, localBuf.fils[j+1], avec_affichage);
      }
   }
}

//////////////////////////////////////////////////////////////////////
BpTree* Open_BpTree(FILE *f,char mode){
BpTree *bpt = malloc(sizeof(BpTree)) ;
if (mode == 'N')
{

  (bpt->tentete.Height)  = 0                 ;
  (bpt->tentete.Root)    = -1                ;
  (bpt->tentete.Nb_Node) = 0                 ;
  (bpt->tentete.Nb_Leaf) = 0                 ;
  fseek(f,BTF,SEEK_SET);
  fwrite(& (bpt->tentete) , sizeof(TEntete) , 1 , f );//Ecriture de l'entete dans le fichier
}
 return bpt;
}
//////////////////////////////////////////////////////////////////////
void Close_BpTree(FILE *f,BpTree *bpt)
{
    fseek(f,BTF,0);
    fwrite(&(bpt->tentete),size_tentete,1,f);//sauvegarder l'entete

}
void Read_Node  ( FILE *f, int i , Tnode *buft)
{
    fseek(f,(i-1)*size_Tnode+size_tentete+size_entete,0);
    fread(buft,size_Tnode,1,f);NbA++;
}
void Write_Node ( FILE *f, int i , Tnode *buft)
{
    fseek(f,(i-1)*size_Tnode+size_tentete+size_entete,0);
    fwrite(buft,size_Tnode,1,f);NbA++;
}
int Alloc_Node(BpTree *bpt)
{
 (bpt->tentete.Nb_Node)++;I++;
 return (I);
}
void Split(FILE *f,BpTree *bpt,int Val,int fd,int k,int *i1,int *m)
{
    nb_split++;
    int Vmax    =   Val ,
        fdmax   =   fd  ,
        h       =   0   ,
        l       =   0   ;
    pere.nb     =   N / 2;
    Write_Node(f,k,&pere)  ;
    *m           =   pere.key[N / 2];
    for( h   =   pere.nb+1   ;h<N -1;h++ )//<=
    {
        pere.key[l]     =   pere.key[h]     ;
        pere.child[l]   =   pere.child[h]   ;
        l++;
    }
    pere.child[l]   =   pere.child[N];
    pere.key[l]     =   Vmax             ;
    pere.child[l+1] =   fdmax            ;
    pere.nb         =   l+1              ;
    *i1             =   Alloc_Node(bpt)  ;

    if(pere.child[0]<=nbofbloc)   ipere   =   *i1   ;//pere.child[0]est une feuille
    else{
        Empiler(P2,pere,*i1);

    }
    Write_Node(f,*i1,&pere)              ;

}
void InsertI (FILE *f,BpTree *bpt, int Val,int sauv)
{

    int k       =   ipere   ,
        continu =   1       ,
        fg      =  -1       ,
        fd      =   sauv    ,
        i1      =   0       ,
        m       =   0       ;

    while(continu)
    {
            if(k    ==  -1  )//Nouvelle Racine
            {
                k                   =   Alloc_Node(bpt) ;
                bpt->tentete.Root   =   k               ;
                buft2.key[0]        =   Val             ;
                buft2.child[0]      =   fg              ;
                buft2.child[1]      =   fd              ;
                buft2.nb            =   1               ;
                continu             =   0               ;
                Write_Node(f,k,&buft2)                ;
                Empiler(P1,buft2,k);
                Empiler2(P1,P2);

            }
            else
            {
                if( pere.nb <   MAX_K   )
                {
                    pere.key[pere.nb]       =   Val ;
                    pere.child[pere.nb+1]   =   fd  ;
                    (pere.nb)++;
                    continu                 =   0   ;
                    Write_Node(f,k,&pere)          ;
                   Empiler(P1,pere,k)             ;
                    Empiler2(P1,P2)                ;

                }
                else
                {
                    Split(f,bpt,Val,fd,k,&i1,&m);

                    if((P1->sommet) != -1)//!Pilevide
                    {   Write_Node(f,ipere,&pere);

                        Depiler(P1,&pere,&k);

                        Val =   m   ;
                        fd  =   i1  ;

                    }
                    else
                    {
                        fg  =   k   ;
                        fd  =   i1  ;
                        k   =   -1  ;
                        Val =   m   ;

                    }
                }
            }
    }

}
void Insert_buft(FILE *f,BpTree *bpt,int Val,int sauv)
{
    if( boolean )
    {
        pere.child[0]       =   sauv    ;
        boolean             =   0       ;
        bpt->tentete.Root   =   ipere   ;//////////////////////
    }
    else
    {
        if( pere.nb < MAX_K ) //le pere n'est pas plein
        {
            pere.key[pere.nb]       =   Val  ;
            pere.child[pere.nb+1]   =   sauv ;
            pere.nb++;
        }
        else//le pere est plein
        {
            InsertI(f,bpt,Val,sauv);//system("pause");
            Read_Node(f,ipere,&pere);
        }
    }
}
void Load_Leaf(BpTree *bpt,FILE *f,int i)
{   lirdir(f,i,&Buff);//lecture du bloc i à partir du fichier du donnée
    if( I   ==  nbofbloc)
    {
        I            =   Alloc_Node(bpt);
        ipere        =   I              ;
        pere.nb      =   0              ;
        boolean      =   1              ;
        (bpt->tentete.Root)   =   I     ;
    }
      Insert_buft(f,bpt,Buff.donne[0],i);

}
BpTree *Bulk_Loading(FILE *f)
{   BpTree *bpt;
    fseek(f,0,0);
    fread(&Header,size_entete,1,f);//Lecture de l'entete du fichier
    bpt=Open_BpTree(f,'N');
    int i           =   1;
    while(i <= Header.nb_bloc){
        Load_Leaf(bpt,f,i);
        (bpt->tentete.Nb_Leaf)++;
        i++;
    }
    Write_Node(f,ipere,&pere);
    (bpt->tentete.Nb_Leaf) = Header.nb_bloc;
    fseek(f,BTF,0);
    fwrite(&(bpt->tentete),size_tentete,1,f);//ecriture de l'entete de l'arbre
    return bpt;

}
void Get_Height(FILE *f,BpTree *bpt)
{  int i=1;
    Read_Node(f,bpt->tentete.Root,&buft2);
    while(buft2.child[0]>=nbofbloc)
    {
      Read_Node(f,buft2.child[0],&buft2);
    i++;
    }
    bpt->tentete.Height=i;
}

void Display_Node(FILE *f,BpTree *bpt,int i)
{
    Read_Node(f,i,&buft);
    int j=0;
    printf("\n               Affichage du Noeud %d  \n",i);
    for(j=0;j<buft.nb;j++)
    {
        printf("@ %d | %d |",buft.child[j],buft.key[j]);
    }
    printf("@ %d",buft.child[j]);
}
//////////////////////////////////////////////////////////////////////
void ins_node_rech (int valeur,int fd,node* n)
{
    if (n->nb<maxnode)
    {
        n->donn[n->nb]=valeur;
        n->fils[n->nb+1]=fd;
        n->nb++;
    }
}
//////////////////////////////////////////////////////////
void ins_bplstree_rech (bplustree *bst,int val,node* BUFFER)
{
    int which_leaf=0,pos_in_leaf=0,nb_pl=0;
        if (bst->pila.sommet==-1)
        {
            bst->entt.root = allocbloc_bplstree(bst);	// nouvelle racine
           BUFFER->nb=0;
	        ins_node_rech(val, -1, BUFFER);
	        BUFFER->suiv=-1;
	        BUFFER->prec=-1;
            BUFFER->fils[0] =-1;
            Empiler1(&(bst->pila),bst->entt.root,*BUFFER);
        }
        else {
        int continu = 1, fd = -1;
        (*BUFFER)=bst->pila.Noeud[0];
	   which_leaf=bst->pila.adr[0];
	   pos_in_leaf=0;
        while (continu) 	// Boucle Principale...
	   // Si le bloc n'est pas plein ...

	   if (BUFFER->nb < maxnode) {
	      ins_node_rech(val, fd, BUFFER);	// inserer dans le bloc
	      bst->pila.Noeud[pos_in_leaf]=(*BUFFER);
	      continu = 0;	// sortir de la boucle
	   }
	   else {
	   // Sinon : le bloc est plein ...
	   	// Eclatement du noeud courant
	   	nb_split++;
              int k = 0; int temp=0,son=0;
              son=fd;
	      temp=BUFFER->suiv;
	   fd = allocbloc_bplstree(bst); // un nouveau noeud pour l'eclatement
	      // 1ere moitie de la sequence

	      BUFFER->nb = (maxnode+1)/2;
	      k=(maxnode+1)/2;
	      if ((BUFFER->fils[0]==-1)){BUFFER->suiv=fd; }
	      else BUFFER->suiv=-1;
	      ecrirbloc_bplstree(bst, BUFFER, which_leaf);

	      	// 2e moitie dans un nouveau bloc ...
	      	int sauv=0;
	      	sauv=BUFFER->donn[k];

  	     if ((BUFFER->fils[0]==-1)){
                nb_leaf++;
	      while (k < (maxnode)) {
		BUFFER->donn[k-((maxnode+1)/2)] =BUFFER->donn[k];
		BUFFER->fils[k-((maxnode-1)/2)] = -1;
		k++;
              }
        BUFFER->donn[k-((maxnode+1)/2)] =val;
		BUFFER->fils[k-((maxnode-1)/2)] = -1;
	      BUFFER->nb = k - ((maxnode-1)/2) ;
	      BUFFER->suiv=temp;
	      bst->pila.Noeud[pos_in_leaf]=(*BUFFER);
	      bst->pila.adr[pos_in_leaf]=fd;
	      }
	      else
          {
              k++;
	      while (k < (maxnode)) {
		BUFFER->donn[k-((maxnode+1)/2)-1] =BUFFER->donn[k];
		BUFFER->fils[k-((maxnode+1)/2)-1] = BUFFER->fils[k];
		k++;
              }
              BUFFER->fils[k-((maxnode+1)/2)-1] = BUFFER->fils[k];
	      BUFFER->nb = k - ((maxnode+1)/2) - 1;
	      ins_node_rech(val,son,BUFFER);
           bst->pila.Noeud[pos_in_leaf]=(*BUFFER);
           bst->pila.adr[pos_in_leaf]=fd;
          }

     	  	 // le separateur dans le pere ...
	      val = sauv;
	      if (nb_pl < bst->pila.sommet) {
		  nb_pl++;
		  pos_in_leaf++;
		  which_leaf=bst->pila.adr[pos_in_leaf];
        *BUFFER=bst->pila.Noeud[pos_in_leaf];
   	      }
	      else  {
		// si le pere n'existe pas : donc nouvelle racine
		  bst->entt.prof++;
		  bst->entt.root = allocbloc_bplstree(bst);
		  BUFFER->donn[0] = val;
		  BUFFER->fils[0] = which_leaf; // le 1er fils est l'ancienne racine
		  BUFFER->fils[1] = fd;// le 2e = noeud de l'eclatement
		  BUFFER->nb = 1;
		  Empiler1(&(bst->pila),bst->entt.root,*BUFFER);
		  continu = 0;  // sortir de la boucle
	      }
  	   } //  Fin sinon (le bloc est plein...) et Fin boucle (while (continu)...)
	   bst->entt.nb_val++;
     } // Fin : si arbre non vide.

} // Fin Ins
////////////////////////////////////////////////////////////
void init_bplstree_rech (bplustree* bst,FILE* f,buff buf,header entt)
{
    int bcl=0,i=0,cpt=0;
    FILE* ecr=NULL;
    ecr=fopen(" donner1.txt","w+");
    node BUFFER;
    BUFFER.nb=0;
    float deb=0,fin=0,duration=0;
    rewind(f);
    Init_pile(&(bst->pila));
    deb=clock();
     fprintf(ecr," valeurs;temps;prof;accee; noeud ajouter;feuille;taille;eclatements\n");
    for(bcl=1;bcl<=entt.nb_bloc;bcl++)
    {
        lirdir(f,bcl,&buf);
        i=0;
         while ((i<maxnbbuf) && (cpt!=nbvl))
        {
            //printf(" houla %d \n",buf.donne[i]);
            ins_bplstree_rech(bst,buf.donne[i],&BUFFER);
            i++;cpt++;
            if (cpt%999998==0){
                    fin=clock();
                    duration= (double)(fin-deb)/CLOCKS_PER_SEC;
                    fprintf(ecr," %d;",cpt);
                fprintf( ecr," %f;",duration);
                //printf(" %f ",duration);
                          fprintf(ecr," %d;",bst->entt.prof);
                          fprintf ( ecr,"  %d;",nb_acc);
                          nb_node=(bst->entt.nbnode)-nb_leaf;
                          fprintf (ecr," %d;",nb_node);
                          fprintf (ecr,"  %d;",nb_leaf);
                          sizetree=bst->entt.nbnode;
                          fprintf (ecr," %d;",sizetree);
                          fprintf (ecr," %d;\n",nb_split);
            }

        }
        //printf( " bloc %d \n",bcl);

    }
    //printf("gjdhfgkfghdhh");
    while ((bst->pila.sommet)>-1)
    {
        ecrirbloc_bplstree(bst,&(bst->pila.Noeud[bst->pila.sommet]),bst->pila.adr[bst->pila.sommet]);
        bst->pila.sommet--;
    }
    fclose(ecr);
    //fclose(bst->arb);

}
//////////////////////////////////////////////////////////////////////
void Get_Taux(FILE* f,BpTree *bpt)
{
    int i=0;charg=0;
    for (i=nbofbloc+1;i<=I;i++)
    {
        Read_Node(f,i,&buft2);
        charg+=(float) (buft2.nb)/MAX_K;
    }
    charg/=(float)(I-nbofbloc);
}
//////////////////////////////////////////////////////////////////////


int main()
{
                       time_t start, end;
                    FILE*   f =   NULL    ;
                    double t1 =   0       ;
                    P1  =   malloc(sizeof(Pile2));
                    P1->sommet  =   -1      ;
                    P2  =   malloc(sizeof(Pile2));
                    P2->sommet  =   -1      ;
                    BpTree *bpt   = NULL    ;
                 //////////// fin ////////////
                 int choix=0,cnt=0;
                 char contin=' ';
                 char nam[30]="";
                 bplustree* tree;
                 float debut,end1,duration;


                 while (!cnt)
                 {
                     system("cls");
                     printf("\n\n\n");
                     printf( "                                                                  MENU  :    \n");
                 printf( "                             1- cree un fichier lof      \n");
                 printf( "                             2- cree un arbre avec la methode de l'insertion standard 'avec recherche'\n");
                 printf( "                             3- cree un arbre avec la methode de l'insertion standard 'sans recherche'\n");
                 printf( "                             4- cree un arbre avec la methode de l'insertion en vrac 'bulk loading'\n");
                 printf( "                             5- sortir du prgrm \n");
                 printf( " \n\n");
                 printf( " votre choix : ");
                 scanf("%d",&choix);
                 printf("\n");
                 switch (choix)
                 {
                 case 1 :
                    printf(" donner le nom de votre fichier lof : ");
                    scanf("%s",nam);
                    printf("\n");
                    f=fopen(nam,"rb");
                    if (f!=NULL){
                            printf(" ce fichier existe est ce que vous voulez vraiment l'ecraser 'o/n' : ");

                            while ((contin!='o')&&(contin!='n'))
                            {
                              scanf(" %c",&contin);
                              printf("\n");
                              if (contin=='o')
                            {
                                fclose(f);
                                init_file2(nam,f,Buff);
                                f=fopen(nam,"rb+");
                                rewind(f);
                                fread(&Header,size_entete,1,f);
                                 printf(" tete = %d  queue = %d  nb_bloc= %d \n",Header.head,Header.tail,Header.nb_bloc);
                            }
                            else printf(" rien a changer ! \n");
                            }

                            }
                            else
                            {
                                fclose(f);
                                init_file2(nam,f,Buff);
                                f=fopen(nam,"rb+");
                                rewind(f);
                                fread(&Header,size_entete,1,f);
                                 printf(" tete = %d  queue = %d  nb_bloc= %d \n",Header.head,Header.tail,Header.nb_bloc);
                            }
                            printf(" \n appuyer n'importe ou pour continuer!");
                            getch();
                            break;
                 case 2 :
                     printf (" donner le nom du fichier principale : ");
                     scanf ("%s",nam);
                      printf("\n");
                      f=fopen(nam,"rb");
                    if (f!=NULL){

                          tree=Ouvrir_bplstree("filebplstree.bin",'N');
                          debut=clock();
                          init_bplstree(tree,f,Buff,Header);
                          end1=clock();
                          duration= (double)(end1-debut)/CLOCKS_PER_SEC;
                          printf( " le temps necessaire pour cree l'arbre est : %f \n",duration);
                          printf(" la profendeur de l'arbre : %d \n",tree->entt.prof);
                          printf ( " le nombre d'accee memoire est : %d \n",nb_acc);nb_acc=0;
                          nb_node=tree->entt.nbnode-nb_leaf;
                          printf (" le nombre de noeud ajouter : %d \n",nb_node);nb_node=0;
                          printf (" le nombre des feuilles : %d \n",nb_leaf);nb_leaf=0;
                          sizetree=tree->entt.nbnode;
                          printf (" la taille du fichier de l'arbre est : %d MB \n",sizetree);
                          printf (" le nombre des eclatement est : %d",nb_split);nb_split=0;
                          Fermer_bplstree(tree);

                    }else printf(" entrer un nom d'un fichier existant ! ");
                    getch();
                          break;
                 case 3 :
                     printf (" donner le nom du fichier principale : ");
                     scanf ("%s",nam);
                      printf("\n");
                      f=fopen(nam,"rb");
                    if (f!=NULL){
                          tree=Ouvrir_bplstree("filebplstree_r.bin",'N');
                          debut=clock();
                          init_bplstree_rech(tree,f,Buff,Header);
                          end1=clock();
                          duration= (double)(end1-debut)/CLOCKS_PER_SEC;
                          printf( " le temps necessaire pour cree l'arbre est : %f \n",duration);
                          printf(" la profendeur de l'arbre : %d \n",tree->entt.prof);
                          printf ( " le nombre d'accee memoire est : %d \n",nb_acc);nb_acc=0;
                          nb_node=(tree->entt.nbnode)-nb_leaf;
                          printf (" le nombre de noeud ajouter : %d \n",nb_node);nb_node=0;
                          printf (" le nombre des feuilles : %d \n",nb_leaf);nb_leaf=0;
                          sizetree=tree->entt.nbnode;
                          printf (" la taille du fichier de l'arbre est : %d MB \n",sizetree);
                          printf (" le nombre des eclatement est : %d",nb_split);nb_split=0;
                          Fermer_bplstree(tree);
                          //tree=Ouvrir_bplstree("filebplstree_r.bin",'A');
                          //Inordre_bplstree (tree,tree->entt.root,1);
                          //affich_arbre(tree);
                    }else printf (" entrer un nom d'un fichier existant !");
                          getch();
                          break;
                 case 4 :
                     printf (" donner le nom du fichier principale : ");
                     scanf ("%s",nam);
                      printf("\n");
                      f=fopen(nam,"rb");
                    if (f!=NULL){
                            fclose(f);
                         f=fopen(nam,"rb+");
                         rewind(f);
                         start     =   clock()                                     ;
                         bpt       =   Bulk_Loading(f)                             ;
                         end       =   clock()                                     ;
                         t1        = t1 + ((double)(end-start)/CLOCKS_PER_SEC)     ;
                         printf("La duree de la creation de l'arbre = %lf s \n",t1);
                         Get_Height(f,bpt);
                         printf(" Nombre de Noeuds ajoutes = %d  \n Nombre de feuilles = %d \n Height=%d ==> La recherche coute %d acces memoire",bpt->tentete.Nb_Node,bpt->tentete.Nb_Leaf,bpt->tentete.Height,bpt->tentete.Height);
                         printf("\n NbAcces memoire=%d ==> Temps d'un acces memoire=%lf s ==> la recherche d'une donnee coute:%lf s \n",NbA,t1/NbA,t1/NbA*bpt->tentete.Height);
                         Get_Taux(f,bpt);
                         printf("La taille du fichier final %d Mb  Taux =%f ",bpt->tentete.Nb_Leaf+bpt->tentete.Nb_Node,charg);
                         printf (" le nombre des eclatement est : %d ",nb_split);nb_split=0;
                    }else printf(" donner un nom de fichier existant !");
                         getch();


                         break;
                 case 5 :
                    printf( " merci ! \n");
                    cnt=1;
                 default:
                     //choix=10;
                     //getch();
                    break;
                 }


}
return 0;
}

