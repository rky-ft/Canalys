
#include "TArrayIC.hpp"

void TArrayIC::SetIC(Char_t *icName_xml, Char_t *icName_toroot, Int_t ch)
{
	 icname_xml.push_back(std::string(icName_xml));
	 icname_toroot.push_back(std::string(icName_toroot));
	 ic_ch.push_back(ch);

	 return;
};

void TArrayIC::MakeBranch()
{
	 ic_geoave.resize(icname_xml.size());
	 for (Int_t i = 0; i < (Int_t)icname_xml.size(); i++)
	 {
			if (icname_toroot[i].find("ICP") == std::string::npos)
			{
				 otree->Branch(Form("%s_q", icname_toroot[i].c_str()), ic_adc[i], Form("%s_q[%d]/I", icname_toroot[i].c_str(), ic_ch[i]));
				 otree->Branch(Form("%s_geoave", icname_toroot[i].c_str()), &(ic_geoave[i]), Form("%s_geoave/D", icname_toroot[i].c_str()));
			}
			else
			{
				 otree->Branch(Form("%s", icname_toroot[i].c_str()), ic_adc[i], Form("%s/I", icname_toroot[i].c_str()));
			}
	 }
};

void TArrayIC::Clear()
{
	 for (Int_t i = 0; i < (Int_t)icname_xml.size(); i++)
	 {
			for (Int_t j = 0; j < (Int_t)ic_ch[i]; j++)
			{
				 ic_adc[i][j] = -9999;
			}

			ic_geoave[i] = -9999;
	 }
};

void TArrayIC::CopyVal()
{
	 TArtIC *ic;
	 for (Int_t i = 0; i < (Int_t)icname_xml.size(); i++)
	 {
			ic = cic->FindIC((Char_t *)icname_xml[i].c_str());
			if (ic)
			{
				 for (Int_t j = 0; j < ic_ch[i]; j++)
				 {
						ic_adc[i][j] = ic->GetRawADC(j);
				 }

				 if (!use_BGtype)
				 {
						ic_geoave[i] = ic->GetRawADCSqSum();
				 }
				 else // backgammon type
				 {
						ic_geoave[i] = 1.0;
						for (Int_t j = 0; j < ic_ch[i] - 1; j += 2)
						{
							 ic_geoave[i] *= (Double_t)(ic_adc[i][j] + ic_adc[i][j + 1]);
						}

						ic_geoave[i] = pow(ic_geoave[i], 1 / ((Double_t)ic_ch[i] / 2));
				 }
			}
	 }
}
