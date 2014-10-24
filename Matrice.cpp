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
	int i;
	Matrice Resultat(Lignes, Colonnes);
	Resultat.Contenu = Contenu;
	for (i=0; i<=Lignes; i++)
	{
		Resultat.Contenu[i].erase (Resultat.Contenu[i].begin() + Colonne);
	}
	Resultat.Contenu.erase (Resultat.Contenu.begin());
	return Resultat;
}