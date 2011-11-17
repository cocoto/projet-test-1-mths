#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graphe.h"

int main(int argc,char* argv[])
{
	//Création d'un nouveau graphique
	liste_sommet* graphe=malloc(sizeof(liste_sommet));
	graphe->depart=NULL;
	//Parsing du graphe
	char *nomfichier=argv[1];
	if(parse(nomfichier,graphe)==0)
	{
		printf("Impossible d'ouvrir le fichier");
		exit(1); //on quitte le programme avec une erreur 1
	}
	
	
	//Affichage du graphe
	//affiche(graphe);
	printf("Mesure Macabre : %d \n",mcCabe(graphe));
	
	return 0;
}
