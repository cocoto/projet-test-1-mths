#include <stdlib.h>
#include <stdio.h>
#include "graphe.h"
#include <string.h>
#include "analyse.h"

//Calcul du nombre de Mc Cabe
int mcCabe(liste_sommet* graphe)
{
	int nbsommet=0;
	int nbarrete=0;
	cellule_sommet *parcours=graphe->depart;
	//On parcourt le graphique
    	while (parcours!=NULL){
		cellule_arete *reparcours=parcours->liste_arete;
		nbsommet++;	//On compte le nombre de sommet
		while (reparcours!=NULL){	//On parcourt chaque branche du sommet
		    nbarrete++;	//On compte de nombre d'arretes
		    reparcours=reparcours->suivante;
		}
		parcours=parcours->suivant;
    	}
    	return nbarrete-nbsommet+2; //Mcabe = Nbarretes - Nbsommets +2
}

//Procédure d'affichage d'une couverture (liste de chemins (tableaux d'entiers)
void affiche_couverture(struct liste_chemin* chemins)
{
	int i=0;
	while(chemins!=NULL) //On parcour l'ensemble des chemins (liste chainée)
	{
		struct liste_chemin* parcour=chemins;
		printf("CHEMIN : ");
		for(i=0;i<parcour->taille_chemin;i++) //On parcour un chemin
		{
			printf(" --> %d",parcour->chemin[i]); //On affiche tous les sommets du chemin
		}
		printf("\n");
		chemins=parcour->suivant;
	}
}

//Créer la couverture des chemins élémentaires
//graphe = graphique à parcourir, chemin=chemin à complèter, taille_chemin = taille du chemin fournis, long_total= longueur du tableau dans lequel se trouve le chemin
//sommet_suivant : sommet de départ
struct liste_chemin* couverture_chemins(liste_sommet* graphe,int *chemin,int taille_chemin, int long_total, int sommet_suivant)
{
	struct liste_chemin *resultat=malloc(sizeof(struct liste_chemin));
	int arret=0; //Booléen d'arret de boucle, permet un seul return à la fin du programme
	cellule_sommet *parcour=recherche_sommet(sommet_suivant,graphe); //Curseur de parcourt
	while(arret==0) //tant que nous ne tombons pas sur une conditionnelle
	{
		if(taille_chemin-1==long_total) //si on dépasse la mémoire
		{
			chemin=realloc(chemin,sizeof(int)*long_total*2);//On réalloue le tableau de taille double
			long_total*=2;
		}
		if(parcour->suivant==NULL) //Si l'on arrive à la fin de notre chemin
		{
			chemin[taille_chemin]=parcour->numero;//On ajoute le sommet à notre chemin
			taille_chemin++;
			resultat=malloc(sizeof(struct liste_chemin)); //On créer une liste chaînée d'un seul chemin
			resultat->chemin=chemin;
			resultat->suivant=NULL;
			resultat->taille_chemin=taille_chemin;
			arret=1; //On sort de la boucle
		}
		else
		{
			if(parcour->liste_arete->suivante!=NULL) //Si nous sommes sur une conditionnelle
			{
				//Si nous avons déjà croisé ce sommet, nous venons de boucler un tant_que
				if(recherche_sommet_chemin(chemin,taille_chemin,parcour->numero)==1)
				{
					chemin[taille_chemin]=parcour->numero;//On ajoute sommet à notre chemin
					taille_chemin++;
					parcour=recherche_sommet(parcour->liste_arete->arrive,graphe);//On saute à la sortie du tant_que
				}
				else
				{
					//Si nous sommes dans un SI ou un Tantque (premier passage)
					struct liste_chemin *resultat2=malloc(sizeof(struct liste_chemin));
					chemin[taille_chemin]=parcour->numero;//On ajoute sommet à notre chemin
					taille_chemin++;
					
					//On dédouble le chemin déjà parcouru
					int* chemin2=malloc(sizeof(int)*taille_chemin); //On créé une copie de notre chemin
					memcpy(chemin2,chemin,sizeof(int)*taille_chemin);
					
					resultat=couverture_chemins(graphe,chemin,taille_chemin,long_total,parcour->liste_arete->arrive);
					//On complète la branche de gauche
					resultat2=couverture_chemins(graphe,chemin2,taille_chemin,long_total,parcour->liste_arete->suivante->arrive);
					//Puis celle de droite
					
					struct liste_chemin *parcour_res=resultat;
					while(parcour_res->suivant!=NULL)//On parcourt la liste des chemin de gauche
					{
						parcour_res=parcour_res->suivant;
					}
					parcour_res->suivant=resultat2; //Puis on ajoute la liste des chemins de droite à la suite.
					arret=1;
				}
			}
			else
			{
				//Cas général :
				chemin[taille_chemin]=parcour->numero;//On ajoute sommet à notre chemin
				taille_chemin++; //Augmente la taille du tableau
				parcour=recherche_sommet(parcour->liste_arete->arrive,graphe); //On passe au sommet suivant
			}
		}
	}
	return resultat;
}




//Créer la couverture des sommets
//graphe = graphique à parcourir, chemin=chemin à complèter, taille_chemin = taille du chemin fournis, long_total= longueur du tableau dans lequel se trouve le chemin
//sommet_suivant : sommet de départ, sommet_fin : sommet d'arrivée (-1 pour un parcourt total)
//Commentaires : voir ci-dessus
struct liste_chemin* couverture_sommets(liste_sommet* graphe,int *chemin,int taille_chemin, int long_total, int sommet_suivant, int sommet_fin)
{
	struct liste_chemin *resultat=malloc(sizeof(struct liste_chemin));
	int arret=0;
	cellule_sommet *parcour=recherche_sommet(sommet_suivant,graphe);
	while(arret==0) //tant que nous ne tombons pas sur une coditionnelle
	{
		if(taille_chemin-1==long_total) //si on dépasse la mémoire
		{
			chemin=realloc(chemin,sizeof(int)*long_total*2);//On réalloue le tableau de taille double
			long_total*=2;
		}
		if(parcour->suivant==NULL || parcour->numero==sommet_fin) //Si l'on arrive à la fin de notre chemin
		{
			chemin[taille_chemin]=parcour->numero;//On ajoute sommet à notre chemin
			taille_chemin++;
			resultat=malloc(sizeof(struct liste_chemin));
			resultat->chemin=chemin;
			resultat->suivant=NULL;
			resultat->taille_chemin=taille_chemin;
			arret=1;
			//affiche_couverture(resultat);
		}
		else
		{
			if(parcour->liste_arete->suivante!=NULL) //Si nous sommes sur une conditionnelle
			{
				if(strcmp(parcour->liste_arete->etiquette, "Ftantque")==0)//Si nous sommes dans un tantque
					{	
						struct liste_chemin *resultat2=malloc(sizeof(struct liste_chemin));
						chemin[taille_chemin]=parcour->numero;
						taille_chemin++;			
						int *chemin2=calloc(50,sizeof(int)); //On crée un chemin vide
						//On complète la branche du tant que (boucle)
						resultat2=couverture_sommets(graphe,chemin2,0,50,parcour->liste_arete->suivante->arrive, parcour->numero);
						//On concatene chaque chemin trouvé avec notre chemin déjà parcouru
						int taille;
						while(resultat2!=NULL)//On parcourt les chemins
						{
							taille=taille_chemin+(resultat2->taille_chemin); //Calcul de la taille des deux chemins concaténés
							int *chem2;
							chem2=malloc(sizeof(int)*taille);		//Allocation du chemin
							memcpy(chem2,chemin,sizeof(int)*taille_chemin); //On y place le chemin déjà parcouru
							chemin=chem2;
							//On y concatène le chemin trouvé (boucle)
							memcpy(&chemin[taille_chemin],resultat2->chemin,sizeof(int)*resultat2->taille_chemin);
							taille_chemin=taille;
							long_total=taille;
							resultat2=resultat2->suivant; 
						}
						
						//On poursuit la lecture*/			
						parcour=recherche_sommet(parcour->liste_arete->arrive,graphe); //On passe au sommet suivant
					}
				else //si nous sommes dans un si
				{
					if(strcmp(parcour->liste_arete->etiquette, "faux")==0)//Si il n'y a pas de sinon
					{
						chemin[taille_chemin]=parcour->numero;//On ajoute sommet à notre chemin
						taille_chemin++; //Augmente la taille du tableau
						parcour=recherche_sommet(parcour->liste_arete->suivante->arrive,graphe); //On passe au sommet suivant
					}
					else
					{
						struct liste_chemin *resultat2=malloc(sizeof(struct liste_chemin));
						chemin[taille_chemin]=parcour->numero;//On ajoute sommet à notre chemin
						taille_chemin++;
					
						int* chemin2=malloc(sizeof(int)*taille_chemin); //On créé une copie de notre chemin
						memcpy(chemin2,chemin,sizeof(int)*taille_chemin);
					
						resultat=couverture_sommets(graphe,chemin,taille_chemin,long_total,parcour->liste_arete->arrive,sommet_fin);
						//On complète la branche de gauche
						resultat2=couverture_sommets(graphe,chemin2,taille_chemin,long_total,parcour->liste_arete->suivante->arrive,sommet_fin);
						//Puis celle de droite
						struct liste_chemin *parcour_res=resultat;
						while(parcour_res->suivant!=NULL)
						{
							parcour_res=parcour_res->suivant;
						}
						parcour_res->suivant=resultat2;
						arret=1;
					}
				}
			}
			else
			{
				chemin[taille_chemin]=parcour->numero;//On ajoute sommet à notre chemin
				taille_chemin++; //Augmente la taille du tableau
				parcour=recherche_sommet(parcour->liste_arete->arrive,graphe); //On passe au sommet suivant
			}
		}
	}
	return resultat;
}




//Créer la couverture des arêtes
//graphe = graphique à parcourir, chemin=chemin à complèter, taille_chemin = taille du chemin fournis, long_total= longueur du tableau dans lequel se trouve le chemin
//sommet_suivant : sommet de départ, sommet_fin : sommet d'arrivée (-1 pour un parcourt total)
//Commentaires : voir ci-dessus
struct liste_chemin* couverture_aretes(liste_sommet* graphe,int *chemin,int taille_chemin, int long_total, int sommet_suivant, int sommet_fin)
{
	struct liste_chemin *resultat=malloc(sizeof(struct liste_chemin));
	int arret=0;
	cellule_sommet *parcour=recherche_sommet(sommet_suivant,graphe);
	while(arret==0) //tant que nous ne tombons pas sur une coditionnelle
	{
		if(taille_chemin-1==long_total) //si on dépasse la mémoire
		{
			chemin=realloc(chemin,sizeof(int)*long_total*2);//On réalloue le tableau de taille double
			long_total*=2;
		}
		if(parcour->suivant==NULL || parcour->numero==sommet_fin) //Si l'on arrive à la fin de notre chemin
		{
			chemin[taille_chemin]=parcour->numero;//On ajoute sommet à notre chemin
			taille_chemin++;
			resultat=malloc(sizeof(struct liste_chemin));
			resultat->chemin=chemin;
			resultat->suivant=NULL;
			resultat->taille_chemin=taille_chemin;
			arret=1;
			//affiche_couverture(resultat);
		}
		else
		{
			if(parcour->liste_arete->suivante!=NULL) //Si nous sommes sur une conditionnelle
			{
				if(strcmp(parcour->liste_arete->etiquette, "Ftantque")==0)//Si nous sommes dans un tantque
					{	
						struct liste_chemin *resultat2=malloc(sizeof(struct liste_chemin));
						chemin[taille_chemin]=parcour->numero;
						taille_chemin++;			
						int *chemin2=calloc(50,sizeof(int)); //On crée un chemin vide
						//On complète la branche du tant que
						resultat2=couverture_aretes(graphe,chemin2,0,50,parcour->liste_arete->suivante->arrive, parcour->numero);
						//On concatène chaque chemin trouvé avec notre chemin déjà parcouru
						int taille;
						while(resultat2!=NULL)//On parcourt les chemins
						{
							taille=taille_chemin+(resultat2->taille_chemin);
							int *chem2;
							chem2=malloc(sizeof(int)*taille);
							memcpy(chem2,chemin,sizeof(int)*taille_chemin);
							chemin=chem2;
							memcpy(&chemin[taille_chemin],resultat2->chemin,sizeof(int)*resultat2->taille_chemin);
							taille_chemin=taille;
							long_total=taille;
							resultat2=resultat2->suivant;
						}
						
						//On poursuit la lecture*/			
						parcour=recherche_sommet(parcour->liste_arete->arrive,graphe); //On passe au sommet suivant
					}
				else
				{
					struct liste_chemin *resultat2=malloc(sizeof(struct liste_chemin));
					
					//On arrive dans une conditionelle
					chemin[taille_chemin]=parcour->numero;//On ajoute sommet à notre chemin
					taille_chemin++;
					
					int* chemin2=malloc(sizeof(int)*taille_chemin); //On crée une copie de notre chemin
					memcpy(chemin2,chemin,sizeof(int)*taille_chemin);
					
					resultat=couverture_aretes(graphe,chemin,taille_chemin,long_total,parcour->liste_arete->arrive,sommet_fin);
					//On complète la branche de gauche
					resultat2=couverture_aretes(graphe,chemin2,taille_chemin,long_total,parcour->liste_arete->suivante->arrive,sommet_fin);
					//Puis celle de droite
					struct liste_chemin *parcour_res=resultat;
					while(parcour_res->suivant!=NULL)
					{
						parcour_res=parcour_res->suivant;
					}
					parcour_res->suivant=resultat2;
					arret=1;
				}
			}
			else
			{
				chemin[taille_chemin]=parcour->numero;//On ajoute sommet à notre chemin
				taille_chemin++; //Augmente la taille du tableau
				parcour=recherche_sommet(parcour->liste_arete->arrive,graphe); //On passe au sommet suivant
			}
		}
	}
	return resultat;
}

//Algorithme de recherche d'un entier dans un tableau d'entier
int recherche_sommet_chemin(int * chemin,int taille_chemin, int sommet)
{
	int i;
	for(i=taille_chemin-1;i>=0;i--) //On part de la fin car plus de chances de retrouver le sommet en fin de tableau dans notre utilisation
	{
		if(chemin[i]==sommet){return 1;}
	}
	return 0;
}








/******************************************************************************************************************************************************************
LES FONCTIONS CI-DESSOUS NE SONT PAS UTILISES, MAIS OFFRENT UNE AUTRE MANIERE DE CALCULER LES COUVERTURES,
A BASE DE FILTRES APPLIQUES SUR LA COUVERTURE DES CHEMINS ELEMENTAIRES
*******************************************************************************************************************************************************************





//Fonctions comparant deux chemins et retourne 1 si le premier est un sous chemin du second
int compare_chemin(int * chemin1, int taille1, int * chemin2, int taille2)
{
	int i=0; //parcour du premier chemin
	int j=0; //parcour du second chemin
	while(j<taille2 && taille2-j>=taille1-i)//On parcour le tableau 2 jusqu'à la fin ou jusqu'à ce que le tableau 2 ne puisse plus contenir le tableau 1
	{
		if(chemin1[i]==chemin2[j]) //Si deux cases sont communes
		{
			if(i==taille1-1) // Si nous avons trouvé le chemin
			{
				return 1; //On retourne la réponse
			}
			else
			{
				i++; //Sinon on avance le curseur du tableau 1
			}
		}
		else //Si on trouve une différence
		{
			i=0; //On repart au début de la chaine
		}
		j++;
	}
	return 0;
}

//Fonction compare_sommets : 0 si tous les sommets de chemin1 sont dans chemin2
int compare_sommets(int * chemin1, int taille1, int * chemin2, int taille2)
{
	int resultat=0;
	int i=0;
	int j=0;
	while(resultat==0 && i<taille1)
	{
		j=0;
		do
		{
			resultat=chemin1[i]-chemin2[j];
			j++;
		}
		while(resultat!=0 && j<taille2);
		i++;
	}
	return resultat;
}

//Retourne ue couverture des sommets (utilise un filtre de la couverture des chemins en supprimant les chemins inclus les uns dans les autres)
struct liste_chemin* couverture_sommets(liste_sommet* graphe,int *chemin,int taille_chemin, int long_total, int sommet_suivant)
{
	struct liste_chemin* debut=couverture_chemins(graphe,chemin,taille_chemin, long_total, sommet_suivant); //ON récupère l'ensemble des chemins possibles
	struct liste_chemin* parcour1=debut->suivant; //On place un curseur sur le second chemin
	struct liste_chemin* parcour1_prec=debut; //On conserve son précédant
	struct liste_chemin* parcour2;
	struct liste_chemin* parcour2_prec;
	while(parcour1!=NULL)//On parcour l'ensemble des chemins
	{
		parcour2=debut; //On place le parcour au début
		parcour2_prec=NULL;
		while(parcour2!=parcour1) //On parcourt l'ensemble des chemins jusqu'à l'actuel
		{
			//Si le chemin parcour1 est inclus dans le chemin parcour2
			if(compare_sommets(parcour1->chemin,parcour1->taille_chemin,parcour2->chemin,parcour2->taille_chemin)==0)
			{
				//On supprime le parcour1
				parcour1_prec->suivant=parcour1->suivant;
			}
			//Sinon si le chemin parcour2 est inclus dans le chemin parcour1
			else if(compare_sommets(parcour2->chemin,parcour2->taille_chemin,parcour1->chemin,parcour1->taille_chemin)==0)
			{
				//On le supprime
				if(parcour2_prec==NULL) //Permet de supprimer une tête de liste
				{
					debut=parcour2->suivant;
				}
				else
				{
					parcour2_prec->suivant=parcour2->suivant;
				}
			}
			parcour2_prec=parcour2; //On passe au suivant
			parcour2=parcour2->suivant;
		}
		parcour1_prec=parcour1; //On passeau suivant
		parcour1=parcour1->suivant;
	}
	return debut;
}


****************************************************************
FIN
*/
