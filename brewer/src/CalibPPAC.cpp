
#include <CalibPPAC.hpp>
#define CalibPPAC_cpp

void CalibPPAC::SetPPAC(Char_t *ppac1a, Char_t *ppac1b, Char_t *ppac2a, Char_t *ppac2b, Char_t *fplname)
{
	 itree->SetBranchAddress(Form("%s_x", ppac1a), &X_1A);
	 itree->SetBranchAddress(Form("%s_y", ppac1a), &Y_1A);
	 itree->SetBranchAddress(Form("%s_tsumx", ppac1a), &TSUMX_1A);
	 itree->SetBranchAddress(Form("%s_tsumy", ppac1a), &TSUMY_1A);
	 itree->SetBranchAddress(Form("%s_zposx", ppac1a), &Z_1AX);
	 itree->SetBranchAddress(Form("%s_zposy", ppac1a), &Z_1AY);
	 itree->SetBranchAddress(Form("%s_ta", ppac1a), &TA_1A);

	 itree->SetBranchAddress(Form("%s_x", ppac1b), &X_1B);
	 itree->SetBranchAddress(Form("%s_y", ppac1b), &Y_1B);
	 itree->SetBranchAddress(Form("%s_tsumx", ppac1b), &TSUMX_1B);
	 itree->SetBranchAddress(Form("%s_tsumy", ppac1b), &TSUMY_1B);
	 itree->SetBranchAddress(Form("%s_zposx", ppac1b), &Z_1BX);
	 itree->SetBranchAddress(Form("%s_zposy", ppac1b), &Z_1BY);
	 itree->SetBranchAddress(Form("%s_ta", ppac1b), &TA_1B);

	 itree->SetBranchAddress(Form("%s_x", ppac2a), &X_2A);
	 itree->SetBranchAddress(Form("%s_y", ppac2a), &Y_2A);
	 itree->SetBranchAddress(Form("%s_tsumx", ppac2a), &TSUMX_2A);
	 itree->SetBranchAddress(Form("%s_tsumy", ppac2a), &TSUMY_2A);
	 itree->SetBranchAddress(Form("%s_zposx", ppac2a), &Z_2AX);
	 itree->SetBranchAddress(Form("%s_zposy", ppac2a), &Z_2AY);
	 itree->SetBranchAddress(Form("%s_ta", ppac2a), &TA_2A);

	 itree->SetBranchAddress(Form("%s_x", ppac2b), &X_2B);
	 itree->SetBranchAddress(Form("%s_y", ppac2b), &Y_2B);
	 itree->SetBranchAddress(Form("%s_tsumx", ppac2b), &TSUMX_2B);
	 itree->SetBranchAddress(Form("%s_tsumy", ppac2b), &TSUMY_2B);
	 itree->SetBranchAddress(Form("%s_zposx", ppac2b), &Z_2BX);
	 itree->SetBranchAddress(Form("%s_zposy", ppac2b), &Z_2BY);
	 itree->SetBranchAddress(Form("%s_ta", ppac2b), &TA_2B);

	 vars->SetVariable(&X, Form("%sx", fplname));
	 vars->SetVariable(&A, Form("%sa", fplname));
	 vars->SetVariable(&Y, Form("%sy", fplname));
	 vars->SetVariable(&B, Form("%sb", fplname));
	 vars->SetVariable(&TM, Form("%sppac_tm", fplname));

	 flags->SetFlag(flagTSumX, Form("flag%stsumx", fplname), 5, true);
	 flags->SetFlag(flagTSumY, Form("flag%stsumy", fplname), 5, true);

	 return;
}

void CalibPPAC::Set3rdPPAC(Char_t *ppac3a, Char_t *ppac3b, Char_t *fplname)
{
	 itree->SetBranchAddress(Form("%s_x", ppac3a), &X_3A);
	 itree->SetBranchAddress(Form("%s_y", ppac3a), &Y_3A);
	 itree->SetBranchAddress(Form("%s_tsumx", ppac3a), &TSUMX_3A);
	 itree->SetBranchAddress(Form("%s_tsumy", ppac3a), &TSUMY_3A);
	 itree->SetBranchAddress(Form("%s_zposx", ppac3a), &Z_3AX);
	 itree->SetBranchAddress(Form("%s_zposy", ppac3a), &Z_3AY);
	 itree->SetBranchAddress(Form("%s_ta", ppac3a), &TA_3A);

	 itree->SetBranchAddress(Form("%s_x", ppac3b), &X_3B);
	 itree->SetBranchAddress(Form("%s_y", ppac3b), &Y_3B);
	 itree->SetBranchAddress(Form("%s_tsumx", ppac3b), &TSUMX_3B);
	 itree->SetBranchAddress(Form("%s_tsumy", ppac3b), &TSUMY_3B);
	 itree->SetBranchAddress(Form("%s_zposx", ppac3b), &Z_3BX);
	 itree->SetBranchAddress(Form("%s_zposy", ppac3b), &Z_3BY);
	 itree->SetBranchAddress(Form("%s_ta", ppac3b), &TA_3B);

	 vars->SetVariable(&Aout, Form("%sta", fplname));
	 vars->SetVariable(&Bout, Form("%stb", fplname));

	 flags->SetFlag(flag3rdTSumX, Form("flag3rd%stsumx", fplname), 3, true);
	 flags->SetFlag(flag3rdTSumY, Form("flag3rd%stsumy", fplname), 3, true);

	 use_3rdPPAC = true;

	 return;
};

void CalibPPAC::SetPlasticZoffset(Char_t *planame, Char_t *fplname)
{
	 calc_Xonpla = true;
	 itree->SetBranchAddress(Form("%s_zoffset", planame), &Pla_zoffset);
	 vars->SetVariable(&XonPla, Form("%sx_pla", fplname));

	 return;
};

void CalibPPAC::ReadParameters(const Char_t *filename, Int_t run)
{
	 ReadPara rp;
	 std::string parameterlist;
	 Int_t size;

	 parameterlist = rp.ReadParameterList(filename, run, "TSumX");
	 size = parameterlist.size();
	 if (size > 0)
	 {
			std::stringstream ss1;
			ss1 << parameterlist;
			ss1 >> TSUMX_MIN_1A >> TSUMX_MAX_1A >> TSUMX_MIN_1B >> TSUMX_MAX_1B;
			ss1 >> TSUMX_MIN_2A >> TSUMX_MAX_2A >> TSUMX_MIN_2B >> TSUMX_MAX_2B;
			if (use_3rdPPAC)
			{
				 ss1 >> TSUMX_MIN_3A >> TSUMX_MAX_3A >> TSUMX_MIN_3B >> TSUMX_MAX_3B;
			}
	 }

	 parameterlist = rp.ReadParameterList(filename, run, "TSumY");
	 size = parameterlist.size();
	 if (size > 0)
	 {
			std::stringstream ss2;
			ss2 << parameterlist;
			ss2 >> TSUMY_MIN_1A >> TSUMY_MAX_1A >> TSUMY_MIN_1B >> TSUMY_MAX_1B;
			ss2 >> TSUMY_MIN_2A >> TSUMY_MAX_2A >> TSUMY_MIN_2B >> TSUMY_MAX_2B;
			if (use_3rdPPAC)
			{
				 ss2 >> TSUMY_MIN_3A >> TSUMY_MAX_3A >> TSUMY_MIN_3B >> TSUMY_MAX_3B;
			}
	 }

	 parameterlist = rp.ReadParameterList(filename, run, "Offset");
	 size = parameterlist.size();
	 if (size > 0)
	 {
			std::stringstream ss3;
			ss3 << parameterlist;
			ss3 >> TAoffset_1A >> TAoffset_1B;
			ss3 >> TAoffset_2A >> TAoffset_2B;
			if (use_3rdPPAC)
			{
				 ss3 >> TAoffset_3A >> TAoffset_3B;
			}
	 }

	 parameterlist = rp.ReadParameterList(filename, run, "ZShift");
	 size = parameterlist.size();
	 if (size > 0)
	 {
			std::stringstream ss4;
			ss4 << parameterlist;
			ss4 >> zshift;
	 }

	 return;
};

void CalibPPAC::Calc()
{
	 TMatrixD xvec(2, 1);
	 xvec.Zero();
	 TMatrixD yvec(2, 1);
	 yvec.Zero();
	 TMatrixD xmat(2, 2);
	 xmat.Zero();
	 TMatrixD ymat(2, 2);
	 ymat.Zero();

	 flagTSumX[0] = true;
	 flagTSumY[0] = true;

	 Bool_t fired_1ax = true;
	 Bool_t fired_1bx = true;
	 Bool_t fired_2ax = true;
	 Bool_t fired_2bx = true;
	 Bool_t fired_1ay = true;
	 Bool_t fired_1by = true;
	 Bool_t fired_2ay = true;
	 Bool_t fired_2by = true;

	 if (TSUMX_1A < TSUMX_MIN_1A || TSUMX_1A > TSUMX_MAX_1A)
	 {
			fired_1ax = false;
	 }
	 if (TSUMX_1B < TSUMX_MIN_1B || TSUMX_1B > TSUMX_MAX_1B)
	 {
			fired_1bx = false;
	 }
	 if (TSUMX_2A < TSUMX_MIN_2A || TSUMX_2A > TSUMX_MAX_2A)
	 {
			fired_2ax = false;
	 }
	 if (TSUMX_2B < TSUMX_MIN_2B || TSUMX_2B > TSUMX_MAX_2B)
	 {
			fired_2bx = false;
	 }

	 if (TSUMY_1A < TSUMY_MIN_1A || TSUMY_1A > TSUMY_MAX_1A)
	 {
			fired_1ay = false;
	 }
	 if (TSUMY_1B < TSUMY_MIN_1B || TSUMY_1B > TSUMY_MAX_1B)
	 {
			fired_1by = false;
	 }
	 if (TSUMY_2A < TSUMY_MIN_2A || TSUMY_2A > TSUMY_MAX_2A)
	 {
			fired_2ay = false;
	 }
	 if (TSUMY_2B < TSUMY_MIN_2B || TSUMY_2B > TSUMY_MAX_2B)
	 {
			fired_2by = false;
	 }

	 flagTSumX[1] = (Int_t)fired_1ax;
	 flagTSumX[2] = (Int_t)fired_1bx;
	 flagTSumX[3] = (Int_t)fired_2ax;
	 flagTSumX[4] = (Int_t)fired_2bx;
	 flagTSumY[1] = (Int_t)fired_1ay;
	 flagTSumY[2] = (Int_t)fired_1by;
	 flagTSumY[3] = (Int_t)fired_2ay;
	 flagTSumY[4] = (Int_t)fired_2by;

	 if (!(fired_1ax || fired_1bx))
	 {
			//std::cout << !(fired_1ax || fired_1bx) << std::endl;
			flagTSumX[0] = false;
	 }
	 if (!(fired_2ax || fired_2bx))
	 {
			flagTSumX[0] = false;
	 }
	 if (!(fired_1ay || fired_1by))
	 {
			flagTSumY[0] = false;
	 }
	 if (!(fired_2ay || fired_2by))
	 {
			flagTSumY[0] = false;
	 }

	 if (flagTSumX[0])
	 {
			if (fired_1ax)
			{
				 //std::cout << "fired_1ax = " << fired_1ax << std::endl;
				 AddPoint(xvec, xmat, X_1A, Z_1AX);
			}
			if (fired_1bx)
			{
				 AddPoint(xvec, xmat, X_1B, Z_1BX);
			}
			if (fired_2ax)
			{
				 AddPoint(xvec, xmat, X_2A, Z_2AX);
			}
			if (fired_2bx)
			{
				 AddPoint(xvec, xmat, X_2B, Z_2BX);
			}

			TMatrixD rxvec = xmat.Invert() * xvec;
			X = rxvec(1, 0) + zshift * rxvec(0, 0); // rxvec(0,0) = Tan(A/1000)
			A = atan(rxvec(0, 0)) * 1000; // mrad
	 }
	 else
	 {
			X = -9999.;
			A = -9999.;
	 }

	 if (flagTSumY[0])
	 {
			if (fired_1ay)
			{
				 AddPoint(yvec, ymat, Y_1A, Z_1AY);
			}
			if (fired_1by)
			{
				 AddPoint(yvec, ymat, Y_1B, Z_1BY);
			}
			if (fired_2ay)
			{
				 AddPoint(yvec, ymat, Y_2A, Z_2AY);
			}
			if (fired_2by)
			{
				 AddPoint(yvec, ymat, Y_2B, Z_2BY);
			}

			TMatrixD ryvec = ymat.Invert() * yvec;
			Y = ryvec(1, 0) + zshift * ryvec(0, 0); // ryvec(0, 0) = Tan(B/1000)
			B = atan(ryvec(0, 0)) * 1000; // mrad
	 }
	 else
	 {
			Y = -9999.;
			B = -9999.;
	 }

	 // anode timing
	 Int_t nfired = 0;
	 Double_t TM_tmp = 0.;
	 if (fired_1ax || fired_1ay)
	 {
			TM_tmp += TA_1A + TAoffset_1A;
			nfired++;
	 }
	 if (fired_1bx || fired_1by)
	 {
			TM_tmp += TA_1B + TAoffset_1B;
			nfired++;
	 }
	 if (fired_2ax || fired_2ay)
	 {
			TM_tmp += TA_2A + TAoffset_2A;
			nfired++;
	 }
	 if (fired_2bx || fired_2by)
	 {
			TM_tmp += TA_2B + TAoffset_2B;
			nfired++;
	 }
	 if (nfired > 0)
	 {
			TM = TM_tmp / nfired;
	 }

	 if (calc_Xonpla && A != -9999)
	 {
			XonPla = X + Pla_zoffset * tan(A / 1000.);
	 }

	 if (use_3rdPPAC)
	 {
			Calc3rdPPAC();
	 }

	 return;
};

void CalibPPAC::Calc3rdPPAC()
{
	 TMatrixD xvec(2, 1);
	 xvec.Zero();
	 TMatrixD yvec(2, 1);
	 yvec.Zero();
	 TMatrixD xmat(2, 2);
	 xmat.Zero();
	 TMatrixD ymat(2, 2);
	 ymat.Zero();

	 flag3rdTSumX[0] = true;
	 flag3rdTSumY[0] = true;

	 Bool_t fired_3ax = true;
	 Bool_t fired_3bx = true;
	 Bool_t fired_3ay = true;
	 Bool_t fired_3by = true;

	 if (TSUMX_3A < TSUMX_MIN_3A || TSUMX_3A > TSUMX_MAX_3A)
	 {
			fired_3ax = false;
	 }
	 if (TSUMX_3B < TSUMX_MIN_3B || TSUMX_3B > TSUMX_MAX_3B)
	 {
			fired_3bx = false;
	 }
	 if (TSUMY_3A < TSUMY_MIN_3A || TSUMY_3A > TSUMY_MAX_3A)
	 {
			fired_3ay = false;
	 }
	 if (TSUMY_3B < TSUMY_MIN_3B || TSUMY_3B > TSUMY_MAX_3B)
	 {
			fired_3by = false;
	 }

	 flag3rdTSumX[1] = (Int_t)fired_3ax;
	 flag3rdTSumX[2] = (Int_t)fired_3bx;
	 flag3rdTSumY[1] = (Int_t)fired_3ay;
	 flag3rdTSumY[2] = (Int_t)fired_3by;

	 if (!(fired_3ax || fired_3bx))
	 {
			flag3rdTSumX[0] = false;
	 }
	 if (!(fired_3ay || fired_3by))
	 {
			flag3rdTSumY[0] = false;
	 }

	 if (flagTSumX[0] && flag3rdTSumX[0])
	 {
			AddPoint(xvec, xmat, X, zshift);
			if (fired_3ax)
			{
				 AddPoint(xvec, xmat, X_3A, Z_3AX);
			}
			if (fired_3bx)
			{
				 AddPoint(xvec, xmat, X_3B, Z_3BX);
			}

			TMatrixD rxvec = xmat.Invert() * xvec;
			Aout = atan(rxvec(0, 0)) * 1000; // mrad
	 }
	 else
	 {
			Aout = -9999.;
	 }

	 if (flagTSumY[0] && flag3rdTSumY[0])
	 {
			AddPoint(yvec, ymat, Y, zshift);
			if (fired_3ay)
			{
				 AddPoint(yvec, ymat, Y_3A, Z_3AY);
			}
			if (fired_3by)
			{
				 AddPoint(yvec, ymat, Y_3B, Z_3BY);
			}

			TMatrixD ryvec = ymat.Invert() * yvec;
			Bout = atan(ryvec(0, 0)) * 1000; // mrad
	 }
	 else
	 {
			Bout = -9999.;
	 }

	 return;
};

void CalibPPAC::AddPoint(TMatrixD &vec, TMatrixD &mat, Double_t x, Double_t z)
{
	 vec(0, 0) += z * x;
	 vec(1, 0) += x;
	 mat(0, 1) += z;
	 mat(1, 0) += z;
	 mat(0, 0) += z * z;
	 mat(1, 1)++;

	 return;
};
