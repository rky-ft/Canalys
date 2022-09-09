
#include <ConstrF3.hpp>
#define CONSTRF3_CPP

void ConstrF3::MakeBranch()
{
	 appac = new TArrayPPAC();
	 appac->SetTree(otree);
	 appac->SetCalibPPAC(cppac);
	 appac->SetPPAC((Char_t *)"F3PPAC-1A", (Char_t *)"f3ppac1a");
	 appac->SetPPAC((Char_t *)"F3PPAC-1B", (Char_t *)"f3ppac1b");
	 appac->SetPPAC((Char_t *)"F3PPAC-2A", (Char_t *)"f3ppac2a");
	 appac->SetPPAC((Char_t *)"F3PPAC-2B", (Char_t *)"f3ppac2b");
	 appac->MakeBranch();

	 apla = new TArrayPla();
	 apla->SetTree(otree);
	 apla->SetCalibPlastic(cpla);
	 apla->SetPlastic((Char_t *)"F3Pla", (Char_t *)"f3pla");
	 apla->MakeBranch();

	 return;
};

void ConstrF3::Clear()
{
	 appac->Clear();
	 apla->Clear();

	 return;
};

void ConstrF3::CopyVal()
{
	 appac->CopyVal();
	 apla->CopyVal();

	 return;
}
