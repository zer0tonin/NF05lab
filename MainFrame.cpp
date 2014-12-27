#include "MainFrame.h"
#include <wx/aboutdlg.h>
#include <wx/msgdlg.h> 
#include <wx/log.h>
#include <wx/stdpaths.h>
#include <wx/utils.h>

#include <iostream>
#include "AjoutMatriceDialogue.h"
#include "Parseur.h"

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

void MainFrame::OnExit(wxCommandEvent& event)
{
    wxUnusedVar(event);
	
    Close();
}

void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxUnusedVar(event);
	
    wxAboutDialogInfo info;
    info.SetCopyright(_("My MainFrame"));
    info.SetLicence(_("GPL v2 or later"));
    info.SetDescription(_("Short description goes here"));
    ::wxAboutBox(info);
}

void MainFrame::SurValidationCommande(wxCommandEvent& event)
{
	wxString commande = m_zoneCommande->GetValue();
	m_arbreSyntaxe->DeleteAllItems();
	
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
