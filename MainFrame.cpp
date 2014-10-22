#include "MainFrame.h"
#include <wx/aboutdlg.h>
#include <wx/msgdlg.h> 

MainFrame::MainFrame(wxWindow* parent)
    : MainFrameBaseClass(parent)
{
	m_auibar15->Realize();
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

void MainFrame::CalculDeterminant(wxCommandEvent& event)
{
	wxMessageBox("Calcul du déterminant", "Boite de dialogue");
}
