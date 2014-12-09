#include "AjoutMatriceDialogue.h"

AjoutMatriceDialogue::AjoutMatriceDialogue( wxWindow* parent, Conteneur* conteneur, char matriceAEditer )
:
AjoutMatriceDialogueBase( parent ),
m_conteneur(conteneur),
m_editeMatriceExistante(matriceAEditer != '\0')
{
	//Si on souhaite éditer une matrice existance, il faut :
	// - sélectionner le nom de la matrice dans le combobox m_nomMatrice
	// - Charger le contenu de la matrice depuis le conteneur de matrices
	if(m_editeMatriceExistante)
	{
		m_nomMatrice->SetSelection((char)(matriceAEditer - 65));
		m_nomMatrice->Disable(); //On empêche l'utilisateur de changer le nom de la matrice
		
		Matrice &matrice = m_conteneur->Variable(matriceAEditer);
		
		//Chargement de la matrice
		m_tableauMatrice->AppendRows(matrice.ObtenirLignes());
		m_tableauMatrice->AppendCols(matrice.ObtenirColonnes());
		m_lignesSpin->SetValue(matrice.ObtenirLignes());
		m_colonnesSpin->SetValue(matrice.ObtenirColonnes());
		
		for(int i = 0; i < matrice.ObtenirLignes(); i++)
		{
			for(int j = 0; j < matrice.ObtenirColonnes(); j++)
			{
				m_tableauMatrice->SetCellValue(i, j, wxString::FromDouble(matrice.ObtenirValeur(i, j)));
			}
		}
		
		//Affichage du titre de la fenêtre (wxString::Format permet de générer une chaîne de caractère en utilisant
		// les mêmes procédés que pour printf).
		SetTitle(wxString::Format("Edition de la matrice %c", matriceAEditer));
	}
	else
	{
		SetTitle("Ajouter une nouvelle variable");
	}
}

void AjoutMatriceDialogue::SurClicValiderTailleMatrice( wxCommandEvent& event )
{
	//On compare la nouvelle taille souhaitée à la taille actuelle du tableau
	int nombreLignes = m_lignesSpin->GetValue() - m_tableauMatrice->GetNumberRows();
	int nombreColonnes = m_colonnesSpin->GetValue() - m_tableauMatrice->GetNumberCols();
	
	//Si il y a trop de lignes/colonnes, on en retire suffisamment
	if(nombreLignes < 0)
	{
		m_tableauMatrice->DeleteRows(m_tableauMatrice->GetNumberRows() + nombreLignes, -nombreLignes);
	}
	if(nombreColonnes < 0)
	{
		m_tableauMatrice->DeleteCols(m_tableauMatrice->GetNumberCols() + nombreColonnes, -nombreColonnes);
	}
	
	if(nombreLignes > 0)
	{
		m_tableauMatrice->AppendRows(nombreLignes);
	}
	if(nombreColonnes > 0)
	{
		m_tableauMatrice->AppendCols(nombreColonnes);
	}
}

void AjoutMatriceDialogue::SurClicSauver( wxCommandEvent& event )
{
	int i,j;
	if (m_conteneur->Existe((char)m_nomMatrice->GetCurrentSelection()+65))
	{
		if (m_editeMatriceExistante || wxMessageBox(L"La variable existe déjà. Etes-vous sûr de vouloir la remplacer?", "Confirmation", wxYES_NO, this) == wxYES)
		{
			m_conteneur->SupprimerVariable((char)m_nomMatrice->GetCurrentSelection()+65);
		}
		else
		{
			return;
		}
	}
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