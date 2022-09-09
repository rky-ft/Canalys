
#include "TArrayPla.hpp"

void TArrayPla::SetPlastic(Char_t *plaName1_xml, Char_t *plaName_toroot)
{
	 planame1_xml.push_back(std::string(plaName1_xml));
	 planame_toroot.push_back(std::string(plaName_toroot));
	 ref_xml.push_back(std::string(""));
	 use_MTDC.push_back(false);
	 use_FourPMTtype.push_back(false);

	 return;
};

void TArrayPla::SetPlastic(Char_t *plaName1_xml, Char_t *plaName2_xml, Char_t *plaName_toroot)
{
	 planame1_xml.push_back(std::string(plaName1_xml));
	 planame2_xml.push_back(std::string(plaName2_xml));
	 planame_toroot.push_back(std::string(plaName_toroot));
	 ref_xml.push_back(std::string(""));
	 use_MTDC.push_back(false);
	 use_FourPMTtype.push_back(true);

	 return;
};

void TArrayPla::MakeBranch()
{
	 pla_tl.resize(planame1_xml.size());
	 pla_tr.resize(planame1_xml.size());

	 pla_tlu.resize(planame1_xml.size());
	 pla_tld.resize(planame1_xml.size());
	 pla_tru.resize(planame1_xml.size());
	 pla_trd.resize(planame1_xml.size());

	 pla_nhit_tl.resize(planame1_xml.size());
	 pla_nhit_tr.resize(planame1_xml.size());

	 pla_ql.resize(planame1_xml.size());
	 pla_qr.resize(planame1_xml.size());

	 pla_qlu.resize(planame1_xml.size());
	 pla_qld.resize(planame1_xml.size());
	 pla_qru.resize(planame1_xml.size());
	 pla_qrd.resize(planame1_xml.size());

	 pla_zoffset.resize(planame1_xml.size());

	 for (Int_t i = 0; i < (Int_t)planame1_xml.size(); i++)
	 {
			if (!use_FourPMTtype[i])
			{
				 otree->Branch(Form("%s_tl", planame_toroot[i].c_str()), &(pla_tl[i]), Form("%s_tl/D", planame_toroot[i].c_str()));
				 otree->Branch(Form("%s_tr", planame_toroot[i].c_str()), &(pla_tr[i]), Form("%s_tr/D", planame_toroot[i].c_str()));

				 if (use_MTDC[i])
				 {
						otree->Branch(Form("%s_NhitTL", planame_toroot[i].c_str()), &(pla_nhit_tl[i]), Form("%s_NhitTL/I", planame_toroot[i].c_str()));
						otree->Branch(Form("%s_NhitTR", planame_toroot[i].c_str()), &(pla_nhit_tr[i]), Form("%s_NhitTR/I", planame_toroot[i].c_str()));
						otree->Branch(Form("%s_multiTL", planame_toroot[i].c_str()), pla_mul_tl[i], Form("%s_multiTL[%s_NhitTL]/D", planame_toroot[i].c_str(), planame_toroot[i].c_str()));
						otree->Branch(Form("%s_multiTR", planame_toroot[i].c_str()), pla_mul_tr[i], Form("%s_multiTR[%s_NhitTR]/D", planame_toroot[i].c_str(), planame_toroot[i].c_str()));
				 }

				 otree->Branch(Form("%s_ql", planame_toroot[i].c_str()), &(pla_ql[i]), Form("%s_ql/I", planame_toroot[i].c_str()));
				 otree->Branch(Form("%s_qr", planame_toroot[i].c_str()), &(pla_qr[i]), Form("%s_qr/I", planame_toroot[i].c_str()));
			}
			else
			{
				 otree->Branch(Form("%s_tlu", planame_toroot[i].c_str()), &(pla_tlu[i]), Form("%s_tlu/D", planame_toroot[i].c_str()));
				 otree->Branch(Form("%s_tld", planame_toroot[i].c_str()), &(pla_tld[i]), Form("%s_tld/D", planame_toroot[i].c_str()));
				 otree->Branch(Form("%s_tru", planame_toroot[i].c_str()), &(pla_tru[i]), Form("%s_tru/D", planame_toroot[i].c_str()));
				 otree->Branch(Form("%s_trd", planame_toroot[i].c_str()), &(pla_trd[i]), Form("%s_trd/D", planame_toroot[i].c_str()));

				 otree->Branch(Form("%s_qlu", planame_toroot[i].c_str()), &(pla_qlu[i]), Form("%s_qlu/I", planame_toroot[i].c_str()));
				 otree->Branch(Form("%s_qld", planame_toroot[i].c_str()), &(pla_qld[i]), Form("%s_qld/I", planame_toroot[i].c_str()));
				 otree->Branch(Form("%s_qru", planame_toroot[i].c_str()), &(pla_qru[i]), Form("%s_qru/I", planame_toroot[i].c_str()));
				 otree->Branch(Form("%s_qrd", planame_toroot[i].c_str()), &(pla_qrd[i]), Form("%s_qrd/I", planame_toroot[i].c_str()));
			}

			otree->Branch(Form("%s_zoffset", planame_toroot[i].c_str()), &(pla_zoffset[i]), Form("%s_zoffset/D", planame_toroot[i].c_str()));
	 }
};

void TArrayPla::Clear()
{
	 for (Int_t i = 0; i < (Int_t)planame1_xml.size(); i++)
	 {
			pla_tl[i] = -9999.;
			pla_tr[i] = -9999.;

			pla_tlu[i] = -9999.;
			pla_tld[i] = -9999.;
			pla_tru[i] = -9999.;
			pla_trd[i] = -9999.;

			pla_nhit_tl[i] = 0;
			pla_nhit_tr[i] = 0;
			for (Int_t j = 0; j < 50; j++)
			{
				 pla_mul_tl[i][j] = -9999.;
				 pla_mul_tr[i][j] = -9999.;
			}

			pla_ql[i] = -9999;
			pla_qr[i] = -9999;

			pla_qlu[i] = -9999;
			pla_qld[i] = -9999;
			pla_qru[i] = -9999;
			pla_qrd[i] = -9999;

			pla_zoffset[i] = -9999.;
	 }
};

void TArrayPla::CopyVal()
{
	 TArtPlastic *pla;
	 Double_t t_ref;
	 for (Int_t i = 0; i < (Int_t)planame1_xml.size(); i++)
	 {
			t_ref = 0.;
			pla = cpla->FindPlastic((Char_t *)ref_xml[i].c_str());
			if (pla)
			{
				 t_ref = pla->GetTimeL() - 50000; // Trigger
			}

			pla = cpla->FindPlastic((Char_t *)planame1_xml[i].c_str());
			if (pla)
			{
				 if (!use_FourPMTtype[i])
				 {
						if (pla->GetTimeL() > 0)
						{
							 pla_tl[i] = pla->GetTimeL(); // - t_ref;
						}
						if (pla->GetTimeR() > 0)
						{
							 pla_tr[i] = pla->GetTimeR(); // - t_ref;
						}

						if (use_MTDC[i]) // test
						{
							 pla_nhit_tl[i] = pla->GetNHitL();
							 pla_nhit_tr[i] = pla->GetNHitR();
							 for (Int_t j = 0; j < pla->GetNHitL(); j++)
							 {
									pla_mul_tl[i][j] = pla->GetMulHitTDCL(j) * pla->GetTCalLeft(); // - t_ref;
							 }
							 for (Int_t j = 0; j < pla->GetNHitR(); j++)
							 {
									pla_mul_tr[i][j] = pla->GetMulHitTDCR(j) * pla->GetTCalRight(); // - t_ref;
							 }
						}

						if (pla->GetQLRaw() > 0)
						{
							 pla_ql[i] = pla->GetQLRaw();
						}
						if (pla->GetQRRaw() > 0)
						{
							 pla_qr[i] = pla->GetQRRaw();
						}
				 }
				 else // left side pmts
				 {
						if (pla->GetTimeL() > 0)
						{
							 pla_tlu[i] = pla->GetTimeL(); // - t_ref;
						}
						if (pla->GetTimeR() > 0)
						{
							 pla_tld[i] = pla->GetTimeR(); // - t_ref;
						}

						if (pla->GetQLRaw() > 0)
						{
							 pla_qlu[i] = pla->GetQLRaw();
						}
						if (pla->GetQRRaw() > 0)
						{
							 pla_qld[i] = pla->GetQRRaw();
						}
				 }
			}

			if (use_FourPMTtype[i]) // right side pmts
			{
				 pla = cpla->FindPlastic((Char_t *)planame2_xml[i].c_str());
				 if (pla)
				 {
						if (pla->GetTimeL() > 0)
						{
							 pla_tru[i] = pla->GetTimeL(); // - t_ref;
						}
						if (pla->GetTimeR() > 0)
						{
							 pla_trd[i] = pla->GetTimeR(); // - t_ref;
						}

						if (pla->GetQLRaw() > 0)
						{
							 pla_qru[i] = pla->GetQLRaw();
						}
						if (pla->GetQRRaw() > 0)
						{
							 pla_qrd[i] = pla->GetQRRaw();
						}
				 }
			}

			pla_zoffset[i] = pla->GetZoffset();
	 }
}
