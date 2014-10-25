#include "AnalyseurLexical.h"

#include <iostream>

#include <wx/regex.h>
#include <wx/msgdlg.h>  

namespace parseur
{

AnalyseurLexical::AnalyseurLexical()
{
}

AnalyseurLexical::~AnalyseurLexical()
{
}

std::vector<Lexeme> AnalyseurLexical::Parse(std::string expression)
{
	std::vector<Lexeme> listeLexeme;
	wxMessageBox(expression);
	
	while(expression.size() > 0)
	{
		unsigned int debutCorrespondance;
		unsigned int longueurCorrespondance;
		
		wxRegEx constantRegex("^[0-9.]+");
		wxRegEx variableRegex("^[A-Z]");
		wxRegEx operateurRegex("^[\\+-\\*\\/=]");
		wxRegEx parentheseRegex("^[\\(\\)]");
		wxRegEx fonctionRegex("^[a-z]+\\(");
		
		if(constantRegex.Matches(expression))
		{
			//On est sur une constante
			constantRegex.GetMatch(&debutCorrespondance, &longueurCorrespondance, 0);
			
			Lexeme nouveauLexeme;
			nouveauLexeme.type = Lexeme::CONSTANTE;
			double valeurConstante;
			constantRegex.GetMatch(expression, 0).ToDouble(&valeurConstante);
			nouveauLexeme.nombre = valeurConstante;
			listeLexeme.push_back(nouveauLexeme);
		}
		else if(variableRegex.Matches(expression))
		{
			//On est sur une variable
			variableRegex.GetMatch(&debutCorrespondance, &longueurCorrespondance, 0);
			
			Lexeme nouveauLexeme;
			nouveauLexeme.type = Lexeme::VARIABLE_MATRICE;
			nouveauLexeme.chaine = variableRegex.GetMatch(expression, 0).ToStdString();
			listeLexeme.push_back(nouveauLexeme);
		}
		else if(operateurRegex.Matches(expression))
		{
			//On est sur un opérateur
			operateurRegex.GetMatch(&debutCorrespondance, &longueurCorrespondance, 0);
			
			Lexeme nouveauLexeme;
			if(operateurRegex.GetMatch(expression, 0) == "+")
				nouveauLexeme.type = Lexeme::OPERATEUR_PLUS;
			else if(operateurRegex.GetMatch(expression, 0) == "-")
				nouveauLexeme.type = Lexeme::OPERATEUR_MOINS;
			else if(operateurRegex.GetMatch(expression, 0) == "*")
				nouveauLexeme.type = Lexeme::OPERATEUR_MULTIPLIE;
			else if(operateurRegex.GetMatch(expression, 0) == "/")
				nouveauLexeme.type = Lexeme::OPERATEUR_DIVISE;
			else if(operateurRegex.GetMatch(expression, 0) == "=")
				nouveauLexeme.type = Lexeme::OPERATEUR_EGAL;
			listeLexeme.push_back(nouveauLexeme);
		}
		else if(parentheseRegex.Matches(expression))
		{
			//On est sur une parenthèse
			parentheseRegex.GetMatch(&debutCorrespondance, &longueurCorrespondance, 0);
			
			Lexeme nouveauLexeme;
			nouveauLexeme.type = Lexeme::PARENTHESE;
			if(parentheseRegex.GetMatch(expression, 0) == "(")
				nouveauLexeme.booleen = true; //On stocke VRAI dans le lexème si c'est une parenthèse ouvrante, FAUX sinon.
			else if(parentheseRegex.GetMatch(expression, 0) == ")")
				nouveauLexeme.booleen = false;
			listeLexeme.push_back(nouveauLexeme);
		}
		else if(fonctionRegex.Matches(expression))
		{
			//On est sur une fonction (par exemple, determinant, nombre de lignes d'une matrice)
			fonctionRegex.GetMatch(&debutCorrespondance, &longueurCorrespondance, 0);
			
			Lexeme nouveauLexeme;
			nouveauLexeme.type = Lexeme::FONCTION;
			//Extraction du nom de la fonction (on doit supprimer la parenthèse)
			nouveauLexeme.chaine = fonctionRegex.GetMatch(expression, 0).substr(0, fonctionRegex.GetMatch(expression, 0).size() - 1);
			
			listeLexeme.push_back(nouveauLexeme);
		}
		else
		{
			break;
		}
		
		while(expression[debutCorrespondance + longueurCorrespondance] == ' ')
			longueurCorrespondance++;
		expression = expression.substr(debutCorrespondance + longueurCorrespondance);
	}
	
	if(expression.size() != 0)
	{
		m_erreur = true;
	}
	else
	{
		m_erreur = false;
	}
	
	return listeLexeme;
}


}

