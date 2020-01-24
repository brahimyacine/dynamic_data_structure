#include <stdio.h>
#include <stdlib.h>
int factoriel(int n)
{ //Calculate n!
    if (n ==1)
            return n;
    else
        return n * factoriel(n-1);
}

int fibonacci(int n)
{
    if (n == 0 || n == 1)
            return n;
    else
        return fibonacci(n-1) + fibonacci(n-2);
}

int reste (int a, int b)
{
    if (a<b) return a;
    else
        return reste(a-b,b);
}

int PGCD (int a, int b)
{
    if (reste(a,b)==0) return b;
    else
        return PGCD(b,reste(a,b));
}

int multiply(int a, int b)
{
    if (b==0) return 0;
    else
        return multiply(a,b-1)+a;
}

int power(int a, int b)
{
    if (b==0) return 1;
    else
        return a*pow(a,b-1);
}

int quotient (int a, int b)
{
    if (a<b) return 0;
    else
        return quotient(a-b,b)+1;
}

const ma=100; // maximum size of the array
void read_array(int n, int tab[ma]  )
{ int i;

     for (i=0; i<n; i++)
     {
         printf (" Veuillez introduire la valeur %d :",i+1);
         scanf ("%d",&tab[i]);
     }
}
void print_array (int n, int tab[ma])
{
   int i;
   for (i=0;i<n;i++)
   {
       printf("%d | ",tab[i]);
   }
}

int dichotomic_search(int tab[ma],int x, int inf, int sup)
{int milieu;
     if (inf > sup) return -1;
     else
     {
         milieu= ((inf+sup)/2);
         if (x==tab[milieu]) {
                printf("%d found at the position %d",x,milieu);return milieu;}
         else {
                if (x< tab[milieu]) return dichotomic_search(tab,x,inf,milieu-1);
                else {
                        return dichotomic_search(tab,x,milieu+1,sup);
     }}
     }
}
int main ()
{    int x, inf,sup;
     int tab[ma];
     int n;
     printf("Entrez la taille du tableau (Array size): ");
     scanf("%d",&n);
     read_array(n,tab);
     print_array(n,tab);
     inf=0;
     sup=n-1;
     printf ("\nVeuillez introduire le nombre que vous cherchez : ");
     scanf("%d",&x);

dichotomic_search(tab,x,inf,sup);
}
