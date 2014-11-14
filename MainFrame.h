#ifndef MAINFRAME_H
#define MAINFRAME_H
#include "Dialogs.h"

#include "RibbonMetroArtProvider.h"
#include "Conteneur.h"

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
	virtual void SurClicAjouterVariable( wxCommandEvent& event);
	
protected:

	RibbonMetroArtProvider m_artProvider;
	Conteneur m_conteneurVariables;
	
};
#endif // MAINFRAME_H
