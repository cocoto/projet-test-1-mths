#include <stdio.h>
#include "graphe.h"

// Ajoute un sommet à la fin de la liste donnée, avec le numéro donné
void ajouter_sommet(int numero, liste_sommet* liste, char* etiquette)
{
	cellule_sommet *nouveau;
	nouveau->numero=numero;
	nouveau->etiquette=etiquette;
	nouveau->suivant=NULL;
	if(liste->depart==NULL)
	{
		liste->depart=nouveau;
		liste->fin=nouveau;
	}
	else
	{
		liste->fin->suivant=nouveau;
		liste->fin=nouveau;
	}
}

// Ajoute une arete au début de la liste donnée
void ajouter_arete_l(char* etiquette, cellule_sommet* sommet, int numero)
{
	cellule_arete *nouveau;
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
        while (reparcours!=NULL){
            printf("%d -- %s --> %d", dep , reparcours->etiquette , reparcours->arrive);
            reparcours=reparcours->suivante;
        }
        parcours=parcours->suivant;
    }
	printf("ZBOOOOOOOB");
}


void main(){
    liste_sommet* encule;
    encule->depart=NULL;

    ajouter_sommet(1,encule ,"");
    ajouter_sommet(2,encule,"");
    ajouter_sommet(3,encule,"");
    ajouter_sommet(4,encule,"");
    ajouter_sommet(5,encule,"");
    ajouter_arete("je",1,2,encule);
    ajouter_arete("suis",2,3,encule);
    ajouter_arete("un",3,4,encule);
    ajouter_arete("connard",4,5,encule);
    ajouter_arete("assis a cote d'",3,5,encule);
    affiche(encule);

}
