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
Matrice::Matrice(int Lignes, int Colonnes): m_lignes(Lignes), m_colonnes(Colonnes), m_contenu(m_lignes, std::vector<float>(m_colonnes, 0) )
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
	for (i=0; i<m_colonnes; i++)
	{
		for (j=0; j<m_lignes; j++)
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
		if(m_lignes == 1)
		{
			return m_contenu[0][0];
		}
		else
		{
			for(i=0; i<m_lignes; i++)
			{
				Resultat += pow(-1, n)*m_contenu[0][i]*RetraitColonne(i).Determinant();
			}
			return Resultat;
		}
	}
}

/*
 * La fonction inverse utilise l'élimination de Gauss-Jordan pour générer une matrice inverse :
 * pour cela on utilise le pseudo-code trouver à cette adresse : http://stackoverflow.com/a/1684801 
 * On effectue les opérations sur la matrice à inverser et sur une matrice identité de même dimension.
 * Lorsque l'algorithme est terminé, la matrice identité à pris les valeurs de la matrice inverse.
 * La matrice à inversr a pris les valeurs de sa matrice échelonnée réduite.
 */ 
Matrice Matrice::Inverse() const
{
	int i = 0, j = 0, k, l, max;
	Matrice Resultat = Identite();
	
	while (i <= m_lignes && j <= m_colonnes)
	{
		max = i;
		
		for (k = i+1; k< m_lignes ; k++)
		{
			//recherche du maximum de la colonne :
			if (fabs(m_contenu[k][j]) > fabs(m_contenu[max][j]))
			{
				max = k;
			}
			
		}
		
		if (m_contenu[max][j] != 0)
		{
			//echange des lignes i et max :
			this->InversionLignes(max,i);
			//on effectue la même opération sur la matrice résultat :
			Resultat = Resultat.InversionLignes(max, i);
			//m_contenu[i][j] devrait désormais contenir la même valeur que l'ancien m_contenu[max][j]
			
			//on divise chaque valeur de la ligne i par m_contenu[i][j]
			for (k=0; k<m_colonnes; k++)
			{
				m_contenu[i][j] = m_contenu[i][k] / m_contenu[i][j]);
				
				Resultat.FixerValeur(i, k, Resultat.ObtenirValeur(i,k) / Resultat.ObtenirValeur(i,k));
			}
			//Désormais m_contenu[i][j] doit être égal à 1
			
			for (k = i+1; k<m_lignes ; k++)
			{
				//on soustrait m_contenu[k][j] * m_contenu[i][l] à la colonne k
				for (l = 0; l<m_colonnes ; l++)
				{
					m_contenu[k][l] -= m_contenu[k][j] * m_contenu[i][l];
					
					Resultat.FixerValeur(k, l, Resultat.ObtenirValeur(k, l) - Resultat.ObtenirValeur(k,j) * Resultat.ObtenirValeur(i,l));
				}
				//m_coneneur[k][j] est désomrais égal à 0 car m_conteneur[k][j] -= m_conteneur[k][j] * m_conteneur[i][j] revient à faire m_conteneur[k][j] -= m_conteneur[k][j] 
			}
			i++;
		}
		j++;
	}
	
	return Resultat;
}

/*
 * On assigne à l'opérateur unaire '-' l'opération qui consiste à multiplier par -1 chaque valeur contenue dans la matrice.
*/

Matrice Matrice::operator-() const
{
	int i, j;
	Matrice Resultat(m_lignes, m_colonnes);
	for(i=0; i<m_lignes; i++)
	{
		for(j=0; j<m_colonnes; j++)
		{
			Resultat.FixerValeur(i, j, (-1)*m_contenu[i][j]);
		}
	}
	return Resultat;
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
	if (Ligne < m_lignes && Colonne < m_colonnes)
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
	for (i=1; i<m_lignes; i++)
	{
		for (j=0; j<m_colonnes; j++)
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

/*
 * La fonction Identite permet de génrérer une matrice identité de taille égale à la matrice d'origine..
 * Elle est utiliser dans la fonction inverse pour initialiser la matrice Resultat.
 */

Matrice Matrice::Identite() const
{
	int i, j;
	Matrice Resultat(m_lignes, m_colonnes);
	for (i = 0; i<m_lignes; i++)
	{
		for (j = 0; j<m_colonnes; j++)
		{
			if (i==j)
			{
				Resultat.FixerValeur(i,j, 1);
			}
			else
			{
				Resultat.FixerValeur(i,j,0);
			}
		}
	}
	return Resultat;
}

/*
 * La fonction InversionLignes renvoie une matrice dont ont a inversé le contenu des deux lignes passé en argument.
 * Elle est utlisé dans la fonction Inverse.
 */

Matrice Matrice::InversionLignes(int Ligne1, int Ligne2) const
{
	int i, j;
	Matrice Resultat(m_lignes, m_colonnes);
	std::vector<float> inter;
	
	//On initialise la matrice en lui donnant les valeurs de la matrice de départ.
	for (i=0; i<m_lignes; i++)
	{
		for(j=0; j<m_colonnes; j++)
		{
			Resultat.FixerValeur(i, j, m_contenu[i][j]);
		}
	}
	
	//On rentre les valeurs de la Ligne1 dans un vector
	for(i=0; i<m_colonnes; i++)
	{
		inter[i] = Resultat.ObtenirValeur(Ligne1, i);
	}
	
	//On assigne les valeurs de la ligne2 à la ligne1 
	for(i=0; i<m_colonnes; i++)
	{
		Resultat.FixerValeur(Ligne1, i, Resultat.ObtenirValeur(Ligne2,i));
	}
	
	//On assigne les valeurs du vector à la ligne 2
	for(i=0; i<m_colonnes; i++)
	{
		Resultat.FixerValeur(Ligne2, i, inter[i]);
	}
	return Resultat;
}