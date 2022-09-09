
#include <CalcFL.hpp>

void CalcFL::SetPosAngDelta(std::string x, std::string a, std::string y, std::string b, std::string del)
{
	 pX = vars->GetVariableDouble(x);
	 pA = vars->GetVariableDouble(a);
	 pY = vars->GetVariableDouble(y);
	 pB = vars->GetVariableDouble(b);
	 pdelta = vars->GetVariableDouble(del);

	 return;
};
void CalcFL::SetPosDelta(std::string x, std::string del)
{
	 pX = vars->GetVariableDouble(x);
	 pdelta = vars->GetVariableDouble(del);

	 return;
};

void CalcFL::Calc()
{
	 Double_t X = 0;
	 Double_t Y = 0;
	 Double_t A = 0;
	 Double_t B = 0;
	 Double_t delta = 0;
	 if (pX != 0)
	 {
			X = *pX;
	 }
	 if (pA != 0)
	 {
			A = *pA;
	 }
	 if (pY != 0)
	 {
			Y = *pY;
	 }
	 if (pB != 0)
	 {
			B = *pB;
	 }
	 if (pdelta != 0)
	 {
			delta = *pdelta;
	 }

	 if (FLc < 0)
	 {
			std::cout << "Flight length is not given." << std::endl;
			exit(1);
	 }
	 FL = FLc;

	 if (Y < -9998 || B < -9998)
	 {
			use_YB = false;
	 }
	 else
	 {
			use_YB = true;
	 }

	 if (X > -9999 && A > -9999 && delta > -9999)
	 {
			FL = FLc - (mat(0, 4) * X + mat(1, 4) * A + mat(5, 4) * delta + // first order
			            mat(6, 4) * X * X + mat(7, 4) * X * A + mat(11, 4) * X * delta + // second order
			            mat(12, 4) * A * A + mat(16, 4) * A * delta + mat(26, 4) * delta * delta + X * X * (mat(27, 4) * X + mat(28, 4) * A + mat(32, 4) * delta) + // third order
			            A * A * (mat(33, 4) * X + mat(48, 4) * A + mat(52, 4) * delta) + delta * delta * (mat(47, 4) * X + mat(62, 4) * A + mat(82, 4) * delta) + mat(37, 4) * X * A * delta);
			if (use_YB)
			{
				 FL += -(mat(17, 4) * Y * Y + mat(18, 4) * Y * B + mat(21, 4) * B * B + // second order
				         Y * Y * (mat(38, 4) * X + mat(53, 4) * A + mat(66, 4) * delta) + // third order
				         B * B * (mat(42, 4) * X + mat(57, 4) * A + mat(75, 4) * delta) + mat(39, 4) * X * Y * B + mat(54, 4) * A * Y * B + mat(69, 4) * Y * B * delta);
			}
	 }

	 return;
}

void CalcFL::ReadParameters(std::string filename, TMatrixD &ma)
{
	 std::ifstream fin(filename.c_str());
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
				 ma(i, j) = val[j];
			}
	 }
	 fin.close();

	 return;
};

void CalcFL::ReadParameters(std::string matrixfile, std::string paradir, Int_t run)
{
	 SetPara fpar1((paradir + std::string("/") + matrixfile).c_str());
	 std::string file1 = fpar1.GetFileName(run);
	 ReadParameters(paradir + std::string("/") + file1, mat);
};
