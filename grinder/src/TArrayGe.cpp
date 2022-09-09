
#include "TArrayGe.hpp"

void TArrayGe::SetGe_xml(Char_t *geName_xml)
{
	 gename_xml.push_back(std::string(geName_xml));
	 ge_ch++;

	 return;
};

void TArrayGe::SetGe_root(Char_t *geName_toroot)
{
	 gename_toroot = std::string(geName_toroot);

	 return;
};

void TArrayGe::MakeBranch()
{
	 otree->Branch(Form("%s_qraw", gename_toroot.c_str()), ge_adc, Form("%s_qraw[%d]/I", gename_toroot.c_str(), ge_ch));
	 otree->Branch(Form("%s_traw", gename_toroot.c_str()), ge_tdc, Form("%s_traw[%d]/I", gename_toroot.c_str(), ge_ch));
	 otree->Branch(Form("%s_e", gename_toroot.c_str()), ge_e, Form("%s_e[%d]/D", gename_toroot.c_str(), ge_ch));
	 otree->Branch(Form("%s_t", gename_toroot.c_str()), ge_t, Form("%s_t[%d]/D", gename_toroot.c_str(), ge_ch));
};

void TArrayGe::Clear()
{
	 for (Int_t i = 0; i < ge_ch; i++)
	 {
			ge_adc[i] = -9999;
			ge_tdc[i] = -9999;
			ge_e[i] = -9999;
			ge_t[i] = -9999;
	 }
};

void TArrayGe::CopyVal()
{
	 TArtGe *ge;
	 TArtGePara *gepara;
	 for (Int_t i = 0; i < (Int_t)gename_xml.size(); i++)
	 {
			ge = 0;
			for (Int_t j = 0; j < cge->GetNumGe(); j++)
			{
				 if (strcmp(cge->GetGe(j)->GetDetectorName()->Data(), (Char_t *)gename_xml[i].c_str()) == 0)
				 {
						ge = cge->GetGe(j);
						gepara = cge->GetGePara(j);

						break;
				 }
			}
			if (ge)
			{
				 ge_adc[i] = ge->GetRawADC();
				 ge_tdc[i] = ge->GetRawTDC();
				 ge_e[i] = ge->GetEnergy();
				 ge_e[i] += random.Uniform(-0.5, 0.5) * (gepara->GetESlope()); // To avoid bininng effect for small binning such as 1keV
				 ge_t[i] = ge->GetTiming();
			}
	 }
}
