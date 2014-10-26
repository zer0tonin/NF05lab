#include "Conteneur.h"

Conteneur::Conteneur()
{
}

Conteneur::~Conteneur()
{
}

Matrice& Conteneur::Variable(char Nom)
{
	return m_conteneur[Nom];
}

void Conteneur::AjouterVariable(char Nom, int Lignes, int Colonnes)
{
	m_conteneur[Nom] = Matrice(Lignes, Colonnes);
}

void Conteneur::SupprimerVariable(char Nom)
{
	m_conteneur.erase(Nom);
}