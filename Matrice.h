#ifndef MATRICE_h
#define MATRICE_h

#include <vector>

class Matrice
{
public:
	Matrice(int Lignes, int Colonnes);
	~Matrice();
	
	int ObtenirLongueur() const;
	int ObtenirLargeur() const;
	float ObtenirValeur(int Ligne, int Colonne) const;
	void FixerValeur(int Ligne, int Colonne, float Valeur);
	Matrice Transposee() const;
	float Determinant() const;
	bool Inversible() const;
	Matrice Inverse() const;
	
private:
	std::vector < std::vector <float> > Contenu;
};

#endif // MATRICE_h
