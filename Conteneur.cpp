#include "Conteneur.h"

Conteneur::Conteneur()
{
}

Conteneur::~Conteneur()
{
}

Matrice& Conteneur::Variable(char Nom)
{
	return m_conteneur.at(Nom);
}

void Conteneur::AjouterVariable(char Nom, int Lignes, int Colonnes)
{
	m_conteneur.insert(std::pair<char, Matrice>(Nom, Matrice(Lignes, Colonnes)));
}

void Conteneur::SupprimerVariable(char Nom)
{
	m_conteneur.erase(Nom);
}

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

void Conteneur::MAJGUI(wxTreeCtrl* Arbre) const
{
	auto Racine = Arbre->AddRoot("Variables :");
	for (auto iterateur = m_conteneur.begin(); iterateur!=m_conteneur.end(); iterateur++)
	{
		Arbre->AppendItem(Racine, iterateur->first);
	}
}