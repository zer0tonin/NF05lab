#include "Conteneur.h"

Conteneur::Conteneur()
{
}

Conteneur::~Conteneur()
{
	for(auto it = m_conteneur.begin(); it != m_conteneur.end(); it++)
	{
		delete it->second; //On désalloue la matrice (grâce à son pointeur)
	}
}

Matrice& Conteneur::Variable(char Nom)
{
	return *m_conteneur[Nom];
}

void Conteneur::AjouterVariable(char Nom, int Lignes, int Colonnes)
{
	m_conteneur[Nom] = new Matrice(Lignes, Colonnes); //On ajoute la matrice
}

void Conteneur::SupprimerVariable(char Nom)
{
	delete m_conteneur[Nom]; //On déalloue la mémoire associé à la variable
	m_conteneur.erase(Nom);
}