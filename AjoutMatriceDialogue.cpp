#include "AjoutMatriceDialogue.h"
#include <wx/msgdlg.h> 

AjoutMatriceDialogue::AjoutMatriceDialogue( wxWindow* parent )
:
AjoutMatriceDialogueBase( parent )
{

}

void AjoutMatriceDialogue::SurClicValiderTailleMatrice( wxCommandEvent& event )
{
	wxMessageBox("test");
	m_tableauMatrice->CreateGrid(m_lignesSpin->GetValue(), m_colonnesSpin->GetValue());
}