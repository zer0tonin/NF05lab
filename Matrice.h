#ifndef MATRICE_h
#define MATRICE_h

#include <vector>

/* 
 * Déclaration de la classe Matrice.
 * Les matrices sont des vectors à deux dimensions contenant des floats.
 * La classe Matrice contient différentes méthodes permettant d'obtenir des données liées à la matrice en question:
 * son nombre de lignes, de colonnes, son déterminant, son inverse (si elle est inversible)...
 * Le détail de ces méthodes se trouve dans le fichier Matrice.cpp
*/
class Matrice
{
public:
	Matrice(int Lignes, int Colonnes);
	~Matrice();
	
	int ObtenirLignes() const;
	int ObtenirColonnes() const;
	float ObtenirValeur(int Ligne, int Colonne) const;
	void FixerValeur(int Ligne, int Colonne, float Valeur);
	Matrice Transposee() const;
	float Determinant() const;
	Matrice Inverse() const;
	bool Inversible() const;
	Matrice operator-() const;
	bool Carree() const;
	Matrice InversionLignes(int Ligne1, int Ligne2) const;
	float Trace() const;
	
	void AfficherMatrice() const;
	
private:
	bool CaseExiste(int Ligne, int Colonne) const;
	Matrice RetraitColonne(int Colonne) const;
	Matrice Identite() const;
	
	
	int m_lignes;
	int m_colonnes;
	std::vector < std::vector <float> > m_contenu;
};

#endif // MATRICE_h
