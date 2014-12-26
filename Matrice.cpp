#include "Matrice.h"
#include "Calculs.h"
#include <wx/msgdlg.h> 
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
 * Pour cela on se sert de l'élimination de Gauss-Jordan afin d'obtenir la matrice échelonnée réduite 
 * à partir de laquelle on peut obtenir le déterminant en multipliant les coefficients de la diagonales de cette matrice.
*/

float Matrice::Determinant() const
{
	int i, r = -1; //Attention au indices décalés dans notre logiciel (0 -> -1)
	float Resultat = 1;
	Matrice Echelonnee(*this);
	
	for(int j = 0; j < m_colonnes; j++)
	{
		//Recherche du maximum
		int k = r + 1; //<Position du maximum
		for(int i = k + 1; i < m_lignes; i++) // pas besoin de comparer la case de la ligne k avec elle-même
		{
			if(fabs(Echelonnee.ObtenirValeur(i, j)) > fabs(Echelonnee.ObtenirValeur(k, j)))
				k = i;
		}
		
		if(Echelonnee.ObtenirValeur(k, j) != 0.f) //Si le max est != de 0
		{
			//Incrémentation de r
			r++;
			
			//Echange des lignes k et r
			Echelonnee = Echelonnee.InversionLignes(r, k);
			if (k!=r)
			{
				Resultat = -Resultat;
			}
			
			//Division de la ligne r par A[r,j]
			float coeff = Echelonnee.ObtenirValeur(r, j); //< A[r,j]
			//On stocke la valeur avant dans la variable coeff car elle est susceptible d'être modifiée par la division
			for(int l = 0; l < m_colonnes; l++)
			{
				Echelonnee.FixerValeur(r, l, Echelonnee.ObtenirValeur(r, l) / coeff);
				Resultat/coeff;
			}
			
			//On parcourt toutes lignes
			for(int i = 0; i < m_lignes; i++)
			{
				if(i == r) //sauf la ligne r
					continue;
				
				//Soustraction de la ligne i par la ligne r multipliée par le coeff i;j
				float coeffIJ = Echelonnee.ObtenirValeur(i, j); //< A[i,j]
				//Pour les mêmes raisons que l'on garde A[r,j] dans coeff, on garde A[i,j] dans coeffIJ.
				for(int l = 0; l < m_colonnes; l++)
				{
					Echelonnee.FixerValeur(i, l, Echelonnee.ObtenirValeur(i, l) - Echelonnee.ObtenirValeur(r, l) * coeffIJ);
				}
			}
		}
	}
	
	//On multiplie les éléments de la diagonale :
	/*Resultat = Echelonnee.ObtenirValeur(0,0);
	for (i=1; i<m_colonnes; i++)
	{
		Resultat = Resultat * Echelonnee.ObtenirValeur(i,i);
	}*/
	return Resultat;
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
	int r = -1; //Attention au indices décalés dans notre logiciel (0 -> -1)
	Matrice inversible(*this);
	Matrice resultat = Identite();
	
	for(int j = 0; j < m_colonnes; j++)
	{
		//Recherche du maximum
		int k = r + 1; //<Position du maximum
		for(int i = k + 1; i < m_lignes; i++) // pas besoin de comparer la case de la ligne k avec elle-même
		{
			if(fabs(inversible.ObtenirValeur(i, j)) > fabs(inversible.ObtenirValeur(k, j)))
				k = i;
		}
		
		if(inversible.ObtenirValeur(k, j) != 0.f) //Si le max est != de 0
		{
			//Incrémentation de r
			r++;
			
			//Echange des lignes k et r
			inversible = inversible.InversionLignes(r, k);
			resultat = resultat.InversionLignes(r, k);
			
			//Division de la ligne r par A[r,j]
			float coeff = inversible.ObtenirValeur(r, j); //< A[r,j]
			//On stocke la valeur avant dans la variable coeff car elle est susceptible d'être modifiée par la division
			for(int l = 0; l < m_colonnes; l++)
			{
				inversible.FixerValeur(r, l, inversible.ObtenirValeur(r, l) / coeff);
				resultat.FixerValeur(r, l, resultat.ObtenirValeur(r, l) / coeff);
			}
			
			//On parcourt toutes lignes
			for(int i = 0; i < m_lignes; i++)
			{
				if(i == r) //sauf la ligne r
					continue;
				
				//Soustraction de la ligne i par la ligne r multipliée par le coeff i;j
				float coeffIJ = inversible.ObtenirValeur(i, j); //< A[i,j]
				//Pour les mêmes raisons que l'on garde A[r,j] dans coeff, on garde A[i,j] dans coeffIJ.
				for(int l = 0; l < m_colonnes; l++)
				{
					inversible.FixerValeur(i, l, inversible.ObtenirValeur(i, l) - inversible.ObtenirValeur(r, l) * coeffIJ);
					resultat.FixerValeur(i, l, resultat.ObtenirValeur(i, l) - resultat.ObtenirValeur(r, l) * coeffIJ);
				}
			}
		}
	}
	
	return resultat;
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
 * La fonction InversionLignes renvoie une matrice dont ont a inversé le contenu des deux lignes passé en argument.
 * Elle est utlisé dans la fonction Inverse.
 */

Matrice Matrice::InversionLignes(int Ligne1, int Ligne2) const
{
	int i;
	Matrice resultat(*this);
	std::vector <float> inter;
	
	//On rentre les valeurs de la Ligne1 dans un vector
	for(i=0; i<m_colonnes; i++)
	{
		inter.push_back(resultat.ObtenirValeur(Ligne1, i));
	}
	
	//On assigne les valeurs de la ligne2 à la ligne1 
	for(i=0; i<m_colonnes; i++)
	{
		resultat.FixerValeur(Ligne1, i, resultat.ObtenirValeur(Ligne2,i));
	}
	
	//On assigne les valeurs du vector à la ligne 2
	for(i=0; i<m_colonnes; i++)
	{
		resultat.FixerValeur(Ligne2, i, inter[i]);
	}
	return resultat;
}

/*
 * La fonction Trace() utilise une boucle pour afin d'effectuer la somme des éléments se situant dans la diagonale.
 */

float Matrice::Trace() const
{
	float Resultat = 0;
	int i;
	for (i=0 ; i < m_colonnes ;i++)
	{
		Resultat += (float) m_contenu[i][i];
	}
	return Resultat;
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



void Matrice::AfficherMatrice() const
{
	wxString matriceStr;
	for(int ligne = 0; ligne < ObtenirLignes(); ligne++)
	{
		for(int colonne = 0; colonne < ObtenirColonnes(); colonne++)
		{
			matriceStr += wxString::FromDouble(ObtenirValeur(ligne, colonne)) + "\t";
		}
		matriceStr += "\n";
	}
	
	wxMessageBox(matriceStr);
}
