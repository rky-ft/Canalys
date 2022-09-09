
#include <ConstrF8.hpp>
#define CONSTRF8_CPP

void ConstrF8::MakeBranch()
{
	 appac = new TArrayPPAC();
	 appac->SetTree(otree);
	 appac->SetCalibPPAC(cppac);
	 appac->SetPPAC((Char_t *)"F8PPAC-1A", (Char_t *)"f8ppac1a");
	 appac->SetPPAC((Char_t *)"F8PPAC-1B", (Char_t *)"f8ppac1b");
	 appac->SetPPAC((Char_t *)"F8PPAC-2A", (Char_t *)"f8ppac2a");
	 appac->SetPPAC((Char_t *)"F8PPAC-2B", (Char_t *)"f8ppac2b");
	 appac->SetPPAC((Char_t *)"F8PPAC-3A", (Char_t *)"f8ppac3a");
	 appac->SetPPAC((Char_t *)"F8PPAC-3B", (Char_t *)"f8ppac3b");
	 appac->MakeBranch();

	 apla = new TArrayPla();
	 apla->SetTree(otree);
	 apla->SetCalibPlastic(cpla);
	 apla->SetPlastic((Char_t *)"F8Pla", (Char_t *)"f8pla");
	 apla->MakeBranch();

	 return;
};

void ConstrF8::Clear()
{
	 appac->Clear();
	 apla->Clear();

	 return;
};

void ConstrF8::CopyVal()
{
	 appac->CopyVal();
	 apla->CopyVal();

	 return;
}
