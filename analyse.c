#include <stdlib.h>
#include <stdio.h>
#include "graphe.h"

int mcCabe(liste_sommet* graphe)
{
	int nbsommet=0;
	int nbarrete=0;
	cellule_sommet *parcours=graphe->depart;
    	while (parcours!=NULL){
		cellule_arete *reparcours=parcours->liste_arete;
		nbsommet++;
		while (reparcours!=NULL){
		    nbarrete++;
		    reparcours=reparcours->suivante;
		}
		parcours=parcours->suivant;
    	}
    	return nbarrete-nbsommet+2;
}
