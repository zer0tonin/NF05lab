#include "MainFrame.h"
#include <wx/aboutdlg.h>
#include <wx/msgdlg.h> 
#include <wx/log.h>

#include <iostream>
<<<<<<< HEAD
#include "AnalyseurLexical.h"
#include "AnalyseurSyntaxique.h"
#include "Calculateur.h"
#include "AjoutMatriceDialogue.h"
=======
#include "Parseur.h"
>>>>>>> d7d5ac8e111d72533c0a3cab3fe37367db431f89

MainFrame::MainFrame(wxWindow* parent) : RibbonFrameBase(parent), m_artProvider(true), m_conteneurVariables()
{
	m_artProvider.SetColourScheme(wxColour(245, 245, 245),
								  wxColour(196, 203, 255),
								  wxColour(0, 0, 0));
	m_ribbonBar1->SetArtProvider(&m_artProvider);
	m_ribbonBar1->Realize();
	
	m_conteneurVariables.AjouterVariable('A', 2, 3);
	m_conteneurVariables.Variable('A').FixerValeur(0, 0, 1);
	m_conteneurVariables.Variable('A').FixerValeur(0, 1, 2);
	m_conteneurVariables.Variable('A').FixerValeur(1, 0, 3);
	m_conteneurVariables.Variable('A').FixerValeur(1, 1, 4);
	
	m_conteneurVariables.AjouterVariable('B', 3, 4);
	m_conteneurVariables.Variable('B').FixerValeur(0, 0, 1);
	m_conteneurVariables.Variable('B').FixerValeur(1, 1, 2);
	m_conteneurVariables.Variable('B').FixerValeur(2, 2, 3);
	m_conteneurVariables.Variable('B').FixerValeur(1, 2, 4);
	
	
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
		m_zoneResultats->SetValue(m_zoneResultats->GetValue() + "\n" + m_zoneCommande->GetValue() + "\n Erreur : " + e.what());
	}
		
	m_arbreSyntaxe->ExpandAll();
	m_zoneCommande->SetValue("");
	
	//Mise à jour de l'arbre qui liste les variables
	m_conteneurVariables.MAJGUI(m_arbreVariables);
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

void MainFrame::SurClicAjouterVariable( wxCommandEvent& event)
{
	AjoutMatriceDialogue AjoutMatrice(this);
	AjoutMatrice.ShowModal();
}
