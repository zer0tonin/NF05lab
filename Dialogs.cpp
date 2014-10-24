///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "Dialogs.h"

#include "res/appbar.add.png.h"
#include "res/appbar.delete.png.h"
#include "res/appbar.edit.png.h"

///////////////////////////////////////////////////////////////////////////

RibbonFrameBase::RibbonFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	m_mgr.SetManagedWindow(this);
	m_mgr.SetFlags(wxAUI_MGR_DEFAULT);
	
	m_ribbonBar1 = new wxRibbonBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxRIBBON_BAR_DEFAULT_STYLE );
	m_ribbonBar1->SetArtProvider(new wxRibbonDefaultArtProvider); 
	m_mgr.AddPane( m_ribbonBar1, wxAuiPaneInfo() .Top() .CaptionVisible( false ).CloseButton( false ).PaneBorder( false ).Movable( false ).Dock().Fixed().DockFixed( false ).BottomDockable( false ).LeftDockable( false ).RightDockable( false ).Floatable( false ).BestSize( wxSize( -1,160 ) ).MinSize( wxSize( -1,160 ) ).Layer( 1000 ) );
	
	m_ribbonPage1 = new wxRibbonPage( m_ribbonBar1, wxID_ANY, wxT("Fichiers") , wxNullBitmap , 0 );
	m_ribbonPage2 = new wxRibbonPage( m_ribbonBar1, wxID_ANY, wxT("Affichage") , wxNullBitmap , 0 );
	m_ribbonPage5 = new wxRibbonPage( m_ribbonBar1, wxID_ANY, wxT("Commandes") , wxNullBitmap , 0 );
	m_ribbonPage3 = new wxRibbonPage( m_ribbonBar1, wxID_ANY, wxT("Variable") , wxNullBitmap , 0 );
	m_ribbonBar1->SetActivePage( m_ribbonPage3 ); 
	m_ribbonPanel2 = new wxRibbonPanel( m_ribbonPage3, wxID_ANY, wxT("Gestion des variables") , wxNullBitmap , wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE );
	m_ribbonButtonBar2 = new wxRibbonButtonBar( m_ribbonPanel2, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_ribbonButtonBar2->AddButton( wxID_ANY, wxT("Ajouter..."), appbar_add_png_to_wx_bitmap(), wxEmptyString);
	m_ribbonButtonBar2->AddButton( wxID_ANY, wxT("Editer..."), appbar_edit_png_to_wx_bitmap(), wxEmptyString);
	m_ribbonButtonBar2->AddButton( wxID_ANY, wxT("Supprimer"), appbar_delete_png_to_wx_bitmap(), wxEmptyString);
	m_ribbonPage4 = new wxRibbonPage( m_ribbonBar1, wxID_ANY, wxT("Historique") , wxNullBitmap , 0 );
	m_ribbonBar1->Realize();
	
	m_panneauPrincipal = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_mgr.AddPane( m_panneauPrincipal, wxAuiPaneInfo() .Center() .CaptionVisible( false ).CloseButton( false ).PaneBorder( false ).Movable( false ).Dock().Resizable().FloatingSize( wxDefaultSize ).DockFixed( false ).BottomDockable( false ).TopDockable( false ).LeftDockable( false ).RightDockable( false ).Floatable( false ) );
	
	m_panneauHistorique = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_mgr.AddPane( m_panneauHistorique, wxAuiPaneInfo() .Left() .Caption( wxT("Historique des commandes") ).PinButton( true ).Dock().Resizable().FloatingSize( wxDefaultSize ).DockFixed( false ).BestSize( wxSize( 200,100 ) ).MinSize( wxSize( 200,100 ) ) );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer2->AddGrowableCol( 0 );
	fgSizer2->AddGrowableRow( 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_treeCtrl3 = new wxTreeCtrl( m_panneauHistorique, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE );
	fgSizer2->Add( m_treeCtrl3, 0, wxALL|wxEXPAND, 0 );
	
	
	m_panneauHistorique->SetSizer( fgSizer2 );
	m_panneauHistorique->Layout();
	fgSizer2->Fit( m_panneauHistorique );
	m_panneauVariables = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_mgr.AddPane( m_panneauVariables, wxAuiPaneInfo() .Left() .Caption( wxT("Variables") ).PinButton( true ).Dock().Resizable().FloatingSize( wxSize( 400,250 ) ).DockFixed( false ).BestSize( wxSize( 200,100 ) ).MinSize( wxSize( 200,100 ) ) );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer1->AddGrowableCol( 0 );
	fgSizer1->AddGrowableRow( 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_treeCtrl2 = new wxTreeCtrl( m_panneauVariables, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE );
	fgSizer1->Add( m_treeCtrl2, 0, wxALL|wxEXPAND, 0 );
	
	
	m_panneauVariables->SetSizer( fgSizer1 );
	m_panneauVariables->Layout();
	fgSizer1->Fit( m_panneauVariables );
	m_treeCtrl4 = new wxTreeCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE );
	m_mgr.AddPane( m_treeCtrl4, wxAuiPaneInfo() .Right() .PinButton( true ).Dock().Resizable().FloatingSize( wxDefaultSize ).DockFixed( false ).BestSize( wxSize( 200,-1 ) ).MinSize( wxSize( 200,-1 ) ) );
	
	
	m_mgr.Update();
	this->Centre( wxBOTH );
}

RibbonFrameBase::~RibbonFrameBase()
{
	m_mgr.UnInit();
	
}
