#include "Calculs.h"
#include "Math.h"

/*
 * On assigne l'opérateur '+' à l'addition de deux matrices de même tailles :
 * on utilise deux boucles pour parcourir chaque case de chaque lignes et additionner les valeurs contenues dans chaque matrice
 */

Matrice operator+(const Matrice &M1, const Matrice &M2)
{
	int i, j;
	Matrice Resultat(M1.ObtenirLignes(), M1.ObtenirColonnes());
	
	if (M1.ObtenirLignes() == M2.ObtenirLignes() && M1.ObtenirColonnes() == M2.ObtenirColonnes())
	{
		for (i=0; i<M1.ObtenirLignes(); i++)
		{
			for (j=0; j<M1.ObtenirColonnes(); j++)
			{
				Resultat.FixerValeur(i, j, M1.ObtenirValeur(i, j) + M2.ObtenirValeur(i, j));
			}
		}
		return Resultat;
	}
}

/*
 * On assigne l'opérateur '-' à la soustraction, qui n'est qu'une addition de deux matrices
 * dont l'une a subit l'opération unaire '-' visant à donner l'opposé de chacun de ses coefficients
*/

Matrice operator-(const Matrice &M1, const Matrice &M2)
{
	return M1+(-M2);
}

/*
 * On assigne l'opérateur '*' à la multiplication de deux matrices :
 * si le nombre de colonne de la première matrice est égal au nombre de lignes de la seconde matrice,
 * pour chaque case de la matrice résultat (ayant le nombre de lignes de la première matrice et le nombre de colonne de la seconde);
 * on y assigne la somme du produit des valeurs de la ligne (pour la première matrice) et de la colonne (pour la deuxième) correspondante
*/

Matrice operator*(const Matrice &M1, const Matrice &M2)
{
	int i, j, k;
	float Valeur;
	Matrice Resultat(M1.ObtenirLignes(), M2.ObtenirColonnes());
	
	if(M1.ObtenirColonnes() == M2.ObtenirLignes())
	{
		for (i=0; i<M1.ObtenirLignes(); i++)
		{
			for (j=0; j<M2.ObtenirColonnes(); j++)
			{
				Valeur = 0;
				for(k=0; k<M1.ObtenirColonnes(); k++)
				{
					Valeur += M1.ObtenirValeur(i, k) * M2.ObtenirValeur(k, j);
				}
				Resultat.FixerValeur(i, j, Valeur);
			}
		}
		return Resultat;
	}
}

/*
 * On assigne l'opérateur '/' à la divison de matrice :
 * il s'agit simplement de multiplier une matrice par l'inverse d'une deuxième matrice.
*/

Matrice operator/(const Matrice &M1, const Matrice &M2)
{
	return M1*M2.Inverse();
}

/*
 * On assigne l'opérateur '*' à la multiplication entre matrice et scalaire :
 * pour chaque case de la matrice, on multiplie la valeur contenue par le scalaire.
*/

Matrice operator*(const Matrice &M1, float Scalaire)
{
	Matrice Resultat(M1.ObtenirLignes(), M1.ObtenirColonnes());
	int i, j;
	for (i=0; i<M1.ObtenirLignes(); i++)
	{
		for (j=0; j<M1.ObtenirColonnes(); j++)
		{
			Resultat.FixerValeur(i, j, M1.ObtenirValeur(i, j)*Scalaire);
		}
	}
	return Resultat;
}

/*
 * On s'assure de la commmutativité de l'opérateur '*'
*/

Matrice operator*(float Scalaire, const Matrice &M1)
{
	return M1*Scalaire;
}

/*
 * On assigne l'opérateur '/' à la division d'une matrice par un scalaire
 * ce qui revient à multiplier par l'inverse de ce scalaire.
*/

Matrice operator/(const Matrice &M1, float Scalaire)
{
	return M1*(1/Scalaire);
}

/*
 * La fonction ProduitScalaire() permet de connaître le produit scalaire de deux matrices.
 * Pour cela on additionne le produit des valeurs contenues dans chacunes des matrices.
*/

float ProduitScalaire(Matrice M1, Matrice M2)
{
	int i,j;
	float Resultat = 0;
	for (i=0; i<M1.ObtenirLignes(); i++)
	{
		for (j=0; j<M2.ObtenirColonnes(); j++)
		{
			Resultat += M1.ObtenirValeur(i,j) * M2.ObtenirValeur(i,j);
		}
	}
	return Resultat;
}

/*
 * La fonction Norme() permet de connaître la norme d'une matrice, 
 * c'est à dire la racine carrée de son produit scalaire par elle même.
 */
float Norme(Matrice M1)
{
	return sqrt(ProduitScalaire(M1, M1));
}

/*
 * La fonction Puissance utilise une relation de récurrenc afin de renvoyer la matrice à la puissance indiquée.
 * C'est à dire que l'on sait que si la matrice puissance est 0 on renvoie la matrice identité.
 * Sinon on utilise la formule matrice^scalaire = matrice * matrice^scalaire-1.
 */

Matrice Puissance(Matrice matrice, float scalaire)
{
	Matrice resultat(matrice.ObtenirLignes(), matrice.ObtenirColonnes());
	int i;
	if (matrice.Carree())
	{
		if(scalaire == 0)
		{
			for (i=0; i<matrice.ObtenirLignes(); i++)
			{
				resultat.FixerValeur(i, i, 1);
			}
			return resultat;
		}
		else if(scalaire > 0)
		{
			return matrice * Puissance(matrice, scalaire-1);
		}
		else //scalaire < 0
		{
			return matrice.Inverse() * Puissance(matrice.Inverse(), -scalaire - 1); //Evite de recalculer l'inverse à chaque étape
		}
	}
}