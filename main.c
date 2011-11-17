#include <stdlib.h>
#include <stdio.h>
#include "graphe.h"
#include <string.h>

int main(char* argv[])
{
	//Création d'un nouveau graphique
	liste_sommet* graphe=malloc(sizeof(liste_sommet));
	graphe->depart=NULL;
	
	//Parsing du graphe
	char *nomfichier="pseudocode.txt";
	if(parse(nomfichier,graphe)==0)
	{
		printf("Impossible d'ouvrir le fichier");
		exit(1); //on quitte le programme avec une erreur 1
	}
	
	
	//Affichage du graphe
	affiche(graphe);
	
	
	return 0;
}
