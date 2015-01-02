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
	
protected:

	void ExecuterCommande();
	void Enregistrer();
	
	virtual void SurClicEnregistrer(wxRibbonButtonBarEvent& event);
	virtual void SurClicOuvrir(wxRibbonButtonBarEvent& event);
	
	virtual void SurValidationCommande(wxCommandEvent& event);
	virtual void SurClicExecuterCommande( wxRibbonButtonBarEvent& event );
	virtual void SurClicEffacerResultats( wxRibbonButtonBarEvent& event );
	
	virtual void SurChangementOngletRuban( wxRibbonBarEvent& event );
	
	virtual void SurClicAffichageHistorique( wxCommandEvent& event );
	virtual void SurClicAffichageVariables( wxCommandEvent& event );
	virtual void SurClicAjouterVariable( wxRibbonButtonBarEvent& event);
	virtual void SurClicEditerVariable( wxRibbonButtonBarEvent& event );
	virtual void SurClicSupprimerVariable( wxRibbonButtonBarEvent& event);
	virtual void SurClicBouttonResoudreSysteme( wxRibbonButtonBarEvent& event);

	
	void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

	RibbonMetroArtProvider m_artProvider;
	Conteneur m_conteneurVariables;
	
};
#endif // MAINFRAME_H
