
#include "TArrayPPAC.hpp"

void TArrayPPAC::SetPPAC(Char_t *ppacName_xml, Char_t *ppacName_toroot)
{
	 ppacname_xml.push_back(std::string(ppacName_xml));
	 ppacname_toroot.push_back(std::string(ppacName_toroot));
	 ref_xml.push_back(std::string(""));

	 return;
};
void TArrayPPAC::SetPPAC(Char_t *ppacName_xml, Char_t *Ref_xml, Char_t *ppacName_toroot)
{
	 ppacname_xml.push_back(std::string(ppacName_xml));
	 ppacname_toroot.push_back(std::string(ppacName_toroot));
	 ref_xml.push_back(std::string(Ref_xml));

	 return;
};

void TArrayPPAC::MakeBranch()
{
	 ppac_x.resize(ppacname_xml.size());
	 ppac_y.resize(ppacname_xml.size());
	 ppac_tsumx.resize(ppacname_xml.size());
	 ppac_tsumy.resize(ppacname_xml.size());
	 ppac_xzpos.resize(ppacname_xml.size());
	 ppac_yzpos.resize(ppacname_xml.size());
	 ppac_ta.resize(ppacname_xml.size());
	 for (Int_t i = 0; i < (Int_t)ppacname_xml.size(); i++)
	 {
			otree->Branch(Form("%s_x", ppacname_toroot[i].c_str()), &(ppac_x[i]), Form("%s_x/D", ppacname_toroot[i].c_str()));
	 }
	 for (Int_t i = 0; i < (Int_t)ppacname_xml.size(); i++)
	 {
			otree->Branch(Form("%s_y", ppacname_toroot[i].c_str()), &(ppac_y[i]), Form("%s_y/D", ppacname_toroot[i].c_str()));
	 }
	 for (Int_t i = 0; i < (Int_t)ppacname_xml.size(); i++)
	 {
			otree->Branch(Form("%s_tsumx", ppacname_toroot[i].c_str()), &(ppac_tsumx[i]), Form("%s_tsumx/D", ppacname_toroot[i].c_str()));
	 }
	 for (Int_t i = 0; i < (Int_t)ppacname_xml.size(); i++)
	 {
			otree->Branch(Form("%s_tsumy", ppacname_toroot[i].c_str()), &(ppac_tsumy[i]), Form("%s_tsumy/D", ppacname_toroot[i].c_str()));
	 }
	 for (Int_t i = 0; i < (Int_t)ppacname_xml.size(); i++)
	 {
			otree->Branch(Form("%s_zposx", ppacname_toroot[i].c_str()), &(ppac_xzpos[i]), Form("%s_zposx/D", ppacname_toroot[i].c_str()));
	 }
	 for (Int_t i = 0; i < (Int_t)ppacname_xml.size(); i++)
	 {
			otree->Branch(Form("%s_zposy", ppacname_toroot[i].c_str()), &(ppac_yzpos[i]), Form("%s_zposy/D", ppacname_toroot[i].c_str()));
	 }
	 for (Int_t i = 0; i < (Int_t)ppacname_xml.size(); i++)
	 {
			otree->Branch(Form("%s_ta", ppacname_toroot[i].c_str()), &(ppac_ta[i]), Form("%s_ta/D", ppacname_toroot[i].c_str()));
	 }
};

void TArrayPPAC::Clear()
{
	 for (Int_t i = 0; i < (Int_t)ppacname_xml.size(); i++)
	 {
			ppac_x[i] = -9999;
			ppac_y[i] = -9999;
			ppac_tsumx[i] = -9999;
			ppac_tsumy[i] = -9999;
			ppac_xzpos[i] = -9999;
			ppac_yzpos[i] = -9999;
			ppac_ta[i] = -9999;
	 }
};

void TArrayPPAC::CopyVal()
{
	 TArtPPAC *ppac;
	 Double_t t_ref;
	 for (Int_t i = 0; i < (Int_t)ppacname_xml.size(); i++)
	 {
			t_ref = 0.;
			ppac = cppac->FindPPAC((Char_t *)ref_xml[i].c_str());
			if (ppac)
			{
				 t_ref = ppac->GetTA() - 50000;
			}

			ppac = cppac->FindPPAC((Char_t *)ppacname_xml[i].c_str());
			if (ppac)
			{
				 ppac_xzpos[i] = ppac->GetXZPos();
				 ppac_yzpos[i] = ppac->GetYZPos();
				 if (ppac->GetTA() != -9999)
				 {
						ppac_ta[i] = ppac->GetTA() - t_ref;
				 }
				 ppac_x[i] = ppac->GetX();
				 ppac_y[i] = ppac->GetY();
				 ppac_tsumx[i] = ppac->GetTSumX();
				 ppac_tsumy[i] = ppac->GetTSumY();
			}
	 }
}
