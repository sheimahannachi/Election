#ifndef IHEBPROJECCCCT_H_INCLUDED
#define IHEBPROJECCCCT_H_INCLUDED
#include <stdio.h>
#include <gtk/gtk.h>
typedef struct {
int jour, annee;
char mois[20];
}Date_bv;
typedef struct {
  char numerodebureau [50];	
  char id[20];  
  char capacite[50];
	Date_bv d;
	
	

}	bureaudevote ;
////
typedef struct{
 int j;
 int m;
 int a;

}datee ;

typedef struct{
char nom[20];
char prenom[20];
datee d;
char cin[20];
int role;
int genre;
int num_bureau_vote;
int vote;
int nationalite;
char profess[20];
char appartenance_politique[20];
}utilisateurs;

void afficher_bureau(GtkWidget *liste );

void ajout_bureau(bureaudevote bv);

void rechercher_bureau(GtkWidget *liste,char ch[30] );

void modifier_bv(bureaudevote bv);
void supprimer_bv(char *id);
int veridId_bv(char *id);

void taux (float *te,float *tn);

int cond_gagn();
void afficher_candidat_gagnant(GtkWidget *liste );

#endif // IHEBPROJECCCCT_H_INCLUDED
