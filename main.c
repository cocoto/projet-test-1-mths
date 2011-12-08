#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graphe.h"
#include "analyse.h"
/*PROGRAMME PRINCIPAL*/
int main(int argc,char* argv[])
{
	//Création d'un nouveau graphique
	liste_sommet* graphe=malloc(sizeof(liste_sommet));
	graphe->depart=NULL;
	//Parsing du graphe
	char nomfichier[200];
	int sortie = 0;		//Booléen de sortie de programme
	int fichier_choisi = 0;	//Booléen de graphique chargé
	while(sortie==0){
	int choix;
	printf("\n\nfaites un choix : \n 1. choisir un programme à analyser\n 2. affichage du graphe\n 3. Mesure de McCabe\n 4. Couverture des chemins\n 5. Couverture des Sommets\n 6. Couverture des Aretes\n 7. Sortie\n");
	scanf("%d", &choix);
	switch(choix)
	{
		case 1:
			printf("entrez le nom du programme : ");
			scanf("%s", &nomfichier[0]);
			if(parse(nomfichier,graphe)==0)
			{
			printf("Impossible d'ouvrir le fichier");
			}else{
				printf("graphe calculé sans erreur");
				fichier_choisi=1;
				}
			break;
		case 2:
			if(fichier_choisi==0){
				printf("\n\nVous n'avez pas encore choisi de fichier ...\n\n");
			}else{//Affichage du graphe
			affiche(graphe);}
			break;
		case 3:
			if(fichier_choisi==0){
				printf("\n\nVous n'avez pas encore choisi de fichier ...\n\n");
			}else{
			printf("Mesure de Mc Cabe : %d \n",mcCabe(graphe));}
			break;
		case 4:
			if(fichier_choisi==0){
				printf("\n\nVous n'avez pas encore choisi de fichier ...\n\n");
			}else{
			printf("Couverture des CHEMINS ======================\n");
			int chemin[50]; //On crée un chemin vide d'une taille sans importance
			affiche_couverture(couverture_chemins(graphe,chemin,0,50,0));}
			break;
		case 5:
			if(fichier_choisi==0){
				printf("\n\nVous n'avez pas encore choisi de fichier ...\n\n");
			}else{
			printf("Couverture des SOMMETS =====================\n");
			int chemin_2[50];//On crée un chemin vide d'une taille sans importance
			affiche_couverture(couverture_sommets(graphe,chemin_2,0,50,0,-1));}
			break;
		case 6:
			if(fichier_choisi==0){
				printf("\n\nVous n'avez pas encore choisi de fichier ...\n\n");
			}else{printf("Couverture des ARETES =====================\n");
			int chemin_3[50];//On crée un chemin vide d'une taille sans importance
			affiche_couverture(couverture_aretes(graphe,chemin_3,0,50,0,-1));}
			break;
		case 7:
			sortie = 1;
			break;
		default:
			printf("commande inconnue\n\n");

	}
	}
	
	return 0;
}
