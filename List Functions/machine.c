#include"utils.h"
#include <stdio.h>
#include <stdlib.h>
#include<math.h>
typedef int typeqq;
typedef struct Tmaillon Tmaillon;
typeqq valeur(Tmaillon *p)
{
    return(p->Val);
}
Tmaillon *suivant(Tmaillon *p)
{
    return(p->suiv);
}
void allouer(Tmaillon **p)
{
   *p=(Tmaillon *)malloc(sizeof(Tmaillon));

}
void aff_val(Tmaillon *p,typeqq v)
{
     (p->Val)=v;
}
void aff_adr(Tmaillon *p,Tmaillon *q)
{
    p->suiv=q;
}
void liberer(Tmaillon *tete)
{
    Tmaillon *p,*q;
    p=tete;
    while(p!=NULL)
    {
        q=suivant(p);
        free(p);
        p=q;
    }
}
void construire_llc(Tmaillon **tete,int *llength)
{
    int n,x,i =0;
    Tmaillon *p,*q;
    printf("Entrez la taille de la liste: ");
    scanf("%d",&n);
    *tete=NULL;
    *llength=0;
    srand(time(NULL));

    while(n>=1)
    {   //x=rand()%5;
        allouer(&p);
        (*llength)++;
        printf("Val %d: ",i);
        i++;
        scanf("%d",&x);
        while(getchar()!='\n');
        aff_val(p,x);
        if(*tete==NULL)
            *tete=p;
        else
           aff_adr(q,p);
        q=p;
        n--;
    }
    aff_adr(p,NULL);
}
int frequence(Tmaillon *tete,int nb)
{   Tmaillon *p;
    int freq=0;
    p=tete;
    while(p!=NULL)
    {
        if (valeur(p)==nb)
            freq++;
        p=suivant(p);
    }
    return(freq);
}
int max_freq(Tmaillon *tete,int *occ)
{   Tmaillon *p;
    int freq,maxfreq=0,nbh;
    p=tete;
    *occ=frequence(p,valeur(p));
    while(p!=NULL)
    {
        freq=frequence(tete,valeur(p));
        if (freq>maxfreq)
        {
            nbh=valeur(p);
            maxfreq=freq;
        }
        p=suivant(p);
    }
    *occ=maxfreq;
    return(nbh);
}
int longueur (Tmaillon *tete)
 {  int length=0;
     Tmaillon *p;
     p=tete;
     while(p!=NULL)
     {   length++;
         p=suivant(p);
     }
     return(length);
 }
Tmaillon *acces_val_llc(Tmaillon *tete,int val,Tmaillon **precedent)
{
    Tmaillon *p,*q;
    p=tete;
    *precedent=NULL;
    while((p!=NULL)&&(valeur(p)!=val))
    {
        *precedent=p;
        p=suivant(p);
    }
    if (p==NULL)
    {
        printf("la valeur recherchée n'est pas dans la liste ::");
        return(NULL);
    }
    else
        return(p);
}
Tmaillon *acces_pos_llc(Tmaillon *tete,int pos,Tmaillon **precedent)
{
    Tmaillon *p;
    int cpt=1;
    p=tete;
    while((p!=NULL)&&(cpt!=pos))
    {   *precedent=p;
        p=suivant(p);
        cpt++;
    }
    if(p==NULL)
    {
        return(NULL);
    }
    else
        return(p);
}
 void sup_val(Tmaillon **tete,int val)
 {
     Tmaillon *p,*q;
     p=*tete;
     if(valeur(tete)==val)
     {
         *tete=suivant(tete);
         free(p);
     }
     else
     {
         while((p!=NULL)&&(valeur(p)!=val))
         {
             q=p;
             p=suivant(p);
         }
         aff_adr(q,suivant(p));
         free(p);
     }
 }
void sup_val2(Tmaillon **tete,int val)
{
    Tmaillon *p,*q;
    p=*tete;
    while(p!=NULL)
    {
        if(valeur(tete)==val)
        {
            *tete=suivant(*tete);
            free(p);
            p=tete;
        }
        else
        {
            if(valeur(p)==val)
            {
                aff_adr(q,suivant(p));
                free(p);
                p=suivant(q);
            }
            else
            {
                q=p;
                p=suivant(p);
            }
        }
    }
}
void inserer(Tmaillon **tete,int pos,int val)
{
    Tmaillon *p,*q,*r;
    allouer(&p);
    aff_val(p,val);
    if (pos!=1)
    {
        r=acces_pos_llc(*tete,pos,&q);
        aff_adr(p,r);
        aff_adr(q,p);
    }
   else
   {
       aff_adr(p,*tete);
       *tete=p;
   }

}
void sup_pos(Tmaillon **tete,int position)
{
    Tmaillon *p,*q;
    if (position<=longueur(*tete))
    {
        if(position==1)
        {
            p=*tete;
            *tete=suivant(*tete);

        }
        else
        {
            p=acces_pos_llc(*tete,position,&q);

            aff_adr(q,suivant(p));
        }
        free(p);
    }
    else
        printf("permission denied");

}
void interclass_llc(Tmaillon *tete1,Tmaillon *tete2,Tmaillon **tete3)
{
    Tmaillon *p1,*p2,*p3,*q3,*q4;
    p1=tete1;p2=tete2;*tete3=NULL;q3=NULL;
    while (p1!=NULL && p2!=NULL)
    {
        allouer(&p3);
        if(*tete3==NULL) //1ere fois
        {
           *tete3=p3;
           q3=p3;
        }
        else
        {
            aff_adr(q3,p3);
            q3=p3;
        }
        if(valeur(p1)<valeur(p2))
        {
            aff_val(p3,valeur(p1));
            p1=suivant(p1);
        }
        else
        {
            if(valeur(p1)==valeur(p2))
            {
                aff_val(p3,valeur(p1));
                allouer(&q4);
                aff_adr(p3,q4);
                aff_val(q4,valeur(p1));
                q3=q4;
                p1=suivant(p1);
                p2=suivant(p2);
            }
            else
            {
                aff_val(p3,valeur(p2));
                p2=suivant(p2);
            }
        }
    }
    while(p1!=NULL)
    {
        q3=p3;
        allouer(&p3);
        aff_adr(q3,p3);
        aff_val(p3,valeur(p1));
        p1=suivant(p1);
    }
    while(p2!=NULL)
    {
        q3=p3;
        allouer(&p3);
        aff_adr(q3,p3);
        aff_val(p3,valeur(p2));
        p2=suivant(p2);
    }
}

void interclass(Tmaillon *t1,Tmaillon *t2,Tmaillon **t3)
{
    Tmaillon *q;
    if(valeur(t1)<valeur(t2))
    {
        *t3=t1;
        t1=suivant(t1);
    }
    else{
        *t3=t2;
        t2=suivant(t2);
    }
    q=*t3;
    while(t1!=NULL && t2!=NULL)
    {
        if(valeur(t1)<valeur(t2))
        {
            aff_adr(q,t1);
            q=t1;
            t1=suivant(t1);
        }
        else
        {
            aff_adr(q,t2);
            q=t2;
            t2=suivant(t2);
        }
    }
    if(t1!=NULL)
        aff_adr(q,t1);
    else
        aff_adr(q,t2);
}

void print_llc(Tmaillon *tete)
{ //print the list
    while(tete!=NULL)
    {
        printf("%d  ",valeur(tete));
        tete=suivant(tete);
    }
}
void invert_llc(Tmaillon **tete,Tmaillon **p,Tmaillon **q,Tmaillon **s,int n)
{
   // Recursive function to invert a linear list
    if(n==2)//cas particulier
    {
        *p=suivant(*tete);
        aff_adr(*tete,suivant(*p));
        aff_adr(*p,*tete);
        *q=*tete;*tete=*p;
    }
    else
    {   system("pause");
        invert_llc(&tete,&p,&q,&s,n-1);
        *s=suivant(*q);printf("koko");
        system("pause");printf("s \n");
        aff_adr(*q,suivant(*s));
        system("pause");printf("q,suivant(s) \n");
        aff_adr(*s,*tete);
        system("pause");printf("s,tete \n");
        *tete=*s;
    }
}
