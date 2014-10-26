#ifndef CONTENEUR_H
#define CONTENEUR_H

#include "Matrice.h"
#include <map>

class Conteneur
{
public:
	Conteneur();
	~Conteneur();
	
	Matrice& Variable(char nom);
	void AjouterVariable(char nom, int Lignes, int Colonnes);
	void SupprimerVariable(char nom);
	
private:
	std::map<char, Matrice> m_conteneur; 
};

#endif // CONTENEUR_H
