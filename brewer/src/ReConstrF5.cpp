
#include <ReConstrF5.hpp>
#define RECONSTRF5_CPP

ReConstrF5::ReConstrF5() {
   //calibpla.resize(1);
};

void ReConstrF5::SetVariable(Variables *vars)
{
	 calibppac.SetVariable(vars);
	 calibppac.SetPPAC((Char_t *)"f5ppac1a", (Char_t *)"f5ppac1b", (Char_t *)"f5ppac2a", (Char_t *)"f5ppac2b", (Char_t *)"f5");
	 //calibppac.SetPlasticZoffset((Char_t *)"f5pla", (Char_t *)"f5");

	 // Plastic
	 //for (Int_t i = 0; i < (Int_t)calibpla.size(); i++)
	 //{
	 //		calibpla[i].SetVariable(vars);
	 //}
	 //calibpla[0].SetPlastic((Char_t *)"f5pla");

	 return;
}

void ReConstrF5::SetFlags(Flags *flags)
{
	 calibppac.SetFlags(flags);

	 return;
};

void ReConstrF5::ReadParameters(std::string paradir, Int_t run)
{
	 calibppac.ReadParameters((paradir + std::string("PPAC/F5PPAC.txt")).c_str(), run);
	 //calibpla[0].ReadParameters("Pla/F5Pla.txt", paradir, run);

	 return;
}

void ReConstrF5::SetIOTree(TTree *iTree, TTree *oTree)
{
	 calibppac.SetIOTree(iTree, oTree);
	 //for (Int_t i = 0; i < (Int_t)calibpla.size(); i++)
	 //{
	 //		calibpla[i].SetIOTree(iTree, oTree);
	 //}

	 itree = iTree;
	 otree = oTree;

	 return;
}

void ReConstrF5::Calc()
{ // calculation of new values
	 calibppac.Calc();
	 //for (Int_t i = 0; i < (Int_t)calibpla.size(); i++)
	 //{
	 //		calibpla[i].Calc();
	 //}

	 return;
}
