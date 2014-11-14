#include "AjoutMatriceDialogue.h"

AjoutMatriceDialogue::AjoutMatriceDialogue( wxWindow* parent )
:
AjoutMatriceDialogueBase( parent )
{

}

void AjoutMatriceDialogue::SurClicValiderTailleMatrice( wxCommandEvent& event )
{
		m_tableauMatrice->DeleteCols(0, m_tableauMatrice->GetNumberCols());
		m_tableauMatrice->DeleteRows(0, m_tableauMatrice->GetNumberRows());
		m_tableauMatrice->AppendCols(m_colonnesSpin->GetValue());
		m_tableauMatrice->AppendRows(m_lignesSpin->GetValue());
}