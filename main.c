#include <stdlib.h>
#include <stdio.h>
struct cellule_arete {
	int arrive;
	char etiquette[];	
	cellule suivante;
}
struct cellule_sommet {
	int numero;
	cellule_arete liste;
	cellule_sommet suivante;
}
struct liste_sommet {
	cellule_sommet depart;
	cellule_sommet fin;
	int taille;
}

