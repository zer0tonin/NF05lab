#include "ResolutionSystemeDialogue.h"

ResolutionSystemeDialogue::ResolutionSystemeDialogue( wxWindow* parent)
:
ResolutionSystemeDialogueBase( parent )
{

}

/*
 * La méthode ResolutionSystemeDialogue prend le nombre d'équation (nombreEquations) indiqué par l'utilisateur et s'en sert pour générer:
 * - une grille nombreEquations * nombreEquations pour l'application
 * - une grille nombreEquations * 1 pour le vecteur
 * (Le système étant : Application * Solution = Vecteur).
 */
void ResolutionSystemeDialogue::SurClicBoutonValiderSysteme(wxCommandEvent& event)
{
	int nombreEquations = m_equationsSpin->GetValue();
	
	if(nombreEquations > 0)
	{
		//On supprime les colonnes et les lignes des deux grilles
		if(m_tableauMatriceSysteme->GetRows() > 0)
			m_tableauMatriceSysteme->DeleteRows(0, m_tableauMatriceSysteme->GetRows());
		if(m_tableauMatriceSysteme->GetCols() > 0)
			m_tableauMatriceSysteme->DeleteCols(0, m_tableauMatriceSysteme->GetCols());
		
		if(m_tableauVecteurSysteme->GetRows() > 0)
			m_tableauVecteurSysteme->DeleteRows(0, m_tableauVecteurSysteme->GetRows());
		if(m_tableauVecteurSysteme->GetCols() > 0)
			m_tableauVecteurSysteme->DeleteCols(0, 1);
		
		//On ajoute le nombre de colonnes et de lignes nécessaires
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