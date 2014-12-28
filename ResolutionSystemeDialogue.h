#ifndef __ResolutionSystemeDialogue__
#define __ResolutionSystemeDialogue__

/**
@file
Subclass of ResolutionSystemeDialogueBase, which is generated by wxFormBuilder.
*/

#include "Dialogs.h"
#include "Calculs.h"
#include <wx/grid.h>
#include <wx/string.h>
#include <wx/msgdlg.h>

//// end generated include

/** Implementing ResolutionSystemeDialogueBase */
class ResolutionSystemeDialogue : public ResolutionSystemeDialogueBase
{
	public:
		/** Constructor */
		ResolutionSystemeDialogue( wxWindow* parent);
	//// end generated class members
	protected:
		void SurClicBoutonValiderSysteme(wxCommandEvent& event);
		void SurCLicBouttonResoudre(wxCommandEvent& event);
	private:
};

#endif // __ResolutionSystemeDialogue__
