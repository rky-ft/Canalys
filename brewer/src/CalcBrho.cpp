
#include <CalcBrho.hpp>

void CalcBrho::SetInitialPosAng(std::string xi, std::string yi, std::string bi)
{
	 Xi = vars->GetVariableDouble(xi);
	 Yi = vars->GetVariableDouble(yi);
	 Bi = vars->GetVariableDouble(bi);

	 return;
};
void CalcBrho::SetInitialPos(std::string xi)
{
	 Xi = vars->GetVariableDouble(xi);
	 Yi = &Yidummy;
	 Bi = &Bidummy;

	 return;
};

void CalcBrho::SetFinalPosAng(std::string xf, std::string af)
{
	 Xf = vars->GetVariableDouble(xf);
	 Af = vars->GetVariableDouble(af);

	 return;
};
void CalcBrho::SetFinalPos(std::string xf)
{
	 Xf = vars->GetVariableDouble(xf);
	 Af = &Afdummy;

	 return;
};

void CalcBrho::SetCenterBrho(Double_t cbr)
{
	 CenterBrho = cbr;

	 return;
};

void CalcBrho::Calc()
{
	 epsilon = 1.0;
	 nita = 0;

	 Double_t ai, di; // initial value for root finder

	 CalcFirstOrder(di, ai);

	 if (di > 5.0 || di < -5.0)
	 {
			Ai = ai;
			Delta = di;
			fCalculated = false;

			return;
	 }

	 if ((*Yi) < -9998 || (*Bi) < -9998)
	 {
			use_YB = false;
	 }
	 else
	 {
			use_YB = true;
	 }

	 Double_t limit = 0.000001;

	 while (nita < 20 && epsilon > limit)
	 {
			vec0(0, 0) = ai;
			vec0(1, 0) = di;

			// drv = derivation (微分)

			func_drv(0, 0) = -(mat(1, 0) + mat(7, 0) * (*Xi) + mat(12, 0) * 2 * ai + mat(16, 0) * di + (*Xi) * (*Xi) * mat(28, 0) + di * di * mat(62, 0) + 2 * ai * (mat(33, 0) * (*Xi) + mat(48, 0) * ai / 2.0 * 3 + mat(52, 0) * di) + mat(37, 0) * (*Xi) * di);
			if (use_YB)
			{
				 func_drv(0, 0) += -((*Yi) * (*Yi) * mat(53, 0) + (*Bi) * (*Bi) * mat(57, 0) + mat(54, 0) * (*Yi) * (*Bi));
			}
			//std::cout << "(0, 0) = " << func_drv(0, 0) << std::endl;

			func_drv(1, 0) = -(mat(1, 1) + mat(7, 1) * (*Xi) + mat(12, 1) * 2 * ai + mat(16, 1) * di + (*Xi) * (*Xi) * mat(28, 1) + di * di * mat(62, 1) + 2 * ai * (mat(33, 1) * (*Xi) + mat(48, 1) * ai / 2.0 * 3 + mat(52, 1) * di) + mat(37, 1) * (*Xi) * di);
			if (use_YB)
			{
				 func_drv(1, 0) += -((*Yi) * (*Yi) * mat(53, 1) + (*Bi) * (*Bi) * mat(57, 1) + mat(54, 1) * (*Yi) * (*Bi));
			}
			//std::cout << "(1, 0) = " << func_drv(1, 0) << std::endl;

			func_drv(0, 1) = -(mat(5, 0) + mat(11, 0) * (*Xi) + mat(16, 0) * ai + mat(26, 0) * 2 * di + (*Xi) * (*Xi) * mat(32, 0) + ai * ai * mat(52, 0) + 2 * di * (mat(47, 0) * (*Xi) + mat(62, 0) * ai + mat(82, 0) * di / 2.0 * 3) + mat(37, 0) * (*Xi) * ai);
			if (use_YB)
			{
				 func_drv(0, 1) += -((*Yi) * (*Yi) * mat(66, 0) + (*Bi) * (*Bi) * mat(75, 0) + mat(69, 0) * (*Yi) * (*Bi));
			}
			//std::cout << "func_drv(0, 1) = " << func_drv(0, 1) << std::endl;

			func_drv(1, 1) = -(mat(5, 1) + mat(11, 1) * (*Xi) + mat(16, 1) * ai + mat(26, 1) * 2 * di + (*Xi) * (*Xi) * mat(32, 1) + ai * ai * mat(52, 1) + 2 * di * (mat(47, 1) * (*Xi) + mat(62, 1) * ai + mat(82, 1) * di / 2.0 * 3) + mat(37, 1) * (*Xi) * ai);
			if (use_YB)
			{
				 func_drv(1, 1) += -((*Yi) * (*Yi) * mat(66, 1) + (*Bi) * (*Bi) * mat(75, 1) + mat(69, 1) * (*Yi) * (*Bi));
			}
			//std::cout << "func_drv(1, 1) = " << func_drv(1, 1) << std::endl;

			//func_drv.Print();

			func_drv.Invert();

			//func_drv.Print();

			func(0, 0) = (*Xf) - (mat(0, 0) * (*Xi) + mat(1, 0) * ai + mat(5, 0) * di + // first order
			                      mat(6, 0) * (*Xi) * (*Xi) + mat(7, 0) * (*Xi) * ai + mat(11, 0) * (*Xi) * di + // second order
			                      mat(12, 0) * ai * ai + mat(16, 0) * ai * di + mat(26, 0) * di * di + (*Xi) * (*Xi) * (mat(27, 0) * (*Xi) + mat(28, 0) * ai + mat(32, 0) * di) + // third order
			                      ai * ai * (mat(33, 0) * (*Xi) + mat(48, 0) * ai + mat(52, 0) * di) + di * di * (mat(47, 0) * (*Xi) + mat(62, 0) * ai + mat(82, 0) * di) + mat(37, 0) * (*Xi) * ai * di);
			if (use_YB)
			{
				 func(0, 0) += -(mat(17, 0) * (*Yi) * (*Yi) + mat(18, 0) * (*Yi) * (*Bi) + mat(21, 0) * (*Bi) * (*Bi) + // second order
				                 (*Yi) * (*Yi) * (mat(38, 0) * (*Xi) + mat(53, 0) * ai + mat(66, 0) * di) + // third order
				                 (*Bi) * (*Bi) * (mat(42, 0) * (*Xi) + mat(57, 0) * ai + mat(75, 0) * di) + mat(39, 0) * (*Xi) * (*Yi) * (*Bi) + mat(54, 0) * ai * (*Yi) * (*Bi) + mat(69, 0) * (*Yi) * (*Bi) * di);
			}

			func(1, 0) = (*Af) - (mat(0, 1) * (*Xi) + mat(1, 1) * ai + mat(5, 1) * di + // first order
			                      mat(6, 1) * (*Xi) * (*Xi) + mat(7, 1) * (*Xi) * ai + mat(11, 1) * (*Xi) * di + // second order
			                      mat(12, 1) * ai * ai + mat(16, 1) * ai * di + mat(26, 1) * di * di + (*Xi) * (*Xi) * (mat(27, 1) * (*Xi) + mat(28, 1) * ai + mat(32, 1) * di) + // third order
			                      ai * ai * (mat(33, 1) * (*Xi) + mat(48, 1) * ai + mat(52, 1) * di) + di * di * (mat(47, 1) * (*Xi) + mat(62, 1) * ai + mat(82, 1) * di) + mat(37, 1) * (*Xi) * ai * di);
			if (use_YB)
			{
				 func(1, 0) += -(mat(17, 1) * (*Yi) * (*Yi) + mat(18, 1) * (*Yi) * (*Bi) + mat(21, 1) * (*Bi) * (*Bi) + // second order
				                 (*Yi) * (*Yi) * (mat(38, 1) * (*Xi) + mat(53, 1) * ai + mat(66, 1) * di) + // third order
				                 (*Bi) * (*Bi) * (mat(42, 1) * (*Xi) + mat(57, 1) * ai + mat(75, 1) * di) + mat(39, 1) * (*Xi) * (*Yi) * (*Bi) + mat(54, 0) * ai * (*Yi) * (*Bi) + mat(69, 0) * (*Yi) * (*Bi) * di);
			}

			//func.Print();

			vec1 = vec0 - func_drv * func;

			//TMatrixD test(2, 1);

			//test = func_drv * func;

			//test.Print();

			epsilon = func(0, 0) * func(0, 0) + func(1, 0) * func(1, 0);

			ai = vec1(0, 0);
			//std::cout << " a1 = " << vec1(0, 0) << " (" << nita << ") " << std::endl;

			di = vec1(1, 0);
			nita++;
	 }

	 if (epsilon > limit)
	 {
			Ai = ai;
			Delta = di;
			fCalculated = false;
			//std::cout << " a1 = " << vec1(0, 0) << std::endl;
			//std::cout << " d1 = " << vec1(1, 0) << std::endl;
			//std::cout << " e = " << epsilon << std::endl;
	 }
	 else
	 {
			Ai = vec1(0, 0);
			Delta = vec1(1, 0);
			if (fabs(Delta) < 5 && CenterBrho != -9999)
			{
				 Brho = CenterBrho * (1.0 + Delta * 0.01);
			}
			fCalculated = true;
	 }

	 return;
};

void CalcBrho::CalcFirstOrder(Double_t &delta1, Double_t &ai1)
{
	 if ((*Xi) < -9998 || (*Xf) < -9998 || (*Af) < -9998)
	 {
			delta1 = -9999;
			ai1 = -9999;

			return;
	 }

	 Double_t denominator = mat(1, 1) * mat(5, 0) - mat(1, 0) * mat(5, 1);
	 delta1 = mat(1, 1) * (*Xf) - mat(1, 0) * (*Af) + (mat(0, 1) * mat(1, 0) - mat(0, 0) * mat(1, 1)) * (*Xi);
	 delta1 = delta1 / denominator;
	 ai1 = mat(5, 1) * (*Xf) - mat(5, 0) * (*Af) + (mat(0, 1) * mat(5, 0) - mat(0, 0) * mat(5, 1)) * (*Xi);
	 ai1 = -ai1 / denominator;

	 return;
};

void CalcBrho::ReadParameters(std::string filename, std::string paradir)
{
	 std::ifstream fin((paradir + std::string("/") + filename).c_str());
	 if (!fin.is_open())
	 {
			std::cout << "Parameter file: " << filename << " can not be opened." << std::endl;
			exit(1);
	 }

	 Double_t val[6];
	 for (Int_t i = 0; i < 83; i++)
	 {
			fin >> val[0] >> val[1] >> val[2] >> val[3] >> val[4] >> val[5];
			for (Int_t j = 0; j < 5; j++)
			{
				 mat(i, j) = val[j];
			}
	 }
	 fin.close();

	 return;
};

void CalcBrho::ReadParameters(std::string filename, std::string paradir, Int_t run)
{
	 SetPara fpar((paradir + std::string("/") + filename).c_str());
	 std::string file = fpar.GetFileName(run);
	 ReadParameters(file, paradir);

	 return;
};
