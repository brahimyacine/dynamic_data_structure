#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include"bibioprog.h"
#include<conio.h>
void affichage_menu()
{
   printf("                                TP2 realise par Brahim Yacine \n \n ");
   printf("Le Menu : \n");
printf("     1.verifier la relation de dominance entre deux programmes lus.\n");
printf("     2.eliminer tous les programmes domines dans une tache lue.\n");
printf("     3.Execution normale.\n");
printf("     4.combiner deux taches lues. \n");
printf("     5.Quitter \n");
}
void affichage_menu2()
{
    printf("\n Menu2 : \n");
    printf("1.combiner la tache avec une autre tache lue.\n");
    printf("2.trier les programmes de la tache. \n");
    printf("3.eliminer les programmes domines dans la tache.\n");
    printf("4. Retour \n");
}
affich_menu4()
{
    printf(" \n MENU 4:\n");
    printf("1.combiner la tache finale avec une autre . \n");
    printf("2.eliminer les programmes domines dans la tache finale. \n");
    printf("3.trier les programmes. \n");
    printf("4.Retour \n");
}
int main()
{   FILE *F;//pointeur vers un fichier contenant les données
    float w1=0,w2=0;//les pourcentages
    char choice='m',car='m',NOM[50]="";
    int choix;
    Tache *T,*T2,*T1,*T3;
    PROGRAMME *PRG1,*PRG2,*PRG=NULL;
    PROCESSUS *process;

menu1: affichage_menu();
scanf("%d",&choix);car=getchar();while(car!='\n');car='m';
switch(choix)
{
case 1:
    printf("Verification de la relation de dominance entre deux programmes lus: \n");
    creer_programme(&PRG1);//creer le programme1
    creer_programme2(PRG1);//Lecture du premier programme
    creer_programme(&PRG2);//creer le programme2
    creer_programme2(PRG2);//Lecture du deuxième programme
    PRG=dominer1(PRG1,PRG2);//PRG est le programme dominant sinon est egale à NULL
    if(PRG!=NULL)
    affich_prg(PRG);
    else
        printf("Aucun programme domine l'autre :: \n");
    printf("\n");system("PAUSE");system("CLS");
        goto menu1;
    break;
case 2:printf("Elimination des programmes domines dans une tache lue : \n");
    creer_tache(&T);T->tete=NULL;T->queue=NULL;//creation de la tache
    creer_tache2(T);//lecture de la tache (suite de programmes)
    printf("Affichage de la tache \n");
    affich_tache(T);printf("\n");//affichage de la tache avant la suppression des programmes
    system("PAUSE");
    eliminer_candT(T);//élimination des programmes dominés dans la tache T
    printf("affichage de la tache apres l'elimination des programmes domines :\n");
    affich_tache(T);//affichage de la tache finale
    menu2: affichage_menu2();
    scanf("%d",&choix);
    switch(choix)
    {
        case 1:
                creer_tache(&T2);T2->tete=NULL;T2->queue=NULL;//creation de la tache
                creer_tache2(T2);//lecture de la tache (suite de programmes)
                creer_tache(&T3);T3->tete=NULL;T3->queue=NULL;//creation de la tache
                combiner(T,T2,T3);
                printf("\n Affichage de la tache \n");
                affich_tache(T3);
                T=T3;system("PAUSE");system("CLS");
                goto menu2 ;
                break;
        case 3:
            eliminer_candT(T);
            affich_tache(T);system("PAUSE");system("CLS");
            goto menu2 ;
            break;
        case 2:
            /* Lecture des pourcentages*/
        do
        {
        printf("Entrez la valeur de W1<100: ");scanf("%f",&w1);
        printf("Entrez la valeur de W2<%.2f: ",100-w1);scanf("%f",&w2);
        }
        while (w1+w2>100);
        tri_prg(T,w1,w2);
        printf("Affichage de la tache aprés le tri : \n");
        affich_tache(T);printf("\n");system("PAUSE");system("CLS");
        goto menu2;
            break;
        case 4: system("PAUSE");system("CLS");
        goto menu1 ;
            break;
    }

    break;
case 3:
    creer_processus(&process);process->queue=NULL;process->tete=NULL;//initialisation du processus
    F=fopen("data.txt","r");//l'ouverture de fichier contenant les données
    Remp_processus(process,F);//Remplir les champs du Processus avec les données
fclose(F);
printf("Voulez vous ajouter une Tache ?(o pour oui,n pour non) :");
scanf("%c",&choice);while (car!='\n') car=getchar();
car='m';
if(choice=='o')
{

do
{
    creer_tache(&T);T->tete=NULL;T->queue=NULL;
    ajouter_tache2(process,T);
    printf("Voulez vous ajouter une Tache ?(o pour oui,n pour non) :");
    scanf("%c",&choice);
}while (choice=='o');
}
choice='m';
printf("Affichage de processus\n");
affich_processus(process);printf("\n");//affichage de processus
system("PAUSE");printf("\n");
eliminer_candP(process);//éliminer tout les programmes du processus dominés par d'autre programmes de la meme tache
printf("Affichage de processus aprés l'elimination des programmes dominés \n");
affich_processus(process);printf("\n");//affichage de processus

creer_tache(&T2);T2->queue=NULL;T2->tete=NULL;aff_nomT(T2,"TACHEF");//création de la tache qui va contenir les solutions potentielles
combiner_process(process,&T2);//ETAPE2
printf("\n");system("pause");printf("\n");
printf("\n Les solutions potentielles sont :\n");
affich_tache(T2);//affichage des solution potentielles
printf("\n Voulez vous trier les solutions ?");
scanf("%c",&choice);
if(choice=='o')
{

printf("\n Le tri des solutions : \n");
do //Lecture des pourcentages
{
    printf("Entrez la valeur de W1<100: ");scanf("%f",&w1);
    printf("Entrez la valeur de W2<%.2f: ",100-w1);scanf("%f",&w2);
}
while (w1+w2>100);
Remp_TM(T2,w1,w2);//Remplissage des champs M des programmes de la tache T
tri_prg(T2,w1,w2);//tri de la tache contenant les solutions potentielles
affich_tache(T2);//affichage de la tache aprés le tri


}
system("PAUSE");system("CLS");
goto menu1;
    break;
case 4:
    creer_tache(&T);T->tete=NULL;T->queue=NULL;//creation de la tache1
    printf("Lecture de la premiere tache : \n");
    creer_tache2(T);//lecture de la tache1 (suite de programmes)
    creer_tache(&T1);T1->tete=NULL;T1->queue=NULL;//creation de la tache2
   etiq: printf("Lecture de la deuxieme tache : \n");
    creer_tache2(T1);//lecture de la tache2 (suite de programmes)
    creer_tache(&T2);T2->tete=NULL;T2->queue=NULL;strcat(NOM,T->NOMTACHE);strcat(NOM,"#");strcat(NOM,T1->NOMTACHE);aff_nomT(T2,NOM);//creation de la tache
    printf("Affichage de la tache apres la combinaison des deux taches : \n");
    combiner(T,T1,T2);
    affich_tache(T2);printf("\n");
    T=T2;
    system("PAUSE");
  menu4:  affich_menu4();

    scanf("%d",&choix);//while (car!='\n') car=getchar;
    car='m';
    switch(choix)
    {
        case 1: goto etiq ;
            break;
        case 2: eliminer_candT(T);printf("Affichage de la tache apres l'elimination des programmes domines \n");
        affich_tache(T);printf("\n");goto menu4;
            break;
        case 3:
                printf("\n Le tri des solutions : \n");
do //Lecture des pourcentages
{
    printf("Entrez la valeur de W1<100: ");scanf("%f",&w1);
    printf("Entrez la valeur de W2<%.2f: ",100-w1);scanf("%f",&w2);
}
while (w1+w2>100);
Remp_TM(T,w1,w2);//Remplissage des champs M des programmes de la tache T
tri_prg(T,w1,w2);//tri de la tache contenant les solutions potentielles
affich_tache(T);//affichage de la tache aprés le tri
system("PAUSE");system("cls");
            goto menu4;break;
        case 4: goto menu1;
            break;
    }
    goto menu1;
    break;
default: printf("Fin d'execution \n");
break;
case 5 : printf(" \n Merci !");break;
}

    return 0;
}
/*-----Tp réalisé par Brahim_Yacine-------*/
