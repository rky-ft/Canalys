
#ifndef Multihit_hpp
#define Multihit_hpp

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include <TROOT.h>
#include <TGraph.h>
#include <TMath.h>

class Multihit
{
 public:
	 Multihit()
	 {
			use_LR = true;
			tl_low = -1.0e10;
			tl_high = 1.0e10;
			tr_low = -1.0e10;
			tr_high = 1.0e10;
			tlr_low = -1.0e10;
			tlr_high = 1.0e10;
	 };
	 ~Multihit() {};

	 void SetMultihitT(Double_t *multiT_in, Int_t NhitT_in)
	 {
			use_LR = false;
			NhitTL = NhitT_in;
			multiTL = multiT_in;
	 };
	 void SetMultihitTLR(Double_t *multiTL_in, Double_t *multiTR_in, Int_t NhitTL_in, Int_t NhitTR_in)
	 {
			NhitTL = NhitTL_in;
			NhitTR = NhitTR_in;
			multiTL = multiTL_in;
			multiTR = multiTR_in;
	 };
	 void SetTimeWindow(Double_t t_low_in, Double_t t_high_in)
	 {
			tl_low = t_low_in;
			tl_high = t_high_in;
	 };
	 void SetTimeWindowLR(Double_t tl_low_in, Double_t tl_high_in, Double_t tr_low_in, Double_t tr_high_in, Double_t tlr_low_in, Double_t tlr_high_in)
	 {
			tl_low = tl_low_in;
			tl_high = tl_high_in;
			tr_low = tr_low_in;
			tr_high = tr_high_in;
			tlr_low = tlr_low_in;
			tlr_high = tlr_high_in;
	 };

	 void Calc();
	 void GetT(Double_t &Time)
	 {
			Time = TL;
	 };
	 void GetTLR(Double_t &TimeL, Double_t &TimeR)
	 {
			TimeL = TL;
			TimeR = TR;
	 };
	 void GetnhitT(Double_t &nhitT)
	 {
			nhitT = nhitTL;
	 };
	 void GetnhitTLR(Double_t &nhitTl, Double_t &nhitTr)
	 {
			nhitTl = nhitTL;
			nhitTr = nhitTR;
	 };
	 void GetForwardBackward(Double_t &forward, Double_t &backward)
	 {
			forward = TLforward;
			backward = TLbackward;
	 };
	 void GetForwardBackwardLR(Double_t &Lfor, Double_t &Lback, Double_t &Rfor, Double_t &Rback, Double_t &LRfor, Double_t &LRback)
	 {
			Lfor = TLforward;
			Rfor = TRforward;
			LRfor = TLRforward;
			Lback = TLbackward;
			Rback = TRbackward;
			LRfor = TLRbackward;
	 };

 private:
	 Bool_t use_LR;

	 Int_t NhitTL, NhitTR; // from calib/**.root
	 Double_t *multiTL, *multiTR; // array of Timing from multihit TDC

	 // outputs
	 Double_t TL, TR;
	 Int_t nhitTL, nhitTR, nhitTLR; // the number of hit within time window
	 Double_t TLforward, TRforward, TLbackward, TRbackward;
	 Double_t TLRforward, TLRbackward;

	 // Parameter for multihit TDC
	 Double_t tl_low, tl_high, tr_low, tr_high; // window for TL and TR
	 Double_t tlr_low, tlr_high; //window for TL-TR
};

#endif
