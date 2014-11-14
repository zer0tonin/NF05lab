#include "AjoutMatriceDialogue.h"

AjoutMatriceDialogue::AjoutMatriceDialogue( wxWindow* parent )
:
AjoutMatriceDialogueBase( parent )
{

}

void AjoutMatriceDialogue::SurClicValiderTailleMatrice( wxCommandEvent& event )
{
	m_tableauMatrice->CreateGrid(m_lignesSpin->GetValue(), m_colonnesSpin->GetValue());
}