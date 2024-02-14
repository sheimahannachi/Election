#include <stdio.h>
#include "utilisateur.h"
#include <string.h>
#include <gtk/gtk.h>
#include <stdlib.h>


enum
{	NOM1,
	PRENOM,
	JOUR,
	MOIS,
	ANNEE,
	CIN,
	ROLE,
	GENRE,
	VOTE,
	NUMBV,
	NATIONALITE,
	APPARTENANCE_POLITIQUE,
	PROFESSION,
	COLUMNS,
};

void ajout_user(char * fileuser,utilisateur u,int choix,int type )
{
		
	if(type==1)
	strcpy(u.genre_user,"Homme");
	if(type==2)
	strcpy(u.genre_user,"Femme");
	if(choix==1)
	strcpy(u.nationalite_obs,"Tunisienne");
	if(choix==2)
	strcpy(u.nationalite_obs,"Etrangere");
	FILE * f=fopen(fileuser,"a");
	if (f!=NULL)
	{		
		/*if (strcasecmp(u.role_user,"observateur")!=0)

		{
			strcpy(u.nationalite_obs,"-1");
			strcpy(u.profession_obs,"-1");
			strcpy(u.app_politique_obs,"-1");
	 	}*/
		
		fprintf(f,"%s %s %d %d %d %s %s %s %d %d %s %s %s  \n",u.nom_user,u.prenom_user,u.date.jour,u.date.mois,u.date.annee,u.cin_user,u.role_user,u.genre_user,u.num_bv_user,u.vote_user,u.nationalite_obs,u.app_politique_obs,u.profession_obs);
		

		fclose(f);
	}
}


void modifier_user(char * fileuser,char id[],utilisateur nouv,int choix,int type)
{	
	utilisateur u;
	int trouve=0;
	FILE * f=fopen(fileuser,"r");
	FILE * f2=fopen("nouv.txt","a");
	if((f!=NULL) && (f2!=NULL))
	{
		while((trouve==0)&&(fscanf(f,"%s %s %d %d %d %s %s %s %d %d %s %s %s\n ",u.nom_user,u.prenom_user,&u.date.jour,&u.date.mois,&u.date.annee,u.cin_user,u.role_user,u.genre_user,&u.num_bv_user,&u.vote_user,u.nationalite_obs,u.app_politique_obs,u.profession_obs)!=EOF))
		{
			if(strcmp(u.cin_user,id)==0)
			{

				(fprintf(f2," %s %s %d %d %d %s %s %s %d %d %s %s %s \n",nouv.nom_user,nouv.prenom_user,nouv.date.jour,nouv.date.mois,nouv.date.annee,nouv.cin_user,nouv.role_user,nouv.genre_user,nouv.num_bv_user,nouv.vote_user,nouv.nationalite_obs,nouv.app_politique_obs,nouv.profession_obs));
				trouve=1;
			}
			else	
				fprintf(f2,"%s %s %d %d %d %s %s %s %d %d %s %s %s \n",u.nom_user,u.prenom_user,u.date.jour,u.date.mois,u.date.annee,u.cin_user,u.role_user,u.genre_user,u.num_bv_user,u.vote_user,u.nationalite_obs,u.app_politique_obs,u.profession_obs);
		}
	}
	fclose(f);
	fclose(f2);
	remove(fileuser);
	rename("nouv.txt",fileuser);
}

void supprimer_user(char * fileuser,char cin [])
{	
	int trouve=0;
	utilisateur u;
	FILE * f=fopen(fileuser,"r");
	FILE * f2=fopen("nouv.txt","w");
	if(f!=NULL && f2!=NULL)
	{
		while(fscanf(f,"%s %s %d %d %d %s %s %s %d %d %s %s %s \n ",u.nom_user,u.prenom_user,&u.date.jour,&u.date.mois,&u.date.annee,u.cin_user,u.role_user,u.genre_user,&u.num_bv_user,&u.vote_user,u.nationalite_obs,u.app_politique_obs,u.profession_obs)!=EOF)
		{
			if(strcmp(u.cin_user,cin)==0)
				trouve=1;
			else
				fprintf(f2,"%s %s %d %d %d %s %s %s %d %d %s %s %s \n",u.nom_user,u.prenom_user,u.date.jour,u.date.mois,u.date.annee,u.cin_user,u.role_user,u.genre_user,u.num_bv_user,u.vote_user,u.nationalite_obs,u.app_politique_obs,u.profession_obs);
		}
	}
	fclose(f);
	fclose(f2);
	remove(fileuser);
	rename("nouv.txt",fileuser);
}

utilisateur chercher_user(char * fileuser,char cin [])
{
	utilisateur u;
	int trouve=0;
	FILE * f=fopen(fileuser,"r");
	if(f!=NULL)
	{
		while(trouve==0 && fscanf(f,"%s %s %d %d %d %s %s %s %d %d %s %s %s ",u.nom_user,u.prenom_user,&u.date.jour,&u.date.mois,&u.date.annee,u.cin_user,u.role_user,u.genre_user,&u.num_bv_user,&u.vote_user,u.nationalite_obs,u.app_politique_obs,u.profession_obs)!=EOF)
		{
			if(strcmp(u.cin_user,cin)==0){
		
				trouve=1;
				fclose(f);}
		}
	}/*if (test=0)
	strcpy(u.cin_user,"-1");*/
	return u;
}
void afficher_user(GtkWidget *liste, char *fileuser)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

	
	char nom1[20];
	char prenom[50];
	int jour;
	int mois;
	int annee;
	char cin[10];
	char role[50];
	char genre[50];
	int num_bv;
	int vote;
	char nationalite[50];
	char profession[50];
	char appartenance[50];

	utilisateur u;
	store=NULL;
	FILE  *f;
	
	store = gtk_tree_view_get_model(liste);
	if(store==NULL)
	{
	
	

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("nom1", renderer,"text",NOM1,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("prenom", renderer,"text",PRENOM,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
	




	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Jour", renderer,"text",JOUR,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);


	


	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Mois", renderer,"text",MOIS,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Annee",renderer,"text",ANNEE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("cin", renderer,"text",CIN,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);


	
	

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("role", renderer,"text",ROLE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);



	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("genre", renderer,"text",GENRE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);


	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("num_bv", renderer,"text",NUMBV,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);


	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("vote", renderer,"text",VOTE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
	

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("nationalite", renderer,"text",NATIONALITE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("appartenance", renderer,"text",APPARTENANCE_POLITIQUE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);


	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("profession", renderer,"text",PROFESSION,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);


	




	
	
	store=gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

	f=fopen(fileuser,"r");
	if(f==NULL)
	{
		return;
	}
	else
	{
		while(fscanf(f,"%s %s %d %d %d %s %s %s %d %d %s %s %s\n ",u.nom_user,u.prenom_user,&u.date.jour,&u.date.mois,&u.date.annee,u.cin_user,u.role_user,u.genre_user,&u.num_bv_user,&u.vote_user,u.nationalite_obs,u.app_politique_obs,u.profession_obs)!=EOF)
		{	
		
			gtk_list_store_append(store,&iter);
			gtk_list_store_set(store,&iter,NOM1,u.nom_user,PRENOM,u.prenom_user,JOUR,u.date.jour,MOIS,u.date.mois,ANNEE,u.date.annee,CIN,u.cin_user, ROLE,u.role_user,GENRE,u.genre_user,NUMBV,u.num_bv_user,VOTE,u.vote_user,NATIONALITE,u.nationalite_obs,APPARTENANCE_POLITIQUE,u.app_politique_obs,PROFESSION,u.profession_obs);
			
		}
		fclose(f);
		gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
		g_object_unref(store);
	}  
}
}

int verif_EXIST(char id[10]){
int test=0;
utilisateur u;
FILE *f=fopen("utilisateur.txt","r");
	
while(fscanf(f,"%s %s %d %d %d %s %s %s %d %d %s %s %s\n",u.nom_user,u.prenom_user,&u.date.jour,&u.date.mois,&u.date.annee,u.cin_user,u.role_user,u.genre_user,&u.num_bv_user,&u.vote_user,u.nationalite_obs,u.app_politique_obs,u.profession_obs)!=EOF)
{
if(strcmp(u.cin_user,id)==0)test=1;

}
fclose(f);
return test;
}

float TVB(char * fileuser)
{	utilisateur u;
	float nb_votes_blancs;
	float nb_votes;
	FILE *f=fopen(fileuser,"r");
	if (f!=NULL)
	{	while (fscanf(f,"%s %s %d %d %d %s %s %s %d %d %s %s %s\n",u.nom_user,u.prenom_user,&u.date.jour,&u.date.mois,&u.date.annee,u.cin_user,u.role_user,u.genre_user,&u.num_bv_user,&u.vote_user,u.nationalite_obs,u.app_politique_obs,u.profession_obs)!=EOF)
		{	nb_votes++;
			if(u.vote_user==0)
			{	
				nb_votes_blancs++;
				
			}
				
		
		}
		

	}
	fclose(f);
	return (nb_votes_blancs/nb_votes)*100;

}
float TPH (char *fileuser,int type)
{	utilisateur u;
	if(type==1)
	strcpy(u.genre_user,"Homme");
	int H=1;
	int nb=0;
	float th;
	FILE *f1=fopen(fileuser,"r");
	if(f1!=NULL)
	{	while(fscanf(f1,"%s %s %d %d %d %s %s %s %d %d %s %s %s\n ",u.nom_user,u.prenom_user,&u.date.jour,&u.date.mois,&u.date.annee,u.cin_user,u.role_user,u.genre_user,&u.num_bv_user,&u.vote_user,u.nationalite_obs,u.app_politique_obs,u.profession_obs)!=EOF)
		{		nb++;
				if(strcmp(u.genre_user,"Homme")==0)
				{
							
					H++;
				}
		}
		
	}
	fclose(f1);
	return (th=(H/nb)*100);

}
float TPF (char *fileuser,int type)
{	utilisateur u;
	if(type==2)
	strcpy(u.genre_user,"Femme");
	int F,nb;
	char ch[]="Femme";
	float tf;
	FILE *f1=fopen(fileuser,"r");
	FILE *f2=fopen("stat_user.txt","w");

	if(f1!=NULL)
	{	while(fscanf(f1,"%s %s %d %d %d %s %s %s %d %d %s %s %s\n ",u.nom_user,u.prenom_user,&u.date.jour,&u.date.mois,&u.date.annee,u.cin_user,u.role_user,u.genre_user,&u.num_bv_user,&u.vote_user,u.nationalite_obs,u.app_politique_obs,u.profession_obs)!=EOF)
		{		nb++;
				if(strcmp(u.genre_user,"Femme")==0)
				{							
					F++;
				}
		}
		
	}
	fclose(f1);
	tf=(F/nb)*100;
	fprintf(f2,"%f",tf);
	fclose(f2);
	return tf;}



/*utilisateur recherche_role(char role[])
{
    utilisateur u;
    int tr=0;
    FILE * f=fopen("utilisateur.txt", "r");
    if(f!=NULL)
    {
        while(tr==0 && fscanf(f1,"%s %s %d %d %d %s %s %s %d %d %s %s %s\n ",u.nom_user,u.prenom_user,&u.date.jour,&u.date.mois,&u.date.annee,u.cin_user,u.role_user,u.genre_user,&u.num_bv_user,&u.vote_user,u.nationalite_obs,u.app_politique_obs,u.profession_obs)!=EOF)
        {
            if(strcmp(nom,u.role_user)==0){
                tr=1;}
        }
    }
	fclose(f);
    return u;

}*/



	
