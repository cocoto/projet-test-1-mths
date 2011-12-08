struct liste_chemin{
	struct liste_chemin* suivant;
	int *chemin;
	int taille_chemin;
};
//Calcul du nombre de Mc Cabe
int mcCabe(liste_sommet* graphe);

//Procédure d'affichage d'une couverture (liste de chemins (tableaux d'entiers)
void affiche_couverture(struct liste_chemin* chemins);

//Créer la couverture des chemins élémentaires
//graphe = graphique à parcourir, chemin=chemin à complèter, taille_chemin = taille du chemin fournis, long_total= longueur du tableau dans lequel se trouve le chemin
//sommet_suivant : sommet de départ
struct liste_chemin* couverture_chemins(liste_sommet* graphe,int *chemin,int taille_chemin, int long_total, int sommet_suivant);

//Créer la couverture des sommets
//graphe = graphique à parcourir, chemin=chemin à complèter, taille_chemin = taille du chemin fournis, long_total= longueur du tableau dans lequel se trouve le chemin
//sommet_suivant : sommet de départ, sommet_fin : sommet d'arrivée (-1 pour un parcourt total)
struct liste_chemin* couverture_sommets(liste_sommet* graphe,int *chemin,int taille_chemin, int long_total, int sommet_suivant, int sommet_fin);

//Créer la couverture des arêtes
//graphe = graphique à parcourir, chemin=chemin à complèter, taille_chemin = taille du chemin fournis, long_total= longueur du tableau dans lequel se trouve le chemin
//sommet_suivant : sommet de départ, sommet_fin : sommet d'arrivée (-1 pour un parcourt total)
struct liste_chemin* couverture_aretes(liste_sommet* graphe,int *chemin,int taille_chemin, int long_total, int sommet_suivant, int sommet_fin);

//Algorithme de recherche d'un entier dans un tableau d'entier
int recherche_sommet_chemin(int * chemin,int taille_chemin, int sommet);
