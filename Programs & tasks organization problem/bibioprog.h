#ifndef BIBIOPROG_H_INCLUDED
#define BIBIOPROG_H_INCLUDED
typedef struct PROCESSUS PROCESSUS;
typedef struct PROGRAMME PROGRAMME;
typedef struct Tache Tache;

/*--------------Les structures--------------*/
struct PROGRAMME
{
    float T,C,F,M;//T:temp d'execution,C:taux de Consommation des ressources,F:Fiabilit�,M:ce champ servira pour le tri des programme � la fin
    char NOM[50];
    PROGRAMME *Suiv;
};
struct Tache
{
    PROGRAMME *tete;//pointeur vers le premier promgramme de la tache
    PROGRAMME *queue;//pointeur vers le dernier promgramme de la tache
    char NOMTACHE[50];//le nom de la tache
    Tache *tachesuiv;//pointeur vers le tache suivante dans le processus
};
struct PROCESSUS
{
    Tache *tete;
    Tache *queue;
};
/*----------------------------Les Modules----------------*/
/*--------------------Les modules de cr�ation ------------------------*/
void creer_processus(PROCESSUS **process);//process est un pointeur vers la structure PROCESSUS
void creer_tache(Tache **T);//T est un pointeur vers la structure Tache
void creer_programme(PROGRAMME **prg); //prg est un pointeur vers la structure PROGRAMME
/*------------------------La Machine ------------------*/
/*--------------- --------Programme-------------------------*/
void aff_adr(PROGRAMME *prg,PROGRAMME *prg2);//affecter l'adresse du programme (prg2) au champ adresse du programme prg
void aff_valT(PROGRAMME *prg,float valeur); //affecte valeur dans le champ T du programme
void aff_valC(PROGRAMME *prg,float valeur); //affecte valeur dans le champ C du programme
void aff_valF(PROGRAMME *prg,float valeur); //affecte valeur dans le champ F du programme
void aff_valM(PROGRAMME *prg,float valeur);//affecte valeur dans le champ M du programme
void aff_nomP(PROGRAMME *prg,char nom[]); //Remplir le champ NOM du programme prg
/*-------------------Affichage des valeurs T,C,F et le nom du programme---------------------*/
float valeurT(PROGRAMME *prg);//retourne la valeur stock�e dans le champ T(temps d'execution) du programme prg
float valeurC(PROGRAMME *prg); //retourne la valeur stock�e dans le champ C(Complexit�) du programme prg
float valeurF(PROGRAMME *prg);//retourne la valeur stock�e dans le champ F(taux de fiabilit�) du programme prg
float valeurM(PROGRAMME *prg);//retourne la valeur stock�e dans le champ M(Moyenne) du programme prg
void nom_prg(PROGRAMME *prg,char nom[]);//r�cup�rer le nom du programme dans la chaine nom
PROGRAMME *suivant(PROGRAMME *prg);//retourne l'adresse du programme suivant (dans la meme tache)
PROGRAMME *precedent(Tache *T,PROGRAMME *prg);//retourne l'adresse du programme qui pr�c�de prg dans la Tache T
/*-------------------------------------Tache----------------------------------*/
void aff_adrT(Tache *t1,Tache *t2);//affecter l'adresse de la tache (t2) au champ adresse de la tache t1
void aff_nomT(Tache *tache,char nom[]); //Remplir le champ NOMTACHE de la tache
Tache *suivantT(Tache *T);//retourne l'adresse de la tache suivante (dans le meme Processus)
/*--------------------------------------les modules d'ajout-------------------*/
void ajouter_programme(Tache *tache,PROGRAMME *prg);//ajouter le programme prg � la tache (� la derni�re position)
void ajouter_tache(PROCESSUS *process,Tache *T);//ajouter une tache T � un processus
void inserer_PRG(PROGRAMME **tete,PROGRAMME *prg);//inserer le programme prg dans la liste des programme (tete)
void creer_programme2(PROGRAMME *PRG);//creer un programme dont les donn�es sont lues � partir du clavier
void ajouter_tache2(PROCESSUS *process,Tache *T);//ajouter la Tache T � process,les donn�es sont lues � partir de l'utilisateur
void creer_tache2(Tache *T);//creer une tache dont les donn�es sont lues � partir de l'utilisateur
/*--------------------------------------Les modules de suppression---------------------------------------*/
void libererT(Tache *T);//supprimer tout les programmes de la tache T
void liberer(Tache *T,PROGRAMME *prg);//�liminer le programme prg de la tache T
/*--------------------------------------Le Module de Remplissage---------------------------------------*/
void Remp_processus(PROCESSUS *process,FILE *F);//remplir le processus process � partir du fichier F
void Remp_TM(Tache *T,float w1,float w2);//Remplit les champs M des programmes de la tache T
/*------------------------------Les modules d'affichage---------------------------*/
void affich_processus(PROCESSUS *process);//afficher le contenu de process
void affich_prg(PROGRAMME *PRG);//afficher le programme PRG
void affich_tache(Tache *T);//afficher la Tache T
/*----------------------------------Le module de dominance---------------------*/
PROGRAMME *dominer(Tache *T,PROGRAMME *prg1,PROGRAMME *prg2);//retourne l'adresse du programme qui domine l'autre et ajoute programme domin� dans la liste des programme domin� (tete)
/*------------------------------Les modules d'�limination-------------------------------*/
void eliminer_candTf(Tache *T);//�liminer les programmes domin�s dans la meme tache T
void eliminer_candT(Tache *T);//�liminer les programmes domin�s dans la meme tache T
void eliminer_candP(PROCESSUS *process);//�liminer les programmes domin�s dans le processus
/*---------------------------------------Les modules de combinaison--------------------------*/
float max(float a,float b);//retourne le max entre a et b
float moyenne(float a,float b);//calcule la moyenne
void combiner(Tache *T1,Tache *T2,Tache *T3);//combine les programmes de la Tache T1 et T2 et mettre les nouveaux programmes dans la tache T3
void combiner_process(PROCESSUS *process,Tache **T3);//combine tout les programmes du processus et il met toutes les solutions potentielles dans la tache T3
/*---------------------------------------------Les modules de tri-------------------------------*/
void permuter(Tache *T,PROGRAMME *prg1,PROGRAMME *prg2);//permute prg1 avec prg2 dans la tache T
void tri_prg(Tache *T,float w1,float w2);//Trie les solutions potentielles en utilisant le principe du tri � bulles
/*-----Tp r�alis� par Brahim_Yacine-------*/
#endif // FONCTIONS_H_INCLUDED
