#include "AnalyseurSyntaxique.h"

#include <wx/msgdlg.h>

namespace parseur
{

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
	
	// - Fonctions
	
	//On parcourt le noeud pour trouver les crochets (et donc les fonctions) de premier niveau
	int niveauCrochet = 0;
	int debutCrochet = 0;
	std::vector<Noeud*> noeudsDansCrochet;
	
	for(a = 0; a < m_enfants.size(); a++)
	{
		if(m_enfants[a]->m_type == Lexeme::FONCTION && m_enfants[a]->m_enfants.size() == 0 && !m_enfants[a]->m_donneeBooleen)
			niveauCrochet--;
		
		if(niveauCrochet > 0)
		{
			noeudsDansCrochet.push_back(m_enfants[a]);
		}
		else if(noeudsDansCrochet.size() > 0)
		{
			//Cela signifie que l'on vient de finir une parenthèse, donc
			//on crée un nouveau noeud avec ces lexèmes (il devra lui aussi
			//les traiter)
			Noeud *nouveauNoeud = new Noeud(noeudsDansCrochet);
			nouveauNoeud->m_type = Lexeme::FONCTION;
			nouveauNoeud->m_donneeChaine = m_enfants[debutCrochet]->m_donneeChaine;
			
			//On supprime le lexème (noeud) de la parenthèse fermante puis de celle ouvrante
			//Ainsi que tous les noeuds entre.
			m_enfants.erase(m_enfants.begin() + debutCrochet, m_enfants.begin() + a + 1);
			a -= a - debutCrochet;
			
			m_enfants.insert(m_enfants.begin() + debutCrochet, nouveauNoeud);
			
			if(!nouveauNoeud->MettreEnArbre())
				return false;
			
			noeudsDansCrochet.clear();
		}
		
		if(m_enfants[a]->m_type == Lexeme::FONCTION && m_enfants[a]->m_enfants.size() == 0 && m_enfants[a]->m_donneeBooleen)
		{
			if(niveauCrochet == 0)
				debutCrochet = a;
			niveauCrochet++;
		}
	}
	
	if(a == m_enfants.size() && (niveauCrochet != 0))
		return false;
	
	// - Parenthèses
	
	//On parcourt le noeud pour trouver les parenthèses de 1er niveau
	int niveauParenthese = 0;
	int debutParenthese = 0;
	std::vector<Noeud*> noeudsDansParenthese;

	for(a = 0; a < m_enfants.size(); a++)
	{
		if(m_enfants[a]->m_type == Lexeme::PARENTHESE && !m_enfants[a]->m_donneeBooleen)
			niveauParenthese--;
		
		if(niveauParenthese > 0)
		{
			noeudsDansParenthese.push_back(m_enfants[a]);
		}
		else if(noeudsDansParenthese.size() > 0)
		{
			//Cela signifie que l'on vient de finir une parenthèse, donc
			//on crée un nouveau noeud avec ces lexèmes (il devra lui aussi
			//les traiter)
			Noeud *nouveauNoeud = new Noeud(noeudsDansParenthese);
			nouveauNoeud->m_type = Lexeme::PARENTHESE;
			
			//On supprime le lexème (noeud) de la parenthèse fermante puis de celle ouvrante
			//Ainsi que tous les noeuds entre.
			m_enfants.erase(m_enfants.begin() + debutParenthese, m_enfants.begin() + a + 1);
			a -= a - debutParenthese;
			
			m_enfants.insert(m_enfants.begin() + debutParenthese, nouveauNoeud);
			
			if(!nouveauNoeud->MettreEnArbre())
				return false;
			
			noeudsDansParenthese.clear();
		}
		
		if(m_enfants[a]->m_type == Lexeme::PARENTHESE && m_enfants[a]->m_donneeBooleen)
		{
			if(niveauParenthese == 0)
				debutParenthese = a;
			niveauParenthese++;
		}
	}
	
	if(a == m_enfants.size() && (niveauParenthese != 0))
		return false;
	
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
			if(a > 0)
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
				return false;
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
			if(a > 0)
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
				return false;
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
			if(a > 0)
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
			else if(a == 0)
			{
				//L'opérateur est au début de la liste, donc ce sera un opérateur unaire
				std::vector<Noeud*> listeNoeudPourOperateur;
				listeNoeudPourOperateur.push_back(m_enfants[a + 1]);
				
				noeudOperateur->m_enfants = listeNoeudPourOperateur;
				
				//On supprime l'ancien noeud de l'opérateur et le lexème qui le suit
				m_enfants.erase(m_enfants.begin() + a, m_enfants.begin() + a + 2);
				
				//On ajoute le noeud généré de l'opérateur
				m_enfants.insert(m_enfants.begin() + a, noeudOperateur);
			}
			else
			{
				//L'opérateur est par exemple suivi d'un autre opérateur/parenthèse ou en est précédé
				//C'est une erreur de syntaxe
				return false;
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
	
AnalyseurSyntaxique::AnalyseurSyntaxique() : m_noeudPrincipal(nullptr)
{
	
}

AnalyseurSyntaxique::~AnalyseurSyntaxique()
{
	if(m_noeudPrincipal != nullptr)
		delete m_noeudPrincipal;
}

bool AnalyseurSyntaxique::CreerArbreSyntaxique(std::vector<Lexeme> listeLexeme)
{
	m_noeudPrincipal = new Noeud(listeLexeme);
	return m_noeudPrincipal->MettreEnArbre();
}

void AnalyseurSyntaxique::AfficherContenu(wxTreeCtrl *arbre)
{
	m_noeudPrincipal->AfficherContenu(arbre, arbre->AddRoot(L"Arbre de syntaxe généré"));
}

}

