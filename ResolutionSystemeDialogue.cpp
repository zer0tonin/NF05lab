#include "ResolutionSystemeDialogue.h"

ResolutionSystemeDialogue::ResolutionSystemeDialogue( wxWindow* parent)
:
ResolutionSystemeDialogue( parent )
{

}

void ResolutionSystemeDialogue::SurClicBoutonValiderSysteme(wxCommandEvent& event)
{
	//On compare la nouvelle taille souhaitée à la taille actuelle du tableau
	int nombreEquations = m_equationsSpin->GetValue();
	
	//Si il y a trop de lignes/colonnes, on en retire suffisamment
	if(nombreEquations > 0)
	{
		m_tableauMatriceSysteme->AppendRows(nombreEquations);
		m_tableauMatriceSysteme->AppendCols(nombreEquations);
		m_tableauVecteurSysteme->AppendRows(1);
		m_tableauVecteurSysteme->AppendRows(nombreEquations);
	}
}

void ResolutionSystemeDialogue::SurCLicBouttonResoudre(wxCommandEvent& event)
{
	int nombreEquations = m_equationsSpin->GetValue(), i ,j;
	double valeurCellule;
	
	for (i=0; i<nombreEquations; i++)
	{
		for (j=0; j<nombreEquations; j++)
		{
			m_tableauMatriceSysteme->GetCellValue(i,j).ToDouble(&valeurCellule);
			Application.FixerValeur(i,j, (float)valeurCellule);
		}
		m_tableauVecteurSysteme->GetCellValue(i,j).ToDouble(&valeurCellule);
		Vecteur.FixerValeur(i,j, (float)valeurCellule);
	}
	
	Solution = Application.Inverse() * Vecteur;
	Solution.AfficherMatrice();
}