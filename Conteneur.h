#ifndef CONTENEUR_H
#define CONTENEUR_H

#include "Matrice.h"
#include <map>
#include <wx/treectrl.h>

/*
 * La classe conteneur est constitué d'une structure de donnée std::map<char, matrice>
 * c'est à dire un tableau dont les éléments sont des matrices accessibles grâce à un caractère.
 * La classe dispose de fonction permettant d'ajouter, supprimer et vérifier l'existance d'une variable ainsi que de mettre à jour l'arbre.
 */

class Conteneur
{
public:
	Conteneur();
	~Conteneur();
	
	Matrice& Variable(char nom);
	void AjouterVariable(char nom, int Lignes, int Colonnes);
	void SupprimerVariable(char nom);
	bool Existe(char nom);
	void MAJGUI(wxTreeCtrl* Arbre) const;
	
private:
	std::map<char, Matrice> m_conteneur;
};

#endif // CONTENEUR_H
