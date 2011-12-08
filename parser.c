#include "graphe.h"
#include "parser.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int parse(char *nomfichier,liste_sommet *graphe)
{
//Ouverture du fichier contenant le code
	FILE* fichier=NULL;
	fichier=fopen(nomfichier,"r");
	if(fichier==NULL)
	{
		return 0; //on quitte le programme avec une erreur
	}
	
	//==============Variables du parser
	char motlu[50];			//Mot lus lors du parsing (suite de caractère suivit de " " ou \n
	char* instruction=malloc(sizeof(char)); //Instruction -> ensemble des mots jusqu'à ";"
	int sommetactuel=0;		//Sommet actuellement lu (branche)
	int nbsommet=0;			//Nombre de sommet du graphe
	int sinon=0; 			//Flag passé à 1 lors d'un "sinon"
	//==============Tableau de sauvegarde
	int savesommet[50];		// Tableau de "sauvegarde de sommet"
	int taillesave=0;		// Taille du tableau
	
	
	//==============Execution du parsing
	fscanf(fichier,"%s",motlu); //Lecture du premier mot
	while(!feof(fichier))		//Tant que le fichier n'est pas terminé
	{	
		//printf("%s",motlu);
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
			ajouter_sommet(nbsommet+1,graphe,cond);//On crée un nouveau sommet avec l'etiquette
			nbsommet++;
			ajouter_arete("",sommetactuel,nbsommet,graphe); //On branche ce nouveau sommet à notre graphe
			sommetactuel=nbsommet;	//on se place sur le sommet conditionnel
			savesommet[taillesave]=sommetactuel; //On sauvegarde le sommet actuel
			taillesave++;
			ajouter_sommet(nbsommet+1,graphe,""); //On crée la branche "Vraie"
			nbsommet++;
			ajouter_arete("vrai",sommetactuel,nbsommet,graphe);
			sommetactuel=nbsommet;
			sinon=0;
			
		}
		else if(strcmp(motlu,"Sinon")==0) //si nous tombons sur une conditionnelle
		{	
			ajouter_sommet(nbsommet+1,graphe,""); //On crée la branche "Vraie"
			nbsommet++;
			ajouter_arete("sinon (faux)",savesommet[taillesave-1],nbsommet,graphe);
			savesommet[taillesave-1]=sommetactuel;	//on sauvegarde la fin de la branche "vrai"
			sommetactuel=nbsommet;
			sinon=1;
		}
		else if(strcmp(motlu,"Fsi")==0) //si nous tombons sur une conditionnelle
		{	
			ajouter_sommet(nbsommet+1,graphe,"");
			nbsommet++;
			
			//Si l'on est pas passé par un "sinon", l'étiquette doit porter la mention "faux"
			char *etiquette;
			if(sinon==0)
			{
				etiquette="faux";
			}
			else
			{
				etiquette="";
			}
			ajouter_arete("",sommetactuel,nbsommet,graphe);
			ajouter_arete(etiquette,savesommet[taillesave-1],nbsommet,graphe);
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
			ajouter_sommet(nbsommet+1,graphe,cond);//On crée un nouveau sommet avec l'etiquette
			nbsommet++;
			ajouter_arete("",sommetactuel,nbsommet,graphe); //On branche ce nouveau sommet à notre graphe
			sommetactuel=nbsommet;
			savesommet[taillesave]=sommetactuel; //On sauvegarde le sommet actuel
			taillesave++;
			
			ajouter_sommet(nbsommet+1,graphe,""); //On crée la branche "Vrai"
			nbsommet++;
			ajouter_arete("vrai",sommetactuel,nbsommet,graphe);
			sommetactuel=nbsommet;
		}
		else if(strcmp(motlu,"Ftantque")==0) //si nous tombons sur une conditionnelle
		{	
			ajouter_arete("",sommetactuel,savesommet[taillesave-1],graphe);//On relie ce nouveau sommet au graph
			ajouter_sommet(nbsommet+1,graphe,"");//On crée un nouveau sommet (sortie de tantque)
			nbsommet++;
			ajouter_arete("Ftantque",savesommet[taillesave-1],nbsommet,graphe); //Et l'arete correspondante
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
				ajouter_sommet(nbsommet+1,graphe,"");//On crée un nouveau sommet
				nbsommet++;
				ajouter_arete(instruction,sommetactuel,nbsommet,graphe);
				sommetactuel=nbsommet;
				instruction=malloc(sizeof(char));
			}
		}
		fscanf(fichier,"%s",motlu);
	}//Parcourt du ficher
	return 1;
}
