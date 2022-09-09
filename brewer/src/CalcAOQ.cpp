
#include <CalcAOQ.hpp>

void CalcAOQ::SetBrho(std::string br)
{
	 Brho = vars->GetVariableDouble(br);

	 return;
};

void CalcAOQ::SetBeta(std::string b)
{
	 Beta = vars->GetVariableDouble(b);

	 return;
};

void CalcAOQ::SetGamma(std::string g)
{
	 Gamma = vars->GetVariableDouble(g);

	 return;
};

void CalcAOQ::Calc()
{
	 if ((*Brho) > 0 && (*Beta) > 0 && (*Beta) < 1 && (*Gamma) > 1)
	 {
			AOQ = (*Brho) * clight / mnucleon / (*Beta) / (*Gamma);
	 }

	 return;
};
