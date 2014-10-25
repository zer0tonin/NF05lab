#include "Matrice.h"
#include <limits>
#include <math.h>

Matrice::Matrice(int Longueur, int Largeur): Lignes(Longueur-1), Colonnes(Largeur-1), Contenu(Lignes, std::vector<float>(Colonnes, 0) )
{
}

Matrice::~Matrice()
{
}

int Matrice::ObtenirLignes() const
{
	return Lignes;
}

int Matrice::ObtenirColonnes() const
{
	return Colonnes;
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
	if (CaseExiste(Ligne,Colonne))
	{
		Contenu[Ligne][Colonne] = Valeur;
	}
}

Matrice Matrice::Transposee() const
{
	Matrice Resultat(Colonnes, Lignes);
	int i, j;
	for (i=0; i<=Colonnes; i++)
	{
		for (j=0; j<=Lignes; j++)
		{
			Resultat.FixerValeur(i, j, Contenu[j][i]);
		}
	}
	return Resultat;
	
}

float Matrice::Determinant() const
{
	float resultat = 0;
	int i, n= 0;
	if (Carree())
	{
		if(Lignes == 0)
		{
			return Contenu[0][0];
		}
		else
		{
			for(i=0; i<=Lignes; i++)
			{
				resultat += pow(-1, n)*Contenu[0][i]*RetraitColonne(i).Determinant();
			}
			return resultat;
		}
	}
}


Matrice Matrice::Inverse() const
{
	
}
bool Matrice::Carree() const
{
	if (Lignes == Colonnes)
	{
		return true;
	}
	else
	{
		return false;
	}
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
	if (Ligne <= Lignes && Colonne <= Colonnes)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Matrice Matrice::RetraitColonne(int Colonne) const
{
	int i, j;
	Matrice Resultat(Lignes-1, Colonnes-1);
	for (i=1; i<=Lignes; i++)
	{
		for (j=0; j<=Colonnes; j++)
		{
			if (j < Colonne)
			{
				Resultat.FixerValeur(i-1, j, Contenu[i][j]);
			}
			else if (j > Colonne)
			{
				Resultat.FixerValeur(i-1, j-1, Contenu[i][j]);
			}
		}
	}
	return Resultat;
}