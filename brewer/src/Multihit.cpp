
#include <Multihit.hpp>
#define Multihit_cpp

void Multihit::Calc()
{
	 if (!use_LR)
	 {
			NhitTR = 0;
	 }
	 TL = -9999;
	 TR = -9999;
	 nhitTL = 0;
	 nhitTR = 0;
	 nhitTLR = 0;
	 TLforward = -9999;
	 TLbackward = -9999;
	 TRforward = -9999;
	 TRbackward = -9999;
	 TLRforward = -9999;
	 TLRbackward = -9999;

	 for (Int_t i = 0; i < NhitTL && TL < 0; i++)
	 {
			if (multiTL[i] > tl_low && multiTL[i] < tl_high)
			{
				 for (Int_t j = 0; j < NhitTR && TR < 0; j++)
				 {
						if (multiTR[j] > tr_low && multiTR[j] < tr_high && multiTL[i] - multiTR[j] > tlr_low && multiTL[i] - multiTR[j] < tlr_high)
						{
							 // coincidence detected within window:
							 TL = multiTL[i];
							 if (i > 0)
							 {
									TLforward = multiTL[i] - multiTL[i - 1];
							 }
							 if (i + 1 < NhitTL)
							 {
									TLbackward = multiTL[i + 1] - multiTL[i];
							 }
							 TR = multiTR[j];
							 if (j > 0)
							 {
									TRforward = multiTR[j] - multiTR[j - 1];
							 }
							 if (j + 1 < NhitTR)
							 {
									TRbackward = multiTR[j + 1] - multiTR[j];
							 }
						}
				 }
			}
	 }

	 // find forward and backward with L-R coincidence
	 if (TL > 0)
	 {
			for (Int_t i = 0; i < NhitTL; i++)
			{
				 for (Int_t j = 0; j < NhitTR; j++)
				 {
						if (multiTL[i] - multiTR[j] > tlr_low && multiTL[i] - multiTR[j] < tlr_high)
						{
							 nhitTLR++;
							 // coincidence detected:
							 if (TL > multiTL[i])
							 {
									TLRforward = TL - multiTL[i];
							 }
							 if (TL < multiTL[i] && TLRbackward < 0)
							 {
									TLRbackward = multiTL[i] - TL;
							 }
						}
				 }
			}
	 }

	 for (Int_t i = 0; i < NhitTL; i++)
	 {
			if (multiTL[i] > tl_low && multiTL[i] < tl_high)
			{
				 nhitTL++;
				 if (TL < 0)
				 {
						TL = multiTL[i];
						if (i > 0)
						{
							 TLforward = multiTL[i] - multiTL[i - 1];
						}
						if (i + 1 < NhitTL)
						{
							 TLbackward = multiTL[i + 1] - multiTL[i];
						}
				 }
			}
	 }

	 for (Int_t i = 0; i < NhitTR; i++)
	 {
			if (multiTR[i] > tr_low && multiTR[i] < tr_high)
			{
				 nhitTR++;
				 if (TR < 0)
				 {
						TR = multiTR[i];
						if (i > 0)
						{
							 TRforward = multiTR[i] - multiTR[i - 1];
						}
						if (i + 1 < NhitTR)
						{
							 TRbackward = multiTR[i + 1] - multiTR[i];
						}
				 }
			}
	 }
};
