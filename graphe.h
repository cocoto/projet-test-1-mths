/*Précondition de ma structure :
	La variable liste_sommet.depart doit être initialisée à NULL
*/

typedef struct cellule_arete cellule_arete;
typedef struct cellule_sommet cellule_sommet;
typedef struct liste_sommet liste_sommet;

struct cellule_arete{
	int arrive;		//Sommet d'arrivée
	cellule_arete* suivante;
	char* etiquette[];	//Identificateur de l'arrête
};
struct cellule_sommet {
	int numero;		//Identifiant du commet
	cellule_arete* liste_arete;
	cellule_sommet* suivant;
};
struct liste_sommet {
	cellule_sommet depart;
	cellule_sommet fin;
	int taille;		//implémentable ou non, au choix
};

// Ajoute un sommet à la fin de la liste donnée, avec le numéro donné
void ajouter_sommet(int numero, liste_sommet* liste);

// Ajoute une arete au début de la liste donnée
void ajouter_arete_l(char* etiquette, cellule_sommet* sommet, int numero);

// Algorithme de recherche d'une liste
//Précondition : La liste doit comporter un sommet au minimum
cellule_sommet recherche_sommet(int sommet,liste_sommet* liste);

void ajouter_arete (char* etiquette, int sommet_d, int sommet_c, liste_sommet* liste); //sommet départ et sommet cible
