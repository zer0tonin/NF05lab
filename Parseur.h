#ifndef PARSEUR_H
#define PARSEUR_H

#include <exception>
#include <string>
#include <vector>

#include <wx/msgdlg.h>
#include <wx/treectrl.h>

#include "Conteneur.h"
#include "Matrice.h"

/**
 * Classe utilisée pour lancer une exception en cas d'erreur lexicale, syntaxique 
 * ou de calcul.
 */
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
	
	enum LType ///< Types de noeuds/lexèmes possibles
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
	
	LType type; ///< Type
	
	///Données associées
	std::string chaine;
	float nombre;
	bool booleen;
};

/**
 * Elément de base de l'arbre syntaxique permettant de le construire 
 * afin de gérer les priorités des opérations.
 */
class Noeud
{
public:
	/**
	 * Construit un noeud vide.
	 */
	Noeud();
	
	/**
	 * Construit un noeud à partir d'un lexème.
	 * Le noeud créé prendra le type du lexème donné.
	 */ 
	Noeud(const Lexeme &lexeme);
	
	/**
	 * Construit un noeud contenant les noeuds fabriqués à partir des lexèmes donnés.
	 */
	Noeud(const std::vector<Lexeme> &lexemes);
	
	/**
	 * Construit un noeud contenant les noeuds fabriqués en enfants.
	 */
	Noeud(const std::vector<Noeud*> &enfants);
	
	/**
	 * Destructeur.
	 */
	virtual ~Noeud();
	
	/**
	 * Donne le nombre d'enfants du noeud.
	 */
	int NombreEnfants() const {return m_enfants.size();};
	
	/**
	 * Retourne l'enfant à l'indice donnée.
	 */
	Noeud& Enfant(int index) {return *(m_enfants[index]);};
	const Noeud& Enfant(int index) const {return *(m_enfants.at(index));};
	
	/**
	 * Donne le type du noeud.
	 */
	Lexeme::LType Type() const {return m_type;}
	
	/**
	 * Méthodes permettant de récupérer des données supplémentaires associées aux noeuds.
	 * Ex : le nom de la matrice pour un noeud de type VARIABLE_MATRICE
	 */
	std::string DonneeChaine() const {return m_donneeChaine;};
	float DonneeNombre() const {return m_donneeNombre;};
	bool DonneeBooleen() const {return m_donneeBooleen;};
	
	/**
	 * Méthode qui construit l'arbre de syntaxe en utilisant les noeuds enfants
	 * du noeud actuel
	 */
	bool MettreEnArbre();
	
	/**
	 * Méthode qui affiche le contenu du noeud dans un wxTreeCtrl.
	 */
	void AfficherContenu(wxTreeCtrl *arbre, wxTreeItemId parent) const;
	
protected:
	std::vector<Noeud*> m_enfants; ///< Liste des enfants
	Lexeme::LType m_type; ///< Type de noeud
	
	///Données supplémentaires
	std::string m_donneeChaine;
	float m_donneeNombre;
	bool m_donneeBooleen;
};

/**
 * Classe qui représente une résultat.
 * Utilisée lors de l'évaluation de l'arbre syntaxique pour obtenir le résultat final
 * Un résultat peut être soit un scalaire, soit une matrice
 */
class Resultat
{
public:
	enum TypeResultat
	{
		SCALAIRE,
		MATRICE,
	};

	/**
	 * Construit un Resultat à partir d'une matrice ou d'un scalaire.
	 */
	Resultat(const Matrice &matrice);
	Resultat(float scalaire);
	
	/**
	 * Permet de savoir si le résultat est un scalaire ou une matrice.
	 */
	bool EstUnScalaire() const {return m_type == SCALAIRE;};
	bool EstUneMatrice() const {return m_type == MATRICE;};
	
	/**
	 * Permet de récupérer le scalaire ou la matrice.
	 */
	float ValeurScalaire() const {return m_scalaire;};
	Matrice ValeurMatrice() const {return m_matrice;};
	
private:
	TypeResultat m_type;
	float m_scalaire;
	Matrice m_matrice;
};

/**
 * Classe qui gère le parseur dans sa globalité.
 */
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
