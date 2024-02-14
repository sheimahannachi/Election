#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"
#include <gtk/gtk.h>



enum 
{
	EIDENTIFIANT,
	ENLE,
	ENBV,
	ECATEGORIE,
	ERECLAMATION,
	COLUMNS,
};


enum 
{
	EID,
	ENBRL,
	COLUMNS2,
};




void ajouter(reclamation rec,int categorie)
{
    FILE *f=NULL;
	
	if( categorie==1)
	strcpy(rec.categorie,"urgent");
	if( categorie==2)
	strcpy(rec.categorie,"moyen");
	if( categorie==3)
	strcpy(rec.categorie,"faible");

     f=fopen("reclamations.txt","a+");
    if(f!=NULL)
    {
         fprintf(f,"%s %d %s %s %s\n",rec.identifiant,rec.nle,rec.nbv,rec.categorie,rec.reclamation);
        fclose(f);
       
      
    }
     
}


void afficher_rec (GtkWidget *liste) 
{	

	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

	reclamation rec;
	char identifiant[20] ;
        int nle ;
        char nbv[20];
        char categorie [20];
        char reclamation [100];
	store=NULL;
	FILE  *f;

	store = gtk_tree_view_get_model(liste);
	if(store==NULL)
	{
	
	
	
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("identifiant", renderer,"text",EIDENTIFIANT,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("nle", renderer,"text",ENLE,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("nbv", renderer,"text",ENBV,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("categorie",renderer,"text",ECATEGORIE,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("reclamation", renderer,"text",ERECLAMATION,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);



		     
		
}		


		store = gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_INT,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
		f=fopen("reclamations.txt","r");
		if(f==NULL)
		{
			return;
		}
		else
		{

			while(fscanf(f,"%s %d %s %s %s\n",identifiant,&nle,nbv,categorie,reclamation)!=EOF)
			{
			
				gtk_list_store_append(store,&iter);
				gtk_list_store_set(store,&iter,EIDENTIFIANT,identifiant,ENLE,nle,ENBV,nbv,ECATEGORIE,categorie,ERECLAMATION,reclamation,-1);
				
			}

			fclose(f);
			gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
			g_object_unref(store);
		}  
	
	


}


int supprimer_rec(char *id_rec)
{
reclamation rec ;
    FILE * f=fopen("reclamations.txt", "r");
    FILE * f2 =fopen("aux.txt", "w");
    if((f==NULL) || (f2==NULL))
return 0;
else
    {
while(fscanf(f,"%s %d %s %s %s",rec.identifiant,&rec.nle,rec.nbv,rec.categorie,rec.reclamation)!=EOF)
{
if(strcmp(rec.identifiant,id_rec)!=0)
        fprintf(f2,"%s %d %s %s %s\n",rec.identifiant,rec.nle,rec.nbv,rec.categorie,rec.reclamation);

}
        fclose(f);
        fclose(f2);
remove("reclamations.txt");
rename("aux.txt", "reclamations.txt");
        return 1;
    }

}
void chercher_rec (char *id_rec,GtkWidget *liste) 
{	

	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

	reclamation rec;
	char identifiant[20] ;
        int nle ;
        char nbv[20];
        char categorie [20];
        char reclamation [100];
	store=NULL;
	FILE  *f;

	store = gtk_tree_view_get_model(liste);
	if(store==NULL)
	{
	
	
	
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("identifiant", renderer,"text",EIDENTIFIANT,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("nle", renderer,"text",ENLE,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("nbv", renderer,"text",ENBV,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("categorie",renderer,"text",ECATEGORIE,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("reclamation", renderer,"text",ERECLAMATION,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);



		     
		
}		


		store = gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_INT,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
		f=fopen("reclamations.txt","r");
		if(f==NULL)
		{
			return;
		}
		else
		{

			while(fscanf(f,"%s %d %s %s %s\n",identifiant,&nle,nbv,categorie,reclamation)!=EOF)
			{
				if (strcmp(id_rec,identifiant)==0){
				gtk_list_store_append(store,&iter);
				gtk_list_store_set(store,&iter,EIDENTIFIANT,identifiant,ENLE,nle,ENBV,nbv,ECATEGORIE,categorie,ERECLAMATION,reclamation,-1);
				}
			}

			fclose(f);
			gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
			g_object_unref(store);
		}  
	
	


}
int modifier_rec(char *idRec,reclamation nouv)
{
reclamation rec ;
    FILE * f=fopen("reclamations.txt", "r");
    FILE * f2 =fopen("aux.txt", "w");
    if((f==NULL) || (f2==NULL))
return 0;
else
    {
while(fscanf(f,"%s %d %s %s %s\n",rec.identifiant,&rec.nle,rec.nbv,rec.categorie,rec.reclamation)!=EOF)
{
	if(strcmp(rec.identifiant,idRec)!=0)
        	fprintf(f2,"%s %d %s %s %s\n",rec.identifiant,rec.nle,rec.nbv,rec.categorie,rec.reclamation);
	else
		fprintf(f2,"%s %d %s %s %s\n",nouv.identifiant,nouv.nle,nouv.nbv,nouv.categorie,nouv.reclamation);

}
        fclose(f);
        fclose(f2);
remove("reclamations.txt");
rename("aux.txt", "reclamations.txt");
        return 1;
    }

}
/*
void afficher_stat(GtkWidget *liste){
GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

	reclamation rec;
	char identifiant[20] ;
        int nle ;
        char nbv[20];
        char categorie [20];
        char reclamation [100];
	store=NULL;
	FILE  *f,*f2;

	store = gtk_tree_view_get_model(liste);
	if(store==NULL)
	{
	
	
	
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("Id Liste", renderer,"text",EID,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("Nombre de reclamation", renderer,"text",ENBRL,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);


		     
		
}		


		store = gtk_list_store_new(COLUMNS2,G_TYPE_STRING,G_TYPE_INT);
		f=fopen("chaima.txt","r");
		if(f==NULL)
		{
			return;
		}
		else
		{
			while(fscanf(f2,"%s %d %s %s %s \n",rec.identifiant,&rec.nle,rec.nbv,rec.categorie,rec.reclamation)!=EOF)


			



			gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
			g_object_unref(store);
		}  


}
 */
