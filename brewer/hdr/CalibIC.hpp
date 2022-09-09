
#ifndef CalibIC_hpp
#define CalibIC_hpp

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <TROOT.h>
#include <TMath.h>

#include "ReadPara.hpp"
#include "Variables.hpp"

class CalibIC
{
 public:
	 CalibIC()
	 {
			for (Int_t i = 0; i < 32; i++)
			{
				 pedestal[i] = 0.;
				 ch2MeV[i][0] = 0.;
				 ch2MeV[i][1] = 1.;
				 gainRatio = 1.;
			}
			nlayer = 0;
			nch = 0;
			use_BGtype = false;
	 };
	 ~CalibIC() {};

	 void SetIOTree(TTree *tin, TTree *tout)
	 {
			itree = tin;
			otree = tout;
	 };
	 void SetVariable(Variables *var)
	 {
			vars = var;
	 };

	 void SetBGtypeOn()
	 {
			use_BGtype = true;
	 };

	 void SetNCh(Int_t n);
	 void SetADC(Char_t *q);
	 void SetICE(Char_t *e, Char_t *esum);

	 void SetTwoBackgammonSum(Char_t *icbsum)
	 {
			vars->SetVariable(bgSum, TString(icbsum), nlayer);
	 };
	 void SetTwoBackgammonRatio(Char_t *icbratio)
	 {
			vars->SetVariable(bgRatio, TString(icbratio), nlayer);
	 };

	 Double_t GetICE()
	 {
			return ESum;
	 };

	 void Calc();

	 void ReadParameters(const Char_t *filename, Int_t run);

 private:
	 TTree *itree, *otree;
	 Variables *vars;

	 // Input
	 Int_t QRaw[32]; // array from input file

	 // Internal parameters
	 Int_t nch;
	 Int_t nlayer;

	 Double_t pedestal[32]; // for geometrical average
	 Double_t ch2MeV[32][2]; // for E of each layer

	 Double_t gainRatio; // Gain ratio for 2ch of backgammon.

	 // Outputs
	 Double_t E[32];
	 Double_t ESum;

	 Double_t bgSum[32];
	 Double_t bgRatio[32];

	 // Option
	 Bool_t use_BGtype; // backgammon
};

#endif
