#include "MainFrame.h"
#include <wx/aboutdlg.h>
#include <wx/msgdlg.h> 

MainFrame::MainFrame(wxWindow* parent) : RibbonFrameBase(parent), m_artProvider(true)
{
	m_ribbonBar1->SetArtProvider(&m_artProvider);
	m_ribbonBar1->Realize();
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
