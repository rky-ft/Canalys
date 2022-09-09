
#ifndef CalibPPAC_hpp
#define CalibPPAC_hpp

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TStyle.h>
#include <TSystem.h>
#include <TMath.h>
#include <TMatrixD.h>

#include "ReadPara.hpp"
#include "Variables.hpp"
#include "Flags.hpp"

class CalibPPAC
{
 public:
	 CalibPPAC()
	 {
			TSUMX_MIN_1A = -9999;
			TSUMX_MAX_1A = +9999;
			TSUMX_MIN_1B = -9999;
			TSUMX_MAX_1B = +9999;
			TSUMX_MIN_2A = -9999;
			TSUMX_MAX_2A = +9999;
			TSUMX_MIN_2B = -9999;
			TSUMX_MAX_2B = +9999;

			TSUMY_MIN_1A = -9999;
			TSUMY_MAX_1A = +9999;
			TSUMY_MIN_1B = -9999;
			TSUMY_MAX_1B = +9999;
			TSUMY_MIN_2A = -9999;
			TSUMY_MAX_2A = +9999;
			TSUMY_MIN_2B = -9999;
			TSUMY_MAX_2B = +9999;

			TAoffset_1A = 0.;
			TAoffset_1B = 0.;
			TAoffset_2A = 0.;
			TAoffset_2B = 0.;

			TSUMX_MIN_3A = -9999;
			TSUMX_MAX_3A = +9999;
			TSUMX_MIN_3B = -9999;
			TSUMX_MAX_3B = +9999;

			TSUMY_MIN_3A = -9999;
			TSUMY_MAX_3A = +9999;
			TSUMY_MIN_3B = -9999;
			TSUMY_MAX_3B = +9999;

			TAoffset_3A = 0.;
			TAoffset_3B = 0.;

			zshift = 0;

			use_3rdPPAC = false;
			calc_Xonpla = false;
	 };
	 ~CalibPPAC() {};

	 void SetIOTree(TTree *tin, TTree *tout)
	 {
			itree = tin;
			otree = tout;
	 };
	 void SetVariable(Variables *var)
	 {
			vars = var;
	 };
	 void SetFlags(Flags *flag)
	 {
			flags = flag;
	 };

	 void SetPPAC(Char_t *ppac1a, Char_t *ppac1b, Char_t *ppac2a, Char_t *ppac2b, Char_t *fplname);
	 void Set3rdPPAC(Char_t *ppac3a, Char_t *ppac3b, Char_t *fplname);

	 void SetPlasticZoffset(Char_t *planame, Char_t *fplname);

	 void ReadParameters(const Char_t *filename, Int_t run);

	 Double_t GetXonPla()
	 {
			return XonPla;
	 };
	 void GetPosAng(Double_t &x, Double_t &a, Double_t &y, Double_t &b)
	 {
			x = X;
			a = A;
			y = Y;
			b = B;

			return;
	 };
	 Int_t *GetflagX()
	 {
			return flagTSumX;
	 };
	 Int_t *GetflagY()
	 {
			return flagTSumY;
	 };
	 Double_t GetTM()
	 {
			return TM;
	 };

	 void Clear();
	 void Calc();
	 void Calc3rdPPAC();

 private:
	 TTree *itree, *otree;
	 Variables *vars;
	 Flags *flags;

	 std::vector<TString> PPACName, FPLName;
	 Bool_t use_3rdPPAC, calc_Xonpla;

	 // Inputs, measured values
	 Double_t X_1A, Y_1A;
	 Double_t X_1B, Y_1B;
	 Double_t X_2A, Y_2A;
	 Double_t X_2B, Y_2B;

	 Double_t TSUMX_1A, TSUMY_1A, TSUMX_1B, TSUMY_1B;
	 Double_t TSUMX_2A, TSUMY_2A, TSUMX_2B, TSUMY_2B;

	 // Anode timing
	 Double_t TA_1A, TA_1B;
	 Double_t TA_2A, TA_2B;

	 // parameters
	 Double_t Z_1AX, Z_1BX;
	 Double_t Z_2AX, Z_2BX;
	 Double_t Z_1AY, Z_1BY;
	 Double_t Z_2AY, Z_2BY;

	 Double_t Pla_zoffset;
	 Double_t zshift;

	 Double_t TSUMX_MIN_1A, TSUMX_MAX_1A, TSUMX_MIN_1B, TSUMX_MAX_1B;
	 Double_t TSUMX_MIN_2A, TSUMX_MAX_2A, TSUMX_MIN_2B, TSUMX_MAX_2B;

	 Double_t TSUMY_MIN_1A, TSUMY_MAX_1A, TSUMY_MIN_1B, TSUMY_MAX_1B;
	 Double_t TSUMY_MIN_2A, TSUMY_MAX_2A, TSUMY_MIN_2B, TSUMY_MAX_2B;

	 Double_t TAoffset_1A, TAoffset_1B;
	 Double_t TAoffset_2A, TAoffset_2B;

	 // Position and angle at focal plane
	 Double_t X, A, Y, B;
	 Double_t XonPla;

	 Double_t TM; // Mean of Anode Timing

	 Double_t X_3A, Y_3A;
	 Double_t X_3B, Y_3B;
	 Double_t TSUMX_3A, TSUMY_3A;
	 Double_t TSUMX_3B, TSUMY_3B;
	 Double_t TA_3A, TA_3B;
	 Double_t Z_3AX, Z_3BX, Z_3AY, Z_3BY;
	 Double_t TSUMX_MIN_3A, TSUMX_MAX_3A, TSUMX_MIN_3B, TSUMX_MAX_3B;
	 Double_t TSUMY_MIN_3A, TSUMY_MAX_3A, TSUMY_MIN_3B, TSUMY_MAX_3B;
	 Double_t TAoffset_3A, TAoffset_3B;

	 Double_t Aout, Bout;

	 Int_t flagTSumX[5];
	 Int_t flagTSumY[5];

	 Int_t flag3rdTSumX[3];
	 Int_t flag3rdTSumY[3];

	 void AddPoint(TMatrixD &vec, TMatrixD &mat, Double_t x, Double_t z);
};

#endif
