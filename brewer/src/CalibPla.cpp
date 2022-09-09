
#include <CalibPla.hpp>
#define CalibPla_cpp

void CalibPla::SetPlastic(Char_t *pla, Bool_t multi)
{
	 //itree->SetBranchAddress("tstamp", &tstamp);

	 use_MTDC = multi;
	 itree->SetBranchAddress(Form("%s_tl", pla), &TL);
	 itree->SetBranchAddress(Form("%s_tr", pla), &TR);

	 if (use_MTDC) // Multihit TDC
	 {
			itree->SetBranchAddress(Form("%s_NhitTL", pla), &NhitTL);
			itree->SetBranchAddress(Form("%s_NhitTR", pla), &NhitTR);
			itree->SetBranchAddress(Form("%s_multiTL", pla), multiTL);
			itree->SetBranchAddress(Form("%s_multiTR", pla), multiTR);
	 }

	 itree->SetBranchAddress(Form("%s_ql", pla), &QL);
	 itree->SetBranchAddress(Form("%s_qr", pla), &QR);

	 vars->SetVariable(&TL, Form("%s_tl", pla));
	 vars->SetVariable(&TR, Form("%s_tr", pla));
	 vars->SetVariable(&TM, Form("%s_tm", pla));
	 vars->SetVariable(&TD, Form("%s_td", pla));
	 vars->SetVariable(&X, Form("%s_x", pla));

	 if (use_MTDC && !use_FourPMTtype)
	 {
			vars->SetVariable(&nhitTL, Form("%s_nhitTL", pla));
			vars->SetVariable(&nhitTR, Form("%s_nhitTR", pla));
			vars->SetVariable(&nhitTLR, Form("%s_nhitTLR", pla));
			vars->SetVariable(&TLforward, Form("%s_TLforward", pla));
			vars->SetVariable(&TLbackward, Form("%s_TLbackward", pla));
			vars->SetVariable(&TRforward, Form("%s_TRforward", pla));
			vars->SetVariable(&TRbackward, Form("%s_TRbackward", pla));
			vars->SetVariable(&TLRforward, Form("%s_TLRforward", pla));
			vars->SetVariable(&TLRbackward, Form("%s_TLRbackward", pla));
	 }

	 vars->SetVariable(&QLA, Form("%s_ql", pla));
	 vars->SetVariable(&QRA, Form("%s_qr", pla));
	 vars->SetVariable(&QA, Form("%s_qa", pla));
	 vars->SetVariable(&QD, Form("%s_qd", pla));
	 vars->SetVariable(&dE, Form("%s_de", pla));

	 return;
}

void CalibPla::Set4PMTsPlastic(Char_t *pla)
{
	 use_FourPMTtype = true;

	 itree->SetBranchAddress(Form("%s_tlu", pla), &TLU);
	 itree->SetBranchAddress(Form("%s_tld", pla), &TLD);
	 itree->SetBranchAddress(Form("%s_tru", pla), &TRU);
	 itree->SetBranchAddress(Form("%s_trd", pla), &TRD);

	 itree->SetBranchAddress(Form("%s_qlu", pla), &QLU);
	 itree->SetBranchAddress(Form("%s_qld", pla), &QLD);
	 itree->SetBranchAddress(Form("%s_qru", pla), &QRU);
	 itree->SetBranchAddress(Form("%s_qrd", pla), &QRD);

	 vars->SetVariable(&TLU, Form("%s_tlu", pla));
	 vars->SetVariable(&TLD, Form("%s_tld", pla));
	 vars->SetVariable(&TLM, Form("%s_tlm", pla));
	 vars->SetVariable(&TRU, Form("%s_tru", pla));
	 vars->SetVariable(&TRD, Form("%s_trd", pla));
	 vars->SetVariable(&TRM, Form("%s_trm", pla));
	 vars->SetVariable(&TM, Form("%s_tm", pla));
	 vars->SetVariable(&TD, Form("%s_td", pla));
	 vars->SetVariable(&X, Form("%s_x", pla));

	 vars->SetVariable(&QLU, Form("%s_qlu", pla));
	 vars->SetVariable(&QLD, Form("%s_qld", pla));
	 vars->SetVariable(&QLA, Form("%s_qla", pla));
	 vars->SetVariable(&QRU, Form("%s_qru", pla));
	 vars->SetVariable(&QRD, Form("%s_qrd", pla));
	 vars->SetVariable(&QRA, Form("%s_qra", pla));
	 vars->SetVariable(&QA, Form("%s_qa", pla));
	 vars->SetVariable(&QD, Form("%s_qd", pla));
	 vars->SetVariable(&dE, Form("%s_de", pla));

	 return;
}

void CalibPla::Calc()
{
	 if (!use_FourPMTtype)
	 {
			TLM = TL;
			TRM = TR;
			if (use_MTDC) // Multihit TDC
			{
				 multi.SetMultihitTLR(multiTL, multiTR, NhitTL, NhitTR);
				 multi.SetTimeWindowLR(tl_low, tl_high, tr_low, tr_high, tlr_low, tlr_high);
				 multi.Calc();
				 multi.GetTLR(TL, TR);
				 multi.GetForwardBackwardLR(TLforward, TLbackward, TRforward, TRbackward, TLRforward, TLRbackward);
			}
			QLA = QL - pedestal[0];
			QRA = QR - pedestal[1];
	 }
	 else // ImPACT Pla
	 {
			TLM = (TLU + TLD) / 2;
			TRM = (TRU + TRD) / 2;

			QLA = sqrt((QLU - pedestal[0]) * (QLD - pedestal[1]));
			QRA = sqrt((QRU - pedestal[2]) * (QRD - pedestal[3]));
	 }

	 if (TLM != -9999 && TRM != -9999)
	 {
			TM = (TLM + TRM) / 2;
			TD = TRM - TLM;
	 }

	 if (QLA > 0 && QRA > 0)
	 {
			QA = sqrt(QLA * QRA);
			QD = log(QLA / QRA);
			if (QA != -9999)
			{
				 dE = ch2MeV[0] + ch2MeV[1] * QA + ch2MeV[2] * QA * QA;
			}
	 }

	 if (TD != -9999 && grTDtoX.GetN() > 2)
	 {
			X = grTDtoX.Eval(TD);
	 }

	 return;
};

void CalibPla::ReadParameters(const Char_t *filename, std::string paradir, Int_t run)
{
	 ReadPara rp;
	 std::string parameterlist;
	 Int_t size;

	 parameterlist = rp.ReadParameterList((paradir + "/" + std::string(filename)).c_str(), run, "PlasticPosition");
	 size = parameterlist.size();
	 if (size > 0)
	 {
			std::stringstream ss0;
			Char_t file[64];
			ss0 << parameterlist;
			ss0 >> file;
			ReadParameters(file, paradir);
	 }

	 parameterlist = rp.ReadParameterList((paradir + "/" + std::string(filename)).c_str(), run, "Pedestal");
	 size = parameterlist.size();
	 if (size > 0)
	 {
			std::stringstream ss1;
			ss1 << parameterlist;
			for (Int_t i = 0; i < 4; i++)
			{
				 ss1 >> pedestal[i];
			}
	 }

	 parameterlist = rp.ReadParameterList((paradir + "/" + std::string(filename)).c_str(), run, "Ch2MeV");
	 size = parameterlist.size();
	 if (size > 0)
	 {
			std::stringstream ss2;
			ss2 << parameterlist;
			for (Int_t j = 0; j < 2; j++)
			{
				 ss2 >> ch2MeV[j];
			}
	 }

	 parameterlist = rp.ReadParameterList((paradir + "/" + std::string(filename)).c_str(), run, "MultiWindow");
	 size = parameterlist.size();
	 if (size > 0)
	 {
			std::stringstream ss3;
			ss3 << parameterlist;
			ss3 >> tl_low >> tl_high >> tr_low >> tr_high >> tlr_low >> tlr_high;
	 }

	 return;
};

void CalibPla::ReadParameters(const Char_t *filename, std::string paradir)
{
	 grTDtoX = TGraph((paradir + "/" + std::string(filename)).c_str());

	 return;
};
