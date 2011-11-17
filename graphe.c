#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"
#include <string.h>

// Ajoute un sommet à la fin de la liste donnée, avec le numéro donné
void ajouter_sommet(int numero, liste_sommet* liste, char* etiquette)
{   cellule_sommet *nouveau=malloc(sizeof(cellule_sommet));
	nouveau->numero=numero;
	nouveau->etiquette=etiquette;
	nouveau->suivant=NULL;
	nouveau->liste_arete = NULL;
	if(liste->depart==NULL)
	{  	liste->depart=nouveau;
		liste->fin=nouveau;
	}
	else
	{   liste->fin->suivant=nouveau;
		liste->fin=nouveau;
	}
}

// Ajoute une arete au début de la liste donnée
void ajouter_arete_l(char* etiquette, cellule_sommet* sommet, int numero)
{
	cellule_arete *nouveau=malloc(sizeof(cellule_arete));
	nouveau->arrive=numero;
	nouveau->etiquette = etiquette;
	nouveau->suivante=sommet->liste_arete;
	sommet->liste_arete=nouveau;
}


// Algorithme de recherche d'une liste
//Précondition : La liste doit comporter un sommet au minimum
cellule_sommet* recherche_sommet(int sommet,liste_sommet* liste)
{
	cellule_sommet *parcour=liste->depart;
	int trouve=0;
	while (!(trouve=(parcour->numero==sommet)) && parcour->suivant!=NULL)
	{
		parcour=parcour->suivant;
	}
	if(trouve) //Utilisation normale de la fonction
	{
		return parcour;
	}
	else	//si jamais on appel un sommet inconnu (précondition non respectée) @TODO attention aux boucles infinies
	{
		ajouter_sommet(sommet,liste,"");
		return recherche_sommet(sommet,liste);
	}
}


void ajouter_arete (char* etiquette, int sommet_d, int sommet_c, liste_sommet* liste) //sommet départ et sommet cible
{
	ajouter_arete_l(etiquette, recherche_sommet(sommet_d,liste), sommet_c);
}

void affiche(liste_sommet* liste)
{
    cellule_sommet *parcours=liste->depart;
    while (parcours!=NULL){
        cellule_arete *reparcours=parcours->liste_arete;
        int dep= parcours->numero;
        char * etiqu = parcours->etiquette;
        printf("sommet %d %s \n", dep , etiqu);
        while (reparcours!=NULL){
            printf("\t --%s--> sommet %d\n", reparcours->etiquette , reparcours->arrive);
            reparcours=reparcours->suivante;
        }
        parcours=parcours->suivant;
    }
}


/*void main(){
    liste_sommet* maman;
    maman->depart=NULL;
    ajouter_sommet(1,maman ,"");
    ajouter_sommet(2,maman,"");
    ajouter_sommet(3,maman,"si");
    ajouter_sommet(4,maman,"alors");
    ajouter_sommet(5,maman,"Fsi");
    ajouter_arete("bla",1,2,maman);
    ajouter_arete("bla",2,3,maman);
    ajouter_arete("vrai",3,4,maman);
    ajouter_arete("exectution",4,5,maman);
    ajouter_arete("faux",3,5,maman);
    affiche(maman);

}*/
