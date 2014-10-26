#include "Matrice.h"
#include <limits>
#include <math.h>

//La classe matrice en déclaré dans Matrice.h

/*
 * Le constructeur de la classe matrice permet d'initialiser le nombre de lignes, de colonnes et le contenu de la matrice
 * On estime que l'utilisateur compte en partant de 1 alors que les tableaux commencent par la case 0
 * m_ligne et m_colonnes correspondent donc aux nombres de lignes et de colonnes rentrées par l'utilisateur -1.
 * Au départ, toutes les cases de la matrice contiennent 0
*/
Matrice::Matrice(int Lignes, int Colonnes): m_lignes(Lignes-1), m_colonnes(Colonnes-1), m_contenu(m_lignes, std::vector<float>(m_colonnes, 0) )
{
}

/*
 * Le destructeur de la classe matrice n'effectue pas d'actions particulière.
*/

Matrice::~Matrice()
{
}

/*
 * La méthode ObtenirLignes() renvoie le nombre de lignes
*/

int Matrice::ObtenirLignes() const
{
	return m_lignes;
}

/*
 * La méthode ObtenirColonnes() renvoie le nombre de colonnes
*/

int Matrice::ObtenirColonnes() const
{
	return m_colonnes;
}

/*
 * La méthode ObtenirValeur() renvoie le nombre contenu dans un case après avoir vérifié que la case existe
*/

float Matrice::ObtenirValeur(int Ligne, int Colonne) const
{
	if (Matrice::CaseExiste(Ligne,Colonne))
	{
		return m_contenu[Ligne][Colonne];
	}
	/*else
	{
		return std::numeric_limits<float::max()>;
	}*/
}

/*
 * La méthode FixerValeur() permet de modifier le contenu d'une case après avoir vérifié que la case existe
*/

void Matrice::FixerValeur(int Ligne, int Colonne, float Valeur) 
{
	if (CaseExiste(Ligne,Colonne))
	{
		m_contenu[Ligne][Colonne] = Valeur;
	}
}

/*
 * La méthode Transposee renvoie une matrice
 * à laquelle on a affecté toutes les valeurs contenues dans la matrice de départ
 * en inversant à chaque fois les lignes et colonnes.
*/

Matrice Matrice::Transposee() const
{
	Matrice Resultat(m_colonnes, m_lignes);
	int i, j;
	for (i=0; i<=m_colonnes; i++)
	{
		for (j=0; j<=m_lignes; j++)
		{
			Resultat.FixerValeur(i, j, m_contenu[j][i]);
		}
	}
	return Resultat;
	
}

/*
 * La méthode Determinant permet d'obtenir le déterminant d'une matrice carrée.
 * Pour cela on utilise une relation de récurrence :
 * On sait qu'une matrice carrée de taille 1 à pour déterminant la seule valeure qu'elle contient,
 * et que toutes matrice carrée de taille supérieure à pour déterminant la somme des
 * (-1)^n * [Valeur de la première ligne] * [Déterminant de la matrice obtenu en retirant la ligne et la colonne de la valeur précédente]
*/

float Matrice::Determinant() const
{
	float Resultat = 0;
	int i, n= 0;
	if (Carree())
	{
		if(m_lignes == 0)
		{
			return m_contenu[0][0];
		}
		else
		{
			for(i=0; i<=m_lignes; i++)
			{
				Resultat += pow(-1, n)*m_contenu[0][i]*RetraitColonne(i).Determinant();
			}
			return Resultat;
		}
	}
}


Matrice Matrice::Inverse() const
{
	
}

Matrice Matrice::operator-()
{
	int i, j;
	Matrice Resultat(m_lignes, m_colonnes);
	for(i=0; i<=m_lignes; i++)
	{
		for(j=0; j<=m_colonnes; j++)
		{
			Resultat.FixerValeur(i, j, -1*m_contenu[i][j]);
		}
	}
}

/*
 * La méthode Carree() renvoie vrai si le nombre de lignes est égal aux nombres de colonnes
 * et faux dans tous les autres cas.
*/

bool Matrice::Carree() const
{
	if (m_lignes == m_colonnes)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
 * La méthode Inversible() renvoie vrai si le déterminant est différent de 0.
*/

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

/*
 * La méthode CaseExiste() renvoie vrai si la ligne et la colonne de la case demande
 * ne dépassent pas le nobmre total de lignes et de colonnes dans la matrice.
*/

bool Matrice::CaseExiste(int Ligne, int Colonne) const
{
	if (Ligne <= m_lignes && Colonne <= m_colonnes)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
 * La méthode RetraitColonne() renvoie une matrice à laquelle on assigné
 * toutes les valeurs de la matrice de départ sauf la première ligne
 * et la colonne reçu en argument.
*/

Matrice Matrice::RetraitColonne(int Colonne) const
{
	int i, j;
	Matrice Resultat(m_lignes-1, m_colonnes-1);
	for (i=1; i<=m_lignes; i++)
	{
		for (j=0; j<=m_colonnes; j++)
		{
			if (j < Colonne)
			{
				Resultat.FixerValeur(i-1, j, m_contenu[i][j]);
			}
			else if (j > Colonne)
			{
				Resultat.FixerValeur(i-1, j-1, m_contenu[i][j]);
			}
		}
	}
	return Resultat;
}