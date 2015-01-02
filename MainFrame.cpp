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
	
	m_barreBoutonsAffichage->ToggleButton(BOUTON_AFFICHAGE_HISTORIQUE, true);
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
	wxFileDialog dialogueOuverture(this, _("Enregistrer dans un fichier XML : "), "", "","XML files (*.XML)|*.XML", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);;
	
	if (dialogueOuverture.ShowModal() ==  wxID_CANCEL)
	{
		return;
	}
	wxFileOutputStream sortie(dialogueOuverture.GetPath());
	if (!sortie.IsOk())
	{
		wxLogError("Impossible d'ouvrir le fichier. '%s'", dialogueOuverture.GetPath());
		return;
	}
	
	fichier.NewDeclaration();
	racine = fichier.NewElement("variable");
	fichier.InsertFirstChild(racine);
	for(i=0; i<26; i++)
	{
		if (m_conteneurVariables.Existe(65+i))
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

void MainFrame::OnExit(wxCommandEvent& event)
{
    wxUnusedVar(event);
	int confirmation;
	confirmation = wxMessageBox("Souhiatez vous enregistrer avant de quitter?", "Confirmation",wxYES_NO | wxCANCEL,this);
	if (confirmation == wxYES)
	{
		Enregistrer();
	}
	else if (confirmation == wxNO)
	{
		Close();
	}
	else
	{
		return;
	}
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

void MainFrame::SurClicEnregistrer(wxRibbonButtonBarEvent& event)
{
	Enregistrer();
}

void MainFrame::SurClicOuvrir(wxRibbonButtonBarEvent& event)
{
	int confirmation;
	confirmation = wxMessageBox("Souhiatez vous enregistrer avant d'ouvrir un nouveau fichier?", "Confirmation",wxYES_NO | wxCANCEL,this);
	if (confirmation == wxYES)
	{
		Enregistrer();
		return;
	}
	else if (confirmation == wxCANCEL)
	{
		return;
	}
	
	tinyxml2::XMLDocument fichier;
	tinyxml2::XMLNode *racine;
	tinyxml2::XMLNode *noeudMatrice;
	tinyxml2::XMLNode *noeudLignes;
	tinyxml2::XMLElement *elementLignes;
	tinyxml2::XMLNode *noeudColonnes;
	tinyxml2::XMLElement *elementColonnes;
	tinyxml2::XMLNode *noeudNom;
	tinyxml2::XMLElement *elementNom;
	tinyxml2::XMLNode *noeudValeur;
	tinyxml2::XMLElement *elementValeur;
	wxFileDialog dialogueOuverture(this, _("Ouvrez un fichier XML"), "", "","XML files (*.XML)|*.XML", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
	int lignes, colonnes, i, j, k;
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
	
	fichier.LoadFile(dialogueOuverture.GetPath());
	racine = fichier.FirstChild();
	noeudMatrice = racine->FirstChild();
	for (i=65;i<91;i++)
	{
		noeudNom = noeudMatrice->FirstChild(); //SIGSEGV
		elementNom = noeudNom->ToElement();
		if (atoi(elementNom->GetText()) == i)
		{
			noeudLignes = noeudNom->NextSibling();
			elementLignes = noeudLignes->ToElement();
			lignes = atoi(elementLignes->GetText());
			noeudColonnes = noeudLignes->NextSibling();
			elementColonnes = noeudColonnes->ToElement();
			colonnes = atoi(elementColonnes->GetText());
			
			m_conteneurVariables.AjouterVariable(i, lignes, colonnes);
			noeudValeur = noeudColonnes->NextSibling();
			for (j=0; j<lignes; j++)
			{
				for (k=0; k<colonnes; k++)
				{
					elementValeur = noeudValeur->ToElement();
					valeur = atof(elementValeur->GetText());
					m_conteneurVariables.Variable(i).FixerValeur(j, k, valeur);
					noeudValeur = noeudValeur->NextSibling();
				}
			}
		}
		noeudMatrice = noeudMatrice->NextSibling();
	}
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

void MainFrame::SurClicAffichageHistorique( wxCommandEvent& event )
{
	m_mgr.GetPane("panneauHistorique").Show(event.IsChecked());
	m_mgr.Update();
}

void MainFrame::SurClicAffichageVariables( wxCommandEvent& event )
{
	m_mgr.GetPane("panneauVariables").Show(event.IsChecked());
	m_mgr.Update();
}

void MainFrame::SurClicAjouterVariable( wxRibbonButtonBarEvent& event)
{
	AjoutMatriceDialogue ajoutMatrice(this, &m_conteneurVariables);
	ajoutMatrice.ShowModal();
	
	m_conteneurVariables.MAJGUI(m_arbreVariables);
}

void MainFrame::SurClicEditerVariable( wxRibbonButtonBarEvent& event )
{
	if(m_arbreVariables->GetFocusedItem() == m_arbreVariables->GetRootItem())
		return;
		
	char nomVariableAEditer = m_arbreVariables->GetItemText(m_arbreVariables->GetFocusedItem())[0];
	AjoutMatriceDialogue modifierMatrice(this, &m_conteneurVariables, nomVariableAEditer);
	modifierMatrice.ShowModal();
}

void MainFrame::SurClicSupprimerVariable( wxRibbonButtonBarEvent& event)
{
	if(wxMessageBox(L"Etes-vous sûr de vouloir supprimer la variable sélectionnée ?", "Confirmation", wxYES_NO, this) != wxYES)
		return;
	
	if(m_arbreVariables->GetFocusedItem() == m_arbreVariables->GetRootItem())
		return;
	
	m_conteneurVariables.SupprimerVariable(m_arbreVariables->GetItemText(m_arbreVariables->GetFocusedItem())[0]);
	
	m_conteneurVariables.MAJGUI(m_arbreVariables);
}

void MainFrame::SurClicBouttonResoudreSysteme( wxRibbonButtonBarEvent& event)
{
	ResolutionSystemeDialogue systeme(this);
	systeme.ShowModal();
}