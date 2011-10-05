#include <stdlib.h>
#include <stdio.h>
struct cellule_arete {
	int arrive;
	char etiquette[];	
	cellule suivante;
}
struct cellule_sommet {
	int numero;
	cellule_arete liste_arete;
	cellule_sommet suivante;
}
struct liste_sommet {
	cellule_sommet depart;
	cellule_sommet fin;
	int taille;
}
liste_sommet liste;

// Ajoute un sommet à la fin de la liste donnée, avec le numéro donné
void ajouter_sommet(int numero, liste_sommet liste)
{
	//@TODO a vérifier
	cellule_sommet nouveau;
	nouveau.numero=numero;
	liste.fin.suivante=nouveau;
	liste.fin=nouveau;
}

// Ajoute une arete au début de la liste donnée
void ajouter_arete(char* etiquette, cellule_arete liste_arete)
{
	cellule_arete nouveau;
	nouveau.etiquette = etiquette;
	//@TODO A finir
}
