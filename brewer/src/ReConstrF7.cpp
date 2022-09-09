
#include <ReConstrF7.hpp>
#define RECONSTRF7_CPP

ReConstrF7::ReConstrF7()
{
	 calibpla.resize(1);
};

void ReConstrF7::SetVariable(Variables *vars)
{
	 calibppac.SetVariable(vars);
	 calibppac.SetPPAC((Char_t *)"f7ppac1a", (Char_t *)"f7ppac1b", (Char_t *)"f7ppac2a", (Char_t *)"f7ppac2b", (Char_t *)"f7");
	 calibppac.SetPlasticZoffset((Char_t *)"f7pla", (Char_t *)"f7");

	 // Plastic
	 for (Int_t i = 0; i < (Int_t)calibpla.size(); i++)
	 {
			calibpla[i].SetVariable(vars);
	 }
	 calibpla[0].SetPlastic((Char_t *)"f7pla");

	 Int_t nIC = 12;
	 calibic.SetVariable(vars);
	 calibic.SetNCh(nIC);
	 calibic.SetADC((Char_t *)"f7ic_q");
	 // output
	 //calibic.SetGeoAve((Char_t *)"f7ic_geoave", (Char_t *)"f7ic_egeoave");
	 calibic.SetICE((Char_t *)"f7ic_e", (Char_t *)"f7ic_esum");

	 Int_t nGe = 8;
	 calibge.SetVariable(vars);
	 calibge.SetNCrystal(nGe);
	 calibge.SetOriginalEnergy((Char_t *)"f7ge_e");
	 calibge.SetOriginalTiming((Char_t *)"f7ge_t");
	 calibge.SetReCalibEnergy((Char_t *)"f7ge_e");
	 calibge.SetReCalibTiming((Char_t *)"f7ge_t");

	 return;
}

void ReConstrF7::SetFlags(Flags *flags)
{
	 calibppac.SetFlags(flags);

	 return;
};

void ReConstrF7::ReadParameters(std::string paradir, Int_t run)
{
	 calibppac.ReadParameters((paradir + std::string("PPAC/F7PPAC.txt")).c_str(), run);
	 calibpla[0].ReadParameters("Pla/F7Pla.txt", paradir, run);
	 calibic.ReadParameters((paradir + std::string("IC/F7IC.txt")).c_str(), run);
	 calibge.ReadParameters((paradir + std::string("Ge/F7Ge.txt")).c_str(), run);

	 return;
}

void ReConstrF7::SetIOTree(TTree *iTree, TTree *oTree)
{
	 calibppac.SetIOTree(iTree, oTree);
	 for (Int_t i = 0; i < (Int_t)calibpla.size(); i++)
	 {
			calibpla[i].SetIOTree(iTree, oTree);
	 }
	 calibic.SetIOTree(iTree, oTree);
	 calibge.SetIOTree(iTree, oTree);

	 itree = iTree;
	 otree = oTree;

	 return;
}

void ReConstrF7::Calc()
{ // calculation of new values
	 calibppac.Calc();
	 for (Int_t i = 0; i < (Int_t)calibpla.size(); i++)
	 {
			calibpla[i].Calc();
	 }
	 calibic.Calc();
	 calibge.Calc();

	 return;
}
