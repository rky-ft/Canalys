
#include <ConstrF9.hpp>
#define CONSTRF9_CPP

void ConstrF9::MakeBranch()
{
	 appac = new TArrayPPAC();
	 appac->SetTree(otree);
	 appac->SetCalibPPAC(cppac);
	 appac->SetPPAC((Char_t *)"F9PPAC-1A", (Char_t *)"f9ppac1a");
	 appac->SetPPAC((Char_t *)"F9PPAC-1B", (Char_t *)"f9ppac1b");
	 appac->SetPPAC((Char_t *)"F9PPAC-2A", (Char_t *)"f9ppac2a");
	 appac->SetPPAC((Char_t *)"F9PPAC-2B", (Char_t *)"f9ppac2b");
	 appac->MakeBranch();

	 return;
};

void ConstrF9::Clear()
{
	 appac->Clear();

	 return;
};

void ConstrF9::CopyVal()
{
	 appac->CopyVal();

	 return;
}
