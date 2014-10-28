#include "MainFrame.h"
#include <wx/aboutdlg.h>
#include <wx/msgdlg.h> 
#include <wx/log.h>

#include <iostream>
#include "AnalyseurLexical.h"
#include "AnalyseurSyntaxique.h"
#include "Calculateur.h"

MainFrame::MainFrame(wxWindow* parent) : RibbonFrameBase(parent), m_artProvider(true), m_conteneurVariables()
{
	m_artProvider.SetColourScheme(wxColour(245, 245, 245),
								  wxColour(196, 203, 255),
								  wxColour(0, 0, 0));
	m_ribbonBar1->SetArtProvider(&m_artProvider);
	m_ribbonBar1->Realize();
	
	m_conteneurVariables.AjouterVariable('A', 2, 3);
	m_conteneurVariables.Variable('A').FixerValeur(1, 1, 1);
	m_conteneurVariables.Variable('A').FixerValeur(1, 2, 2);
	m_conteneurVariables.Variable('A').FixerValeur(2, 1, 3);
	m_conteneurVariables.Variable('A').FixerValeur(2, 2, 4);
	
	m_conteneurVariables.AjouterVariable('B', 4, 3);
	m_conteneurVariables.Variable('B').FixerValeur(1, 1, 1);
	m_conteneurVariables.Variable('B').FixerValeur(2, 2, 2);
	m_conteneurVariables.Variable('B').FixerValeur(3, 3, 3);
	m_conteneurVariables.Variable('B').FixerValeur(4, 2, 4);
	
	
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
	
	parseur::AnalyseurLexical lex;
	parseur::AnalyseurSyntaxique syn;
	parseur::Calculateur cal;
	
	std::vector<parseur::Lexeme> listeLexeme = lex.Parse(commande.ToStdString());
	if(lex.Erreur())
	{
		wxLogError(L"Symbole inconnu dans l'expression !");
		return;
	}
		
	if(syn.CreerArbreSyntaxique(listeLexeme))
		syn.AfficherContenu(m_arbreSyntaxe);
	else
	{
		wxLogError(L"Expression malformée !");
		return;
	}
	
	parseur::Resultat resultatCommande = cal.Calculer(syn.RecupererArbre(), m_conteneurVariables);
	
	if(resultatCommande.EstUnScalaire())
		m_zoneResultats->SetValue(m_zoneResultats->GetValue() + "\n" + m_zoneCommande->GetValue() + "\n --> " + wxString::FromDouble(resultatCommande.ValeurScalaire()));
	else if(resultatCommande.EstUneMatrice())
	{
		//Affichage de la matrice
		m_zoneResultats->SetValue(m_zoneResultats->GetValue() + "\n" + m_zoneCommande->GetValue() + "\n");
		for(int ligne = 1; ligne <= resultatCommande.ValeurMatrice().ObtenirLignes(); ligne++)
		{
			for(int colonne = 1; colonne <= resultatCommande.ValeurMatrice().ObtenirColonnes(); colonne++)
			{
				m_zoneResultats->SetValue(m_zoneResultats->GetValue() + wxString::FromDouble(resultatCommande.ValeurMatrice().ObtenirValeur(ligne, colonne)) + "\t");
			}
			m_zoneResultats->SetValue(m_zoneResultats->GetValue() + "\n");
		}
	}
	else if(resultatCommande.EstUneErreur())
		m_zoneResultats->SetValue(m_zoneResultats->GetValue() + "\n" + m_zoneCommande->GetValue() + "\n Erreur : " + resultatCommande.Erreur());
		
	m_arbreSyntaxe->ExpandAll();
	m_zoneCommande->SetValue("");
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
