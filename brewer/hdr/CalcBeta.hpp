
#ifndef CalcBeta_hpp
#define CalcBeta_hpp

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
#include "CalcFL.hpp"

class CalcBeta
{
 public:
	 CalcBeta()
	 {
			offset = -9999.;

			for (Int_t i = 0; i < 4; i++)
			{
				 slew_factor[i] = 0.;
				 slew_pow[i] = 0.;
			}

			for (Int_t i = 0; i < 2; i++)
			{
				 LumiCorr[i] = 0.;
			}

			TL_start = 0;
			TR_start = 0;
			TL_stop = 0;
			TR_stop = 0;
			QL_start = 0;
			QR_start = 0;
			QL_stop = 0;
			QR_stop = 0;

			tstamp = 0;

			UseLR_Start = true;
			UseLR_Stop = true;

			clight = 299.792458;
			mnucleon = 931.49432;
			FL1 = 0;
			FL2 = 0;
			Brho1 = 0;
			Brho2 = 0;

			use_TwoBrho = false;
			mode_DiffQ = false;
	 };
	 ~CalcBeta() {};

	 void SetVariable(Variables *var)
	 {
			vars = var;
			calFL1.SetVariable(var);
			calFL2.SetVariable(var);
	 };

	 void SetStartTiming(std::string tl, std::string tr);
	 void SetStopTiming(std::string tl, std::string tr);
	 void SetStartCharge(std::string ql, std::string qr);
	 void SetStopCharge(std::string ql, std::string qr);

	 // UseLR_Start or UseLR_Stop will become false
	 void SetStartTiming(std::string t);
	 void SetStartCharge(std::string q);
	 void SetStopTiming(std::string t);
	 void SetStopCharge(std::string q);

	 void SetTimeStamp(std::string ts);
	 void SetBrho(std::string br1, std::string br2);

	 void SetTOF(std::string tof)
	 {
			vars->SetVariable(&TOF, tof);
	 };

	 void SetFLCenter(Double_t fl1, Double_t fl2)
	 {
			calFL1.SetFLCenter(fl1);
			calFL2.SetFLCenter(fl2);
	 };
	 void SetFLCenter(Double_t fl1)
	 {
			calFL1.SetFLCenter(fl1);
	 };

	 void SetPosAngDeltaFirstHalf(std::string x, std::string a, std::string y, std::string b, std::string del)
	 {
			calFL1.SetPosAngDelta(x, a, y, b, del);
	 };
	 void SetPosAngDeltaSecondHalf(std::string x, std::string a, std::string y, std::string b, std::string del)
	 {
			calFL2.SetPosAngDelta(x, a, y, b, del);
	 };

	 void SetDiffQ()
	 {
			mode_DiffQ = true;
	 };

	 void SetBeta(std::string b1, std::string b2)
	 {
			vars->SetVariable(&Beta1, b1);
			vars->SetVariable(&Beta2, b2);
	 };
	 void SetBeta(std::string b1)
	 {
			vars->SetVariable(&Beta1, b1);
	 };

	 void SetGamma(std::string g1, std::string g2)
	 {
			vars->SetVariable(&Gamma1, g1);
			vars->SetVariable(&Gamma2, g2);
	 };
	 void SetGamma(std::string g1)
	 {
			vars->SetVariable(&Gamma1, g1);
	 };

	 void SetFL(std::string l1, std::string l2)
	 {
			vars->SetVariable(&FL1, l1);
			vars->SetVariable(&FL2, l2);
	 };
	 void SetFL(std::string l1)
	 {
			vars->SetVariable(&FL1, l1);
	 };

	 Double_t GetTOF()
	 {
			return TOF;
	 };

	 Double_t GetBeta1()
	 {
			return Beta1;
	 };
	 Double_t GetBeta2()
	 {
			if (use_TwoBrho)
			{
				 return Beta2;
			}
			else
			{
				 return -9999.;
			}
	 };

	 void Clear() {};

	 void Calc();

	 void ReadParameters(std::string filename, Int_t run);

	 void ReadParameters(std::string filename1, std::string paradir, Int_t run)
	 {
			calFL1.ReadParameters(filename1, paradir, run);
	 };
	 void ReadParameters(std::string filename1, std::string filename2, std::string paradir, Int_t run)
	 {
			calFL1.ReadParameters(filename1, paradir, run);
			calFL2.ReadParameters(filename2, paradir, run);
	 };

 private:
	 Variables *vars;

	 // Input 1
	 Double_t *TL_start;
	 Double_t *TR_start;
	 Double_t *QL_start;
	 Double_t *QR_start;

	 Double_t *TL_stop;
	 Double_t *TR_stop;
	 Double_t *QL_stop;
	 Double_t *QR_stop;

	 Double_t *tstamp;

	 // Parameters 1
	 Double_t offset;

	 // True; readout from left and right, false; single readout (Values of L are used internally)
	 Bool_t UseLR_Start;
	 Bool_t UseLR_Stop;

	 // slewing correction
	 Double_t slew[4]; // = slew_factor[i] * pow( Q, slew_pow[i] )
	 Double_t slew_factor[4];
	 Double_t slew_pow[4];

	 Double_t LumiCorr[2];

	 // Output 1
	 Double_t TOF;

	 // Input 2
	 Double_t FL1, FL2;
	 CalcFL calFL1, calFL2;
	 Double_t *Brho1, *Brho2;
	 Int_t Q1, Q2;

	 // Parameters 2
	 Double_t clight; // mm/ns
	 Double_t mnucleon; // MeV

	 // Output 2
	 Double_t Beta1, Beta2;
	 Double_t Gamma1, Gamma2;

	 Bool_t use_TwoBrho;
	 Bool_t mode_DiffQ;
};

#endif
