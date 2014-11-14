#ifndef PARSEUR_H
#define PARSEUR_H

#include <exception>
#include <string>
#include <vector>

#include <wx/msgdlg.h>
#include <wx/treectrl.h>

#include "Conteneur.h"
#include "Matrice.h"

class ExceptionParseur : public std::exception
{
public:
	ExceptionParseur(const std::string str) noexcept : m_msg(str) {};
	
	const char* what() const noexcept {return m_msg.c_str();};
	
private:
	std::string m_msg;
};

/**
 * Représente le plus petit élément d'une expression.
 * Par exemple : une constante, une matrice, un opérateur, une parenthèse...
 * 
 * Elle contient un type et une valeur optionelle associée (dans le cas d'une 
 * constante, la valeur de la constante elle-même).
 */	
struct Lexeme
{
	Lexeme() : type(INDEFINI), chaine(), nombre(0), booleen(false) {};
	
	enum LType
	{
		DEBUT,
		CONSTANTE,
		VARIABLE_MATRICE,
		OPERATEUR_PLUS,
		OPERATEUR_MOINS,
		OPERATEUR_MULTIPLIE,
		OPERATEUR_DIVISE,
		OPERATEUR_EGAL,
		OPERATEUR_PUISSANCE,
		FONCTION,
		PARENTHESE,
		
		INDEFINI = -1
	};
	
	LType type;
	std::string chaine;
	float nombre;
	bool booleen;
};

class Noeud
{
public:
	Noeud();
	Noeud(const Lexeme &lexeme);
	Noeud(const std::vector<Lexeme> &lexemes);
	Noeud(const std::vector<Noeud*> &enfants);
	virtual ~Noeud();
	
	int NombreEnfants() const {return m_enfants.size();};
	Noeud& Enfant(int index) {return *(m_enfants[index]);};
	const Noeud& Enfant(int index) const {return *(m_enfants.at(index));};
	
	Lexeme::LType Type() const {return m_type;}
	std::string DonneeChaine() const {return m_donneeChaine;};
	float DonneeNombre() const {return m_donneeNombre;};
	bool DonneeBooleen() const {return m_donneeBooleen;};
	
	bool MettreEnArbre();
	void AfficherContenu(wxTreeCtrl *arbre, wxTreeItemId parent) const;
	
protected:
	std::vector<Noeud*> m_enfants;
	Lexeme::LType m_type;
	
	std::string m_donneeChaine;
	float m_donneeNombre;
	bool m_donneeBooleen;
};

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


class Parseur
{
public:
	Parseur();
	~Parseur();
	
	Resultat CalculerExpression(const std::string &str, Conteneur &conteneurDeVariables, wxTreeCtrl *arbreSyn = NULL);
	
private:
	std::vector<Lexeme> Parse(std::string expression);
	Noeud* CreerArbreSyntaxique(std::vector<Lexeme> listeLexeme);
	Resultat Calculer(const Noeud &noeud, Conteneur &conteneurDeVariables);
};

#endif // PARSEUR_H
