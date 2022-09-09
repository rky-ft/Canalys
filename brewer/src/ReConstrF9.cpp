
#include <ReConstrF9.hpp>
#define RECONSTRF9_CPP

ReConstrF9::ReConstrF9() {};

void ReConstrF9::SetVariable(Variables *vars)
{
	 calibppac.SetVariable(vars);
	 calibppac.SetPPAC((Char_t *)"f9ppac1a", (Char_t *)"f9ppac1b", (Char_t *)"f9ppac2a", (Char_t *)"f9ppac2b", (Char_t *)"f9");

	 return;
}

void ReConstrF9::SetFlags(Flags *flags)
{
	 calibppac.SetFlags(flags);

	 return;
};

void ReConstrF9::ReadParameters(std::string paradir, Int_t run)
{
	 calibppac.ReadParameters((paradir + std::string("PPAC/F9PPAC.txt")).c_str(), run);

	 return;
}

void ReConstrF9::SetIOTree(TTree *iTree, TTree *oTree)
{
	 calibppac.SetIOTree(iTree, oTree);

	 itree = iTree;
	 otree = oTree;

	 return;
}

void ReConstrF9::Calc()
{ // calculation of new values
	 calibppac.Calc();

	 return;
}
