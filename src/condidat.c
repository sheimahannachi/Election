#  include <config.h>


#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include <stdio.h>
#include "condidat.h"
#include "utilisateur.h"
#include "liste.h"
#include <string.h>


int ajout_cond(char nom[], char prenom[],char cin[],int idl)
{       //filname ficher user.txt
	int r=0;
		
	condidat c ;
	FILE *f2;
	char d[15];
	sprintf(d,"%d",idl);
	strcat(d,".txt");
	f2=fopen(d,"a");
	
	if(f2!=NULL)
	{ 
		
		
		strcpy(c.nom,nom);
		
 		strcpy(c.prenom,prenom);
		
 		strcpy(c.id_condidat,cin);
		
		c.id_liste=idl;
		fprintf(f2,"%s %s %s %d\n",c.nom,c.prenom,c.id_condidat,c.id_liste);
		r=1;
		
	

}
	

		
	fclose(f2);
	
	return r;
}

int suprim_cond(char cin[], int idl)
{
 FILE *f,*f1;
 condidat c;
int r=0;
 char d[15];


 sprintf(d,"%d",idl);
 strcat(d,".txt");
 f=fopen(d,"r");

 
 f1=fopen("nouv.txt","a");
 if( f!=NULL){
 while (fscanf(f," %s %s %s %d\n",c.nom, c.prenom, c.id_condidat, &c.id_liste)!=EOF)
{
 if(strcmp(cin, c.id_condidat)!=0)
{
 fprintf(f1,"%s %s %s %d\n",c.nom, c.prenom, c.id_condidat, c.id_liste);
}
else {r=1;}

}

}
fclose(f1);
fclose(f);
remove(d);
rename("nouv.txt",d);
return r;
}



// callbacks

int nbr_cnd( int nbr_cd)
{ int i=9;
 
 if (nbr_cd==2){i=10;}
 else if (nbr_cd==3){i=11;}
 return i;


}




// treeview liste

enum {
 Noml,
 Id,
 Nb_cond,
 COLUMNS

};



void afficher_liste(GtkTreeView   *listee)
{
 //Declarations
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;
GtkListStore *store;


char id[12],nb_cond[5],nom[30];	
liste l;
FILE *f;
store=NULL;


store=gtk_tree_view_get_model(listee);
if(store==NULL)
{
 renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes("Nom",renderer,"text",Noml,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(listee),column);

 renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes("Identifiant",renderer,"text",Id,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(listee),column);

renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes("Nombre de condidat",renderer,"text",Nb_cond,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW(listee),column);

}

store=gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

f=fopen("les_liste.txt","r");	

if (f==NULL){ return;}	
else {f=fopen("les_liste.txt","a+");

while (fscanf(f,"%s %d %s %d %d %d %d %d\n",l.nom_liste,&l.id_liste,l.id_tete_liste,&l.nombre_condidat,&l.date.jour,&l.date.mois,&l.date.annee,&l.nbr_vote)!=EOF)
{
sprintf(id,"%d",l.id_liste);
sprintf(nb_cond,"%d",l.nombre_condidat);
strcpy(nom,l.nom_liste);
 gtk_list_store_append (store,&iter);
gtk_list_store_set(store,&iter,Noml,nom,Id,id,Nb_cond,nb_cond,-1);

}}
fclose(f);
gtk_tree_view_set_model(GTK_TREE_VIEW(listee),GTK_TREE_MODEL(store));
g_object_unref(store);

	


	
}




// treeview condidats




enum {
 Nom,
 Prenom,
 CIN,
 COLUMNs

};



void afficher_condidat(GtkTreeView   *listee, int idl)
{
 //Declarations
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;
GtkListStore *store;


char cin[10],prenom[20],nom[20],d[15];	
condidat l;
FILE *f;
store=NULL;
store=gtk_tree_view_get_model(listee);
sprintf(d,"%d",idl);
strcat(d,".txt");




if(store==NULL)
{
 renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes("Nom",renderer,"text",Nom,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(listee),column);

 renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes("Prenom",renderer,"text",Prenom,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(listee),column);

renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes("Numero CIN",renderer,"text",CIN,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW(listee),column);

}

store=gtk_list_store_new(COLUMNs, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

f=fopen(d,"r");	

if (f==NULL){ return;}	
else {f=fopen(d,"a+");

while (fscanf(f,"%s %s %s %d\n",l.nom,l.prenom,l.id_condidat,&l.id_liste)!=EOF)
{
strcpy(cin,l.id_condidat);
strcpy(prenom,l.prenom);
strcpy(nom,l.nom);

 gtk_list_store_append (store,&iter);
gtk_list_store_set(store,&iter,Nom,nom,Prenom,prenom,CIN,cin,-1);

}
fclose(f);
gtk_tree_view_set_model(GTK_TREE_VIEW(listee),GTK_TREE_MODEL(store));
g_object_unref(store);

}


}





// treeview listes trier

enum {
 Nomlt,
 Idt,
 Nb_condt,
 Nb_vote,
 COLUMns

};



void afficher_liste_trier(GtkTreeView   *listee)
{
 //Declarations
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;
GtkListStore *store;


char id[12],nb_cond[5],nom[30],nb_vote[20];	
liste l;
FILE *f;
store=NULL;


store=gtk_tree_view_get_model(listee);
if(store==NULL)
{
 renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes("Nom",renderer,"text",Nomlt,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(listee),column);

 renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes("Identifiant",renderer,"text",Idt,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(listee),column);

renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes("Nombre de condidat",renderer,"text",Nb_condt,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW(listee),column);

renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes("Nombre de votes",renderer,"text",Nb_vote,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW(listee),column);

}

store=gtk_list_store_new(COLUMns, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

f=fopen("l_ordre.txt","r");	

if (f==NULL){ return;}	
else {f=fopen("l_ordre.txt","a+");

while (fscanf(f,"%s %d %s %d %d %d %d %d\n",l.nom_liste,&l.id_liste,l.id_tete_liste,&l.nombre_condidat,&l.date.jour,&l.date.mois,&l.date.annee,&l.nbr_vote)!=EOF)
{
sprintf(nb_vote,"%d",l.nbr_vote);
sprintf(id,"%d",l.id_liste);
sprintf(nb_cond,"%d",l.nombre_condidat);
strcpy(nom,l.nom_liste);
 gtk_list_store_append (store,&iter);
gtk_list_store_set(store,&iter,Nomlt,nom,Idt,id,Nb_condt,nb_cond,Nb_vote,nb_vote,-1);

}}
fclose(f);
gtk_tree_view_set_model(GTK_TREE_VIEW(listee),GTK_TREE_MODEL(store));
g_object_unref(store);

	


	
}
