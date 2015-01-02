#include "ResolutionSystemeDialogue.h"

ResolutionSystemeDialogue::ResolutionSystemeDialogue( wxWindow* parent)
:
ResolutionSystemeDialogueBase( parent )
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
		m_tableauVecteurSysteme->AppendCols(1);
		m_tableauVecteurSysteme->AppendRows(nombreEquations);
	}
}

void ResolutionSystemeDialogue::SurCLicBouttonResoudre(wxCommandEvent& event)
{
	int nombreEquations = m_equationsSpin->GetValue(), i ,j;
	double valeurCellule;
	
	Matrice Application(nombreEquations, nombreEquations);
	Matrice Vecteur(nombreEquations, 1);
	Matrice Solution(nombreEquations, 1);
	
	for (i=0; i<nombreEquations; i++)
	{
		for (j=0; j<nombreEquations; j++)
		{
			m_tableauMatriceSysteme->GetCellValue(i,j).ToDouble(&valeurCellule);
			Application.FixerValeur(i,j, (float)valeurCellule);
		}
		m_tableauVecteurSysteme->GetCellValue(i,0).ToDouble(&valeurCellule);
		Vecteur.FixerValeur(i,0, (float)valeurCellule);
	}
	
	if (Application.Inversible())
	{
		Solution = Application.Inverse() * Vecteur;
		Solution.AfficherMatrice();
	}
	else
	{
		wxMessageBox( wxT("Il n'y a aucune solution ou une infinité de solution.") );
	}
	EndModal(0);
}