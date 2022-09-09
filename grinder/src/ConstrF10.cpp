
#include <ConstrF10.hpp>
#define CONSTRF10_CPP

void ConstrF10::MakeBranch()
{
	 appac = new TArrayPPAC();
	 appac->SetTree(otree);
	 appac->SetCalibPPAC(cppac);
	 appac->SetPPAC((Char_t *)"F10PPAC-1A", (Char_t *)"f10ppac1a");
	 appac->SetPPAC((Char_t *)"F10PPAC-1B", (Char_t *)"f10ppac1b");
	 appac->SetPPAC((Char_t *)"F10PPAC-2A", (Char_t *)"f10ppac2a");
	 appac->SetPPAC((Char_t *)"F10PPAC-2B", (Char_t *)"f10ppac2b");
	 appac->MakeBranch();

	 return;
};

void ConstrF10::Clear()
{
	 appac->Clear();

	 return;
};

void ConstrF10::CopyVal()
{
	 appac->CopyVal();

	 return;
}
