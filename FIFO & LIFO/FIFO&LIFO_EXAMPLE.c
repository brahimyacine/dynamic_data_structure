#include <stdio.h>
#include <stdlib.h>
#include "FIFO.h"
#include "LIFO.h"
void menuf ()
{   printf("\n MEnu de la file \n");
    printf("\n 1.Enfiler \n");
    printf("\n 2.Defiler \n");
    printf("\n 3.afficher la file \n");
    printf("\n 4.Vider la file \n");
    printf("\n 5.retour \n");
}
void menup ()
{   printf("\n MEnu de la pile \n");
    printf("\n 1.empiler \n");
    printf("\n 2.Depiler \n");printf("\n 3.afficher la pile \n");
    printf("\n 4.Vider la pile \n");
    printf("\n 5.retour \n");
}
void menu ()
{
    printf("\n MEnu principal \n");
    printf("\n 1.file \n");
    printf("\n 2.pile \n");
    printf("\n 3.QUitter \n");
}
/*--------------------------------------------------------------------------*/


int main()
{   int i,n=0,x,v,choix;//v:valeur,x:le nombre de données,n:pour le défilement
char choice='y'; //pour le scanf
    printf("Hello world!\n");
    filed f;//La file principale
    creer_filed(&f);
    PILED *p;
    creer_piled(&p);
    //listeF *p=NULL;//pointeur vers les éléments de la file
   menu1: menu();
   scanf("%d",&choix);
   switch(choix)
   {
       case 1:
         menu2:  menuf();
         scanf("%d",&choix);
         switch(choix)
         {
             case 1: printf("\n Entrez une valeur : ");scanf("%d",&v);
                     choice=getchar();
                     enfilerd(&f,v);
                 system("PAUSE");goto menu2;break;
             case 2: defilerd(&f,&n);system("PAUSE");goto menu2;break;
             case 3: affich_file(f);system("PAUSE");printf("\n");goto menu2;break;
             case 4: creer_filed(&f);system("PAUSE");goto menu2;break;
             case 5: system("PAUSE");system("CLS");goto menu1; break;
         }
           break;
       case 2: menu3:  menup();
         scanf("%d",&choix);
         switch(choix)
         {
             case 1: printf("\n Entrez une valeur : ");scanf("%d",&v);
                     choice=getchar();
                     empilerd(&p,v);
                 system("PAUSE");goto menu3;break;
             case 2: depilerd(&p,&n);system("PAUSE");goto menu3;break;
             case 3: affich_pile(p);printf("\n");system("PAUSE");goto menu3;break;
             case 4: creer_piled(&p);system("PAUSE");goto menu3;break;
             case 5: system("PAUSE");system("CLS");goto menu1; break;
         }break;
       case 3: break;
   }
   return 0;
}
