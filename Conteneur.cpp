#include "Conteneur.h"

Conteneur::Conteneur()
{
}

Conteneur::~Conteneur()
{
}

/*
 * La méthode Variable renvoie la matrice portant le nom passé en argument.
 * On peut trouver un élément d'un std::map grâce à sa clé en utilsant la méthode at.
 */

Matrice& Conteneur::Variable(char Nom)
{
	return m_conteneur.at(Nom);
}

/*
 * La méthode AjouterVariable ajoute une matrice au conteneur.
 * Pour cela on insère la matrice et son nom(regroupé dans un std::pair) avec la méthode insert.
 */

void Conteneur::AjouterVariable(char Nom, int Lignes, int Colonnes)
{
	m_conteneur.insert(std::pair<char, Matrice>(Nom, Matrice(Lignes, Colonnes)));
}

/*
 * La méthode SupprimerVariable utilise la méthode erase de std::map pour supprimer une matrice dont on donne le nom.
 */

void Conteneur::SupprimerVariable(char Nom)
{
	m_conteneur.erase(Nom);
}

/*
 * La méthode Existe renvoie vrai si la matrice dont on a donné le nom existe.
 * C'est à dire qu'elle renvoie faux si l'on parcours tout le conteneur sans trouver de matrice au nom correspondant.
 */

bool Conteneur::Existe(char Nom)
{
	auto iterateur = m_conteneur.find(Nom);
	if (iterateur == m_conteneur.end())
	{
		return false;
	}
	else
	{
		return true;
	}
}

/**
 * La méthode Vider permet de vider la liste des matrices
 */
void Conteneur::Vider()
{
	m_conteneur.clear();
}

/*
 * La méthode MAJGUI met à jour l'arbre des variables.
 * Pour cela on efface l'arbre existant, on ajoute un racine puis on parcours le conteneur dont on ajoute tous les éléments.
 */

void Conteneur::MAJGUI(wxTreeCtrl* arbre) const
{
	arbre->DeleteAllItems();
	
	wxTreeItemId racine = arbre->AddRoot("Variables");
	for (auto iterateur = m_conteneur.begin(); iterateur != m_conteneur.end(); iterateur++)
	{
		arbre->AppendItem(racine, iterateur->first);
	}
	
	arbre->ExpandAll(); //On étend le nouvel arbre
}