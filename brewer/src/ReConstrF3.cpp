
#include <ReConstrF3.hpp>
#define RECONSTRF3_CPP

ReConstrF3::ReConstrF3()
{
	 calibpla.resize(1);
};

void ReConstrF3::SetVariable(Variables *vars)
{
	 calibppac.SetVariable(vars);
	 calibppac.SetPPAC((Char_t *)"f3ppac1a", (Char_t *)"f3ppac1b", (Char_t *)"f3ppac2a", (Char_t *)"f3ppac2b", (Char_t *)"f3");
	 calibppac.SetPlasticZoffset((Char_t *)"f3pla", (Char_t *)"f3");

	 // Plastic
	 for (Int_t i = 0; i < (Int_t)calibpla.size(); i++)
	 {
			calibpla[i].SetVariable(vars);
	 }
	 calibpla[0].SetPlastic((Char_t *)"f3pla");

	 return;
}

void ReConstrF3::SetFlags(Flags *flags)
{
	 calibppac.SetFlags(flags);

	 return;
};

void ReConstrF3::ReadParameters(std::string paradir, Int_t run)
{
	 calibppac.ReadParameters((paradir + std::string("PPAC/F3PPAC.txt")).c_str(), run);
	 calibpla[0].ReadParameters("Pla/F3Pla.txt", paradir, run);

	 return;
}

void ReConstrF3::SetIOTree(TTree *iTree, TTree *oTree)
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

void ReConstrF3::Calc()
{ // calculation of new values
	 calibppac.Calc();
	 for (Int_t i = 0; i < (Int_t)calibpla.size(); i++)
	 {
			calibpla[i].Calc();
	 }

	 return;
}
