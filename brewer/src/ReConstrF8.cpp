
#include <ReConstrF8.hpp>
#define RECONSTRF8_CPP

ReConstrF8::ReConstrF8()
{
	 calibpla.resize(1);
};

void ReConstrF8::SetVariable(Variables *vars)
{
	 calibppac.SetVariable(vars);
	 calibppac.SetPPAC((Char_t *)"f8ppac1a", (Char_t *)"f8ppac1b", (Char_t *)"f8ppac2a", (Char_t *)"f8ppac2b", (Char_t *)"f8");
	 calibppac.Set3rdPPAC((Char_t *)"f8ppac3a", (Char_t *)"f8ppac3b", (Char_t *)"f8");
	 calibppac.SetPlasticZoffset((Char_t *)"f8pla", (Char_t *)"f8");

	 // Plastic
	 for (Int_t i = 0; i < (Int_t)calibpla.size(); i++)
	 {
			calibpla[i].SetVariable(vars);
	 }
	 calibpla[0].SetPlastic((Char_t *)"f8pla");

	 return;
}

void ReConstrF8::SetFlags(Flags *flags)
{
	 calibppac.SetFlags(flags);

	 return;
};

void ReConstrF8::ReadParameters(std::string paradir, Int_t run)
{
	 calibppac.ReadParameters((paradir + std::string("PPAC/F8PPAC.txt")).c_str(), run);
	 calibpla[0].ReadParameters("Pla/F8Pla.txt", paradir, run);

	 return;
}

void ReConstrF8::SetIOTree(TTree *iTree, TTree *oTree)
{
	 calibppac.SetIOTree(iTree, oTree);
	 for (Int_t i = 0; i < (Int_t)calibpla.size(); i++)
	 {
			calibpla[i].SetIOTree(iTree, oTree);
	 }

	 itree = iTree;
	 otree = oTree;

	 return;
}

void ReConstrF8::Calc()
{ // calculation of new values
	 calibppac.Calc();
	 for (Int_t i = 0; i < (Int_t)calibpla.size(); i++)
	 {
			calibpla[i].Calc();
	 }

	 return;
}
