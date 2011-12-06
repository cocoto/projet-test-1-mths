struct sommet_si{
	cellule_sommet *sommet; //Sommet étiqueté (besoin de repasser dessus)
	char* chemin;		//Chemin d'accès au chemin (si besoin de créer)
};
struct liste_chemin{
	struct liste_chemin* suivant;
	int *chemin;
	int taille_chemin;
};
int mcCabe(liste_sommet* graphe);
void affiche_couverture(struct liste_chemin* chemins);
struct liste_chemin* couverture_sommets(liste_sommet* graphe,int *chemin,int taille_chemin, int long_total, int sommet_suivant, int sommet_arrive);
struct liste_chemin* couverture_chemins(liste_sommet* graphe,int *chemin,int taille_chemin, int long_total, int sommet_suivant);
int recherche_sommet_chemin(int * chemin,int taille_chemin, int sommet);
