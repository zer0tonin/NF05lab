#ifndef CALCULATEUR_H
#define CALCULATEUR_H

#include <string>

#include "AnalyseurSyntaxique.h"
#include "Conteneur.h"
#include "Matrice.h"

namespace parseur
{
	
class Resultat
{
public:
	enum TypeResultat
	{
		SCALAIRE,
		MATRICE,
		ERREUR = -1
	};

	Resultat(const std::string msgErreur);
	Resultat(const Matrice &matrice);
	Resultat(float scalaire);
	
	bool EstUneErreur() const {return m_type == ERREUR;};
	bool EstUnScalaire() const {return m_type == SCALAIRE;};
	bool EstUneMatrice() const {return m_type == MATRICE;};
	
	float ValeurScalaire() const {return m_scalaire;};
	Matrice ValeurMatrice() const {return m_matrice;};
	std::string Erreur() const {return m_erreur;};
	
private:
	TypeResultat m_type;
	float m_scalaire;
	Matrice m_matrice;
	std::string m_erreur;
};

class Calculateur
{
public:
	Calculateur();
	~Calculateur();
	
	Resultat Calculer(const Noeud &noeud, Conteneur &conteneurDeVariables);

};

}

#endif // CALCULATEUR_H
