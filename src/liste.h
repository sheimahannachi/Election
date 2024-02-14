#include <stdio.h>
#include <string.h>

typedef struct
{
	int jour;
	int mois;
	int annee;

} date_liste;

typedef struct 
{
	char nom_liste[50];
	int id_liste;
	char id_tete_liste[10];
	int nombre_condidat;
	date_liste date;
	int nbr_vote;
} liste;

void ajouter_liste(liste l);
int modif_liste( int id, liste nouv );
liste recherche_liste(char nom[]) ;
int supprime_liste(int id);
int nbv (liste l);
int l_ordre();
int id_generate();
liste recherche_liste_id(int id);

void voter(liste l);
