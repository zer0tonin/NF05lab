#ifndef ANALYSEUR_LEXICAL
#define ANALYSEUR_LEXICAL

#include <string>
#include <vector>

namespace parseur
{

/**
 * Représente le plus petit élément d'une expression.
 * Par exemple : une constante, une matrice, un opérateur, une parenthèse...
 * 
 * Elle contient un type et une valeur optionelle associée (dans le cas d'une 
 * constante, la valeur de la constante elle-même).
 */	
struct Lexeme
{
	enum LType
	{
		CONSTANTE,
		VARIABLE_MATRICE,
		OPERATEUR_PLUS,
		OPERATEUR_MOINS,
		OPERATEUR_MULTIPLIE,
		OPERATEUR_DIVISE,
		OPERATEUR_EGAL,
		FONCTION,
		PARENTHESE_DEBUT,
		PARENTHESE_FIN,
	};
	
	LType type;
	std::string chaine;
	float nombre;
};

/**
 * Classe qui permet l'analyse d'une expressions et qui retourne une suite
 * de lexèmes
 */
class AnalyseurLexical
{
public:
	AnalyseurLexical();
	~AnalyseurLexical();
	
	/**
	 * Retourne la liste de lexèmes associés à l'expression
	 */
	std::vector<Lexeme> Parse(std::string expression);
	
private:
	

};

}

#endif // ANALYSEUR_LEXICAL
