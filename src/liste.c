#include<stdio.h>
#include"liste.h"

void ajouter_liste(liste l)
{
	FILE *f;
	f=fopen("les_liste.txt","a");
	if(f!=NULL)
    	{
		l.nbr_vote=0;
        	fprintf(f,"%s %d %s %d %d %d %d %d\n",l.nom_liste,l.id_liste,l.id_tete_liste,l.nombre_condidat,l.date.jour,l.date.mois,l.date.annee,l.nbr_vote);
		l.nbr_vote=0;
        	fclose(f);
        	
    	}
    	

}



/*int nbv()
{
 int r=0,v=0;
 liste l,u;
 FILE *f;
 f=fopen("listes_vote.txt","r");
while(fscanf(f,"%s %d %s %d %d %d %d %d\n",l.nom_liste,&l.id_liste,l.id_tete_liste,&l.nombre_condidat,&l.date.jour,&l.date.mois,&l.date.annee,&l.nbr_vote)!=EOF)
{ u=recherche_liste_id(l.id_liste);
 
 u.nbr_vote++;
 r=modif_liste(u.id_liste, u );
 
}
}*/

int nbv(liste l)
{
 int r;
 l.nbr_vote++;
 r=modif_liste(l.id_liste,l);
}




















int l_ordre()
{
int i=-1,c=0,test=1,aux,aux2,a=0;
liste l,tri;
 FILE *f,*f1;
 int t[100],b[100];
 f=fopen("les_liste.txt","r");
 f1=fopen("l_ordre.txt","w");
while(fscanf(f,"%s %d %s %d %d %d %d %d\n",l.nom_liste,&l.id_liste,l.id_tete_liste,&l.nombre_condidat,&l.date.jour,&l.date.mois,&l.date.annee,&l.nbr_vote)!=EOF)
{i++;
 t[i]=l.id_liste;
 b[i]=l.nbr_vote;
  
}
while (test!=0)
{test=0;
c=0;
for (c;c<=i;c++){
if (b[c]<b[c+1])
{ test=1;
 aux=t[c];
 aux2=b[c];
 t[c]=t[c+1];
 b[c]=b[c+1];
 t[c+1]=aux;
 b[c+1]=aux2; }
}

}
c=0;
while(c<=i)
{
 tri=recherche_liste_id(t[c]);
fprintf(f1,"%s %d %s %d %d %d %d %d\n",tri.nom_liste,tri.id_liste,tri.id_tete_liste,tri.nombre_condidat,tri.date.jour,tri.date.mois,tri.date.annee,tri.nbr_vote);
a=1;
c++;

}
fclose(f);
fclose(f1);
 return a;

}

int modif_liste( int id, liste nouv )
{
    int tr=0;
    liste l;
    FILE * f=fopen("les_liste.txt", "r");
    FILE * f2=fopen("aux.txt", "w");
    if(f!=NULL && f2!=NULL)
    {
        while(fscanf(f,"%s %d %s %d %d %d %d %d\n",l.nom_liste,&l.id_liste,l.id_tete_liste,&l.nombre_condidat,&l.date.jour,&l.date.mois,&l.date.annee,&l.nbr_vote)!=EOF)
        {
            if(l.id_liste== id)
            {
                fprintf(f2,"%s %d %s %d %d %d %d %d\n",nouv.nom_liste,nouv.id_liste,nouv.id_tete_liste,nouv.nombre_condidat,nouv.date.jour,nouv.date.mois,nouv.date.annee,nouv.nbr_vote);
                tr=1;
            }
            else
                fprintf(f2,"%s %d %s %d %d %d %d %d\n",l.nom_liste,l.id_liste,l.id_tete_liste,l.nombre_condidat,l.date.jour,l.date.mois,l.date.annee,l.nbr_vote);

        }
    }
    fclose(f);
    fclose(f2);
    remove("les_liste.txt");
    rename("aux.txt", "les_liste.txt");
    return tr;
}
liste recherche_liste(char nom[])
{
    liste l;
    int tr=0;
    FILE * f=fopen("les_liste.txt", "r");
    if(f!=NULL)
    {
        while(tr==0 && fscanf(f,"%s %d %s %d %d %d %d %d\n",l.nom_liste,&l.id_liste,l.id_tete_liste,&l.nombre_condidat,&l.date.jour,&l.date.mois,&l.date.annee,&l.nbr_vote)!=EOF)
        {
            if(strcmp(nom,l.nom_liste)==0){
                tr=1;}
        }
    }
    
    if(tr==0){
        l.id_liste=-1;}
	fclose(f);
    return l;

}

liste recherche_liste_id(int id)
{
    liste l;
    int tr=0;
    FILE * f=fopen("les_liste.txt", "r");
    if(f!=NULL)
    {
        while(tr==0 && fscanf(f,"%s %d %s %d %d %d %d %d\n",l.nom_liste,&l.id_liste,l.id_tete_liste,&l.nombre_condidat,&l.date.jour,&l.date.mois,&l.date.annee,&l.nbr_vote)!=EOF)
        {
            if(id==l.id_liste)
               { tr=1; }
             
        }
    
    }
 
    return l;

}







int supprime_liste(int id)
{
    int tr=0;
    liste l;
    FILE * f=fopen("les_liste.txt", "r");
    FILE * f2=fopen("nou.txt", "w");
    if(f!=NULL && f2!=NULL)
    {
        while(fscanf(f,"%s %d %s %d %d %d %d %d\n",l.nom_liste,&l.id_liste,l.id_tete_liste,&l.nombre_condidat,&l.date.jour,&l.date.mois,&l.date.annee,&l.nbr_vote)!=EOF)
        {
            if(l.id_liste== id)
                tr=1;
            else
                fprintf(f2,"%s %d %s %d %d %d %d %d\n",l.nom_liste,l.id_liste,l.id_tete_liste,l.nombre_condidat,l.date.jour,l.date.mois,l.date.annee,l.nbr_vote);
        }
    }
    fclose(f);
    fclose(f2);
    remove("les_liste.txt");
    rename("nou.txt", "les_liste.txt");
    return tr;
}




int id_generate()
{
 int i=0;
 FILE *f ;
 liste l;
 f=fopen("les_liste.txt","r");
 if(f!=NULL)
{
 while(fscanf(f,"%s %d %s %d %d %d %d %d\n",l.nom_liste,&l.id_liste,l.id_tete_liste,&l.nombre_condidat,&l.date.jour,&l.date.mois,&l.date.annee,&l.nbr_vote)!=EOF){ i++;}
i++;
return i;
}


}







void voter(liste l)
{
FILE *f;
f=fopen("listes_vote.txt","a");
fprintf(f,"%s %d %s %d %d %d %d %d\n",l.nom_liste,l.id_liste,l.id_tete_liste,l.nombre_condidat,l.date.jour,l.date.mois,l.date.annee,l.nbr_vote);
fclose(f);


}
