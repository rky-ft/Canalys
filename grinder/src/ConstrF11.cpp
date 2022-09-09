
#include <ConstrF11.hpp>
#define CONSTRF11_CPP

void ConstrF11::MakeBranch()
{
	 appac = new TArrayPPAC();
	 appac->SetTree(otree);
	 appac->SetCalibPPAC(cppac);
	 appac->SetPPAC((Char_t *)"F11PPAC-1A", (Char_t *)"f11ppac1a");
	 appac->SetPPAC((Char_t *)"F11PPAC-1B", (Char_t *)"f11ppac1b");
	 appac->SetPPAC((Char_t *)"F11PPAC-2A", (Char_t *)"f11ppac2a");
	 appac->SetPPAC((Char_t *)"F11PPAC-2B", (Char_t *)"f11ppac2b");
	 appac->MakeBranch();

	 apla = new TArrayPla();
	 apla->SetTree(otree);
	 apla->SetCalibPlastic(cpla);
	 apla->SetPlastic((Char_t *)"F11Pla", (Char_t *)"f11pla");
	 //apla->SetPlastic((Char_t *)"F11Pla-2", (Char_t *)"V1290-TRef", (Char_t *)"f11pla2");
	 //apla->SetPlastic((Char_t *)"F11Pla-L", (Char_t *)"F11Pla-R", (Char_t *)"V1290-TRef", (Char_t *)"f11pla");
	 apla->MakeBranch();

	 aic = new TArrayIC();
	 aic->SetTree(otree);
	 aic->SetCalibIC(cic);
	 aic->SetIC((Char_t *)"F11IC", (Char_t *)"f11ic", 6);
	 //aic->SetIC((Char_t *)"F11IC", (Char_t *)"f11ic", 30);
	 //aic->SetBGtype();
	 aic->MakeBranch();

	 return;
};

void ConstrF11::Clear()
{
	 appac->Clear();
	 apla->Clear();
	 aic->Clear();

	 return;
};

void ConstrF11::CopyVal()
{
	 appac->CopyVal();
	 apla->CopyVal();
	 aic->CopyVal();

	 return;
}
