#include <stdlib.h>
#include <stdio.h>
#include "graphe.h"
#include <string.h>

int main(char* argv[])
{
	liste_sommet* graphe=malloc(sizeof(liste_sommet));
	graphe->depart=NULL;
	
	//Ouverture du fichier contenant le code
	FILE* fichier=NULL;
	fichier=fopen("pseudocode.txt","r");
	if(fichier==NULL)
	{
		printf("Impossible d'ouvrir le fichier");
		exit(1); //on quitte le programme avec une erreur 1
	}
	
	char motlu[50];			//Mot lus lors du parsing (suite de caractère suivit de " " ou \n
	char* instruction=malloc(sizeof(char)); //Instruction -> ensemble des mots jusqu'à ";"
	int sommetactuel=0;		//Sommet actuellement lu (branche)
	int nbsommet=0;			//Nombre de sommet du graphe
	int savesommet[50];		// Tableau de "sauvegarde de sommet" @TODO mode dynamique
	int taillesave=0;		// Taille du tableau
	fscanf(fichier,"%s",motlu); //Lecture du premier mot
	while(!feof(fichier))		//Tant que le fichier n'est pas terminé
	{	
		printf("%s",motlu);
		if(strcmp(motlu,"Si")==0) //si nous tombons sur une conditionnelle
		{	
			char* cond=malloc(sizeof(char)); //On initialise l'etiquette de conditionnelle
			fscanf(fichier,"%s",motlu);	//On lis le premier "mot" de la conditionnelle
			while(strcmp(motlu,"Alors")!=0)	//Tant que le Tant-Que n'est pas lu
			{
				int lenmot=strlen(motlu); //On calcul la taille de la nouvelle étiquette
				int lencond=strlen(cond);
				int taille=lenmot+lencond+1;
				cond = realloc(cond,sizeof(char)*taille); //On réalloue la mémoire
				strcat(cond,motlu);				//Puis on concatène le nouveau mot
				fscanf(fichier,"%s",motlu);
			}
			ajouter_sommet(nbsommet+1,graphe,cond);//On créer un nouveau sommet avec l'etiquette
			nbsommet++;
			ajouter_arete("",sommetactuel,nbsommet,graphe); //On branche ce nouveau sommet à notre graphe
			sommetactuel=nbsommet;	//on se place sur le sommet conditionnel
			savesommet[taillesave]=sommetactuel; //On sauvegarde le sommet actuel
			taillesave++;
			ajouter_sommet(nbsommet+1,graphe,""); //On creer la branche "Vraie"
			nbsommet++;
			ajouter_arete("vrai",sommetactuel,nbsommet,graphe);
			sommetactuel=nbsommet;
			
		}
		else if(strcmp(motlu,"Sinon")==0) //si nous tombons sur une conditionnelle
		{	
			ajouter_sommet(nbsommet+1,graphe,""); //On creer la branche "Vraie"
			nbsommet++;
			ajouter_arete("faux",savesommet[taillesave-1],nbsommet,graphe);
			savesommet[taillesave-1]=sommetactuel;	//on sauvegarde la fin de la branche "vrai"
			sommetactuel=nbsommet;
		}
		else if(strcmp(motlu,"Fsi")==0) //si nous tombons sur une conditionnelle
		{	
			ajouter_sommet(nbsommet+1,graphe,""); //On creer la branche "Vraie"
			nbsommet++;
			ajouter_arete("",sommetactuel,nbsommet,graphe);
			ajouter_arete("",savesommet[taillesave-1],nbsommet,graphe);
			taillesave--;
			sommetactuel=nbsommet;
		}
		else if(strcmp(motlu,"Tantque")==0) //si nous tombons sur une conditionnelle
		{	
			char* cond=malloc(sizeof(char)); //On initialise l'etiquette de conditionnelle
			fscanf(fichier,"%s",motlu);	//On lis le premier "mot" de la conditionnelle
			while(strcmp(motlu,"Faire")!=0)	//Tant que le Tant-Que n'est pas lu
			{
				int lenmot=strlen(motlu); //On calcul la taille de la nouvelle étiquette
				int lencond=strlen(cond);
				int taille=lenmot+lencond+1;
				cond = realloc(cond,sizeof(char)*taille); //On réalloue la mémoire
				strcat(cond,motlu);			//Puis on concatène le nouveau mot
				fscanf(fichier,"%s",motlu);
			}
			ajouter_sommet(nbsommet+1,graphe,cond);//On créer un nouveau sommet avec l'etiquette
			nbsommet++;
			ajouter_arete("",sommetactuel,nbsommet,graphe); //On branche ce nouveau sommet à notre graphe
			sommetactuel=nbsommet;
			savesommet[taillesave]=sommetactuel; //On sauvegarde le sommet actuel
			taillesave++;
			
			ajouter_sommet(nbsommet+1,graphe,""); //On creer la branche "Vraie"
			nbsommet++;
			ajouter_arete("vrai",sommetactuel,nbsommet,graphe);
			sommetactuel=nbsommet;
		}
		else if(strcmp(motlu,"Ftantque")==0) //si nous tombons sur une conditionnelle
		{	
			ajouter_arete("",sommetactuel,savesommet[taillesave-1],graphe);//On relie ce nouveau sommet au graph
			ajouter_sommet(nbsommet+1,graphe,"");//On créer un nouveau sommet (sortie de tantque)
			nbsommet++;
			ajouter_arete("faux",savesommet[taillesave-1],nbsommet,graphe);
			taillesave--;
			sommetactuel=nbsommet;
		}
		else
		{
			int lenmot=strlen(motlu); //On calcul la taille de la nouvelle étiquette
			int leninstruction=strlen(instruction);
			int taille=lenmot+leninstruction+1;
			instruction=realloc(instruction,sizeof(char)*taille);//On réalloue la mémoire
			strcat(instruction,motlu);			//Puis on concatène le nouveau mot
			if(motlu[strlen(motlu)-1]==';')
			{
				ajouter_sommet(nbsommet+1,graphe,"");//On créer un nouveau sommet
				nbsommet++;
				ajouter_arete(instruction,sommetactuel,nbsommet,graphe);
				sommetactuel=nbsommet;
				instruction=malloc(sizeof(char));
			}
		}
		fscanf(fichier,"%s",motlu);
	}//Parcourt du ficher
	affiche(graphe);
	return 0;
	
}
