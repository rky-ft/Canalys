
#ifndef CalcZed_hpp
#define CalcZed_hpp

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <TROOT.h>
#include <TMath.h>

#include "ReadPara.hpp"
#include "Variables.hpp"

class CalcZed
{
 public:
	 CalcZed()
	 {
			nlayer = 0;
			nvalid = 0;

			Corr[0] = 0.;
			Corr[1] = 0.;
			Corr[2] = 0.;

			Length = 0.;
			Material = 0.;
			Density = 0.;

			ionpair = -9999.;
			ZCoef[0] = -9999.;
			ZCoef[1] = -9999.;
			ZCoef[2] = -9999.;

			use_TKEmode = false;
	 };
	 ~CalcZed() {};

	 void SetVariable(Variables *var)
	 {
			vars = var;
	 };

	 void SetBeta(std::string b);
	 void SetGamma(std::string g);

	 void SetDeltaE(std::string de);

	 void SetDelta(std::string d);
	 void SetTotE(std::string e);

	 void SetZed(std::string z)
	 {
			vars->SetVariable(&Zed, z);
	 };
	 void SetNValid(std::string v)
	 {
			vars->SetVariable(&nvalid, v);
	 };

	 Double_t GetZed()
	 {
			return Zed;
	 };

	 void Calc();
	 void ReadParameters(std::string filename, Int_t run);

 private:
	 Variables *vars;

	 // Inputs
	 Double_t *Beta;
	 Double_t *Gamma;
	 Double_t *dE1;

	 Double_t *Delta;
	 Double_t *TotE;

	 // Internal parameters
	 Double_t ionpair;
	 Double_t Zic_tmp;

	 Double_t ZCoef[3];

	 Double_t Length;
	 Double_t Material;
	 Double_t Density;

	 Int_t nlayer;
	 Double_t Corr[3];

	 Bool_t use_TKEmode;

	 // Output
	 Double_t Zed;
	 Int_t nvalid;
};

#endif
