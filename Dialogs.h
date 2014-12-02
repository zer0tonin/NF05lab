///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __DIALOGS_H__
#define __DIALOGS_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/ribbon/page.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/ribbon/buttonbar.h>
#include <wx/ribbon/panel.h>
#include <wx/ribbon/control.h>
#include <wx/ribbon/art.h>
#include <wx/ribbon/bar.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/treectrl.h>
#include <wx/frame.h>
#include <wx/aui/aui.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/spinctrl.h>
#include <wx/button.h>
#include <wx/grid.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

#define BOUTON_AFFICHAGE_HISTORIQUE 1000
#define BOUTON_AFFICHAGE_VARIABLES 1001
#define AJOUTER_VARIABLE_BOUTON_ID 1002
#define SUPPRIMER_VARIABLE_BOUTON_ID 1003
#define VALIDER_TAILLE_MATRICE_ID 1004

///////////////////////////////////////////////////////////////////////////////
/// Class RibbonFrameBase
///////////////////////////////////////////////////////////////////////////////
class RibbonFrameBase : public wxFrame 
{
	private:
	
	protected:
		wxRibbonBar* m_ribbonBar1;
		wxRibbonPage* m_ribbonPage1;
		wxRibbonPage* m_ribbonPage2;
		wxRibbonPanel* m_ribbonPanel6;
		wxRibbonButtonBar* m_barreBoutonsAffichage;
		wxRibbonPage* m_ribbonPage5;
		wxRibbonPanel* m_ribbonPanel3;
		wxRibbonButtonBar* m_ribbonButtonBar3;
		wxRibbonPage* m_ribbonPage3;
		wxRibbonPanel* m_ribbonPanel2;
		wxRibbonButtonBar* m_ribbonButtonBar2;
		wxRibbonPanel* m_ribbonPanel21;
		wxRibbonButtonBar* m_ribbonButtonBar21;
		wxPanel* m_panneauPrincipal;
		wxTextCtrl* m_zoneResultats;
		wxTextCtrl* m_zoneCommande;
		wxPanel* m_panneauHistorique;
		wxTreeCtrl* m_treeCtrl3;
		wxPanel* m_panneauVariables;
		wxTreeCtrl* m_arbreVariables;
		wxTreeCtrl* m_arbreSyntaxe;
		
		// Virtual event handlers, overide them in your derived class
		virtual void SurClicAffichageHistorique( wxCommandEvent& event ) { event.Skip(); }
		virtual void SurClicAffichageVariables( wxCommandEvent& event ) { event.Skip(); }
		virtual void SurClicAjouterVariable( wxRibbonButtonBarEvent& event ) { event.Skip(); }
		virtual void SurClicSupprimerVariable( wxRibbonButtonBarEvent& event ) { event.Skip(); }
		virtual void SurValidationCommande( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		RibbonFrameBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("NF05Lab"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 900,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		wxAuiManager m_mgr;
		
		~RibbonFrameBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class AjoutMatriceDialogueBase
///////////////////////////////////////////////////////////////////////////////
class AjoutMatriceDialogueBase : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText2;
		wxChoice* m_nomMatrice;
		wxSpinCtrl* m_lignesSpin;
		wxSpinCtrl* m_colonnesSpin;
		wxButton* BoutonValider;
		wxGrid* m_tableauMatrice;
		wxStdDialogButtonSizer* m_sdbSizer1;
		wxButton* m_sdbSizer1Save;
		wxButton* m_sdbSizer1Cancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void SurClicValiderTailleMatrice( wxCommandEvent& event ) { event.Skip(); }
		virtual void SurClicAnnuler( wxCommandEvent& event ) { event.Skip(); }
		virtual void SurClicSauver( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		AjoutMatriceDialogueBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,312 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~AjoutMatriceDialogueBase();
	
};

#endif //__DIALOGS_H__
