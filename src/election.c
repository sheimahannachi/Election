#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"election.h"
#include <gtk/gtk.h>

enum
{ 
	EID,
	EJOUR,
	EMOIS,
	EANNEE,
	EGOUV,
	EMUNIC,
	ENBHAB,
	ENBCON,
	COLUMNS,
};


////////////////////Ajouteerr electionn /////////////////
void ajouter_election(election e )
{
FILE *f;
f=fopen("Election.txt","a");
 
fprintf(f,"%s %d %d %d %s %s %s %d  \n",e.identifiant,e.date.jour,e.date.mois,e.date.annee,e.gouvernorat,e.municipalite,e.nbhabit,e.nbcons);
fclose(f);
}
/////////////////////////Afficher Election ////////////////
void afficher_election(GtkWidget *liste){

GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	char identifiant[30];
	char jour[10];
	char mois[10];
	char annee[10];
	char gouvernorat[30];
	char municipalite[30];
	char nbhabit[30];
	char nbcons[10];
	store=NULL;
	FILE *f;
	store=gtk_tree_view_get_model (liste);
	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("identifiant", renderer, "text",EID,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("jour", renderer, "text",EJOUR,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("mois", renderer, "text",EMOIS,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("annee", renderer, "text",EANNEE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);


	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("gouvernorat", renderer, "text",EGOUV,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("municipalite", renderer, "text",EMUNIC,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("nbhabit", renderer, "text",ENBHAB,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("nbcons", renderer, "text",ENBCON,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING,   G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING,  G_TYPE_STRING);
	f=fopen("Election.txt","r");
	if(f==NULL)
	{
		return;
	}
	else
	{
		f= fopen("Election.txt","a+");
		while(fscanf(f,"%s %s %s %s %s %s %s %s  \n",identifiant,jour,mois,annee,gouvernorat,municipalite,nbhabit,nbcons)!=EOF)
		{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set(store,&iter, EID, identifiant, EJOUR,jour, EMOIS, mois, EANNEE, annee, EGOUV, gouvernorat ,EMUNIC ,municipalite,  ENBHAB, nbhabit,ENBCON,nbcons,-1);
		}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
		g_object_unref (store);
	}
}

//////////////////////////////Fonction Modifier///////////////////////
void modifier_election(char identifiant[],election e1,char *elect){
election e;
FILE* f1=fopen(elect, "r");
FILE* f2=fopen("elecModif.txt", "w");


if((f1!=NULL)&&(f2!=NULL))
{
while(fscanf(f1,"%s %d %d %d %s %s %s %d  \n",e.identifiant,&e.date.jour,&e.date.mois,&e.date.annee,e.gouvernorat,e.municipalite,e.nbhabit,&e.nbcons)!=EOF)
	{
	if(strcmp(e.identifiant,e1.identifiant)==0)
		{
		fprintf(f2,"%s %d %d %d %s %s %s %d  \n",e1.identifiant,e1.date.jour,e1.date.mois,e1.date.annee,e1.gouvernorat,e1.municipalite,e1.nbhabit,e1.nbcons);
		}
	else
		{
		fprintf(f2,"%s %d %d %d %s %s %s %d  \n",e.identifiant,e.date.jour,e.date.mois,e.date.annee,e.gouvernorat,e.municipalite,e.nbhabit,e.nbcons);
		}
	}

}
fclose(f1);
fclose(f2);
remove("Election.txt");
rename("elecModif.txt",elect);

}
///////////////////////////////Fonction Supprimer ////////////////////////
void supprimer_election(char id []){
election e;
FILE *f1;
FILE *f2;

f1=fopen("Election.txt","r");
f2=fopen("elecSup.txt","w");
while(fscanf(f1,"%s %d %d %d %s %s %s %d  \n",e.identifiant,&e.date.jour,&e.date.mois,&e.date.annee,e.gouvernorat,e.municipalite,e.nbhabit,&e.nbcons)!=EOF)
{if (strcmp(id,e.identifiant)!=0)
fprintf(f2,"%s %d %d %d %s %s %s %d  \n",e.identifiant,e.date.jour,e.date.mois,e.date.annee,e.gouvernorat,e.municipalite,e.nbhabit,e.nbcons);
}
fclose(f1);
fclose(f2);
remove("Election.txt");
rename("elecSup.txt","Election.txt");
}

//////////////////////////Fonction Remplir TAbleau /////////////////////
int remplirtabRech (election tab[],int nb)
{
    char id[20];
    int jour,mois,annee;
    char gouv[20],munic[20];
    char nbhab[30];
    int nbcon;    
    FILE* fichier ;
    int i;

    fichier = fopen("Election.txt", "a+");

        while (fscanf(fichier,"%s %d %d %d %s %s %s %d  \n",id,&jour,&mois,&annee,gouv,munic,nbhab,&nbcon)!=EOF)
        {
            
            strcpy(tab[i].identifiant,id);
	    tab[i].date.jour=jour;
            tab[i].date.mois=mois;
	    tab[i].date.annee=annee;
	    strcpy(tab[i].gouvernorat,gouv);
	    strcpy(tab[i].municipalite,munic);
	    strcpy(tab[i].nbhabit,nbhab);
	    tab[i].nbcons=nbcon;
            nb++;
	    i++;    
        }
        

        fclose(fichier);
	return(nb);
}
///////////////////////////////////////Fonctio Rechercher ////////////
int rechercher_election(char id[]){
election tab[100];
int nb;
int ce,i;
FILE*f;
ce=0;
nb=remplirtabRech (tab,nb);
for (i=0;i<nb;i++)
	{if ((strcmp(id,tab[i].identifiant)==0) ||(strcmp(id,tab[i].gouvernorat)==0) || (strcmp(id,tab[i].municipalite)==0))
		{
		ce=1;
		f=fopen("recheElection.txt", "w+");
		if("f!=NULL")			
	{fprintf(f,"%s %d %d %d %s %s %s %d  \n",tab[i].identifiant,tab[i].date.jour,tab[i].date.mois,tab[i].date.annee,tab[i].gouvernorat,tab[i].municipalite,tab[i].nbhabit,tab[i].nbcons);}
		fclose(f);		
		}
	
	}

return(ce);


}
//////////////////////////////////Afficher Recherchee/////////////////
void afficher_rechercher_election(GtkWidget *liste){
GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	char identifiant[30];
	char jour[10];
	char mois[10];
	char annee[10];
	char gouvernorat[30];
	char municipalite[30];
	char nbhabit[30];
	char nbcons[10];
	store=NULL;
	FILE *f;
	store=gtk_tree_view_get_model (liste);
	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("identifiant", renderer, "text",EID,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("jour", renderer, "text",EJOUR,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("mois", renderer, "text",EMOIS,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("annee", renderer, "text",EANNEE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);


	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("gouvernorat", renderer, "text",EGOUV,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("municipalite", renderer, "text",EMUNIC,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("nbhabit", renderer, "text",ENBHAB,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("nbcons", renderer, "text",ENBCON,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING,   G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING,  G_TYPE_STRING);
	f=fopen("recheElection.txt","r");
	if(f==NULL)
	{
		return;
	}
	else
	{
		f= fopen("recheElection.txt","a+");
		while(fscanf(f,"%s %s %s %s %s %s %s %s  \n",identifiant,jour,mois,annee,gouvernorat,municipalite,nbhabit,nbcons)!=EOF)
		{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set(store,&iter, EID, identifiant, EJOUR,jour, EMOIS, mois, EANNEE, annee, EGOUV, gouvernorat ,EMUNIC ,municipalite,  ENBHAB, nbhabit,ENBCON,nbcons,-1);
		}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
		g_object_unref (store);
	}
}
////////////////////////////
int TPE(char*file)
{Utilisateur u;
 int  nbreelecteur=0 ;
FILE * f = fopen (file ,"r");
if (f!=NULL)
{ while (fscanf (f ,"%s %s %s %s %d %d %d %s %s %s %d %s  \n",u.cin,u.nom,u.prenom,u.genre,&u.date.jour,&u.date.mois,&u.date.annee,u.login,u.motpasse,u.role,&u.vote,u.numerobureau)!=EOF)
   if ( strcmp (u.role ,"electeur")==0 )
       { nbreelecteur ++;
}
}
fclose (f);
return nbreelecteur ;
}
////////////////////////////////////////
void TPHF(char*file,char*hom,char*fem)
{Utilisateur u;
int nbH=0;
int nbF=0;
remove("homme.txt");
remove("femme.txt");
FILE *f=fopen(file ,"r");
FILE *f1=fopen(hom ,"a");
FILE *f2=fopen(fem ,"a");
if (f!=NULL)
{ while (fscanf (f,"%s %s %s %s %d %d %d %s %s %s %d %s  \n",u.cin,u.nom,u.prenom,u.genre,&u.date.jour,&u.date.mois,&u.date.annee,u.login,u.motpasse,u.role,&u.vote,u.numerobureau)!=EOF)
   if ((strcmp (u.role ,"electeur")==0 ) && (strcmp (u.genre ,"homme")==0 ))
	{nbH++;
	fprintf(f1,"%d\n",nbH);

}
if ((strcmp (u.role ,"electeur")==0 ) && (strcmp (u.genre ,"femme")==0 ))
	{nbF++;
	fprintf(f2,"%d\n",nbF);

}
}


fclose (f);
fclose (f1);
fclose (f2);
}
///////////////////////////////////////
int nombre_dehomme(char*file)
{
int nbh=0;
int nbH;
FILE *f=fopen(file ,"r");
if(f!=NULL)
{ while (fscanf (f,"%d\n",&nbH)!=EOF)
{nbh++;}}
return (nbh);
}
////////////////////////////////////////
int nombre_defemme(char*file)
{
int nbf=0;
int nbF;
FILE *f=fopen(file ,"r");
if(f!=NULL)
{ while (fscanf (f,"%d\n",&nbF)!=EOF)
{nbf++;}}
return (nbf);
}

//////////////////////////////////////////////
int agemoyen(char * filename )
{
  FILE * f = fopen (filename, "r");
FILE*f1=fopen("agemoy.txt","a");
int nbelect =0;
int s = 0;
int age ;
Utilisateur u;


while (fscanf (f , "%s %s %s %s %d %d %d %s %s %s %d %s  \n",u.cin,u.nom,u.prenom,u.genre,&u.date.jour,&u.date.mois,&u.date.annee,u.login,u.motpasse,u.role,&u.vote,u.numerobureau)!=EOF)
{
if (strcmp(u.role,"electeur") == 0 ) {

	nbelect ++ ;
	age = 2022 - u.date.annee ;
	s  = s + age ;
		
 	}
}

int moyenage= s/nbelect;

return moyenage ;
}











