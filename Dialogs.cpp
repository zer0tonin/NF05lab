///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "Dialogs.h"

///////////////////////////////////////////////////////////////////////////

RibbonFrameBase::RibbonFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	m_mgr.SetManagedWindow(this);
	m_mgr.SetFlags(wxAUI_MGR_DEFAULT);
	
	m_ribbonBar1 = new wxRibbonBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxRIBBON_BAR_DEFAULT_STYLE );
	m_ribbonBar1->SetArtProvider(new wxRibbonDefaultArtProvider); 
	m_mgr.AddPane( m_ribbonBar1, wxAuiPaneInfo() .Top() .CaptionVisible( false ).CloseButton( false ).PaneBorder( false ).Movable( false ).Dock().Fixed().DockFixed( false ).BottomDockable( false ).LeftDockable( false ).RightDockable( false ).Floatable( false ).BestSize( wxSize( -1,150 ) ).MinSize( wxSize( -1,150 ) ).Layer( 1000 ) );
	
	m_ribbonPage1 = new wxRibbonPage( m_ribbonBar1, wxID_ANY, wxT("MyRibbonPage") , wxNullBitmap , 0 );
	m_ribbonBar1->SetActivePage( m_ribbonPage1 ); 
	m_ribbonPanel1 = new wxRibbonPanel( m_ribbonPage1, wxID_ANY, wxT("MyRibbonPanel") , wxNullBitmap , wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE );
	m_ribbonButtonBar1 = new wxRibbonButtonBar( m_ribbonPanel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_ribbonButtonBar1->AddButton( wxID_ANY, wxT("MyRibbonButton"), wxNullBitmap, wxEmptyString);
	m_ribbonButtonBar1->AddButton( wxID_ANY, wxT("MyRibbonButton"), wxNullBitmap, wxEmptyString);
	m_ribbonButtonBar1->AddButton( wxID_ANY, wxT("MyRibbonButton"), wxNullBitmap, wxEmptyString);
	m_ribbonButtonBar1->AddHybridButton( wxID_ANY, wxT("MyRibbonHybridButton"), wxNullBitmap, wxEmptyString);
	m_ribbonPage2 = new wxRibbonPage( m_ribbonBar1, wxID_ANY, wxT("MyRibbonPage") , wxNullBitmap , 0 );
	m_ribbonBar1->Realize();
	
	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_mgr.AddPane( m_panel1, wxAuiPaneInfo() .Center() .CaptionVisible( false ).CloseButton( false ).PaneBorder( false ).Movable( false ).Dock().Resizable().FloatingSize( wxDefaultSize ).DockFixed( false ).BottomDockable( false ).TopDockable( false ).LeftDockable( false ).RightDockable( false ).Floatable( false ) );
	
	
	m_mgr.Update();
	this->Centre( wxBOTH );
}

RibbonFrameBase::~RibbonFrameBase()
{
	m_mgr.UnInit();
	
}
