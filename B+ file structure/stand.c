#include "stand.h"

/////////////////// test ///////////////////////////////////

void Init_pile(Pile *p)
{
   p->sommet = -1;
}

//////////////////////////////////////////////////////////////
// Empiler le num de bloc (i) et son contenu (n)

void Empiler(Pile *p, int i, node n)
{
    p->sommet++;
   p->adr[(p->sommet)] = i;
   p->Noeud[p->sommet] = n;
}


// Depiler le num de bloc dans i et son contenu dans n

void Depiler(Pile *p, int *i, node *n)
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
}
///////////////////////////////////////////////////////////////////////////
int rech_bplstree(bplustree *btt, int vl, int *i, int *j, node *buf)
{
   *i = btt->entt.root;
   *j = -1;
   Init_pile (&(btt->pila) );
   int trouv = 0;
   while (*i != -1 ) {
     lirebloc_bplstree(btt, buf, *i);
     trouv = rech_node(vl, j, buf);
      	Empiler( &(btt->pila), *i, *buf );
      	if (!trouv) {
	*i = buf->fils[*j];
     }else *i= buf->fils[*j+1];

   }
   if (btt->pila.sommet >= 0)
	  {Depiler( &(btt->pila), i, buf );}
   return trouv;
}

////////////////////////////////////////////////////////////////////////
void ins_bplstree (bplustree *bst,int val)
{
    node BUFFER;
    BUFFER.nb=0;
    int which_leaf=0,pos_in_leaf=0;
    if (!rech_bplstree(bst,val,&which_leaf,&pos_in_leaf,&BUFFER))
    {
        if (which_leaf==-1)
        {
            bst->entt.root = allocbloc_bplstree(bst);	// nouvelle racine
	        ins_node(val, -1, &BUFFER);
	        BUFFER.suiv=-1;
            BUFFER.fils[0] =-1;
            ecrirbloc_bplstree(bst, &BUFFER, bst->entt.root);
        }
        else {
        int continu = 1, fd = -1;
        while (continu) 	// Boucle Principale...
	   // Si le bloc n'est pas plein ...
	   if (BUFFER.nb < maxnode) {
	      ins_node(val, fd, &BUFFER);	// inserer dans le bloc
	      ecrirbloc_bplstree(bst,&BUFFER,which_leaf);// et
	      continu = 0;	// sortir de la boucle
	   }
	   else {
	   // Sinon : le bloc est plein ...
	   	// Eclatement du noeud courant
              int k = 0; int temp=0,son=0;
              son=fd;
	      temp=BUFFER.suiv;
	   fd = allocbloc_bplstree(bst); // un nouveau noeud pour l'eclatement
	      BUFFER.nb = (maxnode+1)/2;
	      k=(maxnode+1)/2;
	      if ((BUFFER.fils[0]==-1))BUFFER.suiv=fd;
	      else BUFFER.suiv=-1;
	      ecrirbloc_bplstree(bst, &BUFFER, which_leaf);
	      	// 2e moitie dans un nouveau bloc ...
	      	int sauv=0;
	      	sauv=BUFFER.donn[k];

  	     if ((BUFFER.fils[0]==-1)){
	      while (k < (maxnode)) {
		BUFFER.donn[k-((maxnode+1)/2)] =BUFFER.donn[k];
		BUFFER.fils[k-((maxnode-1)/2)] = -1;
		k++;
              }
        BUFFER.donn[k-((maxnode+1)/2)] =val;
		BUFFER.fils[k-((maxnode-1)/2)] = -1;
	      BUFFER.nb = k - ((maxnode-1)/2) ;
	      BUFFER.suiv=temp;
	      ecrirbloc_bplstree(bst, &BUFFER, fd);
	      }
	      else
          {
              k++;
	      while (k < (maxnode)) {
		BUFFER.donn[k-((maxnode+1)/2)-1] =BUFFER.donn[k];
		BUFFER.fils[k-((maxnode+1)/2)-1] = BUFFER.donn[k];
		k++;
              }
              BUFFER.fils[k-((maxnode+1)/2)-1] = BUFFER.donn[k];
	      BUFFER.nb = k - ((maxnode+1)/2) - 1;
	      ins_node(val,son,&BUFFER);
	      ecrirbloc_bplstree(bst, &BUFFER, fd);
          }

     	  	 // le separateur dans le pere ...
	      val = sauv;
	      if (bst->pila.sommet >= 0) {
		// si le pere existe,le depiler
		  Depiler( &(bst->pila), &which_leaf,&BUFFER );
   	      }
	      else  {
		// si le pere n'existe pas : donc nouvelle racine
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
    fwrite(&buf,size_bloc,1,f);
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
        printf("fuck!!!");
        break;
    }

}
///////////////////////////////////////////////////
void ecrir_header (FILE* f,header entt)
{
    fseek(f,0,SEEK_SET);
    fwrite(&entt,size_entete,1,f);
}
//////////////////////////////////////////////////
void lirdir (FILE* f,int i,buff* buf)
{
    fseek(f,size_entete+(i-1)*size_bloc,0);
    fread(buf,size_bloc,1,f);
}
///////////////////////////////////////////////////////////
void init_file (char nam[],FILE* f,buff buf)
{
    f=fopen(nam,"wb+");
    int i=0,j=0,val=1,nbbloc=0;
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
    printf(" entrer le nombre de valeur a inserer : ");
    scanf("%d",&nbvl);
    for (j=0;j<nbvl;j++)
    {
        if (i<maxnbbuf)
        {
            buf.donne[i]=j+1;
            i++;
        }

        if (j!=nbvl-1){buf.suiv=j+1;}
        else  {buf.suiv=-1;}
        if ((i==maxnbbuf)||(j==nbvl-1)){i=0; nbbloc++; ecrirdir(f,nbbloc,buf);}
    }
    aff_entete(1,1,&Header);
    aff_entete(2,nbbloc,&Header);
    aff_entete(3,nbbloc,&Header);
    ecrir_header(f,Header);
    fclose(f);
}
//////////////////////////////////////////////////////////////////////////////////////////////
void init_bplstree (bplustree* bst,FILE* f,buff buf,header entt)
{
    int bcl=0,i=0,cpt=0;
    rewind(f);
    for(bcl=1;bcl<=entt.nb_bloc;bcl++)
    {
        lirdir(f,bcl,&buf);
        i=0;
        while ((i<maxnbbuf) && (cpt!=nbvl))
        {
            ins_bplstree(bst,buf.donne[i]);
            i++;cpt++;
        }

    }

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
    }
    while (temp!=-1)
    {
        for(i=0;i<buf.nb;i++)
        {
            printf(" %d ",buf.donn[i]);
        }
        printf("\n");
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
	Inordre_bplstree(bt, localBuf.fils[j+1], avec_affichage);
      }
   }
}

