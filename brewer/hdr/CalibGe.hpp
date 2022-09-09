
#ifndef CALIBGE
#define CALIBGE

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <TROOT.h>
#include <TMath.h>

#include "ReadPara.hpp"
#include "Variables.hpp"

class CalibGe
{
 public:
	 CalibGe()
	 {
			nGe = 0;
			for (Int_t i = 0; i < 20; i++)
			{
				 offset[i] = 0.;
				 MeV2MeV[i][0] = 0.;
				 MeV2MeV[i][1] = 1.;
			}
	 };
	 ~CalibGe() {};

	 void SetIOTree(TTree *tin, TTree *tout)
	 {
			itree = tin;
			otree = tout;
	 };
	 void SetVariable(Variables *var)
	 {
			vars = var;
	 };

	 void SetNCrystal(Int_t n)
	 {
			nGe = n;
	 };
	 void SetOriginalEnergy(Char_t *en);
	 void SetOriginalTiming(Char_t *time);
	 void SetReCalibEnergy(Char_t *en);
	 void SetReCalibTiming(Char_t *time);

	 void Calc();

	 void ReadParameters(const Char_t *filename, Int_t run);

 private:
	 TTree *itree, *otree;
	 Variables *vars;

	 Int_t nGe; //The number of Ge crystal

	 //from input file
	 Double_t Eoriginal[20];
	 Double_t Toriginal[20];

	 //calculated values
	 Double_t Energy[20];
	 Double_t Timing[20];

	 //parameters
	 Double_t offset[20];
	 Double_t MeV2MeV[20][2];
};

#endif
