#include<string.h>
#include <stdio.h>
typedef struct 
{
	char nom [50];
	char prenom[50];
	char id_condidat[12];
	int id_liste;
	


} condidat;
int ajout_cond(char nom[], char prenom[],char cin[],int idl);
int suprim_cond(char cin[], int idl);
int nbr_cnd( int nbr_cd);
void afficher_liste(GtkTreeView   *listee);
void afficher_condidat(GtkTreeView   *listee, int idl);


