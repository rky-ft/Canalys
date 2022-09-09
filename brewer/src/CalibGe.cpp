
#include <CalibGe.hpp>

void CalibGe::SetOriginalEnergy(char *en)
{
	 itree->SetBranchAddress(TString(en), Eoriginal);
};
void CalibGe::SetOriginalTiming(char *time)
{
	 itree->SetBranchAddress(TString(time), Toriginal);
};
void CalibGe::SetReCalibEnergy(char *en)
{
	 vars->SetVariable(Energy, TString(en), nGe);
};
void CalibGe::SetReCalibTiming(char *time)
{
	 vars->SetVariable(Timing, TString(time), nGe);
};

void CalibGe::Calc()
{
	 for (Int_t i = 0; i < nGe; i++)
	 {
			Timing[i] = Toriginal[i] + offset[i];
			Energy[i] = MeV2MeV[i][0] + MeV2MeV[i][1] * Eoriginal[i];
	 }

	 return;
};

void CalibGe::ReadParameters(const char *filename, Int_t run)
{
	 ReadPara rp;
	 std::string parameterlist;

	 Int_t size;

	 parameterlist = rp.ReadParameterList(filename, run, "Offset");
	 size = parameterlist.size();
	 if (size > 0)
	 {
			std::stringstream ss1;
			ss1 << parameterlist;
			for (Int_t i = 0; i < nGe; i++)
			{
				 ss1 >> offset[i];
			}
	 }

	 parameterlist = rp.ReadParameterList(filename, run, "Ecal");
	 size = parameterlist.size();
	 if (size > 0)
	 {
			std::stringstream ss2;
			ss2 << parameterlist;
			for (Int_t i = 0; i < nGe; i++)
			{
				 ss2 >> MeV2MeV[i][0] >> MeV2MeV[i][1];
			}
	 }
	 return;
};
