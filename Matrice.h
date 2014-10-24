#ifndef MATRICE_h
#define MATRICE_h

#include <vector> //On stockera les valeurs de la matrice dans des vectors

class Matrice
{
public:
	Matrice(int Lignes, int Colonnes); //Le contructeur de la classe matrice, qui prend en argument le nombre de lignes et de colonnes
	~Matrice(); //Le destructeur
	
	int ObtenirLignes() const;
	int ObtenirColonnes() const;
	float ObtenirValeur(int Ligne, int Colonne) const;
	void FixerValeur(int Ligne, int Colonne, float Valeur);
	Matrice Transposee() const; //La méthode permettant d'obtenir la transposée
	float Determinant() const; //La méthode permettant d'obtenir le déterminant
	Matrice Inverse() const; //La méthode permettant d'obtenir la matrice inverse (si la matrice est inversible)
	
private:
	bool Carree() const;
	bool CaseExiste(int Ligne, int Colonne) const; //La méthode permettant de vérifier que certaines coordonnées ne sont pas hors de la matrice
	bool Inversible() const; //La méthode permettant de vérifier que la matrice est inversible
	Matrice RetraitColonne(int Colonne) const;
	
	int Lignes; //Le nombre de lignes
	int Colonnes; //Le nombre de colonnes
	std::vector < std::vector <float> > Contenu; //Le contenu de la matrice
};

#endif // MATRICE_h
