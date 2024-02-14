#include<gtk/gtk.h>


typedef struct
{
    int jour;
    int mois;
    int annee;
}DATE;


typedef struct
{
    char identifiant[20];
    DATE date;
    char gouvernorat[30];
    char municipalite[30];
    char nbhabit[50];
    int nbcons ;


}election;
typedef struct
{
    char cin[20];
    char nom[20];
    char prenom[20];
    char genre[10];	
    DATE date;
    char login[30];
    char motpasse[30];
    char role[50];
    int vote;
    char numerobureau[20];			

}Utilisateur;

void ajouter_election(election e);
void afficher_election(GtkWidget *liste);
void modifier_election(char identifiant[],election e1,char *election);
void supprimer_election(char id []);
int rechercher_election(char id[]);
void afficher_rechercher_election(GtkWidget *liste);
int TPE(char*file);
void TPHF(char*file,char*h,char*f);






