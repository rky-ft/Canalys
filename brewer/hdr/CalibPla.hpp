
#ifndef CalibPla_hpp
#define CalibPla_hpp

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include <TROOT.h>
#include <TGraph.h>
#include <TMath.h>

#include "ReadPara.hpp"
#include "Variables.hpp"
#include "Multihit.hpp"

class CalibPla
{
 public:
	 CalibPla()
	 {
			//for (Int_t i = 0; i < 3; i++)
			for (Int_t i = 0; i < 4; i++)
			{
				 pedestal[i] = 0.;
				 ch2MeV[i] = 0;
			}

			tl_low = -1.0e10;
			tl_high = 1.0e10;
			tr_low = -1.0e10;
			tr_high = 1.0e10;
			tlr_low = -1.0e10;
			tlr_high = 1.0e10;

			QL = 0.;
			QR = 0.;

			QLU = 0.;
			QLD = 0.;
			QRU = 0.;
			QRD = 0.;

			use_FourPMTtype = false;
			use_MTDC = false;
	 };
	 ~CalibPla() {};

	 void SetIOTree(TTree *tin, TTree *tout)
	 {
			itree = tin;
			otree = tout;
	 };
	 void SetVariable(Variables *var)
	 {
			vars = var;
	 };
	 void SetPlastic(Char_t *pla, Bool_t multi = false);
	 void Set4PMTsPlastic(Char_t *pla);

	 void Calc();

	 void ReadParameters(const Char_t *filename, std::string paradir, Int_t run);
	 void ReadParameters(const Char_t *filename, std::string paradir);

 private:
	 TTree *itree, *otree;
	 Variables *vars;

	 //Double_t tstamp;

	 // 2PMTs (L, R)
	 Double_t TL, TR;
	 Int_t NhitTL, NhitTR; // from ground/*.root
	 Int_t nhitTL, nhitTR, nhitTLR;
	 Double_t multiTL[128], multiTR[128];
	 Double_t TLforward, TRforward, TLbackward, TRbackward;
	 Double_t TLRforward, TLRbackward;
	 Int_t QL, QR;

	 // 4PMTs (LU, LD, RU, RD)
	 Double_t TLU, TLD, TRU, TRD;
	 Int_t QLU, QLD, QRU, QRD;
	 Double_t TLM, TRM, QLA, QRA;
	 Bool_t use_FourPMTtype;

	 // common
	 Double_t TM, TD, X, QA, QD, dE;
	 TGraph grTDtoX;

	 Double_t pedestal[4];
	 Double_t ch2MeV[3];

	 // Parameter for multihit TDC
	 Multihit multi;
	 Double_t tl_low, tl_high, tr_low, tr_high; // window for TL and TR
	 Double_t tlr_low, tlr_high; // window for TL-TR

	 // Option
	 Bool_t use_MTDC;
};

#endif
