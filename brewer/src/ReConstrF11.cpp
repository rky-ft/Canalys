
#include <ReConstrF11.hpp>
#define RECONSTRF11_CPP

ReConstrF11::ReConstrF11()
{
	 calibpla.resize(1);
};

void ReConstrF11::SetVariable(Variables *vars)
{
	 calibppac.SetVariable(vars);
	 calibppac.SetPPAC((Char_t *)"f11ppac1a", (Char_t *)"f11ppac1b", (Char_t *)"f11ppac2a", (Char_t *)"f11ppac2b", (Char_t *)"f11");
	 calibppac.SetPlasticZoffset((Char_t *)"f11pla", (Char_t *)"f11");
	 //calibppac.SetPlasticZoffset((Char_t *)"f11pla2", (Char_t *)"f11");
	 //calibppac.SetPlasticZoffset((Char_t *)"f11pla", (Char_t *)"f11");

	 // Plastic
	 for (Int_t i = 0; i < (Int_t)calibpla.size(); i++)
	 {
			calibpla[i].SetVariable(vars);
	 }

	 calibpla[0].SetPlastic((Char_t *)"f11pla");
	 //calibpla[1].SetPlastic((Char_t *)"f11pla2");

	 //calibpla[0].Set4PMTsPlastic((Char_t *)"f11pla");

	 Int_t nIC = 6;
	 //Int_t nIC = 30;
	 calibic.SetVariable(vars);
	 //calibic.SetBGtypeOn();
	 calibic.SetNCh(nIC);
	 calibic.SetADC((Char_t *)"f11ic_q");
	 //calibic.SetTwoBackgammonSum((Char_t *)"f11ic_bgsum");
	 //calibic.SetTwoBackgammonRatio((Char_t *)"f11ic_bgratio");
	 calibic.SetICE((Char_t *)"f11ic_e", (Char_t *)"f11ic_esum");

	 //itree->SetBranchAddress("F11ICP", &ICP);
	 //vars->SetVariable(&ICP, "F11ICP");

	 return;
}

void ReConstrF11::SetFlags(Flags *flags)
{
	 calibppac.SetFlags(flags);

	 return;
};

void ReConstrF11::ReadParameters(std::string paradir, Int_t run)
{
	 calibppac.ReadParameters((paradir + std::string("PPAC/F11PPAC.txt")).c_str(), run);
	 calibpla[0].ReadParameters("/Pla/F11Pla.txt", paradir, run);
	 calibic.ReadParameters((paradir + std::string("IC/F11IC.txt")).c_str(), run);

	 return;
}

void ReConstrF11::SetIOTree(TTree *iTree, TTree *oTree)
{
	 calibppac.SetIOTree(iTree, oTree);
	 for (Int_t i = 0; i < (Int_t)calibpla.size(); i++)
	 {
			calibpla[i].SetIOTree(iTree, oTree);
	 }
	 calibic.SetIOTree(iTree, oTree);

	 itree = iTree;
	 otree = oTree;

	 return;
};

void ReConstrF11::Calc()
{ // calculation of new values
	 calibppac.Calc();
	 for (Int_t i = 0; i < (Int_t)calibpla.size(); i++)
	 {
			calibpla[i].Calc();
	 }
	 calibic.Calc();

	 return;
}
