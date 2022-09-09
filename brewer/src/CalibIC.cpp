
#include <CalibIC.hpp>
#define CalibIC_cpp

void CalibIC::SetNCh(Int_t n)
{
	 nch = n;
	 if (!use_BGtype)
	 {
			nlayer = nch;
	 }
	 else
	 {
			nlayer = nch / 2;
	 }

	 return;
};

void CalibIC::SetADC(Char_t *q)
{
	 itree->SetBranchAddress(TString(q), QRaw);
	 vars->SetVariable(QRaw, TString(q), nch);

	 return;
};

void CalibIC::SetICE(Char_t *e, Char_t *esum)
{
	 vars->SetVariable(E, TString(e), nlayer);
	 vars->SetVariable(&ESum, TString(esum));

	 return;
}

void CalibIC::Calc()
{
	 for (Int_t i = 0; i < nlayer; i++)
	 {
			if (QRaw[2 * i] > 0 && QRaw[2 * i + 1] > 0)
			{
				 bgSum[i] = (QRaw[2 * i] - pedestal[2 * i]) + (QRaw[2 * i + 1] - pedestal[2 * i + 1]);
				 bgRatio[i] = (QRaw[2 * i] - pedestal[2 * i]) / (QRaw[2 * i + 1] - pedestal[2 * i + 1]);
			}
	 }

	 Int_t singleLayer[32];
	 for (Int_t i = 0; i < nlayer; i++)
	 {
			if (!use_BGtype)
			{
				 singleLayer[i] = QRaw[i] - pedestal[i];

				 //if (QRaw[i] < 0 || QRaw[i] > 4096)
				 //{
				 //   std::cout << i << QRaw[i] << std::endl;
				 //}
			}
			else
			{
				 singleLayer[i] = gainRatio * bgSum[i];
			}
	 }

	 ESum = 0;
	 for (Int_t i = 0; i < nlayer; i++)
	 {
			E[i] = ch2MeV[i][0] + ch2MeV[i][1] * singleLayer[i];
			ESum += E[i];
	 }

	 return;
};

void CalibIC::ReadParameters(const Char_t *filename, Int_t run)
{
	 ReadPara rp;
	 std::string parameterlist;
	 Int_t size;

	 parameterlist = rp.ReadParameterList(filename, run, "Pedestal");
	 size = parameterlist.size();
	 if (size > 0)
	 {
			std::stringstream ss1;
			ss1 << parameterlist;
			for (Int_t i = 0; i < nch; i++)
			{
				 ss1 >> pedestal[i];
			}
	 }

	 parameterlist = rp.ReadParameterList(filename, run, "GainRatio");
	 size = parameterlist.size();
	 if (size > 0)
	 {
			std::stringstream ss2;
			ss2 << parameterlist;
			ss2 >> gainRatio;
	 }

	 parameterlist = rp.ReadParameterList(filename, run, "Ch2MeV");
	 size = parameterlist.size();
	 if (size > 0)
	 {
			std::stringstream ss3;
			ss3 << parameterlist;
			for (Int_t i = 0; i < nlayer; i++)
			{
				 for (Int_t j = 0; j < 2; j++)
				 {
						ss3 >> ch2MeV[i][j];
				 }
			}
	 }

	 return;
};
