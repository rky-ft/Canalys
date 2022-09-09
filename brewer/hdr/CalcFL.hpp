
#ifndef CalcFL_hpp
#define CalcFL_hpp

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <TROOT.h>
#include <TMath.h>
#include <TMatrixD.h>

#include "SetPara.hpp"
#include "ReadPara.hpp"
#include "Variables.hpp"

class CalcFL
{
 public:
	 CalcFL()
	 {
			FLc = -9999;
			FL = -9999;
			pX = 0;
			pA = 0;
			pY = 0;
			pB = 0;
			pdelta = 0;
			mat.ResizeTo(83, 5);
	 };
	 ~CalcFL() {};

	 void SetVariable(Variables *var)
	 {
			vars = var;
	 };

	 void SetFLCenter(Double_t flc)
	 {
			FLc = flc;
	 };

	 void SetPosAngDelta(std::string x, std::string a, std::string y, std::string b, std::string del);
	 void SetPosDelta(std::string x, std::string del);

	 Double_t GetFL()
	 {
			Calc();

			return FL;
	 };
	 Double_t GetFLc()
	 {
			return FLc;
	 };
	 void Calc();

	 void ReadParameters(std::string filename, TMatrixD &ma);
	 void ReadParameters(std::string matrixfile, std::string paradir, Int_t run);

 private:
	 Variables *vars;

	 // values from input file
	 Double_t *pX, *pA, *pdelta, *pY, *pB;

	 Double_t FLc; // flight length for central trajectory
	 // for output
	 Double_t FL;

	 TMatrixD mat; // optical matrix elements

	 Bool_t use_YB;
};

#endif
