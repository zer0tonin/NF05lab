#include "MainFrame.h"
#include <wx/aboutdlg.h>
#include <wx/msgdlg.h> 

#include <iostream>
#include "AnalyseurLexical.h"
#include "AnalyseurSyntaxique.h"

MainFrame::MainFrame(wxWindow* parent) : RibbonFrameBase(parent), m_artProvider(true)
{
	m_ribbonBar1->SetArtProvider(&m_artProvider);
	m_ribbonBar1->Realize();
	
	std::cout << "Va parser..." << std::endl;
	parseur::AnalyseurLexical lex;
	parseur::AnalyseurSyntaxique syn;
	if(syn.CreerArbreSyntaxique(lex.Parse("((A+E)*3+B/2)*C+D")))
		syn.AfficherContenu();
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
