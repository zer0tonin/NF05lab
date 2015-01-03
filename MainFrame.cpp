#include "MainFrame.h"
#include <wx/aboutdlg.h>
#include <wx/msgdlg.h> 
#include <wx/log.h>
#include <wx/stdpaths.h>
#include <wx/utils.h>
#include <wx/filedlg.h>
#include <wx/wfstream.h>

#include <iostream>
#include "AjoutMatriceDialogue.h"
#include "Parseur.h"
#include "ResolutionSystemeDialogue.h"
#include "tinyxml2.h"

MainFrame::MainFrame(wxWindow* parent) : RibbonFrameBase(parent), m_artProvider(true), m_conteneurVariables()
{
	m_artProvider.SetColourScheme(wxColour(255, 255, 255),
								  wxColour(196, 203, 255),
								  wxColour(0, 0, 0));
	m_ribbonBar1->SetArtProvider(&m_artProvider);
	m_ribbonBar1->Realize();
	m_barreBoutonsAffichage->ToggleButton(BOUTON_AFFICHAGE_VARIABLES, true);
}

MainFrame::~MainFrame()
{
}

void MainFrame::ExecuterCommande()
{
	wxString commande = m_zoneCommande->GetValue();
	m_arbreSyntaxe->DeleteAllItems();
	
	if(commande.IsEmpty()) //Si la commande est vide, on fait rien
		return;
	
	//On essaie de calculer l'expression.
	//Si l'opération échoue (symbole inconnu, opération impossible...), on exécute ce qu'il y a dans catch{ ... }
	try
	{
		Parseur parseur;
		Resultat resultatCommande = parseur.CalculerExpression(commande.ToStdString(), m_conteneurVariables, m_arbreSyntaxe);
		
		if(resultatCommande.EstUnScalaire())
			m_zoneResultats->SetValue(m_zoneResultats->GetValue() + "\n" + m_zoneCommande->GetValue() + "\n --> " + wxString::FromDouble(resultatCommande.ValeurScalaire()));
		else if(resultatCommande.EstUneMatrice())
		{
			//Affichage de la matrice
			m_zoneResultats->SetValue(m_zoneResultats->GetValue() + "\n" + m_zoneCommande->GetValue() + "\n");
			for(int ligne = 0; ligne < resultatCommande.ValeurMatrice().ObtenirLignes(); ligne++)
			{
				for(int colonne = 0; colonne < resultatCommande.ValeurMatrice().ObtenirColonnes(); colonne++)
				{
					m_zoneResultats->SetValue(m_zoneResultats->GetValue() + wxString::FromDouble(resultatCommande.ValeurMatrice().ObtenirValeur(ligne, colonne)) + "\t");
				}
				m_zoneResultats->SetValue(m_zoneResultats->GetValue() + "\n");
			}
		}
	}
	catch(const std::exception &e)
	{
		//Affichage de l'erreur si échec
		m_zoneResultats->SetValue(m_zoneResultats->GetValue() + "\n" + m_zoneCommande->GetValue() + "\n Erreur : " + e.what());
	}
		

	m_arbreSyntaxe->ExpandAll();
	m_zoneCommande->SetValue("");
	
	//Mise à jour de l'arbre qui liste les variables
	m_conteneurVariables.MAJGUI(m_arbreVariables);
}

/*
 * La méthode Enregistrer() stocke le contenu des variables dans un fichier XML ayant la structure:
<?xml version="1.0" encoding="UTF-8"?>
<variable>
    <matrice>
        <nom>numéro ASCII correspondant au nom de la matrice</nom>
        <lignes>nombre de ligne de la matrice</lignes>
        <colonnes>nombre de colonens de la matrice</colonnes>
        <valeur>valeur en 1,1</valeur>
		<valeur>valeur en 1,2</valeur>
		<valeur>...</valeur>
    </matrice>
	<matrice>
	...
	</matrice>
	...
</variable>
 */ 

void MainFrame::Enregistrer()
{
	
	int i, j, k;
	tinyxml2::XMLDocument fichier;
	tinyxml2::XMLNode *racine;
	tinyxml2::XMLNode *elementMatrice;
	tinyxml2::XMLElement *elementLignes;
	tinyxml2::XMLElement *elementColonnes;
	tinyxml2::XMLElement *elementNom;
	tinyxml2::XMLElement *elementValeur;
	tinyxml2::XMLDeclaration *declaration;
	wxFileDialog dialogueOuverture(this, _("Enregistrer dans un fichier XML : "), "", "","XML files (*.XML)|*.XML", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);; //On demande à l'utilisateur d'indiquer un fichier.
	
	if (dialogueOuverture.ShowModal() ==  wxID_CANCEL)
	{
		return; //Si l'utilisateur annule, on sort de la fonction
	}
	wxFileOutputStream sortie(dialogueOuverture.GetPath());
	if (!sortie.IsOk())
	{
		wxLogError("Impossible d'ouvrir le fichier. '%s'", dialogueOuverture.GetPath());
		return; //Si le fichier ne s'ouvre pas on sort de la fonction
	}
	
	declaration = fichier.NewDeclaration();
	fichier.InsertFirstChild(declaration); //on ajoute une déclaration au début du fichier (<?xml version="1.0" encoding="UTF-8"?>)
	racine = fichier.NewElement("variable");
	fichier.InsertEndChild(racine); //on ajoute ensuite le premier noeud (<variable></variable>)
	for(i=0; i<26; i++)
	{
		if (m_conteneurVariables.Existe(65+i)) //pour chaque matrice existante, on ajoute les données correspondantes :
		{
			elementMatrice = fichier.NewElement("matrice");
			racine->InsertEndChild(elementMatrice);
			
			elementNom = fichier.NewElement("nom");
			elementNom->SetText(65+i);
			elementMatrice->InsertEndChild(elementNom);
			
			elementLignes = fichier.NewElement("lignes");
			elementLignes->SetText(m_conteneurVariables.Variable(65+i).ObtenirLignes());
			elementMatrice->InsertEndChild(elementLignes);
			
			elementColonnes = fichier.NewElement("colonnes");
			elementColonnes->SetText(m_conteneurVariables.Variable(65+i).ObtenirLignes());
			elementMatrice->InsertEndChild(elementColonnes);
			
			//On utilise deux boucles pour ajouter toutes les valeurs de la matrice au fichier.
			for (j=0 ; j<m_conteneurVariables.Variable(65+i).ObtenirLignes(); j++)
			{
				for (k=0; k<m_conteneurVariables.Variable(65+i).ObtenirColonnes(); k++)
				{
					elementValeur = fichier.NewElement("valeur");
					elementValeur->SetText(m_conteneurVariables.Variable(65+i).ObtenirValeur(j,k));
					elementMatrice->InsertEndChild(elementValeur);
				}
			}
		}
	}
	fichier.SaveFile(dialogueOuverture.GetPath());
}

/**
 * Gère la fermeture du logiciel pendant laquelle on propose à l'utilisateur de sauvegarder ses matrices.
 */
void MainFrame::OnExit( wxCloseEvent& event )
{
	int confirmation;
	confirmation = wxMessageBox("Souhaitez vous enregistrer avant de quitter?", "Confirmation",wxYES_NO | wxCANCEL,this);
	if (confirmation == wxYES)
		Enregistrer();
	else if(confirmation == wxCANCEL)
	{	
		event.Veto();
		return;
	}
	
	Destroy();
}

void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxUnusedVar(event);
	
    wxAboutDialogInfo info;
    info.SetCopyright(_("Copyright © 2015 Antoine Girard Guittard <antoine.girard_guittard@utt.fr> & Victor Levasseur <victor.levasseur@utt.fr>"));
    info.SetLicence(_("WTFPL."));
    info.SetDescription(_("Logiciel de calcul matricel."));
    ::wxAboutBox(info);
}

/*
 * Lorsqu'un utilisateur clic sur le boutton enregistrer, cela déclenche la méthode enregistrer()
 */

void MainFrame::SurClicEnregistrer(wxRibbonButtonBarEvent& event)
{
	Enregistrer();
}

/*
 * Lorsqu'un utilisateur clic sur Ouvrir on charge un fichier XML contenant l'ensemble des variables.
 */

void MainFrame::SurClicOuvrir(wxRibbonButtonBarEvent& event)
{
	int confirmation;
	confirmation = wxMessageBox("Souhaitez vous enregistrer avant d'ouvrir un nouveau fichier?", "Confirmation",wxYES_NO | wxCANCEL,this); //On demande d'abord si l'utilisateur veut enregistrer son trabail en cours
	if (confirmation == wxYES)
	{
		Enregistrer(); 
	}
	else if (confirmation == wxCANCEL)
	{
		return;
	}
	
	tinyxml2::XMLDocument fichier;
	tinyxml2::XMLNode *racine;
	tinyxml2::XMLNode *noeudMatrice;
	tinyxml2::XMLElement* curseur;
	wxFileDialog dialogueOuverture(this, _("Ouvrez un fichier XML"), "", "","XML files (*.XML)|*.XML", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
	int lignes, colonnes, i,j;
	char nom;
	float valeur;
	
	
	if (dialogueOuverture.ShowModal() ==  wxID_CANCEL)
	{
		return;
	}
	wxFileInputStream entree(dialogueOuverture.GetPath());
	if (!entree.IsOk())
	{
		wxLogError("Impossible d'ouvrir le fichier. '%s'", dialogueOuverture.GetPath());
		return;
	}
	//Si le fichier s'est bien ouvert et l'utilisateur n'a pas enregistrer :
	
	fichier.LoadFile(dialogueOuverture.GetPath()); //on charge le fichier
	racine = fichier.FirstChild(); 
	racine = racine->NextSibling(); //On passe la déclaration
	for(noeudMatrice = racine->FirstChild(); noeudMatrice != NULL; noeudMatrice = noeudMatrice->NextSibling()) // Pour chaque <matrice></matrice>
	{
		curseur = noeudMatrice->FirstChildElement();
		nom = (char)atoi(curseur->GetText()); 
		curseur = curseur->NextSiblingElement();
		lignes = atoi(curseur->GetText());
		curseur = curseur->NextSiblingElement();
		colonnes = atoi(curseur->GetText());
		m_conteneurVariables.AjouterVariable(nom, lignes, colonnes); //On ajotue une matrice au conteneur avec le nom et le nombre de lignes/colonnes stocké dans le fichier.
		//On se sert de deux boucles pour inscrire toutes les valeurs dans le fichier :
		for(i=0; i<lignes;i++)
		{
			for(j=0;j<colonnes;j++)
			{
				curseur=curseur->NextSiblingElement();
				valeur = atof(curseur->GetText());
				m_conteneurVariables.Variable(nom).FixerValeur(i,j,valeur);
			}
		}
	}
	
	m_conteneurVariables.MAJGUI(m_arbreVariables); //Lorsque le fichier est fini on met à jour l'arbre.
}


void MainFrame::SurValidationCommande(wxCommandEvent& event)
{
	ExecuterCommande();
}

void MainFrame::SurClicExecuterCommande( wxRibbonButtonBarEvent& event )
{
	ExecuterCommande();
}

void MainFrame::SurClicEffacerResultats( wxRibbonButtonBarEvent& event )
{
	m_zoneResultats->SetValue("");
}

void MainFrame::SurChangementOngletRuban( wxRibbonBarEvent& event )
{
	if(m_ribbonBar1->GetActivePage() == 1)
	{
		//On remet immédiatement le 1er onglet
		m_ribbonBar1->SetActivePage((std::size_t)0);
		//Lancement de l'aide
		wxFileName exeFileName(wxStandardPaths::Get().GetExecutablePath());
		wxLaunchDefaultBrowser("file:///" + exeFileName.GetPath() + "/aide.html");
	}
}

/* 
 * La méthode SurClicAffichageVariables permet d'afficher/masquer le panneau contenant la liste des variables.
 */

void MainFrame::SurClicAffichageVariables( wxCommandEvent& event )
{
	m_mgr.GetPane("panneauVariables").Show(event.IsChecked());
	m_mgr.Update();
}

/*
 * Lorsqu'un utilisateur clique sur "Ajouter variable" on ouvre le dialogue d'ajoout d'une matrice.
 */

void MainFrame::SurClicAjouterVariable( wxRibbonButtonBarEvent& event)
{
	AjoutMatriceDialogue ajoutMatrice(this, &m_conteneurVariables);
	ajoutMatrice.ShowModal();
	
	m_conteneurVariables.MAJGUI(m_arbreVariables);
}

/*
 * Lorsqu'un utilisateur clique sur éditer une variable, on ouvre le dialogue permettant d'ajouter une variable en lui passant la variable existanteen argument.
 */

void MainFrame::SurClicEditerVariable( wxRibbonButtonBarEvent& event )
{
	if(m_arbreVariables->GetFocusedItem() == m_arbreVariables->GetRootItem())
		return;
		
	char nomVariableAEditer = m_arbreVariables->GetItemText(m_arbreVariables->GetFocusedItem())[0];
	AjoutMatriceDialogue modifierMatrice(this, &m_conteneurVariables, nomVariableAEditer);
	modifierMatrice.ShowModal();
}

/*
 * Si un utilisateur veut supprimer une variable, on demande confirmation et on supprime la variable sélectionné dans l'arbre.
 */

void MainFrame::SurClicSupprimerVariable( wxRibbonButtonBarEvent& event)
{
	if(wxMessageBox(L"Etes-vous sûr de vouloir supprimer la variable sélectionnée ?", "Confirmation", wxYES_NO, this) != wxYES)
		return;
	
	if(m_arbreVariables->GetFocusedItem() == m_arbreVariables->GetRootItem())
		return; //On quitte la focntion si il n'y a pas de variable sélectionnée.
	
	m_conteneurVariables.SupprimerVariable(m_arbreVariables->GetItemText(m_arbreVariables->GetFocusedItem())[0]);
	
	m_conteneurVariables.MAJGUI(m_arbreVariables);
}

/*
 * Un clic sur le boutton résoudre un système ouvre le dialogue approprié.
 */

void MainFrame::SurClicBouttonResoudreSysteme( wxRibbonButtonBarEvent& event)
{
	ResolutionSystemeDialogue systeme(this);
	systeme.ShowModal();
}

/*
 * La méthode SurClicViderVariables supprime toutes les matrices existantes dans le conteneur et met à jour l'arbre.
 */

void MainFrame::SurClicViderVariables( wxRibbonButtonBarEvent& event)
{
	int i, confirmation;
	
	confirmation = wxMessageBox("Souhaitez vous enregistrer avant d'effacer les variables?", "Confirmation",wxYES_NO | wxCANCEL,this);
	
	if (confirmation == wxYES)
	{
		Enregistrer();
	}
	else if(confirmation == wxCANCEL)
	{
		return;
	}
	
	for(i=65; i<91; i++)
	{
		if (m_conteneurVariables.Existe(i))
		{
			m_conteneurVariables.SupprimerVariable(i);
		}
	}
	m_conteneurVariables.MAJGUI(m_arbreVariables);
}