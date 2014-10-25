#ifndef ANALYSEURSYNTAXIQUE_H
#define ANALYSEURSYNTAXIQUE_H

#include <vector>

#include "AnalyseurLexical.h"
#include <wx/msgdlg.h>
#include <wx/treectrl.h>

namespace parseur
{
	
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
	
	bool MettreEnArbre();
	
	void AfficherContenu(wxTreeCtrl *arbre, wxTreeItemId parent) const;
	
protected:
	std::vector<Noeud*> m_enfants;
	Lexeme::LType m_type;
	
	std::string m_donneeChaine;
	float m_donneeNombre;
	bool m_donneeBooleen;
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
	void AfficherContenu(wxTreeCtrl *arbre);

private:
	Noeud *m_noeudPrincipal;
};

}

#endif // ANALYSEURSYNTAXIQUE_H
