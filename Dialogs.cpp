///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "Dialogs.h"

#include "res/advanced.png.h"
#include "res/edit.png.h"
#include "res/edit_add.png.h"
#include "res/editclear.png.h"
#include "res/editdelete.png.h"
#include "res/edittrash.png.h"
#include "res/month.png.h"
#include "res/toggle_log.png.h"

///////////////////////////////////////////////////////////////////////////

RibbonFrameBase::RibbonFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	m_mgr.SetManagedWindow(this);
	m_mgr.SetFlags(wxAUI_MGR_DEFAULT);
	
	m_ribbonBar1 = new wxRibbonBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxRIBBON_BAR_DEFAULT_STYLE );
	m_ribbonBar1->SetArtProvider(new wxRibbonDefaultArtProvider); 
	m_mgr.AddPane( m_ribbonBar1, wxAuiPaneInfo() .Top() .CaptionVisible( false ).CloseButton( false ).PaneBorder( false ).Movable( false ).Dock().Fixed().DockFixed( false ).BottomDockable( false ).LeftDockable( false ).RightDockable( false ).Floatable( false ).BestSize( wxSize( -1,130 ) ).MinSize( wxSize( -1,130 ) ).Layer( 1000 ) );
	
	m_ribbonPage1 = new wxRibbonPage( m_ribbonBar1, wxID_ANY, wxT("Fichiers") , wxNullBitmap , 0 );
	m_ribbonBar1->SetActivePage( m_ribbonPage1 ); 
	m_ribbonPage2 = new wxRibbonPage( m_ribbonBar1, wxID_ANY, wxT("Affichage") , wxNullBitmap , 0 );
	m_ribbonPanel6 = new wxRibbonPanel( m_ribbonPage2, wxID_ANY, wxT("Fenêtres") , wxNullBitmap , wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE );
	m_barreBoutonsAffichage = new wxRibbonButtonBar( m_ribbonPanel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_barreBoutonsAffichage->AddToggleButton( BOUTON_AFFICHAGE_HISTORIQUE, wxT("Afficher l'historique des commandes"), toggle_log_png_to_wx_bitmap(), wxEmptyString);
	m_barreBoutonsAffichage->AddToggleButton( BOUTON_AFFICHAGE_VARIABLES, wxT("Afficher la liste des variables"), month_png_to_wx_bitmap(), wxEmptyString);
	m_ribbonPage5 = new wxRibbonPage( m_ribbonBar1, wxID_ANY, wxT("Commandes") , wxNullBitmap , 0 );
	m_ribbonPanel3 = new wxRibbonPanel( m_ribbonPage5, wxID_ANY, wxT("Exécution") , wxNullBitmap , wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE );
	m_ribbonButtonBar3 = new wxRibbonButtonBar( m_ribbonPanel3, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_ribbonButtonBar3->AddButton( wxID_ANY, wxT("Exécuter la commande"), advanced_png_to_wx_bitmap(), wxEmptyString);
	m_ribbonButtonBar3->AddButton( wxID_ANY, wxT("Effacer les résultats"), editclear_png_to_wx_bitmap(), wxEmptyString);
	m_ribbonPage3 = new wxRibbonPage( m_ribbonBar1, wxID_ANY, wxT("Variables et historique") , wxNullBitmap , 0 );
	m_ribbonPanel2 = new wxRibbonPanel( m_ribbonPage3, wxID_ANY, wxT("Gestion des variables") , wxNullBitmap , wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE );
	m_ribbonButtonBar2 = new wxRibbonButtonBar( m_ribbonPanel2, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_ribbonButtonBar2->AddButton( wxID_ANY, wxT("Ajouter..."), edit_add_png_to_wx_bitmap(), wxEmptyString);
	m_ribbonButtonBar2->AddButton( wxID_ANY, wxT("Editer..."), edit_png_to_wx_bitmap(), wxEmptyString);
	m_ribbonButtonBar2->AddButton( wxID_ANY, wxT("Supprimer"), editdelete_png_to_wx_bitmap(), wxEmptyString);
	m_ribbonButtonBar2->AddButton( wxID_ANY, wxT("Supprimer toutes les variables"), edittrash_png_to_wx_bitmap(), wxEmptyString);
	m_ribbonPanel21 = new wxRibbonPanel( m_ribbonPage3, wxID_ANY, wxT("Historique") , wxNullBitmap , wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE );
	m_ribbonButtonBar21 = new wxRibbonButtonBar( m_ribbonPanel21, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_ribbonButtonBar21->AddButton( wxID_ANY, wxT("Vider l'historique"), edittrash_png_to_wx_bitmap(), wxEmptyString);
	m_ribbonBar1->Realize();
	
	m_panneauPrincipal = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_mgr.AddPane( m_panneauPrincipal, wxAuiPaneInfo() .Center() .CaptionVisible( false ).CloseButton( false ).PaneBorder( false ).Movable( false ).Dock().Resizable().FloatingSize( wxDefaultSize ).DockFixed( false ).BottomDockable( false ).TopDockable( false ).LeftDockable( false ).RightDockable( false ).Floatable( false ) );
	
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer3->AddGrowableCol( 0 );
	fgSizer3->AddGrowableRow( 0 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_zoneResultats = new wxTextCtrl( m_panneauPrincipal, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	m_zoneResultats->SetFont( wxFont( 12, 75, 90, 90, false, wxT("Consolas") ) );
	
	fgSizer3->Add( m_zoneResultats, 0, wxALL|wxEXPAND, 5 );
	
	m_zoneCommande = new wxTextCtrl( m_panneauPrincipal, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_zoneCommande->SetFont( wxFont( 12, 75, 90, 90, false, wxT("Consolas") ) );
	
	fgSizer3->Add( m_zoneCommande, 0, wxALL|wxEXPAND, 5 );
	
	
	m_panneauPrincipal->SetSizer( fgSizer3 );
	m_panneauPrincipal->Layout();
	fgSizer3->Fit( m_panneauPrincipal );
	m_panneauHistorique = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_mgr.AddPane( m_panneauHistorique, wxAuiPaneInfo() .Name( wxT("panneauHistorique") ).Left() .Caption( wxT("Historique des commandes") ).PinButton( true ).Dock().Resizable().FloatingSize( wxDefaultSize ).DockFixed( false ).BestSize( wxSize( 200,100 ) ).MinSize( wxSize( 200,100 ) ) );
	
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
	m_mgr.AddPane( m_panneauVariables, wxAuiPaneInfo() .Name( wxT("panneauVariables") ).Left() .Caption( wxT("Variables") ).PinButton( true ).Dock().Resizable().FloatingSize( wxSize( 400,250 ) ).DockFixed( false ).BestSize( wxSize( 200,100 ) ).MinSize( wxSize( 200,100 ) ) );
	
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
	m_arbreSyntaxe = new wxTreeCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE );
	m_mgr.AddPane( m_arbreSyntaxe, wxAuiPaneInfo() .Right() .Caption( wxT("Arbre syntaxique") ).PinButton( true ).Dock().Resizable().FloatingSize( wxDefaultSize ).DockFixed( false ).BestSize( wxSize( 200,-1 ) ).MinSize( wxSize( 200,-1 ) ) );
	
	
	m_mgr.Update();
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( BOUTON_AFFICHAGE_HISTORIQUE, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxCommandEventHandler( RibbonFrameBase::SurClicAffichageHistorique ) );
	this->Connect( BOUTON_AFFICHAGE_VARIABLES, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxCommandEventHandler( RibbonFrameBase::SurClicAffichageVariables ) );
	m_zoneCommande->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( RibbonFrameBase::SurValidationCommande ), NULL, this );
}

RibbonFrameBase::~RibbonFrameBase()
{
	// Disconnect Events
	this->Disconnect( BOUTON_AFFICHAGE_HISTORIQUE, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxCommandEventHandler( RibbonFrameBase::SurClicAffichageHistorique ) );
	this->Disconnect( BOUTON_AFFICHAGE_VARIABLES, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxCommandEventHandler( RibbonFrameBase::SurClicAffichageVariables ) );
	m_zoneCommande->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( RibbonFrameBase::SurValidationCommande ), NULL, this );
	
	m_mgr.UnInit();
	
}
