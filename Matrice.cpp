#include "Matrice.h"
#include <limits>

Matrice::Matrice(int Lignes, int Colonnes): Contenu(Lignes, std::vector<float>(Colonnes, 0) ), Longueur(Lignes), Largeur(Colonnes)
{
}

Matrice::~Matrice()
{
}

int Matrice::ObtenirLongueur() const
{
	return Longueur;
}

int Matrice::ObtenirLargeur() const
{
	return Largeur;
}

float Matrice::ObtenirValeur(int Ligne, int Colonne) const
{
	if (Matrice::CaseExiste(Ligne,Colonne))
	{
		return Contenu[Ligne][Colonne];
	}
	/*else
	{
		return std::numeric_limits<float::max()>;
	}*/
}

void Matrice::FixerValeur(int Ligne, int Colonne, float Valeur) 
{
	if (Matrice::CaseExiste(Ligne,Colonne))
	{
		Contenu[Ligne][Colonne] = Valeur;
	}
}

Matrice Matrice::Transposee() const
{
	
}

float Matrice::Determinant() const
{
	
}


Matrice Matrice::Inverse() const
{
	
}

bool Matrice::Inversible() const
{
	if (Matrice::Determinant() != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Matrice::CaseExiste(int Ligne, int Colonne) const
{
	
}