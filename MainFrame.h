#ifndef MAINFRAME_H
#define MAINFRAME_H
#include "Dialogs.h"

#include "RibbonMetroArtProvider.h"

class MainFrame : public RibbonFrameBase
{
public:
    MainFrame(wxWindow* parent);
    virtual ~MainFrame();

    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
	
	virtual void SurValidationCommande(wxCommandEvent& event);
	
	virtual void SurClicAffichageHistorique( wxCommandEvent& event );
	virtual void SurClicAffichageVariables( wxCommandEvent& event );
protected:

	RibbonMetroArtProvider m_artProvider;
	
};
#endif // MAINFRAME_H
