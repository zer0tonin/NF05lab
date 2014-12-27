#include "Parseur.h"

#include <iostream>
#include <wx/regex.h>
#include <wx/msgdlg.h> 

#include "Calculs.h"

Noeud::Noeud() : m_type(Lexeme::INDEFINI), m_donneeNombre(0), m_donneeChaine(), m_donneeBooleen(false)
{
	
}

Noeud::Noeud(const Lexeme &lexeme) : m_type(lexeme.type), m_donneeNombre(lexeme.nombre), m_donneeChaine(lexeme.chaine), m_donneeBooleen(lexeme.booleen)
{

}

Noeud::Noeud(const std::vector<Lexeme> &lexemes) : m_type(Lexeme::INDEFINI), m_donneeNombre(0), m_donneeChaine(), m_donneeBooleen(false)
{
	for(int i = 0; i < lexemes.size(); i++)
	{
		m_enfants.push_back(new Noeud(lexemes.at(i)));
	}
}

Noeud::Noeud(const std::vector<Noeud*> &enfants) : m_type(Lexeme::INDEFINI), m_enfants(enfants), m_donneeNombre(0), m_donneeChaine(), m_donneeBooleen(false)
{
	
}

Noeud::~Noeud()
{
	while(m_enfants.size() > 0)
	{
		delete m_enfants[m_enfants.size() - 1];
		m_enfants.pop_back();
	}
}	

bool Noeud::MettreEnArbre()
{
	int a; //Sera utile pour itérer dans la liste des noeuds
	
	// - Fonctions (on cherche les crochets)
	
	//On parcourt le noeud pour trouver les crochets (et donc les fonctions) de premier niveau
	int niveauCrochet = 0;
	int debutCrochet = 0;
	std::vector<Noeud*> noeudsDansCrochet;
	
	for(a = 0; a < m_enfants.size(); a++)
	{
		if(m_enfants[a]->m_type == Lexeme::FONCTION && m_enfants[a]->m_enfants.size() == 0 && !m_enfants[a]->m_donneeBooleen)
			niveauCrochet--;
		
		//Si on est entre des crochets, on stocke tous les noeuds rencontrés dans noeudsDansCrochet
		if(niveauCrochet > 0)
		{
			noeudsDansCrochet.push_back(m_enfants[a]);
		}
		//Si on n'est plus entre des crochets (niveauCrochet == 0) et que l'on a eu des noeuds à l'intérieur des crochets,
		//on génère un nouveau noeud avec les noeuds entre les crochets en tant qu'enfants
		else if(noeudsDansCrochet.size() > 0)
		{
			//Cela signifie que l'on vient de finir une fonction, donc
			//on crée un nouveau noeud avec les noeuds contenus dans les parenthèses
			//(il devra lui aussi les traiter)
			Noeud *nouveauNoeud = new Noeud(noeudsDansCrochet);
			nouveauNoeud->m_type = Lexeme::FONCTION;
			nouveauNoeud->m_donneeChaine = m_enfants[debutCrochet]->m_donneeChaine;
			
			//On supprime le lexème (noeud) des crochets fermant et ouvrant
			//Ainsi que tous les noeuds entre.
			m_enfants.erase(m_enfants.begin() + debutCrochet, m_enfants.begin() + a + 1);
			
			a -= a - debutCrochet; //On vient de supprimer des noeuds, il faut bien replacer a pour repartir du bon endroit dans l'itération
			
			//On ajoute le noeud FONCTION généré
			m_enfants.insert(m_enfants.begin() + debutCrochet, nouveauNoeud);
			
			//On appelle MettreEnArbre() sur sur noeud (récursivité)
			nouveauNoeud->MettreEnArbre();
			
			noeudsDansCrochet.clear();
		}
		
		//Si on tombe sur un crochet, on incrémente niveauCrochet (qui décrit le niveau de crochet dans lequel on se trouve)
		if(m_enfants[a]->m_type == Lexeme::FONCTION && m_enfants[a]->m_enfants.size() == 0 && m_enfants[a]->m_donneeBooleen)
		{
			if(niveauCrochet == 0)
				debutCrochet = a; //On stocke la position du début des crochets
			niveauCrochet++;
		}
	}
	
	if(a == m_enfants.size() && (niveauCrochet != 0))
		throw ExceptionParseur("Trop/pas assez de crochets");
	
	// - Parenthèses (de 1er niveau uniquement, les autres niveaux seront traités quand MettreEnArbre()
	//   sera utilisé de manière récursive sur les noeuds de parenthèse.
	// NOTE : Cette partie fonctionne de la même manière que pour les fonctions (excepté que l'on n'a pas besoin de stocker le nom de la fonction dans le noeud généré)
	
	//On parcourt le noeud pour trouver les parenthèses de 1er niveau
	int niveauParenthese = 0; //Indique le niveau de parenthèses
	int debutParenthese = 0; //Indique la position du début de la parenthèse
	std::vector<Noeud*> noeudsDansParenthese; //Stocke la liste des noeuds entre deux parenthèses

	for(a = 0; a < m_enfants.size(); a++)
	{
		//On est sur une parenthèse fermante, on réduit niveauParenthese de 1.
		if(m_enfants[a]->m_type == Lexeme::PARENTHESE && !m_enfants[a]->m_donneeBooleen)
			niveauParenthese--;
		
		//On est dans une parenthèse
		if(niveauParenthese > 0)
		{
			noeudsDansParenthese.push_back(m_enfants[a]); //On ajoute le noeud actuellement parcouru dans la liste des noeuds dans la parenthèse
		}
		else if(noeudsDansParenthese.size() > 0)
		{
			//Cela signifie que l'on vient de finir une parenthèse, donc
			//on crée un nouveau noeud contenant les noeuds à l'intérieur des parenthèses
			//(il devra lui aussi les traiter)
			Noeud *nouveauNoeud = new Noeud(noeudsDansParenthese);
			nouveauNoeud->m_type = Lexeme::PARENTHESE;
			
			//On supprime du noeud principal les noeuds contenu dans la parenthèse, ainsi
			//que la parenthèse ouvrante et fermante.
			m_enfants.erase(m_enfants.begin() + debutParenthese, m_enfants.begin() + a + 1);
			a -= a - debutParenthese;
			
			//On insère le noeud "parenthèse" qui contient tous les noeuds qui étaient contenus dans
			//la parenthèse.
			m_enfants.insert(m_enfants.begin() + debutParenthese, nouveauNoeud);
			
			//Il faut aussi mettre en arbre les noeuds contenus dans le noeud "parenthèse"
			nouveauNoeud->MettreEnArbre();
			
			noeudsDansParenthese.clear();
		}
		
		//On est sur une parenthèse ouvrante, on augmente niveauParenthese de 1.
		//Si c'est une parenthèse de niveau 1, on stocke sa position dans debutParenthese.
		if(m_enfants[a]->m_type == Lexeme::PARENTHESE && m_enfants[a]->m_donneeBooleen)
		{
			if(niveauParenthese == 0)
				debutParenthese = a;
			niveauParenthese++;
		}
	}
	
	//Si on a plus de parenthèses fermante que ouvrante ou inversement, cela signifie qu'il y a une erreur
	//de syntaxe
	if(a == m_enfants.size() && (niveauParenthese != 0))
		throw ExceptionParseur("Trop/pas assez de parentheses.");
	
	//Ensuite, on traite les opérateurs de la priorité la plus haute à la priorité la plus basse
	
	// - Puissance
	for(int a = 0; a < m_enfants.size(); a++)
	{
		if(m_enfants[a]->m_type == Lexeme::OPERATEUR_PUISSANCE)
		{
			//Cherche le nombre/matrice précédant et suivant l'opérateur. 
			//(pas de possibilité d'avoir une opération unaire cette fois)
			//On vérifie évidemment que c'est bien une matrice/nombre ou un noeud "parenthèse" qui précède/suit
			//l'opérateur.
			Noeud *noeudOperateur = m_enfants[a];
			if(a > 0 && a < m_enfants.size() - 1)
			{
				//L'opérateur n'est pas au début de la liste, donc ce sera un opérateur binaire
				std::vector<Noeud*> listeNoeudPourOperateur;
				listeNoeudPourOperateur.push_back(m_enfants[a - 1]);
				listeNoeudPourOperateur.push_back(m_enfants[a + 1]);
				
				noeudOperateur->m_enfants = listeNoeudPourOperateur;
				
				//On supprime l'ancien noeud de l'opérateur et le lexème qui le suit
				m_enfants.erase(m_enfants.begin() + a - 1, m_enfants.begin() + a + 2);
				
				//On ajoute le noeud généré de l'opérateur
				m_enfants.insert(m_enfants.begin() + a - 1, noeudOperateur);
				a--;
			}
			else
			{
				//L'opérateur est par exemple précédé/suivi d'un autre opérateur/parenthèse ou en est précédé
				//C'est une erreur de syntaxe
				throw ExceptionParseur("Erreur de syntaxe");
			}
		}
	}
	
	// - Multiplication, division
	for(int a = 0; a < m_enfants.size(); a++)
	{
		if(m_enfants[a]->m_type == Lexeme::OPERATEUR_MULTIPLIE || m_enfants[a]->m_type == Lexeme::OPERATEUR_DIVISE)
		{
			//Cherche le nombre/matrice précédant et suivant l'opérateur. 
			//(pas de possibilité d'avoir une opération unaire cette fois)
			//On vérifie évidemment que c'est bien une matrice/nombre ou un noeud "parenthèse" qui précède/suit
			//l'opérateur.
			Noeud *noeudOperateur = m_enfants[a];
			if(a > 0 && a < m_enfants.size() - 1)
			{
				//On récupère le noeud avant et celui après l'opérateur, ce sont les opérandes de la multiplication/division
				std::vector<Noeud*> listeNoeudPourOperateur;
				listeNoeudPourOperateur.push_back(m_enfants[a - 1]);
				listeNoeudPourOperateur.push_back(m_enfants[a + 1]);
				
				noeudOperateur->m_enfants = listeNoeudPourOperateur; //On les ajoute en noeuds enfants de l'opérateur
				
				//On supprime l'ancien noeud de l'opérateur et les anciens noeuds des opérandes
				m_enfants.erase(m_enfants.begin() + a - 1, m_enfants.begin() + a + 2);
				
				//On ajoute le noeud généré de l'opérateur
				m_enfants.insert(m_enfants.begin() + a - 1, noeudOperateur);
				a--;
			}
			else
			{
				//L'opérateur est par exemple précédé/suivi d'un autre opérateur/parenthèse ou en est précédé
				//C'est une erreur de syntaxe
				throw ExceptionParseur("Erreur de syntaxe");
			}
		}
	}
	
	// - Addition, soustraction (attention, cas de l'addition/soustraction unaire, par exemple : -1, +2)
	for(int a = 0; a < m_enfants.size(); a++)
	{
		if(m_enfants[a]->m_type == Lexeme::OPERATEUR_PLUS || m_enfants[a]->m_type == Lexeme::OPERATEUR_MOINS)
		{
			//Cherche le nombre/matrice précédant et suivant l'opérateur. 
			//(on traite le précédent uniquement si l'opérateur n'est pas au début,
			//ce qui impliquera forcément une opération unaire)
			Noeud *noeudOperateur = m_enfants[a];
			if(a > 0 && a < m_enfants.size() - 1)
			{
				//L'opérateur n'est pas au début de la liste, donc ce sera un opérateur binaire
				std::vector<Noeud*> listeNoeudPourOperateur;
				listeNoeudPourOperateur.push_back(m_enfants[a - 1]);
				listeNoeudPourOperateur.push_back(m_enfants[a + 1]);
				
				noeudOperateur->m_enfants = listeNoeudPourOperateur;
				
				//On supprime l'ancien noeud de l'opérateur et les noeuds des opérandes
				m_enfants.erase(m_enfants.begin() + a - 1, m_enfants.begin() + a + 2);
				
				//On ajoute le noeud généré de l'opérateur
				m_enfants.insert(m_enfants.begin() + a - 1, noeudOperateur);
				a--;
			}
			else if(a == 0 && m_enfants.size() >= 2)
			{
				//L'opérateur est au début de la liste, donc ce sera un opérateur unaire
				std::vector<Noeud*> listeNoeudPourOperateur;
				listeNoeudPourOperateur.push_back(m_enfants[a + 1]);
				
				noeudOperateur->m_enfants = listeNoeudPourOperateur;
				
				//On supprime l'ancien noeud de l'opérateur et le noeud des l'opérandes
				m_enfants.erase(m_enfants.begin() + a, m_enfants.begin() + a + 2);
				
				//On ajoute le noeud généré de l'opérateur
				m_enfants.insert(m_enfants.begin() + a, noeudOperateur);
			}
			else
			{
				//L'opérateur est par exemple suivi d'un autre opérateur/parenthèse ou en est précédé
				//C'est une erreur de syntaxe
				throw ExceptionParseur("Erreur de syntaxe");
			}
		}
	}
	
	// - Affectation (=)
	for(int a = 0; a < m_enfants.size(); a++)
	{
		if(m_enfants[a]->m_type == Lexeme::OPERATEUR_EGAL)
		{
			//Cherche le nombre/matrice précédant et suivant l'opérateur. 
			//(pas de possibilité d'avoir une opération unaire cette fois)
			Noeud *noeudOperateur = m_enfants[a];
			if(a > 0 && a < m_enfants.size() - 1)
			{
				//L'opérateur n'est pas au début de la liste, donc ce sera un opérateur binaire
				std::vector<Noeud*> listeNoeudPourOperateur;
				listeNoeudPourOperateur.push_back(m_enfants[a - 1]);
				listeNoeudPourOperateur.push_back(m_enfants[a + 1]);
				
				noeudOperateur->m_enfants = listeNoeudPourOperateur;
				
				//On supprime l'ancien noeud de l'opérateur et le lexème qui le suit
				m_enfants.erase(m_enfants.begin() + a - 1, m_enfants.begin() + a + 2);
				
				//On ajoute le noeud généré de l'opérateur
				m_enfants.insert(m_enfants.begin() + a - 1, noeudOperateur);
				a--;
			}
			else
			{
				//L'opérateur est par exemple précédé/suivi d'un autre opérateur/parenthèse ou en est précédé
				//C'est une erreur de syntaxe
				throw ExceptionParseur("Erreur de syntaxe");
			}
		}
	}
		
	return true;
}

void Noeud::AfficherContenu(wxTreeCtrl *arbre, wxTreeItemId parent) const
{
	wxString contenu;
	
	if(m_type == Lexeme::OPERATEUR_PLUS)
		contenu += "+";
	else if(m_type == Lexeme::OPERATEUR_MOINS)
		contenu += "-";
	else if(m_type == Lexeme::OPERATEUR_MULTIPLIE)
		contenu += "*";
	else if(m_type == Lexeme::OPERATEUR_DIVISE)
		contenu += "/";
	else if(m_type == Lexeme::OPERATEUR_PUISSANCE)
		contenu += "^";
	else if(m_type == Lexeme::OPERATEUR_EGAL)
		contenu += "=";
	else if(m_type == Lexeme::PARENTHESE)
		contenu += "()";
	else if(m_type == Lexeme::CONSTANTE)
		contenu += wxString::FromDouble(m_donneeNombre);
	else if(m_type == Lexeme::VARIABLE_MATRICE)
		contenu += m_donneeChaine;
	else if(m_type == Lexeme::FONCTION)
		contenu += m_donneeChaine;
	else
		contenu += "?";
		
	wxTreeItemId noeudGUI = arbre->AppendItem(parent, contenu);
	
	for(int a = 0; a < m_enfants.size(); a++)
	{
		m_enfants[a]->AfficherContenu(arbre, noeudGUI);
	}
}

//***********************************************************************************************//
//*************************** RESULTAT **********************************************************//
//***********************************************************************************************//

Resultat::Resultat(const std::string msgErreur) : m_type(ERREUR), m_erreur(msgErreur), m_matrice(0,0)
{
	
}

Resultat::Resultat(const Matrice &matrice) : m_type(MATRICE), m_matrice(matrice)
{
	
}

Resultat::Resultat(float scalaire) : m_type(SCALAIRE), m_scalaire(scalaire), m_matrice(0,0)
{
	
}

//***********************************************************************************************//
//*************************** PARSEUR ***********************************************************//
//***********************************************************************************************//

Parseur::Parseur()
{
	
}

Parseur::~Parseur()
{
	
}

Resultat Parseur::CalculerExpression(const std::string &str, Conteneur &conteneurDeVariables, wxTreeCtrl *arbreSyn)
{
	Noeud *arbreSyntaxique = CreerArbreSyntaxique(Parse(str));
	
	if(arbreSyn != NULL)
	{
		arbreSyntaxique->AfficherContenu(arbreSyn, arbreSyn->AddRoot(L"Arbre de syntaxe généré"));
	}
	
	return Calculer(*arbreSyntaxique, conteneurDeVariables);
}

std::vector<Lexeme> Parseur::Parse(std::string expression)
{
	std::vector<Lexeme> listeLexeme;
	
	while(expression.size() > 0)
	{
		std::size_t debutCorrespondance;
		std::size_t longueurCorrespondance;
		
		wxRegEx constantRegex("^[0-9.]+");
		wxRegEx variableRegex("^[A-Z]");
		wxRegEx operateurRegex("^[\\+-\\*\\/=\\^]");
		wxRegEx parentheseRegex("^[\\(\\)]");
		wxRegEx fonctionRegex("^[a-z]+\\[");
		wxRegEx finFonctionRegex("^\\]");
		
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
			else if(operateurRegex.GetMatch(expression, 0) == "^")
				nouveauLexeme.type = Lexeme::OPERATEUR_PUISSANCE;
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
			nouveauLexeme.booleen = true; //Signifie que c'est la début d'une fonction
			//Extraction du nom de la fonction (on doit supprimer la parenthèse)
			nouveauLexeme.chaine = fonctionRegex.GetMatch(expression, 0).substr(0, fonctionRegex.GetMatch(expression, 0).size() - 1);
			
			listeLexeme.push_back(nouveauLexeme);
		}
		else if(finFonctionRegex.Matches(expression))
		{
			//On est sur un crochet fermant "]" donc c'est la fin d'une fonction
			//On est sur une fonction (par exemple, determinant, nombre de lignes d'une matrice)
			finFonctionRegex.GetMatch(&debutCorrespondance, &longueurCorrespondance, 0);
			
			Lexeme nouveauLexeme;
			nouveauLexeme.type = Lexeme::FONCTION;
			nouveauLexeme.booleen = false; //Signifie que c'est la fin d'une fonction
			
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
		throw ExceptionParseur("Symbole non reconnu dans l'expression.");
	}
	
	return listeLexeme;
}

Noeud* Parseur::CreerArbreSyntaxique(std::vector<Lexeme> listeLexeme)
{
	Noeud *m_noeudPrincipal = new Noeud(listeLexeme);
	m_noeudPrincipal->MettreEnArbre();
	return m_noeudPrincipal;
}

Resultat Parseur::Calculer(const Noeud &noeud, Conteneur &conteneurDeVariables)
{
	if(noeud.Type() == Lexeme::CONSTANTE)
	{
		return Resultat(noeud.DonneeNombre());
	}
	else if(noeud.Type() == Lexeme::VARIABLE_MATRICE)
	{
		if(conteneurDeVariables.Existe(noeud.DonneeChaine()[0]))
		{
			//La variable existe, on retourne donc la matrice stockée dans la variable
			return Resultat(conteneurDeVariables.Variable(noeud.DonneeChaine()[0]));
		}
		else
		{
			//Elle n'existe pas, on renvoit une erreur
			//Note : le cas de l'affectation est traité séparément, directement avec
			//l'opérateur d'affectation.
			throw ExceptionParseur("La variable " + noeud.DonneeChaine() + " n'est pas definie");
		}
	}
	else if(noeud.Type() == Lexeme::PARENTHESE)
	{
		if(noeud.NombreEnfants() == 1)
		{
			//On retourne le résultat de l'intérieur de la parenthèse directement
			return Calculer(noeud.Enfant(0), conteneurDeVariables);
		}
		else
		{
			//Un noeud parenthèse ne peut contenir qu'un seul noeud, il y a donc une erreur
			throw ExceptionParseur("Erreur avec une parenthèse");
		}
	}
	else if(noeud.Type() == Lexeme::OPERATEUR_PLUS) //Opérateur +
	{
		if(noeud.NombreEnfants() == 1) //Unaire
		{
			Resultat resultatOperande = Calculer(noeud.Enfant(0), conteneurDeVariables); //On appelle la fonction Calculer sur le noeud enfant de l'opérateur
			return resultatOperande; //L'opérateur + unaire n'a pas vraiment d'effet sur la résultat, on le retourne directement.			
		}
		else if(noeud.NombreEnfants() == 2) //Binaire
		{
			Resultat resultatOperandeGauche = Calculer(noeud.Enfant(0), conteneurDeVariables); //On appelle la fonction Calculer sur les deux opérandes (noeuds) de l'opérateur
			Resultat resultatOperandeDroit = Calculer(noeud.Enfant(1), conteneurDeVariables);
			
			if(resultatOperandeGauche.EstUnScalaire() && resultatOperandeDroit.EstUnScalaire())
			{
				return Resultat(resultatOperandeGauche.ValeurScalaire() + resultatOperandeDroit.ValeurScalaire());
			}
			else if(resultatOperandeGauche.EstUneMatrice() && resultatOperandeDroit.EstUneMatrice())
			{
				if(resultatOperandeGauche.ValeurMatrice().ObtenirColonnes() == resultatOperandeDroit.ValeurMatrice().ObtenirColonnes() &&
				   resultatOperandeGauche.ValeurMatrice().ObtenirLignes()   == resultatOperandeDroit.ValeurMatrice().ObtenirLignes())
				{
					//Bonne dimension
					return Resultat(resultatOperandeGauche.ValeurMatrice() + resultatOperandeDroit.ValeurMatrice());
				}
				else
				{
					//Dimensions qui ne correspondent pas
					throw ExceptionParseur("Impossible d'additionner deux matrices de dimensions differentes");
				}
			}
			else
			{
				throw ExceptionParseur("Non concordance des types pour l'addition");
			}
		}
	}
	else if(noeud.Type() == Lexeme::OPERATEUR_MOINS) //Opérateur +
	{
		if(noeud.NombreEnfants() == 1) //Unaire
		{
			Resultat resultatOperande = Calculer(noeud.Enfant(0), conteneurDeVariables); //On appelle la fonction Calculer sur le noeud enfant de l'opérateur

			if(resultatOperande.EstUnScalaire())
				return Resultat(-resultatOperande.ValeurScalaire());
			else if(resultatOperande.EstUneMatrice())
				return Resultat(-resultatOperande.ValeurMatrice());			
		}
		else if(noeud.NombreEnfants() == 2) //Binaire
		{
			Resultat resultatOperandeGauche = Calculer(noeud.Enfant(0), conteneurDeVariables); //On appelle la fonction Calculer sur les deux opérandes (noeuds) de l'opérateur
			Resultat resultatOperandeDroit = Calculer(noeud.Enfant(1), conteneurDeVariables);
			
			if(resultatOperandeGauche.EstUnScalaire() && resultatOperandeDroit.EstUnScalaire())
			{
				return Resultat(resultatOperandeGauche.ValeurScalaire() - resultatOperandeDroit.ValeurScalaire());
			}
			else if(resultatOperandeGauche.EstUneMatrice() && resultatOperandeDroit.EstUneMatrice())
			{
				if(resultatOperandeGauche.ValeurMatrice().ObtenirColonnes() == resultatOperandeDroit.ValeurMatrice().ObtenirColonnes() &&
				   resultatOperandeGauche.ValeurMatrice().ObtenirLignes()   == resultatOperandeDroit.ValeurMatrice().ObtenirLignes())
				{
					//Bonne dimension
					return Resultat(resultatOperandeGauche.ValeurMatrice() - resultatOperandeDroit.ValeurMatrice());
				}
				else
				{
					//Dimensions qui ne correspondent pas
					throw ExceptionParseur("Impossible de soustraire deux matrices de dimensions différentes");
				}
			}
			else
			{
				throw ExceptionParseur("Non concordance des types pour la soustraction");
			}
		}
	}
	else if(noeud.Type() == Lexeme::OPERATEUR_MULTIPLIE)
	{
		if(noeud.NombreEnfants() == 2)
		{
			Resultat resultatOperandeGauche = Calculer(noeud.Enfant(0), conteneurDeVariables); //On appelle la fonction Calculer sur les deux opérandes (noeuds) de l'opérateur
			Resultat resultatOperandeDroit = Calculer(noeud.Enfant(1), conteneurDeVariables);
				
			if(resultatOperandeGauche.EstUnScalaire() && resultatOperandeDroit.EstUnScalaire())
			{
				return Resultat(resultatOperandeGauche.ValeurScalaire() * resultatOperandeDroit.ValeurScalaire());
			}
			else if(resultatOperandeGauche.EstUnScalaire() && resultatOperandeDroit.EstUneMatrice())
			{
				return Resultat(resultatOperandeGauche.ValeurScalaire() * resultatOperandeDroit.ValeurMatrice());
			}
			else if(resultatOperandeGauche.EstUneMatrice() && resultatOperandeDroit.EstUnScalaire())
			{
				return Resultat(resultatOperandeGauche.ValeurMatrice() * resultatOperandeDroit.ValeurScalaire());
			}
			else if(resultatOperandeGauche.EstUneMatrice() && resultatOperandeDroit.EstUneMatrice())
			{
				//Multiplication entre deux matrices, il faut vérifier la possibilité de le faire
				if(resultatOperandeGauche.ValeurMatrice().ObtenirColonnes() == resultatOperandeDroit.ValeurMatrice().ObtenirLignes())
					return Resultat(resultatOperandeGauche.ValeurMatrice() * resultatOperandeDroit.ValeurMatrice());
				else
					throw ExceptionParseur("Impossible de multiplier les deux matrices");
			}
		}
		else
		{
			throw ExceptionParseur("Pas assez/trop d'operandes pour la multiplication");
		}
	}
	else if(noeud.Type() == Lexeme::OPERATEUR_DIVISE)
	{
		if(noeud.NombreEnfants() == 2)
		{
			Resultat resultatOperandeGauche = Calculer(noeud.Enfant(0), conteneurDeVariables); //On appelle la fonction Calculer sur les deux opérandes (noeuds) de l'opérateur
			Resultat resultatOperandeDroit = Calculer(noeud.Enfant(1), conteneurDeVariables);
				
			if(resultatOperandeGauche.EstUnScalaire() && resultatOperandeDroit.EstUnScalaire())
			{
				return Resultat(resultatOperandeGauche.ValeurScalaire() / resultatOperandeDroit.ValeurScalaire());
			}
			else if(resultatOperandeGauche.EstUnScalaire() && resultatOperandeDroit.EstUneMatrice())
			{
				if(resultatOperandeDroit.ValeurMatrice().Inversible())
					return Resultat(resultatOperandeGauche.ValeurScalaire() * resultatOperandeDroit.ValeurMatrice().Inverse());
				else 
					throw ExceptionParseur("Matrice non inversible !");
			}
			else if(resultatOperandeGauche.EstUneMatrice() && resultatOperandeDroit.EstUnScalaire())
			{
				return Resultat(resultatOperandeGauche.ValeurMatrice() / resultatOperandeDroit.ValeurScalaire());
			}
			else if(resultatOperandeGauche.EstUneMatrice() && resultatOperandeDroit.EstUneMatrice())
			{
				//Multiplication entre deux matrices, il faut vérifier la possibilité de le faire
				if(resultatOperandeDroit.ValeurMatrice().Inversible() && 
				   resultatOperandeGauche.ValeurMatrice().ObtenirColonnes() == resultatOperandeDroit.ValeurMatrice().Inverse().ObtenirLignes())
					return Resultat(resultatOperandeGauche.ValeurMatrice() / resultatOperandeDroit.ValeurMatrice());
				else
					throw ExceptionParseur("Impossible de multiplier les deux matrices");
			}
		}
		else
		{
			throw ExceptionParseur("Pas assez/trop d'operandes pour la multiplication");
		}
	}
	else if(noeud.Type() == Lexeme::OPERATEUR_PUISSANCE)
	{
		if(noeud.NombreEnfants() == 2)
		{
			Resultat resultatOperandeGauche = Calculer(noeud.Enfant(0), conteneurDeVariables); //On appelle la fonction Calculer sur les deux opérandes (noeuds) de l'opérateur
			Resultat resultatOperandeDroit = Calculer(noeud.Enfant(1), conteneurDeVariables);
				
			if(resultatOperandeGauche.EstUnScalaire() && resultatOperandeDroit.EstUnScalaire())
			{
				return Resultat(std::pow(resultatOperandeGauche.ValeurScalaire(), resultatOperandeDroit.ValeurScalaire()));
			}
			else if(resultatOperandeGauche.EstUneMatrice() && resultatOperandeDroit.EstUnScalaire() && resultatOperandeGauche.ValeurMatrice().Carree())
			{
				return Resultat(Puissance(resultatOperandeGauche.ValeurMatrice(), resultatOperandeDroit.ValeurScalaire()));
			}
			else
			{
				throw ExceptionParseur("Operateur ^ mal utilisé");
			}
		}
		else
		{
			throw ExceptionParseur("Pas assez/trop d'operandes pour la puissance");
		}
	}
	else if(noeud.Type() == Lexeme::OPERATEUR_EGAL)
	{
		//On est sur un opérateur d'affectation (=)
		//Il y a forcément deux opérandes, sinon c'est une erreur
		if(noeud.NombreEnfants() == 2)
		{
			//On ne traite pas (avec une récursivité) l'opérande gauche qui doit normalement être
			//une matrice (Type VARIABLE_MATRICE)
			Resultat resultatOperandeDroite = Calculer(noeud.Enfant(1), conteneurDeVariables);
			
			if(resultatOperandeDroite.EstUneMatrice())
			{
				//On vérifie bien que l'opérande gauche est une opérande de type VARIABLE_MATRICE
				if(noeud.Enfant(0).Type() == Lexeme::VARIABLE_MATRICE)
				{
					conteneurDeVariables.AjouterVariable(noeud.Enfant(0).DonneeChaine()[0], 
													     resultatOperandeDroite.ValeurMatrice().ObtenirLignes(),
														 resultatOperandeDroite.ValeurMatrice().ObtenirColonnes());
					
					conteneurDeVariables.Variable(noeud.Enfant(0).DonneeChaine()[0]) = resultatOperandeDroite.ValeurMatrice();
					
					return resultatOperandeDroite; //On renvoit quand même le résultat de l'opérande droite pour pouvoir l'afficher
					//à l'utilisateur.
				}
				else
				{
					//Ce n'est pas possible
					throw ExceptionParseur("Variable attendue a gauche de l'operateur d'affectation");
				}
			}
			else
			{
				throw ExceptionParseur("Seules des matrices peuvent etre stockees dans une variable");
			}
		}
		else
		{
			throw ExceptionParseur("Pas assez/trop d'operandes pour l'affectation");
		}
	}
	else if(noeud.Type() == Lexeme::FONCTION)
	{
		if(noeud.DonneeChaine() == "det" || noeud.DonneeChaine() == "determinant") //Le déterminant
		{
			if(noeud.NombreEnfants() == 1)
			{
				Resultat resultatArgument = Calculer(noeud.Enfant(0), conteneurDeVariables);
				if(resultatArgument.EstUneMatrice())
				{
					return Resultat(resultatArgument.ValeurMatrice().Determinant());
				}
				else
				{
					throw ExceptionParseur("La fonction det a besoin d'une matrice uniquement");
				}
			}
			else
			{
				throw ExceptionParseur("La fonction det a besoin d'un seul argument");
			}
		}
		else if(noeud.DonneeChaine() == "trac" || noeud.DonneeChaine() == "trace") //La trace
		{
			if(noeud.NombreEnfants() == 1)
			{
				Resultat resultatArgument = Calculer(noeud.Enfant(0), conteneurDeVariables);
				if(resultatArgument.EstUneMatrice())
				{
					return Resultat(resultatArgument.ValeurMatrice().Trace());
				}
				else
				{
					throw ExceptionParseur("La fonction trac a besoin d'une matrice uniquement");
				}
			}
			else
			{
				throw ExceptionParseur("La fonction trac a besoin d'un seul argument");
			}
		}
		else
		{
			//Fonction inconnue
			throw ExceptionParseur("La fonction " + noeud.DonneeChaine() + "[...] est inconnue");
		}
	}
	else if(noeud.Type() == Lexeme::INDEFINI)
	{
		//Indéfini mais avec un noeud enfant, on retourne directement le résultat
		if(noeud.NombreEnfants() == 1)
			return Calculer(noeud.Enfant(0), conteneurDeVariables);
	}
	
	throw ExceptionParseur("Operation non supportee");
}

