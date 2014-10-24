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
#include <wx/panel.h>
#include <wx/treectrl.h>
#include <wx/sizer.h>
#include <wx/frame.h>
#include <wx/aui/aui.h>

///////////////////////////////////////////////////////////////////////////


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
		wxRibbonPage* m_ribbonPage5;
		wxRibbonPage* m_ribbonPage3;
		wxRibbonPanel* m_ribbonPanel2;
		wxRibbonButtonBar* m_ribbonButtonBar2;
		wxRibbonPage* m_ribbonPage4;
		wxPanel* m_panneauPrincipal;
		wxPanel* m_panneauHistorique;
		wxTreeCtrl* m_treeCtrl3;
		wxPanel* m_panneauVariables;
		wxTreeCtrl* m_treeCtrl2;
		wxTreeCtrl* m_treeCtrl4;
	
	public:
		
		RibbonFrameBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("NF05Lab"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 900,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		wxAuiManager m_mgr;
		
		~RibbonFrameBase();
	
};

#endif //__DIALOGS_H__
