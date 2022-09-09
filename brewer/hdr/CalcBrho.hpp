
#ifndef CalcBrho_hpp
#define CalcBrho_hpp

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <TROOT.h>
#include <TMath.h>
#include <TMatrixD.h>

#include "SetPara.hpp"
#include "Variables.hpp"

class CalcBrho
{
 public:
	 CalcBrho()
	 {
			CenterBrho = -9999;
			mat.ResizeTo(83, 5);
			vec0.ResizeTo(2, 1);
			vec1.ResizeTo(2, 1);
			func_drv.ResizeTo(2, 2);
			func.ResizeTo(2, 1);
			Xidummy = 0;
			Yidummy = 0;
			Bidummy = 0;
			Xfdummy = 0;
			Afdummy = 0;
			Xi = &Xidummy;
			Yi = &Yidummy;
			Bi = &Bidummy;
			Xf = &Xfdummy;
			Af = &Afdummy;
			fCalculated = false;
			use_YB = true;
	 };
	 ~CalcBrho() {};

	 void SetVariable(Variables *var)
	 {
			vars = var;
	 };

	 void SetInitialPosAng(std::string xi, std::string yi, std::string bi);
	 void SetInitialPos(std::string xi);

	 void SetFinalPosAng(std::string xf, std::string af);
	 void SetFinalPos(std::string xf);

	 void SetCenterBrho(Double_t cbr);

	 void SetDelta(std::string del)
	 {
			vars->SetVariable(&Delta, del);
	 };

	 void SetRecoAngle(std::string ang)
	 {
			vars->SetVariable(&Ai, ang);
	 };

	 void SetBrho(std::string br)
	 {
			vars->SetVariable(&Brho, br);
	 };

	 Double_t GetDelta()
	 {
			return Delta;
	 };
	 Double_t GetReconstructedAngle()
	 {
			return Ai;
	 };
	 Double_t GetEpsilon()
	 {
			return epsilon;
	 };
	 Int_t GetNIta()
	 {
			return nita;
	 };
	 Bool_t Is_Converged()
	 {
			return fCalculated;
	 };

	 void Clear()
	 {
			Delta = -9999.;
			Ai = -9999.;
			fCalculated = false;
			use_YB = true;
	 };

	 void Calc();
	 void CalcFirstOrder(Double_t &delta1, Double_t &ai1); // Calculation within firstorder of X, A

	 void ReadParameters(std::string filename, std::string paradir);
	 void ReadParameters(std::string filename, std::string paradir, Int_t run);

 private:
	 Variables *vars;

	 // A: angle of X direction, B: angle of Y direction
	 // input of reconstruction
	 Double_t *Xi, *Yi, *Bi;
	 Double_t *Xf, *Af;

	 Double_t Yidummy, Bidummy, Afdummy; // always 0 for use of Plastic_position
	 Double_t Xidummy, Xfdummy;

	 // output of reconstruction
	 Double_t Ai;
	 Double_t Delta; // ( p - p_0 ) / p_0
	 Double_t Brho;

	 // internal values
	 TMatrixD mat; // optical matrix elements
	 Int_t nita;
	 Double_t epsilon;
	 TMatrixD vec0, vec1, func_drv, func;
	 Double_t CenterBrho;

	 Bool_t fCalculated;
	 Bool_t use_YB;
};

#endif
