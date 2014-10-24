#ifndef ANALYSEURSYNTAXIQUE_H
#define ANALYSEURSYNTAXIQUE_H

#include <vector>

#include "AnalyseurLexical.h"
#include <wx/msgdlg.h>

namespace parseur
{
	
class Noeud
{
public:

	enum NType
	{
		ROOT,
		CONSTANTE,
		VARIABLE_MATRICE,
		OPERATEUR_PLUS,
		OPERATEUR_MOINS,
		OPERATEUR_MULTIPLIE,
		OPERATEUR_DIVISE,
		OPERATEUR_EGAL,
		FONCTION,
		PARENTHESE,
		
		INDEFINI = -1
	};

	Noeud();
	Noeud(const Lexeme &lexeme);
	Noeud(const std::vector<Lexeme> &lexemes);
	Noeud(const std::vector<Noeud*> &enfants);
	virtual ~Noeud();
	
	int NombreEnfants() const {return m_enfants.size();};
	Noeud& Enfant(int index) {return *(m_enfants[index]);};
	const Noeud& Enfant(int index) const {return *(m_enfants.at(index));};
	
	NType Type() const {return m_type;}
	
	bool MettreEnArbre();
	
	wxString AfficherContenu(int niveau = 0) const;
	
protected:
	std::vector<Noeud*> m_enfants;
	NType m_type;
	Lexeme::LType m_lexType;
	std::string m_donneeChaine;
	float m_donneeNombre;
};

class AnalyseurSyntaxique
{
public:
	AnalyseurSyntaxique();
	~AnalyseurSyntaxique();
	
	/**
	 * Utilise la liste des lexèmes générée par l'analyseur lexical pour générer
	 * un arbre syntaxique qui permettra d'évaluer l'expression tout en respectant
	 * la priorité des opérations et les parenthèses.
	 */
	bool CreerArbreSyntaxique(std::vector<Lexeme> listeLexeme);
	void AfficherContenu();

private:
	Noeud *m_noeudPrincipal;
};

}

#endif // ANALYSEURSYNTAXIQUE_H
