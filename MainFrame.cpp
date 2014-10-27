#include "MainFrame.h"
#include <wx/aboutdlg.h>
#include <wx/msgdlg.h> 
#include <wx/log.h>

#include <iostream>
#include "AnalyseurLexical.h"
#include "AnalyseurSyntaxique.h"
#include "Calculateur.h"

MainFrame::MainFrame(wxWindow* parent) : RibbonFrameBase(parent), m_artProvider(true)
{
	m_artProvider.SetColourScheme(wxColour(245, 245, 245),
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
	
	parseur::Resultat resultatCommande = cal.Calculer(syn.RecupererArbre());
	
	if(resultatCommande.EstUnScalaire())
		m_zoneResultats->SetValue(m_zoneResultats->GetValue() + "\n" + m_zoneCommande->GetValue() + "\n --> " + wxString::FromDouble(resultatCommande.ValeurScalaire()));
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
