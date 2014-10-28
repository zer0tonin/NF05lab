#include "Calculateur.h"

#include "Calculs.h"
#include <cmath>

namespace parseur
{
	
Resultat::Resultat(const std::string msgErreur) : m_type(ERREUR), m_erreur(msgErreur), m_matrice(0,0)
{
	
}

Resultat::Resultat(const Matrice &matrice) : m_type(MATRICE), m_matrice(matrice)
{
	
}

Resultat::Resultat(float scalaire) : m_type(SCALAIRE), m_scalaire(scalaire), m_matrice(0,0)
{
	
}

Calculateur::Calculateur()
{
}

Calculateur::~Calculateur()
{
}

Resultat Calculateur::Calculer(const Noeud &noeud, Conteneur &conteneurDeVariables)
{
	if(noeud.Type() == Lexeme::CONSTANTE)
	{
		return Resultat(noeud.DonneeNombre());
	}
	else if(noeud.Type() == Lexeme::VARIABLE_MATRICE)
	{
		if(conteneurDeVariables.Existe(noeud.DonneeChaine()[0]))
		{
			//La variable existe, on retourne donc la matrice stockée dans la variable
			return Resultat(conteneurDeVariables.Variable(noeud.DonneeChaine()[0]));
		}
		else
		{
			//Elle n'existe pas, on renvoit une erreur
			//Note : le cas de l'affectation est traité séparément, directement avec
			//l'opérateur d'affectation.
			return Resultat("La variable " + noeud.DonneeChaine() + " n'est pas definie");
		}
	}
	else if(noeud.Type() == Lexeme::PARENTHESE)
	{
		if(noeud.NombreEnfants() == 1)
		{
			//On retourne le résultat de l'intérieur de la parenthèse directement
			return Calculer(noeud.Enfant(0), conteneurDeVariables);
		}
		else
		{
			//Un noeud parenthèse ne peut contenir qu'un seul noeud, il y a donc une erreur
			return Resultat("Erreur avec une parenthèse");
		}
	}
	else if(noeud.Type() == Lexeme::OPERATEUR_PLUS) //Opérateur +
	{
		if(noeud.NombreEnfants() == 1) //Unaire
		{
			Resultat resultatOperande = Calculer(noeud.Enfant(0), conteneurDeVariables); //On appelle la fonction Calculer sur le noeud enfant de l'opérateur
			return resultatOperande; //L'opérateur + unaire n'a pas vraiment d'effet sur la résultat, on le retourne directement.			
		}
		else if(noeud.NombreEnfants() == 2) //Binaire
		{
			Resultat resultatOperandeGauche = Calculer(noeud.Enfant(0), conteneurDeVariables); //On appelle la fonction Calculer sur les deux opérandes (noeuds) de l'opérateur
			Resultat resultatOperandeDroit = Calculer(noeud.Enfant(1), conteneurDeVariables);
			
			//En cas d'erreur, on retourne directement l'erreur.
			if(resultatOperandeGauche.EstUneErreur())
				return resultatOperandeGauche;
			else if(resultatOperandeDroit.EstUneErreur())
				return resultatOperandeDroit;
			
			if(resultatOperandeGauche.EstUnScalaire() && resultatOperandeDroit.EstUnScalaire())
			{
				return Resultat(resultatOperandeGauche.ValeurScalaire() + resultatOperandeDroit.ValeurScalaire());
			}
			else if(resultatOperandeGauche.EstUneMatrice() && resultatOperandeDroit.EstUneMatrice())
			{
				return Resultat(resultatOperandeGauche.ValeurMatrice() + resultatOperandeDroit.ValeurMatrice());
			}
			else
			{
				return Resultat("Non concordance des types pour l'addition");
			}
		}
	}
	else if(noeud.Type() == Lexeme::OPERATEUR_MOINS) //Opérateur +
	{
		if(noeud.NombreEnfants() == 1) //Unaire
		{
			Resultat resultatOperande = Calculer(noeud.Enfant(0), conteneurDeVariables); //On appelle la fonction Calculer sur le noeud enfant de l'opérateur
			if(resultatOperande.EstUneErreur()) //C'est une erreur, on la retourne directement
				return resultatOperande;
			else if(resultatOperande.EstUnScalaire())
				return Resultat(-resultatOperande.ValeurScalaire());
			else if(resultatOperande.EstUneMatrice())
				return Resultat(-resultatOperande.ValeurMatrice());			
		}
		else if(noeud.NombreEnfants() == 2) //Binaire
		{
			Resultat resultatOperandeGauche = Calculer(noeud.Enfant(0), conteneurDeVariables); //On appelle la fonction Calculer sur les deux opérandes (noeuds) de l'opérateur
			Resultat resultatOperandeDroit = Calculer(noeud.Enfant(1), conteneurDeVariables);
			
			//En cas d'erreur, on retourne directement l'erreur.
			if(resultatOperandeGauche.EstUneErreur())
				return resultatOperandeGauche;
			else if(resultatOperandeDroit.EstUneErreur())
				return resultatOperandeDroit;
			
			if(resultatOperandeGauche.EstUnScalaire() && resultatOperandeDroit.EstUnScalaire())
			{
				return Resultat(resultatOperandeGauche.ValeurScalaire() - resultatOperandeDroit.ValeurScalaire());
			}
			else if(resultatOperandeGauche.EstUneMatrice() && resultatOperandeDroit.EstUneMatrice())
			{
				return Resultat(resultatOperandeGauche.ValeurMatrice() - resultatOperandeDroit.ValeurMatrice());
			}
			else
			{
				return Resultat("Non concordance des types pour la soustraction");
			}
		}
	}
	else if(noeud.Type() == Lexeme::OPERATEUR_MULTIPLIE)
	{
		if(noeud.NombreEnfants() == 2)
		{
			Resultat resultatOperandeGauche = Calculer(noeud.Enfant(0), conteneurDeVariables); //On appelle la fonction Calculer sur les deux opérandes (noeuds) de l'opérateur
			Resultat resultatOperandeDroit = Calculer(noeud.Enfant(1), conteneurDeVariables);
			
			//En cas d'erreur, on retourne directement l'erreur.
			if(resultatOperandeGauche.EstUneErreur())
				return resultatOperandeGauche;
			else if(resultatOperandeDroit.EstUneErreur())
				return resultatOperandeDroit;
				
			if(resultatOperandeGauche.EstUnScalaire() && resultatOperandeDroit.EstUnScalaire())
			{
				return Resultat(resultatOperandeGauche.ValeurScalaire() * resultatOperandeDroit.ValeurScalaire());
			}
			else if(resultatOperandeGauche.EstUnScalaire() && resultatOperandeDroit.EstUneMatrice())
			{
				return Resultat(resultatOperandeGauche.ValeurScalaire() * resultatOperandeDroit.ValeurMatrice());
			}
			else if(resultatOperandeGauche.EstUneMatrice() && resultatOperandeDroit.EstUnScalaire())
			{
				return Resultat(resultatOperandeGauche.ValeurMatrice() * resultatOperandeDroit.ValeurScalaire());
			}
			else if(resultatOperandeGauche.EstUneMatrice() && resultatOperandeDroit.EstUneMatrice())
			{
				//Multiplication entre deux matrices, il faut vérifier la possibilité de le faire
				if(resultatOperandeGauche.ValeurMatrice().ObtenirColonnes() == resultatOperandeDroit.ValeurMatrice().ObtenirLignes())
					return Resultat(resultatOperandeGauche.ValeurMatrice() * resultatOperandeDroit.ValeurMatrice());
				else
					return Resultat("Impossible de multiplier les deux matrices");
			}
		}
		else
		{
			return Resultat("Pas assez/trop d'operandes pour la multiplication");
		}
	}
	else if(noeud.Type() == Lexeme::OPERATEUR_DIVISE)
	{
		if(noeud.NombreEnfants() == 2)
		{
			Resultat resultatOperandeGauche = Calculer(noeud.Enfant(0), conteneurDeVariables); //On appelle la fonction Calculer sur les deux opérandes (noeuds) de l'opérateur
			Resultat resultatOperandeDroit = Calculer(noeud.Enfant(1), conteneurDeVariables);
			
			//En cas d'erreur, on retourne directement l'erreur.
			if(resultatOperandeGauche.EstUneErreur())
				return resultatOperandeGauche;
			else if(resultatOperandeDroit.EstUneErreur())
				return resultatOperandeDroit;
				
			if(resultatOperandeGauche.EstUnScalaire() && resultatOperandeDroit.EstUnScalaire())
			{
				return Resultat(resultatOperandeGauche.ValeurScalaire() / resultatOperandeDroit.ValeurScalaire());
			}
			else if(resultatOperandeGauche.EstUnScalaire() && resultatOperandeDroit.EstUneMatrice())
			{
				return Resultat("Ne peut pas diviser un nombre par une matrice");
			}
			else if(resultatOperandeGauche.EstUneMatrice() && resultatOperandeDroit.EstUnScalaire())
			{
				return Resultat(resultatOperandeGauche.ValeurMatrice() / resultatOperandeDroit.ValeurScalaire());
			}
			else if(resultatOperandeGauche.EstUneMatrice() && resultatOperandeDroit.EstUneMatrice())
			{
				//Multiplication entre deux matrices, il faut vérifier la possibilité de le faire
				if(resultatOperandeDroit.ValeurMatrice().Inversible() && 
				   resultatOperandeGauche.ValeurMatrice().ObtenirColonnes() == resultatOperandeDroit.ValeurMatrice().Inverse().ObtenirLignes())
					return Resultat(resultatOperandeGauche.ValeurMatrice() / resultatOperandeDroit.ValeurMatrice());
				else
					return Resultat("Impossible de multiplier les deux matrices");
			}
		}
		else
		{
			return Resultat("Pas assez/trop d'operandes pour la multiplication");
		}
	}
	else if(noeud.Type() == Lexeme::OPERATEUR_PUISSANCE)
	{
		if(noeud.NombreEnfants() == 2)
		{
			Resultat resultatOperandeGauche = Calculer(noeud.Enfant(0), conteneurDeVariables); //On appelle la fonction Calculer sur les deux opérandes (noeuds) de l'opérateur
			Resultat resultatOperandeDroit = Calculer(noeud.Enfant(1), conteneurDeVariables);
			
			//En cas d'erreur, on retourne directement l'erreur.
			if(resultatOperandeGauche.EstUneErreur())
				return resultatOperandeGauche;
			else if(resultatOperandeDroit.EstUneErreur())
				return resultatOperandeDroit;
				
			if(resultatOperandeGauche.EstUnScalaire() && resultatOperandeDroit.EstUnScalaire())
			{
				return Resultat(std::pow(resultatOperandeGauche.ValeurScalaire(), resultatOperandeDroit.ValeurScalaire()));
			}
			else if(resultatOperandeGauche.EstUneMatrice() && resultatOperandeDroit.EstUnScalaire())
			{
				return Resultat(Puissance(resultatOperandeGauche.ValeurMatrice(), resultatOperandeDroit.ValeurScalaire()));
			}
			else
			{
				return Resultat("Operateur ^ mal utilisé");
			}
		}
		else
		{
			return Resultat("Pas assez/trop d'operandes pour la puissance");
		}
	}
	else if(noeud.Type() == Lexeme::OPERATEUR_EGAL)
	{
		//On est sur un opérateur d'affectation (=)
		//Il y a forcément deux opérandes, sinon c'est une erreur
		if(noeud.NombreEnfants() == 2)
		{
			//On ne traite pas (avec une récursivité) l'opérande gauche qui doit normalement être
			//une matrice (Type VARIABLE_MATRICE)
			Resultat resultatOperandeDroite = Calculer(noeud.Enfant(1), conteneurDeVariables);
			
			if(resultatOperandeDroite.EstUneErreur())
				return resultatOperandeDroite;
			
			if(resultatOperandeDroite.EstUneMatrice())
			{
				//On vérifie bien que l'opérande gauche est une opérande de type VARIABLE_MATRICE
				if(noeud.Enfant(0).Type() == Lexeme::VARIABLE_MATRICE)
				{
					conteneurDeVariables.AjouterVariable(noeud.Enfant(0).DonneeChaine()[0], 
													     resultatOperandeDroite.ValeurMatrice().ObtenirLignes(),
														 resultatOperandeDroite.ValeurMatrice().ObtenirColonnes());
					
					conteneurDeVariables.Variable(noeud.Enfant(0).DonneeChaine()[0]) = resultatOperandeDroite.ValeurMatrice();
					
					return resultatOperandeDroite; //On renvoit quand même le résultat de l'opérande droite pour pouvoir l'afficher
					//à l'utilisateur.
				}
				else
				{
					//Ce n'est pas possible
					return Resultat("Variable attendue a gauche de l'operateur d'affectation");
				}
			}
			else
			{
				return Resultat("Seules des matrices peuvent etre stockee dans une variable");
			}
		}
		else
		{
			return Resultat("Pas assez/trop d'operandes pour l'affectation");
		}
	}
	else if(noeud.Type() == Lexeme::INDEFINI)
	{
		//Indéfini mais avec un noeud enfant, on retourne directement le résultat
		if(noeud.NombreEnfants() == 1)
			return Calculer(noeud.Enfant(0), conteneurDeVariables);
	}
	
	return Resultat("Operation non supportee");
}

}

