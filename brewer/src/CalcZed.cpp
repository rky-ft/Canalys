
#include <CalcZed.hpp>

void CalcZed::SetBeta(std::string b)
{
	 Beta = vars->GetVariableDouble(b);
};

void CalcZed::SetDeltaE(std::string de)
{
	 dE1 = vars->GetVariableDouble(de);
};

void CalcZed::SetDelta(std::string d)
{
	 Delta = vars->GetVariableDouble(d);
};

void CalcZed::SetTotE(std::string e)
{
	 TotE = vars->GetVariableDouble(e);
	 use_TKEmode = true;
};

void CalcZed::Calc()
{
	 //if (*Beta < 0 || *Beta > 1 || *dE1 < 0)
	 if (*Beta < 0 || *Beta > 1)
	 {
			return;
	 }

	 //Double_t delE = 0.;
	 //for (Int_t i = 0; i < nlayer; i++)
	 //{
	 //   delE += dE1[i];
	 //}

	 nvalid = 0;
	 Double_t delE = 0.;
	 for (Int_t i = 0; i < nlayer; i++)
	 {
			if (dE1[i] > 0)
			{
				 delE += dE1[i];
				 nvalid += 1;
			}
	 }

	 //if (nvalid >= 1)
	 //{
	 //   delE = delE / nvalid * nlayer;
	 //}
	 //else
	 //{
	 //   delE = -9999;
	 //}

	 if (!use_TKEmode)
	 {
			Double_t C1 = (Length / 10) * Material * Density;
			Double_t de_v = log(ionpair * pow(*Beta, 2)) - log(1 - pow(*Beta, 2)) - pow(*Beta, 2);
			Zic_tmp = sqrt(delE / de_v / 0.307 / C1) * (*Beta) - Corr[0] * (*Beta);
	 }
	 else
	 {
			Zic_tmp = sqrt(delE) * (*Beta) - Corr[0] * (*TotE) - Corr[1] * pow((*TotE), 2) - Corr[2] * pow((*TotE), 3);
	 }

	 Zed = ZCoef[0] + ZCoef[1] * Zic_tmp + ZCoef[2] * pow(Zic_tmp, 2);

	 return;
};

void CalcZed::ReadParameters(std::string filename, Int_t run)
{
	 ReadPara rp;
	 std::string parameterlist;
	 Int_t size;

	 parameterlist = rp.ReadParameterList(filename.c_str(), run, "ICEnv");
	 size = parameterlist.size();
	 if (size > 0)
	 {
			std::stringstream ss1;
			ss1 << parameterlist;
			ss1 >> Length >> Material >> Density;
	 }

	 parameterlist = rp.ReadParameterList(filename.c_str(), run, "ICLayer");
	 size = parameterlist.size();
	 if (size > 0)
	 {
			std::stringstream ss2;
			ss2 << parameterlist;
			ss2 >> nlayer;
	 }

	 parameterlist = rp.ReadParameterList(filename.c_str(), run, "BetaCorr");
	 size = parameterlist.size();
	 if (size > 0)
	 {
			std::stringstream ss3;
			ss3 << parameterlist;
			ss3 >> Corr[0];
	 }

	 parameterlist = rp.ReadParameterList(filename.c_str(), run, "TotECorr");
	 size = parameterlist.size();
	 if (size > 0)
	 {
			std::stringstream ss4;
			ss4 << parameterlist;
			ss4 >> Corr[0] >> Corr[1] >> Corr[2];
	 }

	 parameterlist = rp.ReadParameterList(filename.c_str(), run, "ZCoef");
	 size = parameterlist.size();
	 if (size > 0)
	 {
			std::stringstream ss5;
			ss5 << parameterlist;
			ss5 >> ionpair >> ZCoef[0] >> ZCoef[1] >> ZCoef[2];
	 }

	 return;
};
