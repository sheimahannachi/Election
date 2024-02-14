#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "liste.h"
#include "utilisateur.h"
#include "condidat.h"
#include "bureaudevote.h"
#include "election.h"
#include <stdio.h>
#include <string.h>
#include"fonction.h"
#include "login.h"
////////////Ranifiras/////////////////////////////////
// declaration des variables 
// idl id liste pour treeview
//ida id liste pour ajout de condidat
// i_c variable togled button nombre de condidat liste
// variable test pour inetrface ajout-liste (0 ajouter une liste ; 1 modifier une liste)
int i_c=0, idl=0, ida=0, test=0,check_buton_liste=0 ;
////////////////////ranniiheb////////////
int x=0;
int y=0;
int valid_confirm=0;
bureaudevote e;
////////////ranniyounesss//////

int x,y;
char Tpe[20];
char Nbh[20];
char Nbf[20];


////////////////ranichaima////////////////////////////////////
int confirmer=0;
int categorie=3;
reclamation rec_modifier ;






//////////////////////ranifirass///////////////////////////////////////////////////////////





// nombre de condidat a ajouter (window1)
void
on_t3_toggled                           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
 if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))){i_c=3;}
}


void
on_t2_toggled                           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
 if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))){i_c=2;}
}


void
on_t1_toggled                           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
 if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))){i_c=1;}
}








//Afficher les liste  (window2)
void
on_aff_clicked                         (GtkWidget       *objet,
                                        gpointer         user_data)
{
// Declaration
 GtkWidget *window1;
 GtkWidget *window2;
 GtkTreeView *tree;

window1=lookup_widget(objet,"window1");
window2=lookup_widget(objet,"window2");


window2=create_window2();
gtk_widget_show(window2);
gtk_widget_hide(window1);

tree=lookup_widget(window2,"treels");
afficher_liste(tree);



 
}





//ajouter une liste (window1)
void
on_ajout_clicked                       (GtkWidget       *objet,
                                        gpointer         user_data)
{
 GtkWidget *nom;
 GtkWidget *w1;
 GtkWidget *w2;
 GtkWidget *w3;
 GtkWidget *id;
 GtkWidget *jour;
 GtkWidget *mois;
 GtkWidget *annee;
 GtkWidget *window4;
 GtkWidget *label;
 GtkWidget *erreur;
 int i=0,j=0,k=0;
 char id_liste[10];
 
liste l;
//liason des fenetre
 w1=lookup_widget(objet,"window1");
 w2=lookup_widget(objet,"window2");
 w3=lookup_widget(objet,"window3");
 window4=lookup_widget(objet,"window4");
// liason des entrees
nom=lookup_widget(w1,"nom_liste");
id=lookup_widget(w1,"id_teteliste"); 
jour=lookup_widget(w1,"jour");
mois=lookup_widget(w1,"mois");
annee=lookup_widget(w1,"annee");
erreur=lookup_widget(w1,"erreur_id");
gtk_label_set_text(erreur,"");
// les entrees
strcpy(l.nom_liste,gtk_entry_get_text(GTK_ENTRY(nom)));
strcpy(l.id_tete_liste,gtk_entry_get_text(GTK_ENTRY(id)));
i=nbr_cnd( i_c);
l.nombre_condidat=i;
l.date.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jour));
l.date.mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(mois));
l.date.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(annee));
l.nbr_vote=0;
if ((strlen(l.id_tete_liste)<8)|(strlen(l.id_tete_liste)>8)){
 gtk_label_set_text(erreur,"Ecrire CIN de 8 chiffre");
}

else{
// test si ajout liste ou modif liste
if (test==0){
l.id_liste = id_generate();
ida=l.id_liste;
sprintf(id_liste,"%d",ida);
ajouter_liste(l);
while(j<i){
window4=create_window4();
gtk_widget_show(window4);
label=lookup_widget(window4,"lid_liste");
 gtk_label_set_text(GTK_LABEL(label),id_liste);
j++;}

}
else if (test==1){
l.id_liste=ida;
// fonction modifier 
k=modif_liste(l.id_liste,l);
test=0;
}
}
}






//treeview des liste (window2)
void
on_treels_row_activated                (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;
gchar *Nom;
gchar *Id;
gchar *Nb_cond;

liste l;

GtkTreeModel *model =gtk_tree_view_get_model(treeview);

if (gtk_tree_model_get_iter(model, &iter, path)){
gtk_tree_model_get(GTK_LIST_STORE(model), &iter, 0, &Nom, 1, &Id, 2, &Nb_cond, -1);

}


afficher_liste(treeview);
}


// recherche liste affichage (window3)
void
on_re_clicked                          (GtkWidget       *objet,
                                        gpointer         user_data)
{
 GtkTreeView *tree;
 GtkWidget *rech;
 GtkWidget *window2;
 GtkWidget *window3;
 GtkWidget *nom;
 GtkWidget *id;
 GtkWidget *date;
 char tmp[30],jour[5],mois[5],annee[10];
  int idliste;

 liste k;

window3=lookup_widget(objet,"window3");
window2=lookup_widget(objet,"window2");
rech=lookup_widget(window2,"rech");

strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(rech)));


k=recherche_liste(tmp);

if (k.id_liste!=-1){
// creation d'une nouvelle fenetre
window3=create_window3();
gtk_widget_show(window3);
nom=lookup_widget(window3,"noi");
id=lookup_widget(window3,"id_t");
date=lookup_widget(window3,"date");
tree=lookup_widget(window3,"treecond");
// outputs
idl=k.id_liste;
gtk_label_set_text(GTK_LABEL(nom),k.nom_liste);
gtk_label_set_text(GTK_LABEL(id),k.id_tete_liste);
sprintf(jour,"%d",k.date.jour);
sprintf(mois,"%d",k.date.mois);
sprintf(annee,"%d",k.date.annee);
strcat(jour,"/");
strcat(jour,mois);
strcat(jour,"/");
strcat(jour,annee);
gtk_label_set_text(GTK_LABEL(date),jour);
afficher_condidat(tree, idl);

} 
else
{ idliste=atoi(tmp); 
k=recherche_liste_id(idliste);
if (k.id_liste!=-1){
// creation d'une nouvelle fenetre
window3=create_window3();
gtk_widget_show(window3);
nom=lookup_widget(window3,"noi");
id=lookup_widget(window3,"id_t");
date=lookup_widget(window3,"date");
tree=lookup_widget(window3,"treecond");
// outputs
idl=k.id_liste;
gtk_label_set_text(GTK_LABEL(nom),k.nom_liste);
gtk_label_set_text(GTK_LABEL(id),k.id_tete_liste);
sprintf(jour,"%d",k.date.jour);
sprintf(mois,"%d",k.date.mois);
sprintf(annee,"%d",k.date.annee);
strcat(jour,"/");
strcat(jour,mois);
strcat(jour,"/");
strcat(jour,annee);
gtk_label_set_text(GTK_LABEL(date),jour);
afficher_condidat(tree, idl);
}
}




}








// Ouvre window1 ajouter une liste
void
on_listadd_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{
 GtkWidget *window1;
 GtkWidget *window2;
 
 window2=lookup_widget(objet,"window2");
 window1=lookup_widget(objet,"window1");
 
 
 window1=create_window1();
 gtk_widget_show(window1);
 gtk_widget_hide(window2);

}








// ouvre (window5) fenetre de vote
void
on_vote1_clicked                       (GtkWidget       *objet,
                                        gpointer         user_data)
{
 GtkWidget *window4;
 GtkWidget *window5;
 GtkWidget *comb;
 FILE *f;
 liste l;
 f=fopen("les_liste.txt","r");
window4=lookup_widget(objet,"window4");
window5=lookup_widget(objet,"window5");
window5=create_window5();
gtk_widget_show(window5);
comb=lookup_widget(window5,"comboboxentry1");
if (f!=NULL)
{ while(fscanf(f,"%s %d %s %d %d %d %d %d\n",l.nom_liste,&l.id_liste,l.id_tete_liste,&l.nombre_condidat,&l.date.jour,&l.date.mois,&l.date.annee,&l.nbr_vote)!=EOF)
{ 

 gtk_combo_box_append_text(GTK_COMBO_BOX(comb),l.nom_liste);
}
}

}






// Ouvre la fenetre main 
void
on_main_liste_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data)
{ GtkWidget *main;
  GtkWidget *window2;
  window2=lookup_widget(objet,"window2");
  main=lookup_widget(objet,"Main");
 main=create_Main();
 gtk_widget_show(main);
 gtk_widget_hide(window2);
 
}



// treeview condidat (window3)
void
on_treecond_row_activated              (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
  GtkTreeIter iter;
gchar *Nom;
gchar *Prenom;
gchar *CIN;
int r;
condidat c;


condidat l;

GtkTreeModel *model =gtk_tree_view_get_model(treeview);

if (gtk_tree_model_get_iter(model, &iter, path)){
gtk_tree_model_get(GTK_LIST_STORE(model), &iter,0,&Nom,1,&Prenom,2,&CIN,-1);
strcpy(c.nom,Nom);
strcpy(c.prenom,Prenom);
strcpy(c.id_condidat,CIN);
r=suprim_cond(c.id_condidat,idl);

afficher_condidat(treeview,  idl);


}

}









// modifier une liste (redirige vers window1)
void
on_modif_liste_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data)
{
 GtkWidget *window1;
 GtkWidget *window3;
 GtkWidget *nom;
 GtkWidget *id_tete;
 GtkWidget *jour;
 GtkWidget *mois;
 GtkWidget *annee; 
 GtkWidget *noi; 
 GtkWidget *label;
 char noml[20];
liste l;
 test=1;
 window3=lookup_widget(objet,"window3");
 window1=lookup_widget(objet,"window1");
 window1=create_window1();
 gtk_widget_show(window1);
 label=lookup_widget(window1,"label2");
 gtk_widget_hide(window3);
 nom=lookup_widget(window1,"nom_liste");
 id_tete=lookup_widget(window1,"id_teteliste");
 jour=lookup_widget(window1,"jour");
 mois=lookup_widget(window1,"mois");
 annee=lookup_widget(window1,"annee");
 // Remplir les entry avec les information
 noi=lookup_widget(window3,"noi");
 strcpy(noml,gtk_label_get_text(noi));
 l=recherche_liste(noml);
 if (l.id_liste!=-1){
 gtk_entry_set_text(nom,l.nom_liste);
 gtk_entry_set_text(id_tete,l.id_tete_liste);
 gtk_spin_button_set_value(jour,l.date.jour);
 gtk_spin_button_set_value(mois,l.date.mois);
 gtk_spin_button_set_value(annee,l.date.annee);
 ida=l.id_liste;
 gtk_label_set_text(label,"Modifier la liste");

}
gtk_widget_hide(window3);


}










//Suprimer la liste 
void
on_button3_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{ GtkWidget *nom;
  GtkWidget *window2;
 GtkWidget *window3;
 GtkWidget *label;
 
  GtkTreeView *tree;
 char noml[20];
 int tr;
 liste l;
 window2=lookup_widget(objet,"window2");
 window3=lookup_widget(objet,"window3");
 label=lookup_widget(window3,"check");

 nom=lookup_widget(objet,"noi");
 window2=create_window2();
 tree=lookup_widget(window2,"treels");
if(check_buton_liste==1){
 strcpy(noml,gtk_label_get_text(nom));
 l=recherche_liste(noml);
 if( l.id_liste!=-1){
  tr=supprime_liste(l.id_liste);
}
afficher_liste(tree);
gtk_widget_hide(window3);}
else
{gtk_label_set_text(label,"*Cocher le bouton");}
 
 
}















// ajouter un condidat (window4)
void
on_ajout_cond_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data)
{ GtkWidget *window4;
 GtkWidget *nom;
 GtkWidget *prenom;
 GtkWidget *cin;
 GtkWidget *label;
 char id[12],NOM[30],PRENOM[30],CIN[12];
 int i;

 sprintf(id,"%d",ida);
 window4=lookup_widget(objet,"window4");
 nom=lookup_widget (window4,"nom_cond");
 prenom=lookup_widget(window4,"prenom_cond");
 cin=lookup_widget(window4,"CIN_cond");
 label=lookup_widget(window4,"lid_liste");
 strcpy(CIN,gtk_entry_get_text(GTK_ENTRY(cin)));
 
 if((strlen(CIN)>8)|(strlen(CIN)<8)){ gtk_label_set_text(GTK_LABEL(label),"Ecrire un CIN de 8 chiffre");}
 else {
 strcpy(PRENOM,gtk_entry_get_text(GTK_ENTRY(prenom)));
 strcpy(NOM,gtk_entry_get_text(GTK_ENTRY(nom)));
// nom du fichier txt user
 fflush(stdin);
 i=ajout_cond(NOM,PRENOM,CIN, ida);
if(i==1){
 gtk_widget_hide(window4);}}

}

// voter une liste (window5)
void
on_vote2_clicked                       (GtkWidget       *objet,
                                        gpointer         user_data)
{
 GtkWidget *window5;
 GtkWidget *comb;
 liste l;
 int r1=0;
 char nom [30];
 window5=lookup_widget(objet,"window5");
 comb=lookup_widget(window5,"comboboxentry1");
 strcpy(nom,gtk_combo_box_get_active_text(GTK_COMBO_BOX(comb)));
 
l=recherche_liste(nom);
voter(l);
r1=nbv (l);
gtk_widget_hide(window5);

 }




// retour vers l'affichages des listes
void
on_Return_liste_clicked                (GtkWidget       *objet,
                                        gpointer         user_data)
{
 GtkWidget *window2;
 GtkWidget *window6;
 GtkTreeView *tree;
 window2=lookup_widget(objet,"window2");
 window6=lookup_widget(objet,"window6");
 window2=create_window2();
 gtk_widget_show(window2);
 
 gtk_widget_hide(window6);
 tree=lookup_widget(window2,"treels");
 afficher_liste(tree);
}











// Affiche la fenetre 2 des listes 
void
on_listes_clicked                      (GtkWidget       *objet,
                                        gpointer         user_data)
{
 GtkWidget *window2;
 GtkWidget *main;
 GtkTreeView *tree;
 window2=lookup_widget(objet,"window2");
 window2=create_window2();
 gtk_widget_show(window2);
 tree=lookup_widget(window2,"treels");
 
 afficher_liste(tree);
 main=lookup_widget(objet,"Main");
 
 gtk_widget_hide(main);
}


void
on_stat_clicked                        (GtkWidget       *objet,
                                        gpointer         user_data)
{
 GtkWidget *w6;
 GtkWidget *window2;
 GtkTreeView *tree;
 int r1=0,r2=0;
window2=lookup_widget(objet,"window2");
 w6=lookup_widget(objet,"window6");
 w6=create_window6();
 gtk_widget_show(w6);
 gtk_widget_hide(window2);
 
 r2=l_ordre();
 tree=lookup_widget(w6,"ordre_liste");
 afficher_liste_trier(tree);

 
 
}


void
on_suprimer_toggled                    (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
 if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))){check_buton_liste=1;}
}
///////////////ranniiheb/////////////////////

void
on_treeview1_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	gchar* numBV;
        gchar* id;
	gchar* capacite;
	gchar* jour;
	gchar* mois;
	gchar* annee;
	
	
	bureaudevote bv;
      
       GtkTreeIter iter;
	
	

	GtkTreeModel *model =gtk_tree_view_get_model(treeview);

	if (gtk_tree_model_get_iter(model, &iter , path))
	{ 
	  gtk_tree_model_get (GTK_LIST_STORE(model), &iter, 0 ,  &numBV, 1, &id,2,&capacite,3,&jour,4,&mois,5,&annee,-1);
	strcpy(e.id,id);
	strcpy(e.numerodebureau,numBV);
	strcpy(e.capacite,capacite);
	e.d.jour=jour;
	e.d.annee=annee;
	
	
	 

	
	}
}


void
on_button_recherche_bv_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *cherch;
char ch[20];
GtkWidget *treeview1_b;
GtkWidget *afficher_b;
afficher_b=lookup_widget(button,"window1gestionbv");

treeview1_b=lookup_widget(afficher_b,"treeview1");
cherch = lookup_widget (button ,"entry_recherche_bv");
strcpy(ch, gtk_entry_get_text(GTK_ENTRY(cherch)));
 rechercher_bureau(treeview1_b,ch);
}


void
on_afficher1_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *treeview1_bv;
GtkWidget *afficher_bv;
afficher_bv=lookup_widget(button,"window1gestionbv");
treeview1_bv=lookup_widget(afficher_bv,"treeview1");
afficher_bureau(treeview1_bv);
}


void
on_buttongestinbvajouter_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *bureau;
bureau=lookup_widget(button,"window1gestionbv");
gtk_widget_destroy(bureau);
GtkWidget *ajouter ;
ajouter = create_window2ajouterbv ();
  gtk_widget_show (ajouter);
}


void
on_buttongestinbvmodifier_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *gestionbv;
gestionbv=lookup_widget(button,"window1gestionbv");
gtk_widget_destroy(gestionbv);
GtkWidget *modifier;
modifier = create_window3modifier__bv ();
  gtk_widget_show (modifier);


GtkWidget* msgId=lookup_widget(modifier,"label28");
gtk_label_set_text(GTK_LABEL(msgId),e.id);
                gtk_widget_show(msgId);

gtk_entry_set_text(GTK_ENTRY(lookup_widget(modifier,"entry3")),e.numerodebureau);

if (strcmp(e.capacite,"40")==0){
gtk_toggle_button_set_active(GTK_RADIO_BUTTON (lookup_widget(modifier,"radiobutton_modif1")),TRUE);
}
else if (strcmp(e.capacite,"20")==0){
gtk_toggle_button_set_active(GTK_RADIO_BUTTON (lookup_widget(modifier,"radiobutton_modif2")),TRUE);
}
else if (strcmp(e.capacite,"10")==0){
gtk_toggle_button_set_active(GTK_RADIO_BUTTON (lookup_widget(modifier,"radiobutton_modif3")),TRUE);
}


gtk_spin_button_set_value(GTK_SPIN_BUTTON(lookup_widget(modifier,"spinbutton4")),e.d.jour);

gtk_spin_button_set_value(GTK_SPIN_BUTTON(lookup_widget(modifier,"spinbutton5")),e.d.annee);






}


void
on_buttongestionbvsupprimer_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{
char z[30];


strcpy(z,e.id);
	supprimer_bv(z);

GtkWidget *treeview1_bv;
GtkWidget *afficher_bv;
afficher_bv=lookup_widget(button,"window1gestionbv");
treeview1_bv=lookup_widget(afficher_bv,"treeview1");
afficher_bureau(treeview1_bv);
}


void
on_button_stat_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *ajouter_bv;
ajouter_bv=lookup_widget(button,"window1gestionbv");
gtk_widget_destroy(ajouter_bv);
GtkWidget *afficher_bv;
afficher_bv = create_window4_stat ();
  gtk_widget_show (afficher_bv);
}


void
on_buttonretourgestionbv_clicked       (GtkWidget       *objet,
                                        gpointer         user_data)
{
 GtkWidget *window;
 GtkWidget *main;
 window=lookup_widget(objet,"window1gestionbv");
 main=lookup_widget(objet,"Main");
 gtk_widget_hide(window);
 main=create_Main();
 gtk_widget_show(main);
}




void
on_buttonajouterok_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
bureaudevote bv;
int o=0,b=1;
GtkWidget *entrybureau, *entryId , *entryCapacite, *entryJour, *entryMois ,*entryAnnee ;

GtkWidget *e_id_bv;
GtkWidget *label33_id;
GtkWidget *label32_numbureau;

e_id_bv=lookup_widget(button,"e_id_bv");
label33_id=lookup_widget(button,"label33_id");
label32_numbureau=lookup_widget(button,"label32_numbureau");


entrybureau=lookup_widget(button,"entry1");
entryId=lookup_widget(button,"entry2");

entryJour=lookup_widget(button,"spinbutton1");
entryMois=lookup_widget(button,"comboboxentry1");
entryAnnee=lookup_widget(button,"spinbutton3");


strcpy(bv.numerodebureau,gtk_entry_get_text(GTK_ENTRY(entrybureau) ) );
strcpy(bv.id,gtk_entry_get_text(GTK_ENTRY(entryId) ) );
 if (x==1){
strcpy(bv.capacite,"40");}
else 
if (x==2){
strcpy(bv.capacite,"20");}
else
if (x==3){
strcpy(bv.capacite,"10");}


bv.d.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(entryJour));
strcpy(bv.d.mois, gtk_combo_box_get_active_text(GTK_COMBO_BOX(entryMois)));
bv.d.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(entryAnnee));




if (veridId_bv(bv.id)==1)
{o=1;
gtk_widget_show(e_id_bv);
}
else 
{o=0;
gtk_widget_hide(e_id_bv);
}
if(strcmp(bv.id,"")==0){
		  gtk_widget_show (label33_id);
b=0;
}
else {
		  gtk_widget_hide(label33_id);
}
if(strcmp(bv.numerodebureau,"")==0){
		  gtk_widget_show (label32_numbureau);
b=0;
}
else {
		  gtk_widget_hide(label32_numbureau);
}


if(b==1){

if(o==0){
 

	ajout_bureau(bv);


GtkWidget *ajouter1;
ajouter1=lookup_widget(button,"window2ajouterbv");
gtk_widget_destroy(ajouter1);
GtkWidget *bureaudevote;
bureaudevote = create_window1gestionbv();
  gtk_widget_show (bureaudevote);

}
}
}


void
on_button_retour_ajouter_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *ajouter_bv;
ajouter_bv=lookup_widget(button,"window2ajouterbv");
gtk_widget_destroy(ajouter_bv);
GtkWidget *afficher_bv;
afficher_bv = create_window1gestionbv ();
  gtk_widget_show (afficher_bv);
}





void
on_checkbutton_modif1_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if ( gtk_toggle_button_get_active(GTK_CHECK_BUTTON (togglebutton)))
{valid_confirm=1;}
else
{valid_confirm=0;}
}


void
on_buttonok_modifier_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
bureaudevote b;

GtkWidget *entrybureau, *entryId , *entryCapacite, *entryJour, *entryMois ,*entryAnnee ;




entrybureau=lookup_widget(button,"entry3");


entryJour=lookup_widget(button,"spinbutton4");
entryMois=lookup_widget(button,"comboboxentry2");
entryAnnee=lookup_widget(button,"spinbutton5");


strcpy(b.numerodebureau,gtk_entry_get_text(GTK_ENTRY(entrybureau) ) );
strcpy(b.id,e.id);
 if (y==1){
strcpy(b.capacite,"40");}
else 
if (y==2){
strcpy(b.capacite,"20");}
else
if (y==3){
strcpy(b.capacite,"10");}


b.d.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(entryJour));
strcpy(b.d.mois, gtk_combo_box_get_active_text(GTK_COMBO_BOX(entryMois)));
b.d.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(entryAnnee));
if(valid_confirm==1)
{
modifier_bv(b);
GtkWidget *modifier;
modifier=lookup_widget(button,"window3modifier__bv");
gtk_widget_destroy(modifier);

GtkWidget *gestionbv;
gestionbv = create_window1gestionbv ();
gtk_widget_show (gestionbv);
}

}


void
on_buttonannuler_modifier_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *modifier_bv;
modifier_bv=lookup_widget(button,"window3modifier__bv");
gtk_widget_destroy(modifier_bv);
GtkWidget *afficher_bv;
afficher_bv = create_window1gestionbv ();
  gtk_widget_show (afficher_bv);
}


void
on_button_taux_obs_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
float tn ;
float te;
char chnb[10];
char chnb1[10];
GtkWidget *nbResultat;
GtkWidget *nbResultat1;
taux(&te,&tn);
	printf("%f",te);
	printf("%f",tn);
sprintf(chnb,"%f",te);
sprintf(chnb1,"%f",tn);
        
nbResultat=lookup_widget(button,"label_te");
nbResultat1=lookup_widget(button,"label_tn");
gtk_label_set_text(GTK_LABEL(nbResultat),chnb);
gtk_label_set_text(GTK_LABEL(nbResultat1),chnb1);
gtk_widget_show (nbResultat);
gtk_widget_show (nbResultat1);
}


void
on_button1_afficher_stat_gagne_clicked (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *treeview1_bv;
GtkWidget *afficher_bv;
afficher_bv=lookup_widget(button,"window4_stat");
treeview1_bv=lookup_widget(afficher_bv,"treeview_candidat_gagne");
cond_gagn();
afficher_candidat_gagnant(treeview1_bv);
}


void
on_button_retour_stat_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *statt;
statt=lookup_widget(button,"window4_stat");
gtk_widget_destroy(statt);
GtkWidget *afficher_bv;
afficher_bv = create_window1gestionbv ();
  gtk_widget_show (afficher_bv);
}


void
on_button75_clicked                    (GtkWidget      *objet,
                                        gpointer         user_data)
{
 GtkWidget   *window;
 GtkWidget *main;
window=lookup_widget(objet,"window1gestionbv");
main=lookup_widget(objet,"Main");
window=create_window1gestionbv();
gtk_widget_show(window);
gtk_widget_hide(main);
}

//NOUVEAU
void
on_radiobuttonajouter40_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
 if ( gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{x=1;}
}





void
on_radiobuttonajouter10_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
 if ( gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{x=3;}
}


void
on_radiobutton_modif1_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
 if ( gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{y=1;}
}


void
on_radiobutton_modif2_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
 if ( gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{y=2;}
}


void
on_radiobutton_modif3_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
 if ( gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{y=3;}
}


void
on_radiobuttonajouter20_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
 if ( gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{x=2;}
}
////////////youness//////////////

void
on_button1_retourajt_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowajouter, *menu_election;
windowajouter=lookup_widget(button,"window_ajouter_election");
gtk_widget_destroy(windowajouter);
menu_election=create_menu_election();
gtk_widget_show (menu_election);
}


void
on_checkbutton1_confi_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{y=1;}
}


void
on_button1_ajouterElection_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
election e;
GtkWidget *windowajout, *windowelection,*id,*jour,*mois,*annee,*gou,*munic,*nbrh,*nbrc,*output,*output1;
windowajout=create_window_ajouter_election();
windowelection=create_window_election();
id = lookup_widget(button,"entry1_ideclection");
gou= lookup_widget(button,"entry1_gouvernorat");
jour = lookup_widget(button,"spinbutton1_jour");
mois = lookup_widget(button,"spinbutton1_mois");
annee = lookup_widget(button,"spinbutton1_annee");
munic=lookup_widget(button,"comboboxentry1_munic");
strcpy(e.identifiant,gtk_entry_get_text(GTK_ENTRY(id)));
strcpy(e.gouvernorat,gtk_entry_get_text(GTK_ENTRY(gou)));
e.date.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (jour));
e.date.mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (mois));
e.date.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (annee));
strcpy(e.municipalite,gtk_combo_box_get_active_text(GTK_COMBO_BOX(munic)));
if(x==1 )
{strcpy(e.nbhabit,"5000");
e.nbcons=12;
} 
else if(x==2)
{strcpy(e.nbhabit,"5001->10000");
e.nbcons=16;
}
else if(x==3)
{strcpy(e.nbhabit,"10001->25000");
e.nbcons=22;
}
else if(x==4)
{strcpy(e.nbhabit,"25001->50000");
e.nbcons=30;
}
else if(x==5)
{strcpy(e.nbhabit,"50001->100000");
e.nbcons=36;
}
else if(x==7)
{strcpy(e.nbhabit,"100001->500000");
e.nbcons=40;
}
else if(x==6)
{strcpy(e.nbhabit,"Plus500000");
e.nbcons=60;
}
if(y==1){
if ((strcmp(e.identifiant,"")==0)||( strcmp(e.gouvernorat,"")==0)||( strcmp(e.municipalite,"")==0)) {
output=lookup_widget(button,"label2_donnemanq");
gtk_label_set_text(GTK_LABEL(output), "Données manquantes. \n Veuillez remplir tout les champs!");
output1=lookup_widget(button,"label1_ajouter");
gtk_label_set_text(GTK_LABEL(output1), "");
}
else
{int k;

k=rechercher_election(e.identifiant);
if(k==1){output=lookup_widget(button,"label2_donnemanq");
gtk_label_set_text(GTK_LABEL(output), "id est deja existe");}
else{
ajouter_election(e);
output=lookup_widget(button,"label2_donnemanq");
gtk_label_set_text(GTK_LABEL(output), "");
output1=lookup_widget(button,"label1_ajouter");
gtk_label_set_text(GTK_LABEL(output1), "Ajouter avec Succes");
}}}
x=0;
y=0;
}


void
on_button1_ModifierElection_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{
election e1;
GtkWidget *windowajout, *windowelection,*id1,*jour1,*mois1,*annee1,*gou1,*munic1,*nbrh1,*nbrc1,*output2,*output3;
windowajout=create_window_ajouter_election();
windowelection=create_window_election();
id1 = lookup_widget(button,"entry1_ideclection");
gou1= lookup_widget(button,"entry1_gouvernorat");
jour1 = lookup_widget(button,"spinbutton1_jour");
mois1 = lookup_widget(button,"spinbutton1_mois");
annee1 = lookup_widget(button,"spinbutton1_annee");
munic1=lookup_widget(button,"comboboxentry1_munic");
strcpy(e1.identifiant,gtk_entry_get_text(GTK_ENTRY(id1)));
strcpy(e1.gouvernorat,gtk_entry_get_text(GTK_ENTRY(gou1)));
e1.date.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (jour1));
e1.date.mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (mois1));
e1.date.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (annee1));
strcpy(e1.municipalite,gtk_combo_box_get_active_text(GTK_COMBO_BOX(munic1)));
if(x==1 )
{strcpy(e1.nbhabit,"5000");
e1.nbcons=12;
} 
else if(x==2)
{strcpy(e1.nbhabit,"5001->10000");
e1.nbcons=16;
}
else if(x==3)
{strcpy(e1.nbhabit,"10001->25000");
e1.nbcons=22;
}
else if(x==4)
{strcpy(e1.nbhabit,"25001->50000");
e1.nbcons=30;
}
else if(x==5)
{strcpy(e1.nbhabit,"50001->100000");
e1.nbcons=36;
}
else if(x==7)
{strcpy(e1.nbhabit,"100001->500000");
e1.nbcons=40;
}
else if(x==6)
{strcpy(e1.nbhabit,"Plus500000");
e1.nbcons=60;
}if(y==1){
if ((strcmp(e1.identifiant,"")==0)||( strcmp(e1.gouvernorat,"")==0)||( strcmp(e1.municipalite,"")==0)) {
output2=lookup_widget(button,"label2_donnemanq");
gtk_label_set_text(GTK_LABEL(output2), "Données manquantes. \n Veuillez remplir tout les champs!");
output3=lookup_widget(button,"label1_modifier");
gtk_label_set_text(GTK_LABEL(output3), "");
}
else
{
modifier_election(e1.identifiant,e1,"Election.txt");
output2=lookup_widget(button,"label2_donnemanq");
gtk_label_set_text(GTK_LABEL(output2), "");
output3=lookup_widget(button,"label1_modifier");
gtk_label_set_text(GTK_LABEL(output3), "Modifier avec Succes");
}}
x=0;
y=0;

}


void
on_radiobutton1_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{x=1;}
}


void
on_radiobutton2_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{x=2;}
}


void
on_radiobutton3_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{x=3;}
}


void
on_radiobutton4_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{x=4;}
}


void
on_radiobutton5_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{x=5;}
}


void
on_radiobutton6_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{x=6;}
}





void
on_treeview1_affElection_row_activated (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;
gchar* id;
gchar* jour;
gchar* mois;
gchar* annee;
gchar* gou;
gchar* muni;
gchar* nbh;
gchar* nbc;
election e;
GtkTreeModel *model= gtk_tree_view_get_model(treeview);
GtkWidget* windowajout,*windowelection,*tre,*idd,*jj,*mm,*aa,*go,*mu,*nh,*nc;

if (gtk_tree_model_get_iter(model, &iter,path))
{


gtk_tree_model_get(GTK_LIST_STORE(model),&iter,0,&id,1,&jour,2,&mois,3,&annee,4,&gou,5,&muni,6,&nbh,7,&nbc,-1);

windowajout=create_window_ajouter_election();
windowelection=create_window_election();
gtk_widget_hide(windowelection);
gtk_widget_show(windowajout);

idd=lookup_widget(windowajout,"entry1_ideclection");
gtk_entry_set_text(GTK_ENTRY(idd),id);

jj=lookup_widget(windowajout,"spinbutton1_jour");
gtk_entry_set_text(GTK_ENTRY(jj),jour);

mm=lookup_widget(windowajout,"spinbutton1_mois");
gtk_entry_set_text(GTK_ENTRY(mm),mois);

aa=lookup_widget(windowajout,"spinbutton1_annee");
gtk_entry_set_text(GTK_ENTRY(aa),annee);

go=lookup_widget(windowajout,"entry1_gouvernorat");
gtk_entry_set_text(GTK_ENTRY(go),gou);
/*
mu=lookup_widget(windowajout,"comboboxentry1_munic");
gtk_combo_box_new_text(GTK_ENTRY(mu),muni);
*/


}
}


void
on_buttretaffich_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowelection, *menu_election;
windowelection=lookup_widget(button,"windowelection");
gtk_widget_destroy(windowelection);

menu_election=create_menu_election();
gtk_widget_show (menu_election);
}


void
on_button2_affElect_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *tree,*windowElection;
windowElection=lookup_widget(button,"window_election");
gtk_widget_destroy(windowElection);
windowElection=create_window_election();
tree=lookup_widget(windowElection,"treeview1_affElection");

afficher_election(tree);

gtk_widget_hide(windowElection);
gtk_widget_show(windowElection);

}


void
on_button2_tachcalcul_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *window_calcul, *windowElection;
windowElection=lookup_widget(button,"window_election");
gtk_widget_destroy(windowElection);
window_calcul=create_window_calcul();
gtk_widget_show (window_calcul);
}


void
on_button2_windAjouter_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *window_ajouter_election, *windowElection;
windowElection=lookup_widget(button,"window_election");
gtk_widget_destroy(windowElection);
window_ajouter_election=create_window_ajouter_election ();
gtk_widget_show (window_ajouter_election);
}


void
on_button2_windModif_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *window_ajouter_election, *windowElection;
windowElection=lookup_widget(button,"window_election");
gtk_widget_destroy(windowElection);
window_ajouter_election=create_window_ajouter_election ();
gtk_widget_show (window_ajouter_election);
}


void
on_button2_rechElect_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *window_rech, *windowElection;
windowElection=lookup_widget(button,"window_election");
gtk_widget_destroy(windowElection);
window_rech=create_window_recherelect ();
gtk_widget_show (window_rech);
}


void
on_button2_SuppElect_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
int k;
char identi[20];
GtkWidget *windowElection,*tree, *iden,*output;
iden = lookup_widget(button,"entry2_SuppELect");
strcpy(identi,gtk_entry_get_text(GTK_ENTRY(iden)));
k=rechercher_election(identi);
if (k==0)
	{

	output=lookup_widget(button,"label2_SuppEl");
	gtk_label_set_text(GTK_LABEL(output), "ID INTROUVABLE");
	}
if (k==1)	
	{	

supprimer_election(identi);
windowElection=lookup_widget(button,"window_election");
tree=lookup_widget(windowElection,"treeview1_affElection");
afficher_election(tree);
output=lookup_widget(button,"label2_SuppEl");
gtk_label_set_text(GTK_LABEL(output), "Supprimer avec Succes");
}
}


void
on_treeview1_recElect_row_activated    (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}


void
on_button3_retrecher_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *window_rech, *menu_election;
window_rech=lookup_widget(button,"window_recherelect");
gtk_widget_destroy(window_rech);

menu_election=create_menu_election();
gtk_widget_show (menu_election);
}


void
on_button3_reche_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
remove("RechElect.txt");
char ident[20];
GtkWidget *id,*tree,*windowrechercher,*output;
int k;
windowrechercher=lookup_widget(button,"window_recherelect");
id = lookup_widget(button,"entry3_rechelect");
strcpy(ident,gtk_entry_get_text(GTK_ENTRY(id)));
k=rechercher_election(ident);
if (k==0)
	{

	output=lookup_widget(button,"label3_rechint");
	gtk_label_set_text(GTK_LABEL(output), "Election INTROUVABLE");
	}
if (k==1)	
	{	

tree=lookup_widget(windowrechercher,"treeview1_recElect");
afficher_rechercher_election(tree);
}
}


void
on_button4_retCAl_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *window_calcul, *menu_election;
window_calcul=lookup_widget(button,"window_calcul");
gtk_widget_destroy(window_calcul);

menu_election=create_menu_election();
gtk_widget_show (menu_election);
}


void
on_button3_calculEl_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *output,*output1,*output2;
int tp;
int nbhomm,nbf;
output = lookup_widget(button, "label4_TPE") ;
tp=TPE("Utilisateur.txt");
sprintf(Tpe,"%d",tp);
gtk_label_set_text(GTK_LABEL(output),Tpe);


output2 = lookup_widget(button, "label5_femme") ;
nbf=agemoyen("Utilisateur.txt");
sprintf(Nbf,"%d",nbf);
gtk_label_set_text(GTK_LABEL(output2),Nbf);
}


void
on_toajout_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *window_ajouter_election, *menu_election;
menu_election=lookup_widget(button,"menu_election");
gtk_widget_destroy(menu_election);
window_ajouter_election=create_window_ajouter_election ();
gtk_widget_show (window_ajouter_election);
}


void
on_toaffich_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowelection, *menu_election;
menu_election=lookup_widget(button,"menu_election");
gtk_widget_destroy(menu_election);
windowelection=create_window_election ();
gtk_widget_show (windowelection);
}


void
on_tomodif_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *window_ajouter_election, *menu_election;
menu_election=lookup_widget(button,"menu_election");
gtk_widget_destroy(menu_election);
window_ajouter_election=create_window_ajouter_election ();
gtk_widget_show (window_ajouter_election);
}


void
on_tosupp_clicked                      (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowelection, *menu_election;
menu_election=lookup_widget(button,"menu_election");
gtk_widget_destroy(menu_election);
windowelection=create_window_election ();
gtk_widget_show (windowelection);
}


void
on_tocherch_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowcherch, *menu_election;
menu_election=lookup_widget(button,"menu_election");
gtk_widget_destroy(menu_election);
windowcherch=create_window_recherelect ();
gtk_widget_show (windowcherch);
}


void
on_tostat_clicked                      (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowstat, *menu_election;
menu_election=lookup_widget(button,"menu_election");
gtk_widget_destroy(menu_election);
windowstat=create_window_calcul ();
gtk_widget_show (windowstat);
}


void
on_buttonyounes_clicked                (GtkWidget       *objet,
                                        gpointer         user_data)
{
 GtkWidget *window1;
 GtkWidget *main;
main=lookup_widget(objet,"Main");
window1=lookup_widget(objet,"menu_election");
window1=create_menu_election();
gtk_widget_show(window1);
gtk_widget_hide(main);

}


void
on_buttonyounesretour_clicked          (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *window;
 GtkWidget *main;
 window=lookup_widget(objet,"menu_election");
 main=lookup_widget(objet,"Main");
 gtk_widget_hide(window);
 main=create_Main();
 gtk_widget_show(main);
}


void
on_radiobutton7_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{x=7;}
}


void
on_radiobutton1_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *output;
output=lookup_widget(button,"label1_nbrCons");
gtk_label_set_text(GTK_LABEL(output), "12");
}


void
on_radiobutton2_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *output;
output=lookup_widget(button,"label1_nbrCons");
gtk_label_set_text(GTK_LABEL(output), "16");
}


void
on_radiobutton3_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *output;
output=lookup_widget(button,"label1_nbrCons");
gtk_label_set_text(GTK_LABEL(output), "22");
}


void
on_radiobutton4_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *output;
output=lookup_widget(button,"label1_nbrCons");
gtk_label_set_text(GTK_LABEL(output), "30");
}


void
on_radiobutton5_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *output;
output=lookup_widget(button,"label1_nbrCons");
gtk_label_set_text(GTK_LABEL(output), "36");
}


void
on_radiobutton6_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *output;
output=lookup_widget(button,"label1_nbrCons");
gtk_label_set_text(GTK_LABEL(output), "60");
}


void
on_radiobutton7_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *output;
output=lookup_widget(button,"label1_nbrCons");
gtk_label_set_text(GTK_LABEL(output), "40");
}

////////////////////////////YOSER///////////////////////////////////////////

int type,choix;
utilisateur uSupp;
utilisateur ToUse;
void
on_buttonValider_user_clicked          (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *nom1;
GtkWidget *prenom1;
GtkWidget *jour1;
GtkWidget *mois1;
GtkWidget *annee1;
GtkWidget *cin1;
GtkWidget *role1;
GtkWidget *num_bv1;
GtkWidget *vote1;
GtkWidget *profession1;
GtkWidget *appartenance1;
ToUse=chercher_user("utilisateur.txt",uSupp.cin_user);

utilisateur u;



//associer les objets avec des variables

nom1=lookup_widget(objet,"entryNom_user");
prenom1=lookup_widget(objet,"entryPrenom_user");
jour1=lookup_widget(objet,"spinbuttonJour_user");
mois1=lookup_widget(objet,"spinbuttonMois_user");
annee1=lookup_widget(objet,"spinbuttonAnnee_user");
cin1=lookup_widget(objet,"entryCin_user");
role1=lookup_widget(objet,"comboboxRole_user");
num_bv1=lookup_widget(objet,"spinbuttonNumbv_user");
vote1=lookup_widget(objet,"spinbuttonVote_user");
profession1=lookup_widget(objet,"comboboxProf_user");
appartenance1=lookup_widget(objet,"comboboxApp_obs");

//recuperer les valeurs de entry
strcpy(u.nom_user,gtk_entry_get_text(GTK_ENTRY(nom1)));
strcpy(u.prenom_user,gtk_entry_get_text(GTK_ENTRY(prenom1)));
strcpy(u.cin_user,gtk_entry_get_text(GTK_ENTRY(cin1)));
strcpy(u.profession_obs,gtk_combo_box_get_active_text(GTK_COMBO_BOX(profession1)));






//recuperer les valeurs de spin button


u.date.jour=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(jour1));
u.date.mois=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(mois1));
u.date.annee=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(annee1));
u.num_bv_user=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(num_bv1));
u.vote_user=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(vote1));


//recuperer les valeurs de combobox

strcpy(u.role_user,gtk_combo_box_get_active_text(GTK_COMBO_BOX(role1)));
strcpy(u.app_politique_obs,gtk_combo_box_get_active_text(GTK_COMBO_BOX(appartenance1)));


	if(type==1)
	strcpy(u.genre_user,"Homme");
	if(type==2)
	strcpy(u.genre_user,"Femme");
	if(choix=1)
	strcpy(u.nationalite_obs,"Tunisienne");
	if(choix==2)
	strcpy(u.nationalite_obs,"Etrangere");

	/*if(strcmp(u.role_user,"observateur")!=0)
	gtk_widget_hide(profession1);
	gtk_widget_hide(appartenance1);*/


//checkbox

//radio button


if(u.cin_user=="")strcpy(u.cin_user,ToUse.cin_user);
if((strcmp(u.genre_user,"Homme")!=0)&&(strcmp(u.genre_user,"Femme")))strcpy(u.genre_user,ToUse.genre_user);
if((strcmp(u.nationalite_obs,"Tunisienne")!=0)&&(strcmp(u.genre_user,"Etrangere")))strcpy(u.nationalite_obs,ToUse.nationalite_obs);
if(strcmp(u.profession_obs,"-1")==0)strcpy(u.profession_obs,ToUse.profession_obs);




if(verif_EXIST(u.cin_user)==0) ajout_user("utilisateur.txt",u,choix,type);
else modifier_user("utilisateur.txt",u.cin_user,u,choix,type);

GtkWidget *msg;
msg=lookup_widget(objet,"verifcin_user");

if(verif_EXIST(u.cin_user)==0){
if ((strlen(u.cin_user)!=8)) gtk_widget_show(msg);
else ajout_user("utilisateur.txt",u,choix,type);}

}


void
on_buttonAfficher_user_clicked         (GtkWidget       *objet,
                                        gpointer         user_data)
{
utilisateur u;
GtkWidget *fenetre_ajout_user;
GtkWidget *fenetre_afficher_user;
GtkWidget *treeview_user;

fenetre_ajout_user = lookup_widget(objet,"ajout_user");
gtk_widget_destroy(fenetre_ajout_user);
gtk_widget_hide(fenetre_ajout_user);

fenetre_afficher_user=lookup_widget(objet,"afficher_user");
fenetre_afficher_user=create_afficher_user();

gtk_widget_show(fenetre_afficher_user);

treeview_user=lookup_widget(fenetre_afficher_user,"treeview_user");
afficher_user(treeview_user,"utilisateur.txt");
}


void
on_radiobuttonFemme_user_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (togglebutton)))
type=2;
}


void
on_radiobuttonHomme_user_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (togglebutton)))
type=1;
}


void
on_checkbuttonTun_obs_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)))
choix=1;
}


void
on_checkbuttonEtr_obs_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)))
choix=2;
}


void
on_treeview_user_row_activated         (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;
gchar* nom;
gchar* prenom;
gint* jour;
gint* mois;
gint* annee;
gchar* cin;
gchar* role;
gchar* genre;
gint* numBV;
gint* vote;
gchar* nationalite;
gchar* appartenance;
gchar* profession;

utilisateur u;


GtkTreeModel *model=gtk_tree_view_get_model(treeview);
if(gtk_tree_model_get_iter(model,&iter,path))
{
gtk_tree_model_get(GTK_LIST_STORE(model),&iter,0,&nom,1,&prenom,2,&jour,3,&mois,4,&annee,5,&cin,6,&role,7,&genre,8,&numBV,9,&vote,10,&nationalite,11,&appartenance,12,&profession,-1);

strcpy(uSupp.nom_user,nom);
strcpy(uSupp.prenom_user,prenom);
uSupp.date.jour=jour;
uSupp.date.mois=mois;
uSupp.date.annee=annee;
strcpy(uSupp.cin_user,cin);
strcpy(uSupp.role_user,role);
strcpy(uSupp.genre_user,genre);
uSupp.num_bv_user=numBV;
uSupp.vote_user=vote;
strcpy(uSupp.nationalite_obs,nationalite);
strcpy(uSupp.app_politique_obs,appartenance);
strcpy(uSupp.profession_obs,profession);




afficher_user(treeview,"utilisateur.txt");
}
}

void
on_refresh_user_clicked                (GtkWidget       *objet,
                                        gpointer         user_data)
{
utilisateur u;
GtkWidget *w1;
GtkWidget *fenetre_afficher_user;
GtkWidget *treeview_user;

w1=lookup_widget(objet,"afficher_user");
fenetre_afficher_user=create_afficher_user();

gtk_widget_hide(fenetre_afficher_user);
gtk_widget_hide(w1);

gtk_widget_show(fenetre_afficher_user);

treeview_user=lookup_widget(fenetre_afficher_user,"treeview_user");
afficher_user(treeview_user,"utilisateur.txt");
}


void
on_buttonPrec_user_clicked             (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget   *afficher_user;
 GtkWidget *main;
afficher_user=lookup_widget(objet,"afficher_user");
main=lookup_widget(objet,"Main");
main=create_Main();
gtk_widget_show(main);
gtk_widget_hide(afficher_user);
}


void
on_buttonRech_user_clicked             (GtkWidget       *objet,
                                        gpointer         user_data)
{
utilisateur u;
GtkWidget *fenetre_afficher,*w1;

GtkWidget *treeview;
GtkWidget *commentaire;
GtkWidget  *id_entry;
char id[20];
char role[20];
id_entry = lookup_widget (objet,"entryRech_user");
strcpy(id,gtk_entry_get_text(GTK_ENTRY(id_entry)));
//strcpy(role,gtk_entry_get_text(GTK_ENTRY(id_entry)));

u=chercher_user("utilisateur.txt",id);

FILE *f=fopen("search.txt","w");
	if(f!=NULL)
{		
		fprintf(f,"%s %s %d %d %d %s %s %s %d %d %s %s %s \n",u.nom_user,u.prenom_user,u.date.jour,u.date.mois,u.date.annee,u.cin_user,u.role_user,u.genre_user,u.num_bv_user,u.vote_user,u.nationalite_obs,u.app_politique_obs,u.profession_obs);}
		
	fclose(f);


w1=lookup_widget(objet,"afficher_user");
fenetre_afficher=create_afficher_user();
gtk_widget_hide(fenetre_afficher);
gtk_widget_hide(w1);
gtk_widget_show(fenetre_afficher);
treeview=lookup_widget(fenetre_afficher,"treeview_user");
afficher_user(treeview,"search.txt");
if (strcmp(u.cin_user,id)!=0){
commentaire=lookup_widget(fenetre_afficher,"commentaire");
gtk_widget_show(commentaire);
gtk_widget_hide(treeview);}
else{ 
commentaire=lookup_widget(fenetre_afficher,"commentaire");

afficher_user(treeview,"search.txt");
}}


void
on_buttonModifier_user_clicked         (GtkWidget       *objet,
                                        gpointer         user_data)
{

utilisateur u;
GtkWidget *nom;
GtkWidget *prenom;
GtkWidget *jour;
GtkWidget *mois;
GtkWidget *annee;
GtkWidget *cin;
GtkWidget *role;
GtkWidget *num;
GtkWidget *vote;
GtkWidget *profession;
GtkWidget *appartenance;
GtkWidget *fenetre;
GtkWidget *homme;
GtkWidget *femme;
GtkWidget *tunisian;
GtkWidget *etrangere;

GtkWidget *fenetre_ajout_user;
GtkWidget *fenetre_afficher_user;
GtkWidget *treeview_user;

fenetre_afficher_user = lookup_widget(objet,"afficher_user");
gtk_widget_hide(fenetre_afficher_user);


fenetre_ajout_user=lookup_widget(objet,"ajout_user");
fenetre_ajout_user=create_ajout_user();
gtk_widget_show(fenetre_ajout_user);


utilisateur user=chercher_user("utilisateur.txt",uSupp.cin_user);

nom=lookup_widget(fenetre_ajout_user,"entryNom_user");
prenom=lookup_widget(fenetre_ajout_user,"entryPrenom_user");
jour=lookup_widget(fenetre_ajout_user,"spinbuttonJour_user");
mois=lookup_widget(fenetre_ajout_user,"spinbuttonMois_user");
annee=lookup_widget(fenetre_ajout_user,"spinbuttonAnnee_user");
cin=lookup_widget(fenetre_ajout_user,"entryCin_user");
role=lookup_widget(fenetre_ajout_user,"comboboxRole_user");
num=lookup_widget(fenetre_ajout_user,"spinbuttonNumbv_user");
profession=lookup_widget(fenetre_ajout_user,"comboboxProf_user");
appartenance=lookup_widget(fenetre_ajout_user,"comboboxApp_obs");
homme=lookup_widget(fenetre_ajout_user,"radiobuttonHomme_ajout");
femme=lookup_widget(fenetre_ajout_user,"radiobuttonFemme_ajout");
tunisian=lookup_widget(fenetre_ajout_user,"checkbuttonTun_obs");
etrangere=lookup_widget(fenetre_ajout_user,"checkbuttonEtr_obs");


gtk_entry_set_text(GTK_ENTRY(nom),user.nom_user);
gtk_entry_set_text(GTK_ENTRY(prenom),user.prenom_user);
gtk_entry_set_text(GTK_ENTRY(cin),user.cin_user);
gtk_entry_set_text(GTK_ENTRY(profession),user.profession_obs);
int i;
if(strcmp(user.app_politique_obs,"gauche")==0)i=0;
if(strcmp(user.app_politique_obs,"droite")==0)i=1;
if(strcmp(user.app_politique_obs,"autre")==0)i=2;


 gtk_combo_box_set_active(GTK_COMBO_BOX(appartenance),i);






int j;
if(strcmp(user.role_user,"observateur")==0)j=0;
if(strcmp(user.role_user,"electeur")==0)j=1;
if(strcmp(user.role_user,"admin")==0)j=2;
if(strcmp(user.role_user,"agentBV")==0)j=3;
if(strcmp(user.role_user,"autres")==0)j=4;

 gtk_combo_box_set_active(GTK_COMBO_BOX(role),j);
	 gtk_spin_button_set_value(jour,user.date.jour);
	 gtk_spin_button_set_value(mois,user.date.mois);
	 gtk_spin_button_set_value(annee,user.date.annee);




int k;
if(strcmp(user.profession_obs,"professeur")==0)k=0;
if(strcmp(user.profession_obs,"etudiant/e")==0)k=1;
if(strcmp(user.profession_obs,"journaliste")==0)k=2;
if(strcmp(user.profession_obs,"ingenieur")==0)k=3;
if(strcmp(user.profession_obs,"directeur/ice")==0)k=4;
if(strcmp(user.profession_obs,"medecin")==0)k=5;
if(strcmp(user.profession_obs,"technicien/ne")==0)k=6;
if(strcmp(user.profession_obs,"avocat/e")==0)k=8;
if(strcmp(user.profession_obs,"politicien/ne")==0)k=9;
if(strcmp(user.profession_obs,"autre")==0)k=10;


 gtk_combo_box_set_active(GTK_COMBO_BOX(profession),j);
	 gtk_spin_button_set_value(jour,user.date.jour);
	 gtk_spin_button_set_value(mois,user.date.mois);
	 gtk_spin_button_set_value(annee,user.date.annee);



//if(strcmp(user.nationalite_obs,"Tunisienne")==0)
if (choix==1)
{   gtk_toggle_button_set_active(GTK_RADIO_BUTTON(tunisian),TRUE);
    gtk_toggle_button_set_active(GTK_RADIO_BUTTON(etrangere),FALSE);}

//if(strcmp(user.nationalite_obs,"Etrangere")==0)
if (choix==2)
 {   gtk_toggle_button_set_active(GTK_RADIO_BUTTON(etrangere),TRUE);
     gtk_toggle_button_set_active(GTK_RADIO_BUTTON(tunisian),FALSE);}
           
	else {   gtk_toggle_button_set_active(GTK_CHECK_BUTTON(tunisian),FALSE); gtk_toggle_button_set_active(GTK_CHECK_BUTTON(etrangere),FALSE);}
if(strcmp(user.genre_user,"Homme")==0) {
	type=1;
	gtk_toggle_button_set_active(GTK_RADIO_BUTTON(homme),TRUE);
	gtk_toggle_button_set_active(GTK_RADIO_BUTTON(femme),FALSE);}
if(strcmp(user.genre_user,"Femme")==0) {
	gtk_toggle_button_set_active(GTK_RADIO_BUTTON(femme),TRUE);
	gtk_toggle_button_set_active(GTK_RADIO_BUTTON(homme),FALSE);}


	 gtk_spin_button_set_value(num,user.num_bv_user);
}


void
on_buttonAjout_user_clicked            (GtkWidget       *objet,
                                        gpointer         user_data)
{
utilisateur u;
GtkWidget *fenetre_ajout_user;
GtkWidget *fenetre_afficher_user;
GtkWidget *treeview_user;

fenetre_ajout_user = lookup_widget(objet,"ajout_user");

fenetre_afficher_user=lookup_widget(objet,"afficher_user");
gtk_widget_hide(fenetre_afficher_user);

fenetre_ajout_user=create_ajout_user();

gtk_widget_show(fenetre_ajout_user);


treeview_user=lookup_widget(fenetre_afficher_user,"treeview_user");
afficher_user(treeview_user,"utilisateur.txt");
}


void
on_buttonSupp_user_clicked             (GtkWidget       *objet,
                                        gpointer         user_data)
{
supprimer_user("utilisateur.txt",uSupp.cin_user);
GtkWidget *fenetre_afficher,*w1;

GtkWidget *treeview_user;


w1=lookup_widget(objet,"afficher_user");
fenetre_afficher=create_afficher_user();
gtk_widget_hide(fenetre_afficher);
gtk_widget_hide(w1);

gtk_widget_show(fenetre_afficher);

treeview_user=lookup_widget(fenetre_afficher,"treeview_user");

afficher_user(treeview_user,"utilisateur.txt");
}


void
on_buttonStat_user_clicked             (GtkWidget       *objet,
                                        gpointer         user_data)
{
utilisateur u;
GtkWidget *fenetre_statistique;
GtkWidget *fenetre_afficher_user;

fenetre_afficher_user=lookup_widget(objet,"afficher_user");
gtk_widget_hide(fenetre_afficher_user);
fenetre_statistique=create_statistique();
gtk_widget_show(fenetre_statistique);
}


void
on_buttonUser_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *afficher_user;
GtkWidget *main;
afficher_user=lookup_widget(objet,"afficher_user");
main=lookup_widget(objet,"Main");
afficher_user=create_afficher_user();
gtk_widget_show(afficher_user);
gtk_widget_hide(main);
}


void
on_buttonAff_stat_clicked              (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *VB;
GtkWidget *TH;
GtkWidget *TF;
VB=lookup_widget(objet,"TVB");
TH=lookup_widget(objet,"THF");
TF=lookup_widget(objet,"taux");
char tph[20],tpf[20],tvb[20];
float h=TPH("utilisateur.txt",type);
float Tvb=TVB("utilisateur.txt");
float f= TPF ("utilisateur.txt",type);
sprintf(tph,"%.2f",h);
strcat(tph,"%");
sprintf(tpf,"%.2f",f);
strcat(tpf,"%");
sprintf(tvb,"%.2f",Tvb);
strcat(tvb,"%");
gtk_label_set_text(GTK_LABEL(VB),tvb);
//gtk_label_set_text(GTK_LABEL(TH),tph);
//gtk_label_set_text(GTK_LABEL(TF),tpf);
gtk_widget_show(TF);
gtk_widget_show(TH);
}


void
on_buttonPrec_stat_clicked             (GtkWidget       *objet,
                                        gpointer         user_data)
{
utilisateur u;
GtkWidget *fenetre_statistique;
GtkWidget *fenetre_afficher_user;
GtkWidget *treeview_user;

fenetre_statistique=lookup_widget(objet,"statistique");
gtk_widget_hide(fenetre_statistique);
fenetre_afficher_user=create_afficher_user();
gtk_widget_show(fenetre_afficher_user);

treeview_user=lookup_widget(fenetre_afficher_user,"treeview_user");

afficher_user(treeview_user,"utilisateur.txt");
}









/////////////////ranichaima///////////////////////////////////////////////////









void
on_urgent_toggled                      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
 if (gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
	categorie=3;
}


void
on_ajouter_clicked                     (GtkButton       *objet,
                                        gpointer         user_data)
{
 GtkWidget *id,*nle,*nbv ,*recl ;
reclamation rec;
GtkWidget *fenetre_ajout ;
fenetre_ajout =lookup_widget(objet,"ajout_reclamation");

id = lookup_widget (objet,"identifiant" );
nle = lookup_widget (objet,"spinnle");
nbv = lookup_widget (objet,"combonbv");
recl=lookup_widget(objet,"reclamation");




strcpy (rec.identifiant,gtk_entry_get_text(GTK_ENTRY(id)));
rec.nle=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(nle));
strcpy(rec.nbv,gtk_combo_box_get_active_text(GTK_COMBO_BOX(nbv)));
strcpy (rec.reclamation,gtk_entry_get_text(GTK_ENTRY(recl)));
g_print("%d",categorie);
if (confirmer==1){
	ajouter(rec,categorie);}
}


void
on_afficher_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *window,*window2;
	window=create_gestion_reclamation();
	gtk_widget_show(window);
	
	window2=lookup_widget(button,"ajout_reclamation");
	gtk_widget_destroy(window2);

	GtkWidget *treeview;
	treeview=lookup_widget(window,"treeview");
	afficher_rec(treeview);
confirmer=0;
}


void
on_confirmer_toggled                   (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton)){
	confirmer=1;
}
else{
confirmer=0;
}
}


void
on_treeview_row_activated              (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	GtkTreeIter iter;
gchar *identifiant,*nbv, *categorie,*reclamation;
gint *nle;


GtkTreeModel *model = gtk_tree_view_get_model(treeview);

	if (gtk_tree_model_get_iter(model, &iter,path))
	{   
     gtk_tree_model_get (GTK_LIST_STORE(model),&iter,0, &identifiant, 1 , &nle, 2, &nbv, 3, &categorie, 4, &reclamation, -1);

	supprimer_rec(identifiant);
GtkWidget *treeview2;
	treeview2=lookup_widget(treeview,"treeview");
	afficher_rec(treeview2);
 	 }
}


void
on_button_actualiser_rec_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *treeview;
	treeview=lookup_widget(button,"treeview");
	afficher_rec(treeview);
}


void
on_supprimer_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
 reclamation rec;
	char id1[20];
	GtkWidget  *identifiant1 ;
	identifiant1= lookup_widget(button,"identifiant1");
	strcpy(id1,gtk_entry_get_text(GTK_ENTRY(identifiant1)));
	supprimer_rec(id1);
	GtkWidget *treeview;
	treeview=lookup_widget(button,"treeview");
	afficher_rec(treeview);
}


void
on_modifier_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

	char id1[20];
	GtkWidget  *identifiant1 ;
	identifiant1= lookup_widget(button,"identifiant1");
	strcpy(id1,gtk_entry_get_text(GTK_ENTRY(identifiant1)));
	
	
	reclamation rec;

    FILE * f=fopen("reclamations.txt", "r");
    if(f==NULL)
	return 0;
    else
	    {
		while(fscanf(f,"%s %d %s %s %s",rec.identifiant,&rec.nle,rec.nbv,rec.categorie,rec.reclamation)!=EOF)
		{
			if(strcmp(rec.identifiant,id1)==0){
				strcpy(rec_modifier.identifiant,rec.identifiant);
				rec_modifier.nle=rec.nle;
				strcpy(rec_modifier.nbv,rec.nbv);
				strcpy(rec_modifier.categorie,rec.categorie);
				strcpy(rec_modifier.reclamation,rec.reclamation);
			}
		}
		fclose(f);
	    }


	

	GtkWidget *window,*window2;
	window=create_modifier_reclamation();
	gtk_widget_show(window);	
	window2=lookup_widget(button,"gestion_reclamation");
	gtk_widget_destroy(window2);

	GtkWidget *id,*nle,*nbv ,*recl ;


GtkWidget *categorie_faible2,*categorie_moyen2,*categorie_urgent2;
	categorie_faible2=lookup_widget(window,"categorie_faible2");
	categorie_moyen2=lookup_widget(window,"categorie_moyen2");
	categorie_urgent2=lookup_widget(window,"categorie_urgent2");

	if (strcmp(rec_modifier.categorie,"faible")==0){
	categorie=1;
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(categorie_faible2),TRUE);}
else if (strcmp(rec_modifier.categorie,"moyen")==0){
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(categorie_moyen2),TRUE); 
categorie=2;}
else if (strcmp(rec_modifier.categorie,"urgent")==0){
categorie=3;
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(categorie_urgent2),TRUE); 
}







	id = lookup_widget (window,"identifiant2" );
	nle = lookup_widget (window,"spinnle2");
	nbv = lookup_widget (window,"combonbv2");
	recl=lookup_widget(window,"reclamation2");

gtk_entry_set_text(id,rec_modifier.identifiant);
gtk_spin_button_set_value(nle,rec_modifier.nle);

gtk_combo_box_set_active(GTK_ENTRY(nbv),atoi(rec_modifier.nbv)-1);
gtk_entry_set_text(GTK_ENTRY(recl),rec_modifier.reclamation);
}


void
on_chercher_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
 reclamation rec;
	char id1[20];
	GtkWidget  *identifiant1 ;
	identifiant1= lookup_widget(button,"identifiant1");
	strcpy(id1,gtk_entry_get_text(GTK_ENTRY(identifiant1)));
	GtkWidget *treeview;
	treeview=lookup_widget(button,"treeview");
	chercher_rec(id1,treeview);
}


void
on_retour_clicked                      (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *window,*window2;
	window=create_ajout_reclamation();
	gtk_widget_show(window);
	
	window2=lookup_widget(button,"gestion_reclamation");
	gtk_widget_destroy(window2);
}


void
on_button_statistique_rec_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *window,*window2;
	window=create_statistique_reclamation();
	gtk_widget_show(window);
	
	window2=lookup_widget(button,"gestion_reclamation");
	gtk_widget_destroy(window2);

	GtkWidget *treeview;
}


void
on_acceuil_rec_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *window;
GtkWidget *window2;
window2=lookup_widget(button,"gestion_reclamation");
window=lookup_widget(button,"Main");
	window=create_Main();
	gtk_widget_show(window);
	gtk_widget_hide(window2);
}


void
on_confirmer2_toggled                  (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton)){
	confirmer=1;
}
else{
confirmer=0;
}
}





void
on_categorie_urgent2_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
	categorie=3;
}





void
on_button_modifier2_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *id,*nle,*nbv ,*recl ;
	reclamation rec;

	id = lookup_widget (button,"identifiant2" );
	nle = lookup_widget (button,"spinnle2");
	nbv = lookup_widget (button,"combonbv2");
	recl=lookup_widget(button,"reclamation2");




	strcpy (rec.identifiant,gtk_entry_get_text(GTK_ENTRY(id)));
	rec.nle=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(nle));
	strcpy(rec.nbv,gtk_combo_box_get_active_text(GTK_COMBO_BOX(nbv)));
	strcpy (rec.reclamation,gtk_entry_get_text(GTK_ENTRY(recl)));


	if( categorie==1)
strcpy (rec.categorie,"faible");
	if( categorie==2)
strcpy (rec.categorie,"moyen");
	if( categorie==3)
strcpy (rec.categorie,"urgent");

	if (confirmer==1){
		modifier_rec(rec_modifier.identifiant,rec);
	}
}


void
on_button_afficher2_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *window,*window2;
	window=create_gestion_reclamation();
	gtk_widget_show(window);
	
	window2=lookup_widget(button,"modifier_reclamation");
	gtk_widget_destroy(window2);

	GtkWidget *treeview;
	treeview=lookup_widget(window,"treeview");
	afficher_rec(treeview);
	confirmer=0;
}








void
on_button_retour_stat1_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *window,*window2;
	window=create_gestion_reclamation();
	gtk_widget_show(window);
	
	window2=lookup_widget(button,"statistique_reclamation");
	gtk_widget_destroy(window2);
}


void
on_ajout_reclamation_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *main;
GtkWidget *window;
main=lookup_widget(button,"Main");
window=lookup_widget(button,"ajout_reclamation");
gtk_widget_hide(main);
window=create_ajout_reclamation();
gtk_widget_show(window);

}


void
on_faible_toggled                      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
	categorie=1;
}


void
on_moyen_toggled                       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
	categorie=2;
}


void
on_categorie_faible2_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
	categorie=1;
}


void
on_categorie_moyen2_toggled            (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
	categorie=2;
}

////////////////////////login//////////////////////////////////////////
void
on_buttonConnect_clicked               (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *username, *password, *main, *windowlogin;

 
char user[20];
char pasw[20];
int trouve;
username = lookup_widget (objet, "entrylogin1");
password = lookup_widget (objet, "entrypassword2");
strcpy(user, gtk_entry_get_text(GTK_ENTRY(username)));
strcpy(pasw, gtk_entry_get_text(GTK_ENTRY(password)));
trouve=verif_login(user,pasw);

if(trouve==1)
{
main=create_Main();
gtk_widget_show (main);
windowlogin=lookup_widget(objet,"interface_login");
gtk_widget_destroy(windowlogin);
}
}

