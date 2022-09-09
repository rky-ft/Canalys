
#include <CalcBeta.hpp>

void CalcBeta::SetStartTiming(std::string tl, std::string tr)
{
	 TL_start = vars->GetVariableDouble(tl);
	 TR_start = vars->GetVariableDouble(tr);

	 return;
};
void CalcBeta::SetStartCharge(std::string ql, std::string qr)
{
	 QL_start = vars->GetVariableDouble(ql);
	 QR_start = vars->GetVariableDouble(qr);

	 return;
};

void CalcBeta::SetStopTiming(std::string tl, std::string tr)
{
	 TL_stop = vars->GetVariableDouble(tl);
	 TR_stop = vars->GetVariableDouble(tr);

	 return;
};
void CalcBeta::SetStopCharge(std::string ql, std::string qr)
{
	 QL_stop = vars->GetVariableDouble(ql);
	 QR_stop = vars->GetVariableDouble(qr);

	 return;
};

void CalcBeta::SetStartTiming(std::string t)
{
	 TL_start = vars->GetVariableDouble(t);
	 UseLR_Start = false;

	 return;
};
void CalcBeta::SetStartCharge(std::string q)
{
	 QL_start = vars->GetVariableDouble(q);
	 UseLR_Start = false;

	 return;
};

void CalcBeta::SetStopTiming(std::string t)
{
	 TL_stop = vars->GetVariableDouble(t);
	 UseLR_Stop = false;

	 return;
};
void CalcBeta::SetStopCharge(std::string q)
{
	 QL_stop = vars->GetVariableDouble(q);
	 UseLR_Stop = false;

	 return;
};

void CalcBeta::SetTimeStamp(std::string ts)
{
	 tstamp = vars->GetVariableDouble(ts);

	 return;
};

void CalcBeta::SetBrho(std::string br1, std::string br2)
{
	 Brho1 = vars->GetVariableDouble(br1);
	 Brho2 = vars->GetVariableDouble(br2);
	 use_TwoBrho = true;

	 return;
};

void CalcBeta::Calc()
{
	 if (offset < -9998)
	 {
			std::cout << "TOF offset is not given." << std::endl;
			exit(1);
	 }
	 else
	 {
			TOF = offset;
	 }

	 if (*TL_start < -999 || *TL_stop < -999)
	 {
			return;
	 }
	 if (UseLR_Start && *TR_start < -999)
	 {
			return;
	 }
	 if (UseLR_Stop && *TR_stop < -999)
	 {
			return;
	 }

	 if (UseLR_Start)
	 {
			TOF += -((*TL_start) + (*TR_start)) / 2;

			if (QL_start && QR_start)
			{
				 TOF += slew_factor[0] * pow((*QL_start), slew_pow[0]);
				 TOF += slew_factor[1] * pow((*QR_start), slew_pow[1]);
			}
	 }
	 else
	 {
			TOF += -(*TL_start);

			if (QL_start)
			{
				 TOF += slew_factor[0] * pow((*QL_start), slew_pow[0]);
			}
	 }

	 if (UseLR_Stop)
	 {
			TOF += ((*TL_stop) + (*TR_stop)) / 2;

			if (QL_stop && QR_stop)
			{
				 TOF += -slew_factor[2] * pow((*QL_stop), slew_pow[2]);
				 TOF += -slew_factor[3] * pow((*QR_stop), slew_pow[3]);
			}
	 }
	 else
	 {
			TOF += (*TL_stop);

			if (QL_stop)
			{
				 TOF += -slew_factor[2] * pow((*QL_stop), slew_pow[2]);
			}
	 }

	 TOF += -LumiCorr[1] * ((*tstamp) - LumiCorr[0]);
	 //std::cout << LumiCorr[1] * ((*tstamp) - LumiCorr[0]) << std::endl;

	 FL1 = calFL1.GetFL();

	 if (TOF > 0)
	 {
			if (!use_TwoBrho)
			{
				 Beta1 = (FL1 / TOF) / clight;
				 Gamma1 = 1.0 / sqrt((1 - pow(Beta1, 2)));
			}
			else if (*Brho1 > 0 && *Brho2 > 0)
			{
				 FL2 = calFL2.GetFL();
				 Double_t alpha = (*Brho2) / (*Brho1);
				 Double_t rQ = (Double_t)Q1 / Q2;

				 if (!mode_DiffQ)
				 {
						Double_t a1 = sqrt(pow(alpha * clight * TOF, 2) + pow(alpha, 2) * (alpha + 1) * (alpha - 1) * FL1 * FL1 + (1 - alpha) * (1 + alpha) * FL2 * FL2);

						Beta1 = (a1 * FL1 + FL2 * clight * TOF) / (a1 * clight * TOF + (1 - alpha) * (1 + alpha) * FL1 * FL2);
						Beta2 = (a1 * FL1 + FL2 * clight * TOF) / (pow(clight * TOF, 2) + (alpha + 1) * (alpha - 1) * FL1 * FL1);
				 }
				 else
				 {
						Double_t a1 = sqrt(pow(rQ * alpha * clight * TOF, 2) + pow(alpha, 2) * (alpha + rQ) * (alpha - rQ) * FL1 * FL1 + pow(rQ, 2) * (rQ - alpha) * (rQ + alpha) * FL2 * FL2);

						Beta1 = (a1 * FL2 + FL1 * clight * TOF * pow(alpha, 2)) / (pow(clight, 2) * pow(TOF, 2) * pow(alpha, 2) + (rQ - alpha) * (rQ + alpha) * FL2 * FL2);
						Beta2 = (a1 * FL1 + FL2 * clight * TOF * pow(rQ, 2)) / (pow(clight, 2) * pow(TOF * rQ, 2) - (rQ - alpha) * (rQ + alpha) * FL1 * FL1);
				 }

				 Gamma1 = 1.0 / sqrt((1 - pow(Beta1, 2)));
				 Gamma2 = 1.0 / sqrt((1 - pow(Beta2, 2)));
			}
	 }

	 return;
}

void CalcBeta::ReadParameters(std::string filename, Int_t run)
{
	 ReadPara rp;
	 std::string parameterlist;
	 Int_t size;

	 parameterlist = rp.ReadParameterList(filename.c_str(), run, "TStamp");
	 size = parameterlist.size();
	 if (size > 0)
	 {
			std::stringstream ss1;
			ss1 << parameterlist;

			for (Int_t i = 0; i < 2; i++)
			{
				 ss1 >> LumiCorr[i];
			}
	 }

	 parameterlist = rp.ReadParameterList(filename.c_str(), run, "Offset");
	 size = parameterlist.size();
	 if (size > 0)
	 {
			std::stringstream ss2;
			ss2 << parameterlist;
			ss2 >> offset;
	 }

	 parameterlist = rp.ReadParameterList(filename.c_str(), run, "Slew_factor");
	 size = parameterlist.size();
	 if (size > 0)
	 {
			std::stringstream ss3;
			ss3 << parameterlist;

			for (Int_t i = 0; i < 4; i++)
			{
				 ss3 >> slew_factor[i];
			}
	 }

	 parameterlist = rp.ReadParameterList(filename.c_str(), run, "Slew_pow");
	 size = parameterlist.size();
	 if (size > 0)
	 {
			std::stringstream ss4;
			ss4 << parameterlist;

			for (Int_t i = 0; i < 4; i++)
			{
				 ss4 >> slew_pow[i];
			}
	 }

	 parameterlist = rp.ReadParameterList(filename.c_str(), run, "QState");
	 size = parameterlist.size();
	 if (size > 0)
	 {
			std::stringstream ss5;
			ss5 << parameterlist;
			ss5 >> Q1 >> Q2;
	 }

	 return;
};
