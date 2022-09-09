
#ifndef CalcAOQ_hpp
#define CalcAOQ_hpp

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <TROOT.h>
#include <TTree.h>
#include <TMath.h>

#include "SetPara.hpp"
#include "Variables.hpp"

class CalcAOQ
{
 public:
	 CalcAOQ()
	 {
			clight = 299.792458;
			mnucleon = 931.49432;
			Brho = 0;
			Beta = 0;
			Gamma = 0;
	 };
	 ~CalcAOQ() {};

	 void SetVariable(Variables *var)
	 {
			vars = var;
	 };

	 void SetBrho(std::string br);
	 void SetBeta(std::string b);
	 void SetGamma(std::string g);

	 void SetAOQ(std::string aoq)
	 {
			vars->SetVariable(&AOQ, aoq);
	 };

	 Double_t GetAOQ()
	 {
			return AOQ;
	 };

	 void Calc();

	 void ReadParameters(std::string filename1, std::string paradir, Int_t run);
	 void ReadParameters(std::string filename1, std::string filename2, std::string paradir, Int_t run);

 private:
	 Variables *vars;

	 // Inputs
	 Double_t *Brho;
	 Double_t *Beta;
	 Double_t *Gamma;

	 // Parameters
	 Double_t clight; // mm/ns
	 Double_t mnucleon; // MeV

	 // Output
	 Double_t AOQ;
};

#endif
