
#include <ReConstrF10.hpp>
#define RECONSTRF10_CPP

ReConstrF10::ReConstrF10() {};

void ReConstrF10::SetVariable(Variables *vars)
{
	 calibppac.SetVariable(vars);
	 calibppac.SetPPAC((Char_t *)"f10ppac1a", (Char_t *)"f10ppac1b", (Char_t *)"f10ppac2a", (Char_t *)"f10ppac2b", (Char_t *)"f10");

	 return;
}

void ReConstrF10::SetFlags(Flags *flags)
{
	 calibppac.SetFlags(flags);

	 return;
};

void ReConstrF10::ReadParameters(std::string paradir, Int_t run)
{
	 calibppac.ReadParameters((paradir + std::string("PPAC/F10PPAC.txt")).c_str(), run);

	 return;
}

void ReConstrF10::SetIOTree(TTree *iTree, TTree *oTree)
{
	 calibppac.SetIOTree(iTree, oTree);

	 itree = iTree;
	 otree = oTree;

	 return;
}

void ReConstrF10::Calc()
{ // calculation of new values
	 calibppac.Calc();

	 return;
}
