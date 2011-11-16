#include <stdlib.h>
#include <stdio.h>
#include "graphe.h"

int main(char* argv[])
{
	liste_sommet* graphe;
	graphe->depart=NULL;
	
	//Ouverture du fichier contenant le code
	FILE* fichier=NULL;
	fichier=fopen("pseudocode.txt","r");
	if(fichier==NULL)
	{
		printf("Impossible d'ouvrir le fichier");
		exit(1); //on quitte le programme avec une erreur 1
	}
	
	char motlu[50];
	int sommetactuel=0;
	int savesommet;
	while(!feof(fichier))
	{
		sommetactuel++;
		fscanf(fichier,"%s",motlu);
		if(strcmp(motlu,"Si")==0) //si nous tombons sur une conditionnelle
		{	
			char* cond=malloc(sizeof(char));
			fscanf(fichier,"%s",motlu);
			while(strcmp(motlu,"Alors")!=0)
			{
				int lenmot=strlen(motlu);
				int lencond=strlen(cond);
				int taille=lenmot+lencond+1;
				char* result;
				cond = realloc(cond,sizeof(char)*taille);
				strcat(cond,motlu);
				//printf("apres : %s \n",cond);
				//free(cond);
				//cond=condtemp;
				fscanf(fichier,"%s",motlu);
			}
			//ajouter_sommet(sommetactuel,graphe,cond);
			savesommet=sommetactuel; //On sauvegarde le sommet actuel
			affiche();
			free(cond);
		}
	}
	return 0;
}
