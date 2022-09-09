
#include <ConstrF7.hpp>
#define CONSTRF7_CPP

void ConstrF7::MakeBranch()
{
	 appac = new TArrayPPAC();
	 appac->SetTree(otree);
	 appac->SetCalibPPAC(cppac);
	 appac->SetPPAC((Char_t *)"F7PPAC-1A", (Char_t *)"f7ppac1a");
	 appac->SetPPAC((Char_t *)"F7PPAC-1B", (Char_t *)"f7ppac1b");
	 appac->SetPPAC((Char_t *)"F7PPAC-2A", (Char_t *)"f7ppac2a");
	 appac->SetPPAC((Char_t *)"F7PPAC-2B", (Char_t *)"f7ppac2b");
	 appac->MakeBranch();

	 apla = new TArrayPla();
	 apla->SetTree(otree);
	 apla->SetCalibPlastic(cpla);
	 apla->SetPlastic((Char_t *)"F7Pla", (Char_t *)"f7pla");
	 apla->MakeBranch();

	 aic = new TArrayIC();
	 aic->SetTree(otree);
	 aic->SetCalibIC(cic);
	 aic->SetIC((Char_t *)"F7IC", (Char_t *)"f7ic", 12);
	 aic->MakeBranch();

	 age = new TArrayGe();
	 age->SetTree(otree);
	 age->SetCalibGe(cge);
	 age->SetGe_xml((Char_t *)"F7Clv1-1");
	 age->SetGe_xml((Char_t *)"F7Clv1-2");
	 age->SetGe_xml((Char_t *)"F7Clv1-3");
	 age->SetGe_xml((Char_t *)"F7Clv1-4");
	 age->SetGe_xml((Char_t *)"F7Clv2-1");
	 age->SetGe_xml((Char_t *)"F7Clv2-2");
	 age->SetGe_xml((Char_t *)"F7Clv2-3");
	 age->SetGe_xml((Char_t *)"F7Clv2-4");
	 age->SetGe_root((Char_t *)"f7ge");
	 age->MakeBranch();

	 return;
};

void ConstrF7::Clear()
{
	 appac->Clear();
	 apla->Clear();
	 aic->Clear();
	 age->Clear();

	 return;
};

void ConstrF7::CopyVal()
{
	 appac->CopyVal();
	 apla->CopyVal();
	 aic->CopyVal();
	 age->CopyVal();

	 return;
}
