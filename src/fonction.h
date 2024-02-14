#ifndef fonction_H_
#define fonction_H_
#include <string.h>
#include <gtk/gtk.h>

typedef struct
{
char identifiant[20] ;
int  nle;
char nbv[20];
char categorie [20];
char reclamation [100];
}reclamation;

void ajouter(reclamation rec,int categorie);
void afficher_rec (GtkWidget *liste) ;

#endif
