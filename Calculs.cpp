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
				Resultat.FixerValeur(i, j, M1.Contenu[i][j] + M1.Contenu[i][j]);
			}
		}
		return Resultat;
	}
}

Matrice MultiplicationMatrice(Matrice M1, Matrice M2)
{
	int i, j;
	float Valeur;
	Matrice Resultat(M1.ObtenirLignes(), M2.ObtenirColonnes());
	
	if(M1.ObtenirColonnes() == M2.ObtenirLignes())
	{
		for (i=0; i<=M1.ObtenirLignes(); i++)
		{
			Valeur = 0;
			for (j=0; j<=M1.ObtenirColonnes(), j++)
			{
			}
		}
		return Resultat;
	}
	
}
