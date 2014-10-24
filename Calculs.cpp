#include "Calculs.h"

Matrice SommeMatrice(Matrice M1, Matrice M2)
{
	int i, j;
	Matrice Resultat(M1.ObtenirLignes(), M1.ObtenirColonnes());
	
	if (M1.ObtenirLignes() == M2.ObtenirLignes() && M1.ObtenirColonnes() == M2.ObtenirColonnes())
	{
		for (i=0; i<=M1.ObtenirLignes(); i++)
		{
			for (j=0; j<=M1.ObtenirColonnes(); j++)
			{
				Resultat.FixerValeur(i, j, M1.ObtenirValeur(i, j) + M2.ObtenirValeur(i, j));
			}
		}
		return Resultat;
	}
}

Matrice MultiplicationMatrice(Matrice M1, Matrice M2)
{
	int i, j, k;
	float Valeur;
	Matrice Resultat(M1.ObtenirLignes(), M2.ObtenirColonnes());
	
	if(M1.ObtenirColonnes() == M2.ObtenirLignes())
	{
		for (i=0; i<=M1.ObtenirLignes(); i++)
		{
			for (j=0; j<=M2.ObtenirColonnes(); j++)
			{
				Valeur = 0;
				for(k=0; k<=M1.ObtenirColonnes(); k++)
				{
					Valeur += M1.ObtenirValeur(i, k) * M2.ObtenirValeur(k, j);
				}
				Resultat.FixerValeur(i, j, Valeur);
			}
		}
		return Resultat;
	}
}

Matrice DivisionMatrice(Matrice M1, Matrice M2)
{
	Matrice Resultat(M1.ObtenirLignes(), M2.ObtenirColonnes());
	M2 = M2.Inverse();
	Resultat = MultiplicationMatrice(M1, M2);
	return Resultat;
}

float ProduitScalaire(Matrice M1, Matrice M2)
{
	int i;
	float Resultat = 0;
	if (M1.ObtenirColonnes() == 1 && M2.ObtenirColonnes() == 1 && M1.ObtenirLignes() == M2.ObtenirLignes())
	{
		for (i=0; i<=M1.ObtenirLignes(); i++)
		{
			Resultat += M1.ObtenirValeur(i, 1) * M2.ObtenirValeur(i, 1);
		}
	}
	return Resultat;
}

Matrice MultiplicationMatriceScalaire(Matrice M1, float Scalaire)
{
	Matrice Resultat(M1.ObtenirLignes(), M1.ObtenirColonnes());
	int i, j;
	for (i=0; i<=M1.ObtenirLignes(); i++)
	{
		for (j=0; j<=M1.ObtenirColonnes(); j++)
		{
			Resultat.FixerValeur(i, j, M1.ObtenirValeur(i, j)*Scalaire);
		}
	}
	return Resultat;
}

Matrice DivisionMatriceScalaire(Matrice M1, float Scalaire)
{
	return MultiplicationMatriceScalaire(M1, 1/Scalaire);
}