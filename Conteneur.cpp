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