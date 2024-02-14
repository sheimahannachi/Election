#include "bureaudevote.h"
#include <gtk/gtk.h>



//////////////////////////////

enum{
NUMERODEBUREAU,
IDENTIFIANT,
CAPACITE,
JOUR,
MOIS,
ANNEE,
COLUMNS
};


void afficher_bureau(GtkWidget *liste )

{


GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;
GtkListStore *store;


store=NULL;
FILE *f;
store=gtk_tree_view_get_model(liste);
if (store==NULL)
{


renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("NUMERODEBUREAU",
                                                            renderer,
                                                            "text", NUMERODEBUREAU,
                                                            NULL);
        
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
        
	
	
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("IDENTIFIANT",
                                                            renderer,
                                                            "text", IDENTIFIANT,
                                                            NULL);
	
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	

	
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("CAPACITE",
                                                            renderer,
                                                            "text", CAPACITE,
                                                            NULL);
	
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("JOUR",
                                                            renderer,
                                                            "text", JOUR,
                                                            NULL);
        
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);



        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("MOIS",
                                                            renderer,
                                                            "text", MOIS,
                                                            NULL);
       
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ANNEE",
                                                            renderer,
                                                            "text", ANNEE,
                                                            NULL);
	
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);


}
store=gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_INT,G_TYPE_STRING,G_TYPE_INT);


char numerodebureau1[30];
char id1[30];
char capacite1[30];
int jour1;
char mois1[30];
int annee1;



{

f=fopen("bureau.txt","r");
	while(fscanf(f,"%s %s %s %d %s %d \n",numerodebureau1,id1,capacite1,&jour1,mois1,&annee1)!=EOF)
	{ 
gtk_list_store_append(store,&iter);
	gtk_list_store_set(store,&iter,NUMERODEBUREAU,numerodebureau1,IDENTIFIANT,id1,CAPACITE,capacite1,JOUR,jour1,MOIS,mois1,ANNEE,annee1,-1);
	}
fclose(f);
gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
g_object_unref(store);
}
}
//////////////////////

void rechercher_bureau(GtkWidget *liste,char ch[30] )
{
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;
GtkListStore *store;


store=NULL;
FILE *f;
store=gtk_tree_view_get_model(liste);
if (store==NULL)
{


renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("NUMERODEBUREAU",
                                                            renderer,
                                                            "text", NUMERODEBUREAU,
                                                            NULL);
        
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
        
	
	
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("IDENTIFIANT",
                                                            renderer,
                                                            "text", IDENTIFIANT,
                                                            NULL);
	
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	

	
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("CAPACITE",
                                                            renderer,
                                                            "text", CAPACITE,
                                                            NULL);
	
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("JOUR",
                                                            renderer,
                                                            "text", JOUR,
                                                            NULL);
        
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);



        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("MOIS",
                                                            renderer,
                                                            "text", MOIS,
                                                            NULL);
       
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ANNEE",
                                                            renderer,
                                                            "text", ANNEE,
                                                            NULL);
	
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);


}
store=gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_INT,G_TYPE_STRING,G_TYPE_INT);


char numerodebureau1[30];
char id1[30];
char capacite1[30];
int jour1;
char mois1[30];
int annee1;



{

f=fopen("bureau.txt","r");
	while(fscanf(f,"%s %s %s %d %s %d \n",numerodebureau1,id1,capacite1,&jour1,mois1,&annee1)!=EOF)
	{ if((strcmp(ch,id1)==0) || (strcmp(ch,capacite1)==0) || (strcmp(ch,numerodebureau1)==0) ){ 
gtk_list_store_append(store,&iter);
	gtk_list_store_set(store,&iter,NUMERODEBUREAU,numerodebureau1,IDENTIFIANT,id1,CAPACITE,capacite1,JOUR,jour1,MOIS,mois1,ANNEE,annee1,-1);
	}}
fclose(f);
gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
g_object_unref(store);
}
}

/////////////////////
void ajout_bureau(bureaudevote bv)
{
    FILE* f;
f=fopen("bureau.txt","a+");
    if(f!=NULL)
    {
        fprintf(f,"%s %s %s %d %s %d\n",bv.numerodebureau,bv.id,bv.capacite,bv.d.jour,bv.d.mois,bv.d.annee);
        fclose(f);
        
    }
}
   
////////////////////////////////
void supprimer_bv(char *id)
{

FILE*f=NULL;
FILE*f1=NULL;
bureaudevote bv;
f=fopen("bureau.txt","r");
f1=fopen("ancien.txt","w+"); 
while(fscanf(f,"%s %s %s %d %s %d\n",bv.numerodebureau,bv.id,bv.capacite,&bv.d.jour,bv.d.mois,&bv.d.annee)!=EOF){
if(strcmp(id,bv.id)!=0)fprintf(f1,"%s %s %s %d %s %d\n",bv.numerodebureau,bv.id,bv.capacite,bv.d.jour,bv.d.mois,bv.d.annee);
}
fclose(f);
fclose(f1);
remove("bureau.txt");
rename("ancien.txt","bureau.txt");
}
/////////////////////

void modifier_bv(bureaudevote bv){
FILE*f=NULL;
FILE*f1=NULL;
bureaudevote bva;
f=fopen("bureau.txt","r");
f1=fopen("ancien.txt","w+");
while(fscanf(f,"%s %s %s %d %s %d \n",bva.numerodebureau,bva.id,bva.capacite,&bva.d.jour,bva.d.mois,&bva.d.annee)!=EOF){
if( strcmp(bv.id,bva.id)==0)
{
fprintf(f1,"%s %s %s %d %s %d \n",bv.numerodebureau,bv.id,bv.capacite,bv.d.jour,bv.d.mois,bv.d.annee);
}
else
{
fprintf(f1,"%s %s %s %d %s %d \n",bva.numerodebureau,bva.id,bva.capacite,bva.d.jour,bva.d.mois,bva.d.annee);
}

}
fclose(f);
fclose(f1);
remove("bureau.txt");
rename("ancien.txt","bureau.txt");
}
///////////////////////////////////////
int veridId_bv(char *id)
{

FILE*f=NULL;

bureaudevote bva ;
f=fopen("bureau.txt","r");
while(fscanf(f,"%s %s %s %d %s %d \n",bva.numerodebureau,bva.id,bva.capacite,&bva.d.jour,bva.d.mois,&bva.d.annee)!=EOF){
if(strcmp(id,bva.id)==0)
return 1;
}

fclose(f);

return 0;
}
//////////////////////////////////////////


void taux (float *te,float *tn)
{
    int nbr_obs=0;
    int nbr_obst=0;
    int nbr_obse=0;
    utilisateurs L;
    FILE * f=fopen("utulisateur.txt","r");
    if(f!=NULL)
    {
        while(fscanf(f,"%s %s %d %d %d %s %d %d %d %d %d %s %s\n",L.nom,L.prenom,&L.d.j,&L.d.m,&L.d.a,L.cin,&L.role,&L.genre,&L.num_bureau_vote,&L.vote,&L.nationalite,L.profess,L.appartenance_politique)!=EOF)
        {
            if (L.role==3)
            {
                nbr_obs++;
            if (L.nationalite==1){
                   nbr_obst++;
            }
            if (L.nationalite==2)
            {
                nbr_obse++;
            }
            }
        }
        *te=(float)nbr_obse/nbr_obs;
        *tn=(float)nbr_obst/nbr_obs;

        }
    fclose(f);
}

/////////////////////////
int cond_gagn()
{
utilisateurs L;
int r[100];
int z=0;
int n=0;
FILE *f;
FILE *f1;
f= fopen("utulisateur.txt","a+");
 while(fscanf(f,"%s %s %d %d %d %s %d %d %d %d %d %s %s\n",L.nom,L.prenom,&L.d.j,&L.d.m,&L.d.a,L.cin,&L.role,&L.genre,&L.num_bureau_vote,&L.vote,&L.nationalite,L.profess,L.appartenance_politique)!=EOF)
{
r[z]=L.vote;
z++;
}
int maxcount = 0;
    int gagnant;
   int i,j,c;
for(i=0;i<z-1;i++){
    for(j=i+1;j<z;j++)
        if ( r[i] < r[j] ) {
            c = r[i];
            r[i] = r[j];
            r[j] = c;
        }
}
f1= fopen("vote.txt","w+");
 for (int i = 0; i < z; i++) {
     fprintf(f1,"%d \n" , r[i]);
printf("%s" ," ");
        }
 fclose(f1);
return gagnant;
}
///////////////////////

enum{
CANDIDATS_GAGNE,
COLUMNS1
};


void afficher_candidat_gagnant(GtkWidget *liste )
{


GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;
GtkListStore *store;


store=NULL;
FILE *f;
store=gtk_tree_view_get_model(liste);
if (store==NULL)
{


renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("CANDIDATS_GAGNE",
                                                            renderer,
                                                            "text", CANDIDATS_GAGNE,
                                                            NULL);
        
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
        
	
	

	

}
store=gtk_list_store_new(COLUMNS1,G_TYPE_INT);



int candidat;



{
f=fopen("vote.txt","r");
	while(fscanf(f," %d \n",&candidat)!=EOF)
	{ 
gtk_list_store_append(store,&iter);
	gtk_list_store_set(store,&iter,CANDIDATS_GAGNE,candidat,-1);
	}
fclose(f);
gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
g_object_unref(store);
}

}


