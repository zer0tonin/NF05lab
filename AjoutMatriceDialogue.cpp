#include "AjoutMatriceDialogue.h"

AjoutMatriceDialogue::AjoutMatriceDialogue( wxWindow* parent, Conteneur* conteneur )
:
AjoutMatriceDialogueBase( parent ),
m_conteneur(conteneur)
{

}

void AjoutMatriceDialogue::SurClicValiderTailleMatrice( wxCommandEvent& event )
{
		m_tableauMatrice->DeleteCols(0, m_tableauMatrice->GetNumberCols());
		m_tableauMatrice->DeleteRows(0, m_tableauMatrice->GetNumberRows());
		m_tableauMatrice->AppendCols(m_colonnesSpin->GetValue());
		m_tableauMatrice->AppendRows(m_lignesSpin->GetValue());
}

void AjoutMatriceDialogue::SurClicSauver( wxCommandEvent& event )
{
	int i,j;
	double valeurCase = 0;
	m_conteneur->AjouterVariable((char)m_nomMatrice->GetCurrentSelection()+65, m_lignesSpin->GetValue(), m_colonnesSpin->GetValue());
	for (i=0 ; i<m_lignesSpin->GetValue() ; i++)
	{
		for (j=0 ; j<m_colonnesSpin->GetValue() ; j++)
		{
			if (m_tableauMatrice->GetCellValue(i, j ).ToDouble(&valeurCase))
			{
				m_conteneur->Variable((char)m_nomMatrice->GetCurrentSelection()+65).FixerValeur(i, j, valeurCase);
			}
		}
	}
	EndModal(0);
}