
  /**--------------------------------------------------------**/
  /**       C o n v e r s i o n   Z vers C (Standard)        **/
  /**             Réalisée par Pr D.E ZEGOUR                 **/
  /**             E S I - Alger                              **/
  /**             Copywrite 2014                             **/
  /**--------------------------------------------------------**/

  #include <stdio.h>
  #include <stdlib.h>
  #include <time.h>

  typedef int bool ;

  #define True 1
  #define False 0

  /** Implémentation **\: TABLEAU DE STRUCTURES**/

  /** Structures dynamiques **/

  typedef struct Uii * Pointeur_Uii  ;
  typedef int Type1_Uii ;
  typedef int Type2_Uii ;

  struct Uii
    {
      Type1_Uii Champ1 ;
      Type2_Uii Champ2 ;
    };

  Type1_Uii Struct1_Uii ( Pointeur_Uii S)
    {
       return  S->Champ1 ;
    }

  Type2_Uii Struct2_Uii ( Pointeur_Uii S)
    {
       return  S->Champ2 ;
    }

  void Aff_struct1_Uii ( Pointeur_Uii S, Type1_Uii Val )
    {
       S->Champ1 = Val ;
    }

  void Aff_struct2_Uii ( Pointeur_Uii S, Type2_Uii Val )
    {
       S->Champ2 = Val ;
    }

  void Alloc_struct_Uii( Pointeur_Uii *S)
     {
      *S = (struct Uii *) malloc( sizeof( struct Uii))   ;
     }

  void Liber_struct_Uii( Pointeur_Uii S )
     { free(S); }


  /** Tableaux dynamiques **/
  typedef Pointeur_Uii Typeelem_W12Uii ;
  typedef Typeelem_W12Uii *  Pointeur_W12Uii;

  void Alloc_tab_W12Uii ( Pointeur_W12Uii *T,int m )//Reservation d'un espace memoire de taille m
    { *T = malloc(m * sizeof(struct Uii)); }

  void Liber_tab_W12Uii ( Pointeur_W12Uii T)
    { free(T) ;}

  Typeelem_W12Uii Element_W12Uii ( Pointeur_W12Uii V  , int I1  )
    {
      return *(V + I1-1 );
    }

  void Aff_element_W12Uii ( Pointeur_W12Uii V,  int I1 ,  Typeelem_W12Uii Val )
    {
      *(V + I1-1 ) = Val ;
    }


  /** Implémentation **\: ARBRE BINAIRE DE STRUCTURES**/

  /** Arbres de recherche binaire **/

  typedef Pointeur_Uii Typeelem_AUii   ;
  typedef struct Noeud_AUii * Pointeur_AUii ;

  struct Noeud_AUii
    {
      Typeelem_AUii  Val ;
      Pointeur_AUii Fg ;
      Pointeur_AUii Fd ;
      Pointeur_AUii Pere ;
     } ;

  Typeelem_AUii Info_AUii( Pointeur_AUii P )
    { return P->Val;   }

  Pointeur_AUii Fg_AUii( Pointeur_AUii P)
    { return P->Fg ; }

  Pointeur_AUii Fd_AUii( Pointeur_AUii P)
    { return P->Fd ; }

  Pointeur_AUii Pere_AUii( Pointeur_AUii P)
    { return P->Pere ; }

  void Aff_info_AUii ( Pointeur_AUii P, Typeelem_AUii Val)
    {
       P->Val = Val ;
    }

  void Aff_fg_AUii( Pointeur_AUii P, Pointeur_AUii Q)
    { P->Fg =  Q;  }

  void Aff_fd_AUii( Pointeur_AUii P, Pointeur_AUii Q)
    { P->Fd =  Q ; }

  void Aff_pere_AUii( Pointeur_AUii P, Pointeur_AUii Q)
    { P->Pere =  Q ; }

  void Creernoeud_AUii( Pointeur_AUii *P)
    {
      *P = (struct Noeud_AUii *) malloc( sizeof( struct Noeud_AUii))   ;
      (*P)->Fg = NULL;
      (*P)->Fd = NULL;
      (*P)->Pere = NULL;
    }

  void Liberernoeud_AUii( Pointeur_AUii P)
    { free( P ) ; }


  /** Variables du programme principal **/
  Pointeur_W12Uii T;
  int H;
  int Nbnoeud,nbrotat1=0,nbrotat2=0,nbvisit1=0,nbvisit2=0;
  int N,m,i;
  Pointeur_Uii S;
  Pointeur_AUii A1;
  Pointeur_AUii A2;
  int _Px1;
  int _Px2;
  int _Izw;  /** Variable de contrôle **/

  /** Fonctions standards **/

  int Aleanombre( int N )
    { return ( rand() % N ); }

  int Max (int a, int b)
    {
      if (a > b) return(a);
      else return(b);
    }

  int Exp (int a, int b)
    {
     int i; int Ex ;
     Ex = 1;
     for (i= 1; i<=b; i++)
       Ex = Ex * a  ;
     return (Ex);
    }


  /** Prototypes des fonctions **/

  int  Getnode (Pointeur_AUii *A,int *nbvisit) ;//calcule le nombre de noeuds d'un arbre
  void Inserer (Pointeur_AUii *Racine , int *Val);//insere la valeur val dans l'arbre
  void Creer_arbre (Pointeur_AUii *A , int *Nbnoeud2 , Pointeur_W12Uii *T);//creation d'un arbre
  int  Min1 (int *A , int *B) ;
  int  Max1 (int *A , int *B) ;
  int  Profondeur (Pointeur_AUii *N,int *nbvisit) ;//calcule la profondeur de l'arbre
  Pointeur_AUii Suiv_post (Pointeur_AUii *A,int *nbvisit) ;//retourne le  suivant postordre d'un noeud nil sinon
  Pointeur_AUii First_post_el (Pointeur_AUii *N,int *nbvisit) ;//retourne me premier element postordre
  Pointeur_AUii Rg (Pointeur_AUii *N) ;//Rotation gauche du noeud N et retourne la nouvelle racine du nouveau sous arbre
  Pointeur_AUii Rd (Pointeur_AUii *N) ;//rotation droite du noeud N et retourne la nouvelle racine du nouveau sous arbre
  Pointeur_AUii Equilibrer (Pointeur_AUii *N,int *nbrotat,int *nbvisit) ;
  Pointeur_AUii Equilibrer_arb (Pointeur_AUii *R,int *nbrotat,int *nbvisit) ;//equilibrer l'arbre avec le 2eme algorithme
  bool  Is_avl2 (Pointeur_AUii *N) ;//verifier si c'est l'arbre est un arbre avl
  void Liberer_arb (Pointeur_AUii *R);//Libere l'arbre AVL
  void Liberer_arb2 (Pointeur_AUii *A);//Libere l'arbre du DSW
  void Rebalance (Pointeur_AUii *Racine,int *nbnoeud,int *nbrotat,int *nbvisit);//equilibre l'arbre avec la methode de DSW
  void Creer_lld (Pointeur_AUii *Racine , int *Nbnoeud,int *nbrotat,int *nvisit);//creer une liste droite
  void Vine_to_tree (Pointeur_AUii *A , int *Size,int *nbrotat,int *nbvisit);//transforme la liste en un arbre
  void Compression (Pointeur_AUii *A , int *Nf,int *nbrotat,int *nbvisit);
  int  Msb (int *X) ;//calcule le log2(X)
  bool  Is_avl (Pointeur_AUii *N) ;//verifie si l'arbre est un arbre avl

  /************************************************************/
  /*               Modules 2eme algorithme                    */
  /************************************************************/
  int  Getnode (Pointeur_AUii *A,int *nbvisit)
    {
      /** Variables locales **/
      int  Getnode2 ;
      int Cpt;
      Pointeur_AUii _Px1;
      Pointeur_AUii _Px2;

      /** Corps du module **/
     if( ( *A == NULL )) {
       Getnode2  =  0 ;
       (*nbvisit)++;
       }
     else
       {
       _Px1 =  Fg_AUii(*A ) ;
       _Px2 =  Fd_AUii(*A ) ;
       (*nbvisit)+=2;
       Getnode2  =  1 + Getnode ( &_Px1,nbvisit) + Getnode ( &_Px2,nbvisit) ;

     } ;

     return Getnode2 ;
    }
  void Inserer (Pointeur_AUii *Racine , int *Val)
    {
      /** Variables locales **/
      Pointeur_AUii R;
      Pointeur_AUii Q;
      Pointeur_Uii S;
      Pointeur_Uii S1;
      bool Continu;

      /** Corps du module **/
     Continu  =  True ;
     R  =  *Racine ;
     Alloc_struct_Uii(&S1 ) ;
     Aff_struct1_Uii(S1  , *Val ) ;
     Aff_struct2_Uii(S1  , 0 ) ;
     if( R == NULL) {
       Creernoeud_AUii(&R ) ;
       Aff_info_AUii(R , S1 ) ;
       Aff_pere_AUii(R , NULL ) ;
       *Racine  =  R ;
       }
     else
       {
       while( ( R != NULL ) && ( Continu )) {
         Q  =  R ;
         if( ( Struct1_Uii(Info_AUii(R )  ) != *Val )) {
           if( *Val > Struct1_Uii(Info_AUii(R )  )) {
             R  =  Fd_AUii(R ) ;
             }
           else
             {
             R  =  Fg_AUii(R ) ;

           } ;
           }
         else
           {
           Continu  =  False ;

         } ;

       } ;
       if( R == NULL) {
         Creernoeud_AUii(&R ) ;
         Aff_info_AUii(R , S1 ) ;
         Aff_pere_AUii(R , Q ) ;
         if( *Val > Struct1_Uii(Info_AUii(Q )  )) {
           Aff_fd_AUii(Q , R ) ;
           }
         else
           {
           Aff_fg_AUii(Q , R ) ;

         } ;

       } ;

     } ;

    }
  void Creer_arbre (Pointeur_AUii *A , int *Nbnoeud2 , Pointeur_W12Uii *T)
    {
      /** Variables locales **/
      Pointeur_AUii Racine;
      int I;
      int Val;
      Pointeur_Uii S;

      /** Corps du module **/
     Racine  =  *A ;
     I  =  *Nbnoeud2 ;
     while( ( I > 0 )) {
       Val  =  Struct1_Uii(Element_W12Uii(*T , I   )  ) ;
       Inserer ( & Racine , & Val ) ;
       I  =  I - 1 ;

     } ;
     *A  =  Racine ;

    }
  int  Min1 (int *A , int *B)
    {
      /** Variables locales **/
      int  Min12 ;

      /** Corps du module **/
     if( *A <= *B) {
       Min12  =  *A ;
       }
     else
       {
       Min12  =  *B ;

     } ;

     return Min12 ;
    }
  int  Max1 (int *A , int *B)
    {
      /** Variables locales **/
      int  Max12 ;

      /** Corps du module **/
     if( *A >= *B) {
       Max12  =  *A ;
       }
     else
       {
       Max12  =  *B ;

     } ;

     return Max12 ;
    }
  int  Profondeur (Pointeur_AUii *N,int *nbvisit)
    {
      /** Variables locales **/
      int  Profondeur2 ;
      Pointeur_AUii _Px1;
      Pointeur_AUii _Px2;

      /** Corps du module **/
     if( *N == NULL) {
       Profondeur2  =  - 1 ;
       (*nbvisit)++;
       }
     else
       {
       _Px1 =  Fg_AUii(*N ) ;
       _Px2 =  Fd_AUii(*N ) ;
       (*nbvisit)+=1;
       Profondeur2  =  1 + Max(Profondeur ( &_Px1,nbvisit) , Profondeur ( &_Px2,nbvisit) ) ;

     }
     return Profondeur2 ;
    }
  Pointeur_AUii Suiv_post (Pointeur_AUii *A,int *nbvisit)
    {
      /** Variables locales **/
      Pointeur_AUii Suiv_post2 ;
      Pointeur_AUii N;
      Pointeur_AUii Sauv;

      /** Corps du module **/
     N  =  *A ;
     Sauv  =  N ;
     N  =  Pere_AUii(N ) ;
     (*nbvisit)++;
     if( ( N != NULL )) {
       if( ( Fd_AUii(N ) != Sauv )) {
         if( ( Fd_AUii(N ) != NULL )) {
           N  =  Fd_AUii(N ) ;
           (*nbvisit)++;
           while( ( ( Fg_AUii(N ) != NULL ) || ( Fd_AUii(N ) != NULL ) )) {
             ;
             if( ( Fg_AUii(N ) != NULL )) {
               N  =  Fg_AUii(N ) ;
               (*nbvisit)++;
               }
             else
               {
               N  =  Fd_AUii(N ) ;
                (*nbvisit)++;
             } ;

           } ;

         } ;

       } ;

     } ;
     Suiv_post2  =  N ;

     return Suiv_post2 ;
    }
  Pointeur_AUii First_post_el (Pointeur_AUii *N,int *nbvisit)
    {
      /** Variables locales **/
      Pointeur_AUii First_post_el2 ;
      Pointeur_AUii A;

      /** Corps du module **/
     A  =  *N ;
     if( ( A != NULL )) {
       while( ( Fg_AUii(A ) != NULL ) || ( Fd_AUii(A ) != NULL )) {
         if( ( Fg_AUii(A ) == NULL )) {
           A  =  Fd_AUii(A ) ;
           (*nbvisit)++;
           }
         else
           {
           A  =  Fg_AUii(A ) ;
            (*nbvisit)++;
         } ;

       } ;

     } ;
     First_post_el2  =  A ;

     return First_post_el2 ;
    }
  Pointeur_AUii Rg (Pointeur_AUii *N)
    {
      /** Variables locales **/
      Pointeur_AUii Rg2 ;
      Pointeur_AUii A;
      Pointeur_AUii B;
      int X;
      int Y;
      int _Px1;
      int _Px2;
      int _Px3;
      int _Px4;
      int _Px5;

      /** Corps du module **/
     A  =  *N ;
     B  =  Fd_AUii(A ) ;

     Aff_fd_AUii(A , Fg_AUii(B ) ) ;
     if( ( Fg_AUii(B ) != NULL )) {
       Aff_pere_AUii(Fg_AUii(B ) , A ) ;

     } ;
     Aff_fg_AUii(B , A ) ;
     Aff_pere_AUii(B , Pere_AUii(A ) ) ;
     if( ( Pere_AUii(A ) != NULL )) {
       if( ( A == Fg_AUii(Pere_AUii(A ) ) )) {
         Aff_fg_AUii(Pere_AUii(A ) , B ) ;
         }
       else
         {
         Aff_fd_AUii(Pere_AUii(A ) , B ) ;

       } ;

     } ;
     Aff_pere_AUii(A , B ) ;
     X  =  Struct2_Uii(Info_AUii(A )  ) ;
     Y  =  Struct2_Uii(Info_AUii(B )  ) ;
     _Px1 =  0 ;
     Aff_struct2_Uii(Info_AUii(A )  , X - Min1 ( & Y , &_Px1) + 1 ) ;
     _Px2 =  X + 2 ;
     _Px3 =  Y + X + 2 ;
     _Px4 =  Max1 ( &_Px2, &_Px3) ;
     _Px5 =  Y + 1 ;
     Aff_struct2_Uii(Info_AUii(B )  , Max1 ( &_Px4, &_Px5) ) ;
     Rg2  =  B ;

     return Rg2 ;
    }
  Pointeur_AUii Rd (Pointeur_AUii *N)
    {
      /** Variables locales **/
      Pointeur_AUii Rd2 ;
      Pointeur_AUii A;
      Pointeur_AUii B;
      int X;
      int Y;
      int _Px1;
      int _Px2;
      int _Px3;
      int _Px4;
      int _Px5;

      /** Corps du module **/
     A  =  *N ;
     B  =  Fg_AUii(A ) ;
     Aff_fg_AUii(A , Fd_AUii(B ) ) ;
     if( ( Fd_AUii(B ) != NULL )) {
       Aff_pere_AUii(Fd_AUii(B ) , A ) ;

     } ;
     Aff_fd_AUii(B , A ) ;
     Aff_pere_AUii(B , Pere_AUii(A ) ) ;
     if( ( Pere_AUii(A ) != NULL )) {
       if( ( A == Fg_AUii(Pere_AUii(A ) ) )) {
         Aff_fg_AUii(Pere_AUii(A ) , B ) ;
         }
       else
         {
         Aff_fd_AUii(Pere_AUii(A ) , B ) ;

       } ;

     } ;
     Aff_pere_AUii(A , B ) ;
     X  =  Struct2_Uii(Info_AUii(A )  ) ;
     Y  =  Struct2_Uii(Info_AUii(B )  ) ;
     _Px1 =  0 ;
     Aff_struct2_Uii(Info_AUii(A )  , X - Max1 ( & Y , &_Px1) - 1 ) ;
     _Px2 =  X - 2 ;
     _Px3 =  Y + X - 2 ;
     _Px4 =  Min1 ( &_Px2, &_Px3) ;
     _Px5 =  Y - 1 ;
     Aff_struct2_Uii(Info_AUii(B )  , Min1 ( &_Px4, &_Px5) ) ;
     Rd2  =  B ;

     return Rd2 ;
    }
  Pointeur_AUii Equilibrer (Pointeur_AUii *N,int *nbrotat,int *nbvisit)
    {
      /** Variables locales **/
      Pointeur_AUii Equilibrer2 ;
      Pointeur_AUii A;
      Pointeur_AUii Sr;
      int Balance;
      Pointeur_AUii _Px1;
      Pointeur_AUii _Px2;

      /** Corps du module **/
     A  =  *N ;
     Sr  =  A ;
     Balance  =  Struct2_Uii(Info_AUii(A )  ) ;
     if( ( Balance >= 2 )) {
       while( ( Balance >= 2 )) {
         if( ( Struct2_Uii(Info_AUii(Fg_AUii(A ) )  ) != - 1 )) {
           Sr  =  Rd ( & A ) ;
           (*nbvisit)+=2;
           (*nbrotat)++;
           }
         else//double rotation
           {
           _Px1 =  Fg_AUii(A ) ;
           Sr  =  Rg ( &_Px1) ;
           Sr  =  Rd ( & A ) ;
           (*nbvisit)+=4;
            (*nbrotat)+=2;
         } ;
         Balance  =  Struct2_Uii(Info_AUii(A )  ) ;

       } ;
       }
     else
       {
       while( ( Balance <= - 2 )) {
         if( ( Struct2_Uii(Info_AUii(Fd_AUii(A ) )  ) != 1 )) {
           Sr  =  Rg ( & A ) ;
           (*nbrotat)++;
           (*nbvisit)+=2;
           }
         else//double rotation
           {
           _Px2 =  Fd_AUii(A ) ;
           Sr  =  Rd ( &_Px2) ;
           Sr  =  Rg ( & A ) ;
           (*nbvisit)+=4;
            (*nbrotat)+=2;
         } ;
         Balance  =  Struct2_Uii(Info_AUii(A )  ) ;

       } ;

     } ;
     Equilibrer2  =  Sr ;

     return Equilibrer2 ;
    }
  Pointeur_AUii Equilibrer_arb (Pointeur_AUii *R,int *nbrotat,int *nbvisit)
    {
      /** Variables locales **/
      Pointeur_AUii Equilibrer_arb2 ;
      Pointeur_AUii A;
      Pointeur_AUii Q;
      int Balance;
      Pointeur_AUii _Px1;
      Pointeur_AUii _Px2;

      /** Corps du module **/
      (*nbvisit)=1;
      (*nbrotat)=0;
     A  =  First_post_el ( & *R,nbvisit) ;
     while( ( A != NULL )) {
       _Px1 =  Fg_AUii(A ) ;
       _Px2 =  Fd_AUii(A ) ;
       (*nbvisit)++;
       Balance  =  Profondeur ( &_Px1,nbvisit) - Profondeur ( &_Px2,nbvisit) ;//calculer la balance du noeud A
       Aff_struct2_Uii(Info_AUii(A )  , Balance ) ;
       A  =  Equilibrer ( & A,nbrotat,nbvisit ) ;//equilibrer le sous arbre A
       Q  =  A ;
       A  =  Suiv_post ( & A,nbvisit) ;

     } ;
     Equilibrer_arb2  =  Q ;

     return Equilibrer_arb2 ;
    }
  bool  Is_avl2 (Pointeur_AUii *N)
    {
      /** Variables locales **/
      bool  Is_avl22 ;
      int Res;
      Pointeur_AUii _Px1;
      Pointeur_AUii _Px2;

      /** Corps du module **/
     if( *N == NULL) {
       Is_avl22  =  True ;
       }
     else
       {
       Res  =  Struct2_Uii(Info_AUii(*N )  ) ;
       if( ( Res >= - 1 ) && ( Res <= 1 )) {
         _Px1 =  Fd_AUii(*N ) ;
         _Px2 =  Fd_AUii(*N ) ;
         Is_avl22  =  ( Is_avl2 ( &_Px1) ) && ( Is_avl2 ( &_Px2) ) ;
         }
       else
         {
         Is_avl22  =  False ;

       }
     }
     return Is_avl22 ;
    }
  void Liberer_arb (Pointeur_AUii *R)//Liberer l'arbre avec un algorithme iteratif
    {
      /** Variables locales **/
      Pointeur_AUii A;
      Pointeur_AUii Q;
        int i=0;
      /** Corps du module **/
     A  =  First_post_el ( & *R ,&i) ;
     while( ( A != NULL )) {
       Q  =  A ;
       A  =  Suiv_post ( & A,&i ) ;

       Liber_struct_Uii(Info_AUii(Q ) ) ;

       Liberernoeud_AUii(Q) ;


     } ;
     *R  =  NULL ;

    }
     void Liberer_arb2 (Pointeur_AUii *A)
    {
      /** Variables locales **/
      Pointeur_AUii _Px1;
      Pointeur_AUii _Px2;

      /** Corps du module **/
     if( ( *A != NULL )) {
       _Px1 =  Fg_AUii(*A ) ;
       Liberer_arb2 ( &_Px1) ;
       _Px2 =  Fd_AUii(*A ) ;
       Liberer_arb2 ( &_Px2) ;
       Liber_struct_Uii(Info_AUii(*A ) ) ;
       Liberernoeud_AUii(*A ) ;

     } ;

    }
  /***************************************************************************/
  /*                           Les modules de DSW                            */
  /***************************************************************************/
  void Rebalance (Pointeur_AUii *Racine,int *nbnoeud,int *nbrotat,int *nbvisit)
    {
      /** Variables locales **/
      Pointeur_AUii Pr;
      Pointeur_Uii S;
      int Nbnoeud;

      /** Corps du module **/
      (*nbrotat)=0;(*nbvisit)=1;
     Creernoeud_AUii(&Pr ) ;
     Alloc_struct_Uii(&S ) ;
     Aff_struct1_Uii(S  , 0 ) ;//Initialisation de la structure
     Aff_struct2_Uii(S  , 0 ) ;
     Aff_info_AUii(Pr , S ) ;
     Aff_fd_AUii(Pr , *Racine ) ;
     Creer_lld ( & Pr , & Nbnoeud ,nbrotat,nbvisit) ;//creation de la liste chainée
     Vine_to_tree ( & Pr , & Nbnoeud,nbrotat,nbvisit ) ;
     *Racine  =  Fd_AUii(Pr ) ;
     (*nbvisit)++;
     Aff_pere_AUii(*Racine,NULL);
     Liber_struct_Uii(Info_AUii(Pr ) ) ;
     Liberernoeud_AUii(Pr ) ;
    *nbnoeud=Nbnoeud;
    }
  void Creer_lld (Pointeur_AUii *Racine , int *Nbnoeud,int *nbrotat,int *nbvisit)
    {
      /** Variables locales **/
      Pointeur_AUii Queue;
      Pointeur_AUii Temp;
      Pointeur_AUii Remainder;

      /** Corps du module **/
     Queue  =  *Racine ;
     Remainder  =  Fd_AUii(Queue ) ;
     (*nbvisit)++;
     *Nbnoeud  =  0 ;
     while( ( Remainder != NULL )) {
       if( ( Fg_AUii(Remainder ) == NULL )) {
         Queue  =  Remainder ;
         Remainder  =  Fd_AUii(Remainder ) ;
         (*nbvisit)+=2;
         *Nbnoeud  =  *Nbnoeud + 1 ;

         }
       else
         {
         Temp  =  Fg_AUii(Remainder ) ;
         Aff_fg_AUii(Remainder , Fd_AUii(Temp ) ) ;
         Aff_fd_AUii(Temp , Remainder ) ;
         Remainder  =  Temp ;
         Aff_fd_AUii(Queue , Temp ) ;
            (*nbvisit)+=4;
            (*nbrotat)++;
       } ;

     } ;

    }
  void Vine_to_tree (Pointeur_AUii *A , int *Size,int *nbrotat,int *nbvisit)
    {
      /** Variables locales **/
      Pointeur_AUii Racine;
      int Nbnoeud;
      int Nbfeuille;
      int _Px1;
      int _Px2;

      /** Corps du module **/
     Nbnoeud  =  *Size ;
     Racine  =  *A ;
     (*nbvisit)++;
     _Px1 =  Nbnoeud + 1 ;
     Nbfeuille  =  Nbnoeud + 1 - Exp(2 , Msb ( &_Px1) ) ;
     Compression ( & Racine , & Nbfeuille,nbrotat,nbvisit ) ;
     Nbnoeud  =  Nbnoeud - Nbfeuille ;
     while( ( Nbnoeud > 1 )) {
       _Px2 =  Nbnoeud / 2 ;
       Compression ( & Racine , &_Px2,nbrotat,nbvisit) ;
       Nbnoeud  =  Nbnoeud / 2 ;

     } ;

    }
  void Compression (Pointeur_AUii *A , int *Nf,int *nbrotat,int *nbvisit)
    {
      /** Variables locales **/
      Pointeur_AUii Racine;
      Pointeur_AUii Scanner;
      Pointeur_AUii F;
      int Nombre;
      int I;

      /** Corps du module **/
     Racine  =  *A ;
     Nombre  =  *Nf ;
     Scanner  =  Racine ;
     I  =  1 ;
     while( ( I <= Nombre )) {
       F  =  Fd_AUii(Scanner ) ;

       Aff_fd_AUii(Scanner , Fd_AUii(F ) ) ;
       Scanner  =  Fd_AUii(Scanner ) ;
       Aff_fd_AUii(F , Fg_AUii(Scanner ) ) ;
       Aff_fg_AUii(Scanner , F ) ;
       I  =  I + 1 ;
        (*nbvisit)+=3;
        (*nbrotat)++;
     } ;

    }
  int  Msb (int *X)
    {
      /** Variables locales **/
      int  Msb2 ;
      int N;
      int Cpt;

      /** Corps du module **/
     N  =  *X ;
     Cpt  =  0 ;
     while( ( N > 1 )) {
       N  =  N / 2 ;
       Cpt  =  Cpt + 1 ;

     } ;
     Msb2  =  Cpt ;

     return Msb2 ;
    }
  bool  Is_avl (Pointeur_AUii *N)
    {
      /** Variables locales **/
      bool  Is_avl2 ;
      int Res;
      Pointeur_AUii _Px1;
      Pointeur_AUii _Px2;
      Pointeur_AUii _Px3;
      Pointeur_AUii _Px4;
        int nbv=0;
      /** Corps du module **/
     if( *N == NULL) {
       Is_avl2  =  True ;
       }
     else
       {
       _Px1 =  Fg_AUii(*N ) ;
       _Px2 =  Fd_AUii(*N ) ;
       Res  =  Profondeur ( &_Px1,&nbv) - Profondeur ( &_Px2,&nbv) ;
       if( ( Res >= - 1 ) && ( Res <= 1 )) {
         _Px3 =  Fd_AUii(*N ) ;
         _Px4 =  Fd_AUii(*N ) ;
         Is_avl2  =  ( Is_avl ( &_Px3) ) && ( Is_avl ( &_Px4) ) ;
         }
       else
         {
         Is_avl2  =  False ;

       }
     }
     return Is_avl2 ;
    }

  int main(int argc, char *argv[])
    {time_t start, end;
    FILE *f;
    Nbnoeud=0;
    int a=0,b=0;
     int moyenne_nbv1,moyenne_nbv2,moyenne_rt2,moyenne_rt1;
     f=fopen("data.txt","w");//l'ouverture du fichier qui contient les statistiques

        srand(time(NULL));

for(m=100;m<=80000;m+=1000)//m est le nombre de noeuds à inserer dans les 120 differents arbres
{

    printf("Creation des arbres de %d noeuds \n",m);
     Alloc_tab_W12Uii(&T,m ) ;
     N  =  1 ;//N le nombre d'arbres a creer dans chaque itération
           /* moyenne_nbv1=0 ;
             moyenne_nbv2=0 ;
             moyenne_rt2=0;
             moyenne_rt1=0;*/
             double t1=0;//temps d'execution du premier algorithme
             double t2=0;//temps d'execution du deuxieme algorithme

     while( ( N <= 120)) //creation des arbres
        {
       H  =  1 ;
       while( ( H <= m )) //rempilssage du tableau{
         {

                  Alloc_struct_Uii(&S ) ;
         Aff_struct1_Uii(S  , Aleanombre(990730537 )*(H+4) ) ;
         Aff_struct2_Uii(S  , 0 ) ;//initialisation du champ balance à 0;
         Aff_element_W12Uii(T , H   , S ) ;
         H  =  H + 1 ;

       } ;
      /**************************************************************/
       Creer_arbre ( & A1 , &m, & T ) ;//creation de l'arbre à equilibrer avec DSW
       Creer_arbre ( & A2 , &m, & T ) ;//creation de l'arbre à equilibrer avec 2eme algo
       start= clock();
       A2  =  Equilibrer_arb ( & A2,&nbrotat2,&nbvisit2 ) ;//equilibrer le deuxieme arbre
       end=clock();
       //moyenne_rt2+=nbrotat2 ;//Calcul de la moyenne de nombre de rotations dans 150 arbres avec 2eme algo
       //moyenne_nbv2+=nbvisit2 ;//Calcul de la moyenne de nombre de noeuds visités dans 150 arbres avec 2eme algo
       t1= t1 + ((double)(end-start)/CLOCKS_PER_SEC)*1000;
       start= clock();
       Rebalance ( & A1,&Nbnoeud,&nbrotat1,&nbvisit1 ) ;
       end=clock();
       //moyenne_rt1+=nbrotat1 ;//Calcul de la moyenne de nombre de rotations dans 150 arbres avec DSW
      // moyenne_nbv1+=nbvisit1 ;//Calcul de la moyenne de nombre de noeuds visités dans 150 arbres avec DSW
       t2= t2 + ((double)(end-start)/CLOCKS_PER_SEC)*1000;
       fprintf ( f," DSW  %d %d %d %d %lf",Is_avl(&A1),Nbnoeud,nbrotat1,nbvisit1,t2 ) ;
       fprintf ( f," AVL  %d %d %d %d %lf\n",Is_avl2(&A2),Nbnoeud,nbrotat2,nbvisit2,t1 ) ;

      Liberer_arb2(&A1);//Liberer l'arbre A1
      Liberer_arb(&A2);//Liberer l'arbre A2
      A1=NULL;
       N  =  N + 1 ;
       for(i=1;i<=m;i++)//liberer le tableau T
       {
           Liber_struct_Uii(Element_W12Uii(T,i));
       }
       Liber_tab_W12Uii(&T);
     } ;
       /* t1/=150;
        t2/=150;
        moyenne_rt1/=150;
        moyenne_rt2/=150;
        moyenne_nbv1/=150;
        moyenne_nbv2/=150;*/
       //fprintf ( f," DSW  %d %d %d %d %d ",Is_avl(&A1),Nbnoeud,moyenne_rt1,moyenne_nbv1,(int)t2 ) ;//l'ecriture dans le fichier des données
      // fprintf ( f," AVL  %d %d %d %d %d \n",Is_avl2(&A2),Nbnoeud,moyenne_rt2,moyenne_nbv2,(int)t1 ) ;
}
        return 0;
        fclose(f);
    }
/*Tp réalisé Par Brahim Yacine et Kerris Nadir Islam G10*/
