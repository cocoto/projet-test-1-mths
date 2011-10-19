#include "graphe.h"

// Ajoute un sommet à la fin de la liste donnée, avec le numéro donné
void ajouter_sommet(int numero, liste_sommet* liste)
{
	cellule_sommet nouveau;
	nouveau.numero=numero;
	nouveau.suivante=NULL;
	if(liste.depart==NULL)
	{
		liste.depart=nouveau;
		liste.fin=nouveau;
	}
	else
	{
		liste.fin.suivante=nouveau;
		liste.fin=nouveau;
	}
}

// Ajoute une arete au début de la liste donnée
void ajouter_arete_l(char* etiquette, cellule_sommet* sommet, int numero)
{
	cellule_arete nouveau;
	nouveau.arrive=numero;
	nouveau.etiquette = etiquette;
	nouveau.suivante=sommet.liste_arete;
	sommet.liste_arete=nouveau;
}


// Algorithme de recherche d'une liste
//Précondition : La liste doit comporter un sommet au minimum
cellule_sommet recherche_sommet(int sommet,liste_sommet* liste)
{
	cellule_sommet parcour=liste.depart;
	int trouve=0;
	while (!(trouve=(parcour.numero==sommet)) && parcour.suivant!=NULL)
	{
		parcour=parcour.suivant;
	}
	if(trouve) //Utilisation normale de la fonction
	{
		return parcour;
	}
	else	//si jamais on appel un sommet inconnu (précondition non respectée) @TODO attention aux boucles infinies
	{
		ajouter_sommet(sommet,liste);
		return recherche_sommet(sommet,liste);
	}
}


void ajouter_arete (char* etiquette, int sommet_d, int sommet_c, liste_sommet* liste) //sommet départ et sommet cible
{
	ajouter_arrete_l(etiquette, recherche_sommet(sommet_d,liste), sommet_c);
}
