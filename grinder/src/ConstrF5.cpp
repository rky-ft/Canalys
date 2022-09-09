
#include <ConstrF5.hpp>
#define CONSTRF5_CPP

void ConstrF5::MakeBranch()
{
	 appac = new TArrayPPAC();
	 appac->SetTree(otree);
	 appac->SetCalibPPAC(cppac);
	 appac->SetPPAC((Char_t *)"F5PPAC-1A", (Char_t *)"f5ppac1a");
	 appac->SetPPAC((Char_t *)"F5PPAC-1B", (Char_t *)"f5ppac1b");
	 appac->SetPPAC((Char_t *)"F5PPAC-2A", (Char_t *)"f5ppac2a");
	 appac->SetPPAC((Char_t *)"F5PPAC-2B", (Char_t *)"f5ppac2b");
	 appac->MakeBranch();

	 //apla = new TArrayPla();
	 //apla->SetTree(otree);
	 //apla->SetCalibPlastic(cpla);
	 //apla->SetPlastic((Char_t *)"F5Pla", (Char_t *)"f5pla");
	 //apla->MakeBranch();

	 return;
};

void ConstrF5::Clear()
{
	 appac->Clear();
	 //apla->Clear();

	 return;
};

void ConstrF5::CopyVal()
{
	 appac->CopyVal();
	 //apla->CopyVal();

	 return;
}
