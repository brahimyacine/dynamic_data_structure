#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"bibioprog.h"
/*--------------------Les modules de création ------------------------*/
void creer_processus(PROCESSUS **process)//process est un pointeur vers la structure PROCESSUS
{
    *process=malloc(sizeof(PROCESSUS));
}
void creer_tache(Tache **T)//T est un pointeur vers la structure Tache
{
    *T=(Tache*)malloc(sizeof(Tache));
    aff_adrT(*T,NULL);
    //*T.tete=NULL;
   // *T.queue=NULL;
}
void creer_programme(PROGRAMME **prg) //prg est un pointeur vers la structure PROGRAMME
{
    *prg=(PROGRAMME *)malloc(sizeof(PROGRAMME));
    aff_adr(*prg,NULL);
}
/*------------------------La Machine ------------------*/
/*--------------- --------Programme-------------------------*/
void aff_adr(PROGRAMME *prg,PROGRAMME *prg2)//affecter l'adresse du programme (prg2) au champ adresse du programme prg
{
    prg->Suiv=prg2;
}
void aff_valT(PROGRAMME *prg,float valeur) //affecte valeur dans le champ T du programme
{
    prg->T=valeur;
}
void aff_valC(PROGRAMME *prg,float valeur) //affecte valeur dans le champ C du programme
{
    prg->C=valeur;
}
void aff_valF(PROGRAMME *prg,float valeur) //affecte valeur dans le champ F du programme
{
    prg->F=valeur;
}
void aff_valM(PROGRAMME *prg,float valeur)//affecte valeur dans le champ M du programme
{
    prg->M=valeur;
}
void aff_nomP(PROGRAMME *prg,char nom[]) //Remplir le champ NOM du programme prg
{
    strcpy(prg->NOM,nom);
}
/*-------------------Affichage des valeurs T,C,F et le nom du programme---------------------*/
float valeurT(PROGRAMME *prg) //retourne la valeur stockée dans le champ T(temps d'execution) du programme prg
{
    return(prg->T);
}
float valeurC(PROGRAMME *prg) //retourne la valeur stockée dans le champ C(taux de Consommation des ressources) du programme prg
{
    return(prg->C);
}
float valeurF(PROGRAMME *prg) //retourne la valeur stockée dans le champ F(taux de fiabilité) du programme prg
{
    return(prg->F);
}
float valeurM(PROGRAMME *prg)//retourne la valeur stockée dans le champ M(Moyenne) du programme prg
{
    return(prg->M);
}
void nom_prg(PROGRAMME *prg,char nom[])
{
    strcpy(nom,prg->NOM);
}
PROGRAMME *suivant(PROGRAMME *prg) //retourne l'adresse du programme suivant (dans la meme tache)
{
    return(prg->Suiv);
}
PROGRAMME *precedent(Tache *T,PROGRAMME *prg)//retourne l'adresse du programme qui précède prg dans la Tache T
{
    PROGRAMME *P,*Q;//P pointeur vers le programme précédent
    Q=T->tete;
    P=NULL;
    while(Q!=NULL && Q!=prg)
    {
        P=Q;
        Q=suivant(Q);
    }
    return(P);

}
/*-------------------------------------Tache----------------------------------*/
void aff_adrT(Tache *t1,Tache *t2) //affecter l'adresse de la tache (t2) au champ adresse de la tache t1
{
    t1->tachesuiv=t2;
}
void aff_nomT(Tache *tache,char nom[]) //Remplir le champ NOMTACHE de la tache
{
    strcpy(tache->NOMTACHE,nom);
}
Tache *suivantT(Tache *T)//retourne l'adresse de la tache suivante (dans le meme Processus)
{
    return(T->tachesuiv);
}
/*--------------------------------------les modules d'ajout-------------------*/
void ajouter_programme(Tache *tache,PROGRAMME *prg)//ajouter le programme prg à la tache (à la dernière position)
{
     if (tache->tete==NULL)//la tache est vide
             tache->tete=prg;
     else
    aff_adr(tache->queue,prg);
    tache->queue=prg;
}
void ajouter_tache(PROCESSUS *process,Tache *T)//ajouter une tache T à un processus
{
aff_adrT(T,NULL);
if(process->tete==NULL)
    process->tete=T;
else
aff_adrT(process->queue,T);
process->queue=T;
}
void inserer_PRG(PROGRAMME **tete,PROGRAMME *prg)//inserer le programme prg dans la liste des programme (tete)
{   //l'insertion se fait au début de la liste
    if(*tete!=NULL)//la liste n'est pas vide
    aff_adr(prg,*tete);
    *tete=prg;

}
/*--------------------------------------Les modules de suppression---------------------------------------*/
void libererT(Tache *T)//supprimer tout les programmes de la tache T
{
    PROGRAMME *PRG1,*PRG2;
    PRG1=T->tete;
    while(PRG1!=NULL)
    {   PRG2=PRG1;
        PRG1=suivant(PRG1);
        free(PRG2);
    }
    T->tete=NULL;T->queue=NULL;
}
void liberer(Tache *T,PROGRAMME *prg)//éliminer le programme prg de la tache T
{
    if(prg==T->tete)//1er programme de la tache
     T->tete=suivant(prg);
    else
    {
        if(prg==T->queue)//dernier programme de la tache
        {
            T->queue=precedent(T,prg);
        }
        aff_adr(precedent(T,prg),suivant(prg));
    }
free(prg);
}
void creer_programme2(PROGRAMME *PRG)
{   float temp,f,c;
    int i;
    char NOMPRG[40]="",car='m';//car est pour regler le probleme de lecture avec scanf


        printf("Entrez le nom du programme:");
        gets(NOMPRG);
        aff_nomP(PRG,NOMPRG);
        printf("%s \n",PRG->NOM);
        printf("Entrez la valeur de T :");
        scanf("%f",&temp);car=getchar();while(car!='\n');car='m';
        aff_valT(PRG,temp);
        printf("Entrez la valeur de C :");
        scanf("%f",&c);car=getchar();while(car!='\n');car='m';
        aff_valC(PRG,c);
        printf("Entrez la valeur de F :");
        scanf("%f",&f); car=getchar();while(car!='\n');car='m';
        aff_valF(PRG,f);
}
void ajouter_tache2(PROCESSUS *process,Tache *T)//ajouter la Tache T à process,les données sont lues à partir de l'utilisateur
{
    int i,NBPRG;
    float temp,f,c;
    PROGRAMME *PRG;
    char Nomtache[10]="",NOMPRG[40]="",car='m';//car est pour regler le probleme de lecture avec scanf
    printf("Entrez le nom de Tache : ");
    scanf("%s",Nomtache);
    aff_nomT(T,Nomtache);
    printf("Entrez le nombre de programme : ");
    scanf("%d",&NBPRG); car=getchar();while(car!='\n');car='m';
    for(i=0;i<NBPRG;i++)//lire les programmes de la tache
    {
        creer_programme(&PRG);
        printf("Entrez le nom du programme %d :",i+1);
        gets(NOMPRG);
        aff_nomP(PRG,NOMPRG);
        printf("%s \n",PRG->NOM);
        printf("Entrez la valeur de T :");
        scanf("%f",&temp);car=getchar();while(car!='\n');car='m';
        aff_valT(PRG,temp);
        printf("Entrez la valeur de C :");
        scanf("%f",&c);car=getchar();while(car!='\n');car='m';
        aff_valC(PRG,c);
        printf("Entrez la valeur de F :");
        scanf("%f",&f); car=getchar();while(car!='\n');car='m';
        aff_valF(PRG,f);
        ajouter_programme(T,PRG);
    }
ajouter_tache(process,T);

}
void creer_tache2(Tache *T)//creer une tache dont les données sont lues à partir de l'utilisateur
{
    int i,NBPRG;
    float temp,f,c;
    PROGRAMME *PRG;
    char Nomtache[10]="",NOMPRG[40]="",car='m';//car est pour regler le probleme de lecture avec scanf
    printf("Entrez le nom de Tache : ");
    scanf("%s",Nomtache);
    aff_nomT(T,Nomtache);
    printf("Entrez le nombre de programme : ");
    scanf("%d",&NBPRG); car=getchar();while(car!='\n');car='m';
    for(i=0;i<NBPRG;i++)//lire les programmes de la tache
    {
        creer_programme(&PRG);
        printf("Entrez le nom du programme %d :",i+1);
        gets(NOMPRG);
        aff_nomP(PRG,NOMPRG);
        printf("%s \n",PRG->NOM);
        printf("Entrez la valeur de T :");
        scanf("%f",&temp);car=getchar();while(car!='\n');car='m';
        aff_valT(PRG,temp);
        printf("Entrez la valeur de C :");
        scanf("%f",&c);car=getchar();while(car!='\n');car='m';
        aff_valC(PRG,c);
        printf("Entrez la valeur de F :");
        scanf("%f",&f); car=getchar();while(car!='\n');car='m';
        aff_valF(PRG,f);
        ajouter_programme(T,PRG);
    }
}
/*--------------------------------------Le Module de Remplissage---------------------------------------*/
void Remp_processus(PROCESSUS *process,FILE *F)//remplir le processus process à partir du fichier F
{
    float temp,c,f;
    char Nomtache[8]="",NOMPRG[6]="",car='m';
    Tache *T;
    PROGRAMME *PRG;
    while(!feof(F))
{
    creer_tache(&T);T->queue=NULL;T->tete=NULL;
    fscanf(F,"%s",Nomtache);
    aff_nomT(T,Nomtache);
    while(car!='!')
    {
        creer_programme(&PRG);
        fscanf(F,"%s",NOMPRG);
        aff_nomP(PRG,NOMPRG);
        fscanf(F,"%f",&temp);
        aff_valT(PRG,temp);
        fscanf(F,"%f",&c);
        aff_valC(PRG,c);
        fscanf(F,"%f",&f);
        aff_valF(PRG,f);
        car=fgetc(F);
       ajouter_programme(T,PRG);
    }
    car=fgetc(F);
    ajouter_tache(process,T);
}
}
void Remp_TM(Tache *T,float w1,float w2)//Remplit les champs M des programmes de la tache T
{
PROGRAMME *PRG;
PRG=T->tete;
while(PRG!=NULL)
{
    aff_valM(PRG,valeurT(PRG)*w1+valeurC(PRG)*w2+valeurF(PRG)*(100-w1-w2));
    PRG=suivant(PRG);
}
}
/*------------------------------Les modules d'affichage---------------------------*/
void affich_processus(PROCESSUS *process)//afficher le contenu de process
{
    Tache *T;
    PROGRAMME *PRG;
    T=(process->tete);
while(T!=NULL)
{
    printf("\n %s : ",T->NOMTACHE);
    PRG=(T->tete);
    while(PRG!=NULL)
    {
        printf("%s (%.2f,%.2f,%.2f); ",PRG->NOM,valeurT(PRG),valeurC(PRG),valeurF(PRG));
        PRG=suivant(PRG);
    }
    T=suivantT(T);
}
}
void affich_prg(PROGRAMME *PRG)//afficher le programme PRG
{
    printf("%s (%.2f,%.2f,%.2f)",PRG->NOM,valeurT(PRG),valeurC(PRG),valeurF(PRG));
}
void affich_tache(Tache *T)//afficher la Tache T
{
    PROGRAMME *PRG;
    PRG=T->tete;
    while(PRG!=NULL)
    {
        printf("\n %s : ",T->NOMTACHE);
    PRG=(T->tete);
    while(PRG!=NULL)
    {
        printf("%s (%.2f,%.2f,%.2f); ",PRG->NOM,valeurT(PRG),valeurC(PRG),valeurF(PRG));
        PRG=suivant(PRG);
    }
    }
}
/*----------------------------------Le module de dominance---------------------*/
PROGRAMME *dominer(Tache *T,PROGRAMME *prg1,PROGRAMME *prg2)//retourne l'adresse du programme qui domine l'autre et ajoute programme dominé dans la liste des programme dominé (tete)
{
/*if((valeurT(prg1)==valeurT(prg2))&&(valeurC(prg1)==valeurC(prg2))&&(valeurF(prg1)==valeurF(prg2)))
    return(NULL);*/
if (prg1==prg2)
return(NULL);
else
{

if (valeurT(prg1)<=valeurT(prg2))
{
    if (valeurC(prg1)<=valeurC(prg2))
    {
        if (valeurF(prg1)>=valeurF(prg2))
            {
              return(prg1);
            }
        else
            return(NULL);
    }
    else
    {
        if (valeurF(prg1)>=valeurF(prg2))
            {
              return(prg1);
            }
        else
            {
              return(prg2);
            }
    }
}
else
{
     if (valeurC(prg1)<=valeurC(prg2))
    {
        if (valeurF(prg1)>=valeurF(prg2))
            {
              return(NULL);
            }
        else
           return(prg2);
    }
    else
    {
        if (valeurF(prg1)>=valeurF(prg2))
            {
              return(prg2);
            }
        else
            {
              return(prg1);
            }
    }
}
}
}
PROGRAMME *dominer1(PROGRAMME *prg1,PROGRAMME *prg2)//retourne l'adresse du programme qui domine l'autre
{

if (valeurT(prg1)<=valeurT(prg2))
{
    if (valeurC(prg1)<=valeurC(prg2))
    {
        if (valeurF(prg1)>=valeurF(prg2))
            {
              return(prg1);
            }
        else
            return(NULL);
    }
    else
    {
        if (valeurF(prg1)>=valeurF(prg2))
            {
              return(prg1);
            }
        else
            {
              return(prg2);
            }
    }
}
else
{
     if (valeurC(prg1)<=valeurC(prg2))
    {
        if (valeurF(prg1)>=valeurF(prg2))
            {
              return(NULL);
            }
        else
           return(prg2);
    }
    else
    {
        if (valeurF(prg1)>=valeurF(prg2))
            {
              return(prg2);
            }
        else
            {
              return(prg1);
            }
    }
}

}
/*------------------------------Les modules d'élimination-------------------------------*/
void eliminer_candTf(Tache *T)//éliminer les programmes dominés dans la meme tache T
{
        PROGRAMME *PRG,*PRGdomin,*sauv;//PRGdomin est un pointeur vers le dernier programe dominant
        PRGdomin=sauv=T->tete;
        PRG=suivant(PRGdomin);

        while (PRG!=NULL)
        {
            PRGdomin=dominer(T,PRGdomin,PRG);
            /*------éléminer le programme dominé------*/
            if(PRGdomin==sauv)//PRG est dominé par sauv
                 liberer(T,PRG);
            if(PRGdomin==PRG)//sauv est dominé par PRG
                liberer(T,sauv);
            /*----------------------------------------*/

            if(PRGdomin==NULL)
            {
                PRGdomin=PRG;
               PRG=suivant(PRG);
            }

            else
            PRG=suivant(PRGdomin);

            sauv=PRGdomin;
        }
}
void eliminer_candT(Tache *T)//éliminer les programmes dominés dans la meme tache T
{
        PROGRAMME *PRG1,*PRG2,*PRGdomin,*sauv=NULL;//PRGdomin est un pointeur vers le dernier programe dominant
        PRG1=T->tete;
        int continuer=1;
        while (PRG1!=NULL)
        {   PRG2=T->tete;
            continuer=1;
            while ((PRG2!=NULL)&& continuer)
            {
            PRGdomin=dominer(T,PRG1,PRG2);
            /*------éléminer le programme dominé------*/


           if(PRGdomin==PRG1) //PRG2 est dominé par prg1
           {    sauv=suivant(PRG2);
               liberer(T,PRG2);
           }

            else
            {   if(PRGdomin==PRG2) //PRG1 est dominé par PRG2
                {
                sauv=suivant(PRG1);
                continuer=0;
                liberer(T,PRG1);
                PRG1=sauv;
                }
            }
            /*----------------------------------------*/
                if(sauv==NULL)
                    PRG2=suivant(PRG2);
                else
                    PRG2=sauv;
          sauv=NULL;
        //printf("\n %p",PRGdomin);affich_tache(T);printf("\n");system("pause");
        }
        if(continuer)//PRG1 n'est pas dominé
        PRG1=suivant(PRG1);
        }
}
void eliminer_candP(PROCESSUS *process)//éliminer les programmes dominés dans le processus
{

    Tache *T;
    T=process->tete;
    while (T!=NULL)
    {
        eliminer_candT(T);

    T=suivantT(T);
    }
}
/*---------------------------------------Les modules de combinaison--------------------------*/
float max(float a,float b)//retourne le max entre a et b
{
    if(a>=b)
        return(a);
    else
        return(b);
}
float moyenne(float a,float b)//calcule la moyenne
{
    return((a+b)/2);
}

void combiner(Tache *T1,Tache *T2,Tache *T3)//combine les programmes de la Tache T1 et T2 et mettre les nouveaux programmes dans la tache T3
{   char NOMPRG[50]="",Nomtache[50]="";//va contenir le Nom du nouveau programme
    PROGRAMME *PRG1,*PRG2,*PRG3;
    strcat(Nomtache,T1->NOMTACHE);strcat(Nomtache,"#");strcat(Nomtache,T2->NOMTACHE);aff_nomT(T3,Nomtache);strcpy(Nomtache,"");//modifier le nom de la tache
    PRG1=T1->tete;//1 er programme de la tache T1
    if (T2==NULL)//N=1 cas particulier
    {
        while (PRG1!=NULL)
        {
        creer_programme(&PRG3);
        strcat(NOMPRG,PRG1->NOM);//strcat(NOMPRG,",");strcat(NOMPRG,PRG2->NOM);
        aff_nomP(PRG3,NOMPRG);
        strcpy(NOMPRG,"");
        aff_valT(PRG3,valeurT(PRG1));
        aff_valC(PRG3,valeurC(PRG1));
        aff_valF(PRG3,valeurF(PRG1));
        ajouter_programme(T3,PRG3);
        PRG1=suivant(PRG1);
        }
    }
    else //N<>1
    {
     PRG2=T2->tete;
    while(PRG1!=NULL && PRG2!=NULL)
    {
        while (PRG2!=NULL)
        {
        creer_programme(&PRG3);
        strcat(NOMPRG,PRG1->NOM);strcat(NOMPRG,",");strcat(NOMPRG,PRG2->NOM);
        aff_nomP(PRG3,NOMPRG);
        strcpy(NOMPRG,"");

        aff_valT(PRG3,valeurT(PRG1)+valeurT(PRG2));
        aff_valC(PRG3,max(valeurC(PRG1),valeurC(PRG2)));
        aff_valF(PRG3,moyenne(valeurF(PRG1),valeurF(PRG2)));

        ajouter_programme(T3,PRG3);
        PRG2=suivant(PRG2);
        }
        PRG2=T2->tete;
        PRG1=suivant(PRG1);

    }
}
}
void combiner_process(PROCESSUS *process,Tache **T3)//combine tout les programmes du processus et il met toutes les solutions potentielles dans la tache T3
{
    Tache *T1,*T2,*T4;//T1 et T2 serviront pour le parcours du processus

    char Nomtache[50]="";
    int cpt=1;
    T1=process->tete;//premier tache du processus
    T2=suivantT(T1);
    creer_tache(&T4);T4->queue=NULL;T4->tete=NULL;aff_nomT(T4,"TACHEF");//création d'une Tache
    if (T1!=NULL)
    {
        while (T2!=NULL)
        {
            combiner(T1,T2,*T3);
            strcat(Nomtache,T1->NOMTACHE);strcat(Nomtache,"#");strcat(Nomtache,T2->NOMTACHE);aff_nomT(*T3,Nomtache);strcpy(Nomtache,"");//modifier le nom de la tache
            printf("\n Affichage de la Tache aprés la combinaison et avant l'elimination des programmes dominés \n");
            affich_tache(*T3);
            eliminer_candT(*T3);//éliminer tout les programmes dominés dans la tache T3
            printf("\n Affichage de la Tache apres l'elimination des programmes dominés \n");
            affich_tache(*T3);
            T1=*T3;
            libererT(T4);
            *T3=T4;
            cpt++;
            T2=suivantT(T2);
            if (cpt==2)
            {
               T4=T1;cpt=1;
            }

        }
    *T3=T1;
    }
    else
        printf("ERRREUR");
}
/*---------------------------------------------Les modules de tri-------------------------------*/
void permuter(Tache *T,PROGRAMME *prg1,PROGRAMME *prg2)//permute prg1 avec prg2 dans la tache T
{   PROGRAMME *sauv;
    if(prg1!=NULL && prg2!=NULL)
    {
        if(prg2==T->queue)
                T->queue=prg1;
            aff_adr(precedent(T,prg2),prg1);
            sauv=suivant(prg1);
            aff_adr(prg1,suivant(prg2));
            aff_adr(prg2,sauv);
        if(prg1==T->tete)//prg1 est le premier programme de la Tache
           T->tete=prg2;//prg2 devient le 1er programme de la tache
        else
       aff_adr(precedent(T,prg1),prg2);
    }
    else
        printf("Erreur");
}
void tri_prg(Tache *T,float w1,float w2)//Trie les solutions potentielles en utilisant le principe du tri à bulles
{
PROGRAMME *PRG;
int permut=1;
PRG=T->tete;

if (PRG!=NULL)
{
  while(suivant(PRG)!=NULL && permut)
  { permut=0;
      if(valeurM(PRG)<valeurM(suivant(PRG)))
      {
          permuter(T,PRG,suivant(PRG));permut=1;
      }
       if(suivant(PRG)==NULL)
        PRG=T->tete;

  }
}
else printf("Erreur");

}
/*-----Tp réalisé par Brahim_Yacine-------*/
