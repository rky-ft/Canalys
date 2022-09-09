
#include <CalcZdeg.hpp>

void CalcZdeg::SetBrho(std::string br1, std::string br2)
{
	 Brho1 = vars->GetVariableDouble(br1);
	 Brho2 = vars->GetVariableDouble(br2);
};

void CalcZdeg::SetBeta(std::string b1, std::string b2)
{
	 Beta1 = vars->GetVariableDouble(b1);
	 Beta2 = vars->GetVariableDouble(b2);
};

void CalcZdeg::SetPosAng(std::string pos, std::string ang)
{
	 Pos = vars->GetVariableDouble(pos);
	 Ang = vars->GetVariableDouble(ang);
};
void CalcZdeg::SetPos(std::string pos)
{
	 Pos = vars->GetVariableDouble(pos);
	 Ang = &Angdummy;
};

void CalcZdeg::Calc()
{
	 if (d0 < 0.0000001)
	 {
			return;
	 }

	 Double_t pos_deg = (*Pos) + Zpos * tan((*Ang) / 1000.);
	 Double_t thickness = d0 + pos_deg * tan(ang_deg / 1000.);
	 thickness /= cos((*Ang) / 1000.);

	 if ((*Beta1) < 0.1 || (*Beta2) < 0.1 || thickness < 0.0000001)
	 {
			return;
	 }

	 Double_t Zdeg_tmp = (*Beta1) * (*Beta1) * ((*Brho1) * Q1oZ / (*Beta1) - (*Brho2) * Q2oZ / (*Beta2)) / thickness;

	 // brho1 * Q1oZ gives brho for Q1 = Z
	 Zdeg = zcoef[0] + zcoef[1] * Zdeg_tmp + zcoef[2] * pow(Zdeg_tmp, 2);

	 return;
};

void CalcZdeg::ReadParameters(std::string filename, Int_t run)
{
	 ReadPara rp;
	 std::string parameterlist;
	 std::stringstream ss;
	 Int_t size;

	 parameterlist = rp.ReadParameterList(filename.c_str(), run, "Degrader");
	 size = parameterlist.size();
	 if (size > 0)
	 {
			ss.str("");
			ss.clear(std::stringstream::goodbit);
			ss << parameterlist;
			ss >> d0 >> ang_deg >> Zpos;
	 }

	 parameterlist = rp.ReadParameterList(filename.c_str(), run, "ZCoef");
	 size = parameterlist.size();
	 if (size > 0)
	 {
			ss.str("");
			ss.clear(std::stringstream::goodbit);
			ss << parameterlist;
			ss >> zcoef[0] >> zcoef[1] >> zcoef[2];
	 }

	 parameterlist = rp.ReadParameterList(filename.c_str(), run, "QOZ");
	 size = parameterlist.size();
	 if (size > 0)
	 {
			ss.str("");
			ss.clear(std::stringstream::goodbit);
			ss << parameterlist;
			ss >> Q1oZ >> Q2oZ;
	 }

	 return;
};
