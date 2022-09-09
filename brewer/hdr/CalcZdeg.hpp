
#ifndef CalcZdeg_hpp
#define CalcZdeg_hpp

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <TROOT.h>
#include <TMath.h>

#include "ReadPara.hpp"
#include "Variables.hpp"

class CalcZdeg
{
 public:
	 CalcZdeg()
	 {
			Zpos = 0.;
			d0 = 0.;
			ang_deg = 0.;
			zcoef[0] = 0.;
			zcoef[1] = 1.;
			zcoef[2] = 0.;
			Angdummy = 0.;
			Q1oZ = 1.;
			Q2oZ = 1.;
	 };
	 ~CalcZdeg() {};

	 void SetVariable(Variables *var)
	 {
			vars = var;
	 };

	 void SetBrho(std::string br1, std::string br2);
	 void SetBeta(std::string b1, std::string b2);
	 void SetPosAng(std::string pos, std::string ang);
	 void SetPos(std::string pos);

	 void SetZdeg(std::string zd)
	 {
			vars->SetVariable(&Zdeg, zd);
	 };

	 Double_t GetZdeg()
	 {
			return Zdeg;
	 };
	 void Calc();
	 void ReadParameters(std::string filename, Int_t run);

 private:
	 Variables *vars;

	 // Inputs
	 Double_t *Brho1, *Brho2;
	 Double_t *Beta1, *Beta2;
	 Double_t *Pos, *Ang; // at focal plane in mm, mrad
	 Double_t Angdummy; // for use of Plastic position

	 // Internal parameters
	 Double_t d0; // thickness at center (mm)
	 Double_t ang_deg; // angle of degrader in mrad
	 Double_t Zpos; // distance from focal plane
	 Double_t zcoef[3]; // coefficient for zdeg calculation
	 Double_t Q1oZ, Q2oZ; // Q1oZ means Q1/Z

	 // Output
	 Double_t Zdeg;
};

#endif
