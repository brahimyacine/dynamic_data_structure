/*TP realise par Brahim Yacine */
   SOIENT
       T UN TABLEAU ( 100 ) DYNAMIQUE DE ( ENTIER , ENTIER ) DYNAMIQUE ;
       H , Nbnoeud , N , M DES ENTIER ;
       S : ( ENTIER , ENTIER ) DYNAMIQUE ;
       A1 , A2 DES ARB DE ( ENTIER , ENTIER ) DYNAMIQUE ;
       Creer_lld , Vine_to_tree , Compression , Rebalance DES ACTION ;
       Suiv_post , Rd , Rg , Equilibrer , First_post_el , Equilibrer_arb DES FONCTION ( ARB DE ( ENTIER , ENTIER )
       DYNAMIQUE ) ;
       Inserer , Creer_arbre , Liberer_arb , Liberer_arb2 DES ACTION ;
       Profondeur , Max1 , Min1 , Getnode , Msb DES FONCTION ( ENTIER ) ;
       Is_avl , Is_avl2 DES FONCTION ( BOOLEEN ) ;
      
   DEBUT
       M := 1 ;
       TANTQUE ( M <= 100 )
           ALLOC_TAB ( T ) ;
           N := 1 ;
           ECRIRE ( 'creation des arbres ayant' ) ;
           ECRIRE ( M ) ;
           ECRIRE ( 'noeuds' ) ;
           TANTQUE ( N <= 10 )
          /*creation de N arbre   */
               H := 1 ;
               TANTQUE ( H <= M )
              /*remplissage du tableau*/
                   ALLOC_STRUCT ( S ) ;
                   AFF_STRUCT ( S , 1 , ALEANOMBRE ( 500000 ) ) ;
                   AFF_STRUCT ( S , 2 , 0 ) ;
                   AFF_ELEMENT ( T [ H ] , S ) ;
                   H := H + 1 ;
                  
               FINTANTQUE ;
              /**************************************************************/
               APPEL Creer_arbre ( A1 , M , T ) ;
               APPEL Creer_arbre ( A2 , M , T ) ;
               A2 := Equilibrer_arb ( A2 ) ;
               APPEL Rebalance ( A1 ) ;
               ECRIRE ( 'ArbreDSW' ) ;
               ECRIRE ( Is_avl ( A1 ) ) ;
               ECRIRE ( 'ArbreAVL' ) ;
               ECRIRE ( Is_avl2 ( A2 ) ) ;
               APPEL Liberer_arb2 ( A1 ) ;
               A1 := NIL ;
               APPEL Liberer_arb ( A2 ) ;
               A2 := NIL ;
               N := N + 1 ;
              
           FINTANTQUE ;
           M := M + 10 ;
          
       FINTANTQUE ;
      
   FIN
  /************************************************************/
  /*               Modules 2eme algorithme                    */
  /************************************************************/
   FONCTION Getnode ( A ) : ENTIER
   SOIENT
       A UN ARB DE ( ENTIER , ENTIER ) DYNAMIQUE ;
       Cpt UN ENTIER ;
      
   DEBUT
       SI ( A = NIL )
           Getnode := 0 ;
          
       SINON
           Getnode := 1 + Getnode ( FG ( A ) ) + Getnode ( FD ( A ) ) ;
          
       FINSI ;
      
   FIN
   ACTION Inserer ( Racine , Val )
   SOIENT
       Racine , R , Q DES ARB DE ( ENTIER , ENTIER ) DYNAMIQUE ;
       Val UN ENTIER ;
       S , S1 : ( ENTIER , ENTIER ) DYNAMIQUE ;
       Continu UN BOOLEEN ;
      
   DEBUT
       Continu := VRAI ;
       R := Racine ;
       ALLOC_STRUCT ( S1 ) ;
       AFF_STRUCT ( S1 , 1 , Val ) ;
       AFF_STRUCT ( S1 , 2 , 0 ) ;
       SI R = NIL
           CREERNOEUD ( R ) ;
           AFF_INFO ( R , S1 ) ;
           AFF_PERE ( R , NIL ) ;
           Racine := R ;
          
       SINON
           TANTQUE ( R <> NIL ) ET ( Continu )
               Q := R ;
               SI ( STRUCT ( INFO ( R ) , 1 ) <> Val )
                   SI Val > STRUCT ( INFO ( R ) , 1 )
                       R := FD ( R ) ;
                      
                   SINON
                       R := FG ( R ) ;
                      
                   FINSI ;
                  
               SINON
                   Continu := FAUX ;
                  
               FINSI ;
              
           FINTANTQUE ;
           SI R = NIL
               CREERNOEUD ( R ) ;
               AFF_INFO ( R , S1 ) ;
               AFF_PERE ( R , Q ) ;
               SI Val > STRUCT ( INFO ( Q ) , 1 )
                   AFF_FD ( Q , R ) ;
                  
               SINON
                   AFF_FG ( Q , R ) ;
                  
               FINSI ;
              
           FINSI ;
          
       FINSI ;
      
   FIN
   ACTION Creer_arbre ( A , Nbnoeud2 , T )
   SOIENT
       T UN TABLEAU ( 100 ) DYNAMIQUE DE ( ENTIER , ENTIER ) DYNAMIQUE ;
       Racine , A UN ARB DE ( ENTIER , ENTIER ) DYNAMIQUE ;
       Nbnoeud2 , I , Val DES ENTIER ;
       S : ( ENTIER , ENTIER ) DYNAMIQUE ;
      
   DEBUT
       Racine := A ;
       I := Nbnoeud2 ;
       TANTQUE ( I > 0 )
           Val := STRUCT ( ELEMENT ( T [ I ] ) , 1 ) ;
           APPEL Inserer ( Racine , Val ) ;
           I := I - 1 ;
          
       FINTANTQUE ;
       A := Racine ;
      
   FIN
   FONCTION Min1 ( A , B ) : ENTIER
   SOIENT
       A , B DES ENTIER ;
      
   DEBUT
       SI A <= B
           Min1 := A ;
          
       SINON
           Min1 := B ;
          
       FINSI ;
      
   FIN
   FONCTION Max1 ( A , B ) : ENTIER
   SOIENT
       A , B DES ENTIER ;
      
   DEBUT
       SI A >= B
           Max1 := A ;
          
       SINON
           Max1 := B ;
          
       FINSI ;
      
   FIN
   FONCTION Profondeur ( N ) : ENTIER
   SOIT
       N UN ARB DE ( ENTIER , ENTIER ) DYNAMIQUE ;
      
   DEBUT
       SI N = NIL
           Profondeur := - 1 ;
          
       SINON
           Profondeur := 1 + MAX ( Profondeur ( FG ( N ) ) , Profondeur ( FD ( N ) ) ) ;
          
       FINSI
   FIN
   FONCTION Suiv_post ( A ) : ARB DE ( ENTIER , ENTIER ) DYNAMIQUE ;
   SOIENT
       A , N DES ARB DE ( ENTIER , ENTIER ) DYNAMIQUE ;
       Sauv UN ARB DE ( ENTIER , ENTIER ) DYNAMIQUE ;
      
   DEBUT
       N := A ;
       Sauv := N ;
       N := PERE ( N ) ;
       SI ( N <> NIL )
           SI ( FD ( N ) <> Sauv )
               SI ( FD ( N ) <> NIL )
                   N := FD ( N ) ;
                   TANTQUE ( ( FG ( N ) <> NIL ) OU ( FD ( N ) <> NIL ) )
                       ;
                       SI ( FG ( N ) <> NIL )
                           N := FG ( N ) ;
                          
                       SINON
                           N := FD ( N ) ;
                          
                       FINSI ;
                      
                   FINTANTQUE ;
                  
               FINSI ;
              
           FINSI ;
          
       FINSI ;
       Suiv_post := N ;
      
   FIN
   FONCTION First_post_el ( N ) : ARB DE ( ENTIER , ENTIER ) DYNAMIQUE
   SOIENT
       A , N UN ARB DE ( ENTIER , ENTIER ) DYNAMIQUE ;
      
   DEBUT
       A := N ;
       SI ( A <> NIL )
           TANTQUE ( FG ( A ) <> NIL ) OU ( FD ( A ) <> NIL )
               SI ( FG ( A ) = NIL )
                   A := FD ( A ) ;
                  
               SINON
                   A := FG ( A ) ;
                  
               FINSI ;
              
           FINTANTQUE ;
          
       FINSI ;
       First_post_el := A ;
      
   FIN
   FONCTION Rg ( N ) : ARB DE ( ENTIER , ENTIER ) DYNAMIQUE
   SOIENT
       A , N , B DES ARB DE ( ENTIER , ENTIER ) DYNAMIQUE ;
       X , Y DES ENTIER ;
      
   DEBUT
       A := N ;
       B := FD ( A ) ;
       AFF_FD ( A , FG ( B ) ) ;
       SI ( FG ( B ) <> NIL )
           AFF_PERE ( FG ( B ) , A ) ;
          
       FINSI ;
       AFF_FG ( B , A ) ;
       AFF_PERE ( B , PERE ( A ) ) ;
       SI ( PERE ( A ) <> NIL )
           SI ( A = FG ( PERE ( A ) ) )
               AFF_FG ( PERE ( A ) , B ) ;
              
           SINON
               AFF_FD ( PERE ( A ) , B ) ;
              
           FINSI ;
          
       FINSI ;
       AFF_PERE ( A , B ) ;
       X := STRUCT ( INFO ( A ) , 2 ) ;
       Y := STRUCT ( INFO ( B ) , 2 ) ;
       AFF_STRUCT ( INFO ( A ) , 2 , X - Min1 ( Y , 0 ) + 1 ) ;
       AFF_STRUCT ( INFO ( B ) , 2 , Max1 ( Max1 ( X + 2 , Y + X + 2 ) , Y + 1 ) ) ;
       Rg := B ;
      
   FIN
   FONCTION Rd ( N ) : ARB DE ( ENTIER , ENTIER ) DYNAMIQUE
   SOIENT
       A , N , B DES ARB DE ( ENTIER , ENTIER ) DYNAMIQUE ;
       X , Y DES ENTIER ;
      
   DEBUT
       A := N ;
       B := FG ( A ) ;
       AFF_FG ( A , FD ( B ) ) ;
       SI ( FD ( B ) <> NIL )
           AFF_PERE ( FD ( B ) , A ) ;
          
       FINSI ;
       AFF_FD ( B , A ) ;
       AFF_PERE ( B , PERE ( A ) ) ;
       SI ( PERE ( A ) <> NIL )
           SI ( A = FG ( PERE ( A ) ) )
               AFF_FG ( PERE ( A ) , B ) ;
              
           SINON
               AFF_FD ( PERE ( A ) , B ) ;
              
           FINSI ;
          
       FINSI ;
       AFF_PERE ( A , B ) ;
       X := STRUCT ( INFO ( A ) , 2 ) ;
       Y := STRUCT ( INFO ( B ) , 2 ) ;
       AFF_STRUCT ( INFO ( A ) , 2 , X - Max1 ( Y , 0 ) - 1 ) ;
       AFF_STRUCT ( INFO ( B ) , 2 , Min1 ( Min1 ( X - 2 , Y + X - 2 ) , Y - 1 ) ) ;
       Rd := B ;
      
   FIN
   FONCTION Equilibrer ( N ) : ARB DE ( ENTIER , ENTIER ) DYNAMIQUE ;
   SOIENT
       A , N , Sr DES ARB DE ( ENTIER , ENTIER ) DYNAMIQUE ;
       Balance UN ENTIER ;
      
   DEBUT
       A := N ;
       Sr := A ;
       Balance := STRUCT ( INFO ( A ) , 2 ) ;
       SI ( Balance >= 2 )
           TANTQUE ( Balance >= 2 )
               SI ( STRUCT ( INFO ( FG ( A ) ) , 2 ) <> - 1 )
                   Sr := Rd ( A ) ;
                  
               SINON
                   Sr := Rg ( FG ( A ) ) ;
                   Sr := Rd ( A ) ;
                  
               FINSI ;
               Balance := STRUCT ( INFO ( A ) , 2 ) ;
              
           FINTANTQUE ;
          
       SINON
           TANTQUE ( Balance <= - 2 )
               SI ( STRUCT ( INFO ( FD ( A ) ) , 2 ) <> 1 )
                   Sr := Rg ( A ) ;
                  
               SINON
                   Sr := Rd ( FD ( A ) ) ;
                   Sr := Rg ( A ) ;
                  
               FINSI ;
               Balance := STRUCT ( INFO ( A ) , 2 ) ;
              
           FINTANTQUE ;
          
       FINSI ;
       Equilibrer := Sr ;
      
   FIN
   FONCTION Equilibrer_arb ( R ) : ARB DE ( ENTIER , ENTIER ) DYNAMIQUE
   SOIENT
       A , R , Q DES ARB DE ( ENTIER , ENTIER ) DYNAMIQUE ;
       Balance UN ENTIER ;
      
   DEBUT
       A := First_post_el ( R ) ;
       TANTQUE ( A <> NIL )
           Balance := Profondeur ( FG ( A ) ) - Profondeur ( FD ( A ) ) ;
           AFF_STRUCT ( INFO ( A ) , 2 , Balance ) ;
           A := Equilibrer ( A ) ;
           Q := A ;
           A := Suiv_post ( A ) ;
          
       FINTANTQUE ;
       Equilibrer_arb := Q ;
      
   FIN
   FONCTION Is_avl2 ( N ) : BOOLEEN
   SOIENT
       N UN ARB DE ( ENTIER , ENTIER ) DYNAMIQUE ;
       Res UN ENTIER ;
      
   DEBUT
       SI N = NIL
           Is_avl2 := VRAI ;
          
       SINON
           Res := STRUCT ( INFO ( N ) , 2 ) ;
           SI ( Res >= - 1 ) ET ( Res <= 1 )
               Is_avl2 := ( Is_avl2 ( FD ( N ) ) ) ET ( Is_avl2 ( FD ( N ) ) ) ;
              
           SINON
               Is_avl2 := FAUX ;
              
           FINSI
       FINSI
   FIN
   ACTION Liberer_arb ( R ) ;
   SOIENT
       R , A , Q DES ARB DE ( ENTIER , ENTIER ) DYNAMIQUE ;
      
   DEBUT
       A := First_post_el ( R ) ;
       TANTQUE ( A <> NIL )
           Q := A ;
           A := Suiv_post ( A ) ;
           LIBER_STRUCT ( INFO ( Q ) ) ;
           LIBERERNOEUD ( Q ) ;
          
       FINTANTQUE ;
       R := NIL ;
      
   FIN
   ACTION Liberer_arb2 ( A )
   SOIENT
       A UN ARB DE ( ENTIER , ENTIER ) DYNAMIQUE ;
      
   DEBUT
       SI ( A <> NIL )
           APPEL Liberer_arb2 ( FG ( A ) ) ;
           APPEL Liberer_arb2 ( FD ( A ) ) ;
           LIBER_STRUCT ( INFO ( A ) ) ;
           LIBERERNOEUD ( A ) ;
          
       FINSI ;
      
   FIN
  /***************************************************************************/
  /*                           Les modules de DSW                            */
  /***************************************************************************/
   ACTION Rebalance ( Racine )
   SOIENT
       Racine , Pr DES ARB DE ( ENTIER , ENTIER ) DYNAMIQUE ;
       S : ( ENTIER , ENTIER ) DYNAMIQUE ;
       Nbnoeud UN ENTIER ;
      
   DEBUT
       CREERNOEUD ( Pr ) ;
       ALLOC_STRUCT ( S ) ;
       AFF_STRUCT ( S , 1 , 0 ) ;
       AFF_STRUCT ( S , 2 , 0 ) ;
       AFF_INFO ( Pr , S ) ;
       AFF_FD ( Pr , Racine ) ;
       APPEL Creer_lld ( Pr , Nbnoeud ) ;
       APPEL Vine_to_tree ( Pr , Nbnoeud ) ;
       Racine := FD ( Pr ) ;
       LIBER_STRUCT ( INFO ( Pr ) ) ;
       LIBERERNOEUD ( Pr ) ;
      
   FIN
   ACTION Creer_lld ( Racine , Nbnoeud )
   SOIENT
       Racine , Queue , Temp , Remainder DES ARB DE ( ENTIER , ENTIER ) DYNAMIQUE ;
       Nbnoeud UN ENTIER ;
      
   DEBUT
       Queue := Racine ;
       Remainder := FD ( Queue ) ;
       Nbnoeud := 0 ;
       TANTQUE ( Remainder <> NIL )
           SI ( FG ( Remainder ) = NIL )
               Queue := Remainder ;
               Remainder := FD ( Remainder ) ;
               Nbnoeud := Nbnoeud + 1 ;
              
           SINON
               Temp := FG ( Remainder ) ;
               AFF_FG ( Remainder , FD ( Temp ) ) ;
               AFF_FD ( Temp , Remainder ) ;
               Remainder := Temp ;
               AFF_FD ( Queue , Temp ) ;
              
           FINSI ;
          
       FINTANTQUE ;
      
   FIN
   ACTION Vine_to_tree ( A , Size )
   SOIENT
       A , Racine DES ARB DE ( ENTIER , ENTIER ) DYNAMIQUE ;
       Size , Nbnoeud , Nbfeuille DES ENTIER ;
      
   DEBUT
       Nbnoeud := Size ;
       Racine := A ;
       Nbfeuille := Nbnoeud + 1 - EXP ( 2 , Msb ( Nbnoeud + 1 ) ) ;
       APPEL Compression ( Racine , Nbfeuille ) ;
       Nbnoeud := Nbnoeud - Nbfeuille ;
       TANTQUE ( Nbnoeud > 1 )
           APPEL Compression ( Racine , Nbnoeud / 2 ) ;
           Nbnoeud := Nbnoeud / 2 ;
          
       FINTANTQUE ;
      
   FIN
   ACTION Compression ( A , Nf )
   SOIENT
       Racine , A , Scanner , F DES ARB DE ( ENTIER , ENTIER ) DYNAMIQUE ;
       Nf , Nombre , I DES ENTIER ;
      
   DEBUT
       Racine := A ;
       Nombre := Nf ;
       Scanner := Racine ;
       I := 1 ;
       TANTQUE ( I <= Nombre )
           F := FD ( Scanner ) ;
           AFF_FD ( Scanner , FD ( F ) ) ;
           Scanner := FD ( Scanner ) ;
           AFF_FD ( F , FG ( Scanner ) ) ;
           AFF_FG ( Scanner , F ) ;
           I := I + 1 ;
          
       FINTANTQUE ;
      
   FIN
   FONCTION Msb ( X ) : ENTIER
   SOIENT
       X , N UN ENTIER ;
       Cpt UN ENTIER ;
      
   DEBUT
       N := X ;
       Cpt := 0 ;
       TANTQUE ( N > 1 )
           N := N / 2 ;
           Cpt := Cpt + 1 ;
          
       FINTANTQUE ;
       Msb := Cpt ;
      
   FIN
   FONCTION Is_avl ( N ) : BOOLEEN
   SOIENT
       N UN ARB DE ( ENTIER , ENTIER ) DYNAMIQUE ;
       Res UN ENTIER ;
      
   DEBUT
       SI N = NIL
           Is_avl := VRAI ;
          
       SINON
           Res := Profondeur ( FG ( N ) ) - Profondeur ( FD ( N ) ) ;
           SI ( Res >= - 1 ) ET ( Res <= 1 )
               Is_avl := ( Is_avl ( FD ( N ) ) ) ET ( Is_avl ( FD ( N ) ) ) ;
              
           SINON
               Is_avl := FAUX ;
              
           FINSI
       FINSI
   FIN
