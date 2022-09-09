
#include "Flags.hpp"

void Flags::SetFlag(Int_t *f, TString s)
{
	 intFlag.push_back(f);
	 flag_name.push_back(s);
	 flag_ch.push_back(1);
	 skip_eval.push_back(true);
};

void Flags::SetFlag(Int_t *f, TString s, Int_t ch, Bool_t skip /* = false */)
{
	 intFlag.push_back(f);
	 flag_name.push_back(s);
	 flag_ch.push_back(ch);
	 skip_eval.push_back(skip);
};

void Flags::SetFlag(TString s)
{
	 intFlag.push_back(new Int_t);
	 flag_name.push_back(s);
	 flag_ch.push_back(1);
	 skip_eval.push_back(true);
};

void Flags::SetFlag(TString s, Int_t ch, Bool_t skip /* = false */)
{
	 intFlag.push_back(new Int_t[ch]);
	 flag_name.push_back(s);
	 flag_ch.push_back(ch);
	 skip_eval.push_back(skip);
};

Int_t Flags::GetFlagCh(std::string s)
{
	 for (Int_t i = 0; i < (Int_t)flag_name.size(); i++)
	 {
			if (s.compare(flag_name[i].Data()) == 0)
			{
				 return flag_ch[i];
			}
	 }

	 exit(1);
};

Int_t *Flags::GetFlag(std::string s)
{
	 for (Int_t i = 0; i < (Int_t)flag_name.size(); i++)
	 {
			if (s.compare(flag_name[i].Data()) == 0)
			{
				 return intFlag[i];
			}
	 }

	 return 0;
};

void Flags::MakeBranch()
{
	 for (Int_t i = 0; i < (Int_t)flag_name.size(); i++)
	 {
			if (flag_ch[i] == 1)
			{
				 tout->Branch(flag_name[i], intFlag[i], flag_name[i] + TString("/I"));
			}
			else
			{
				 tout->Branch(flag_name[i], intFlag[i], flag_name[i] + Form("[%d]/I", flag_ch[i]));
			}
	 }
};

void Flags::Clear()
{
	 for (Int_t i = 0; i < (Int_t)flag_name.size(); i++)
	 {
			if (flag_ch[i] == 1)
			{
				 *(intFlag[i]) = 1;
			}
			else
			{
				 for (Int_t j = 0; j < flag_ch[i]; j++)
				 {
						intFlag[i][j] = 1;
				 }
			}
	 }
};

void Flags::Evaluate()
{
	 for (Int_t i = 0; i < (Int_t)flag_name.size(); i++)
	 {
			if (flag_ch[i] > 1 && skip_eval[i] == false)
			{
				 for (Int_t j = 1; j < flag_ch[i]; j++)
				 {
						if (!intFlag[i][j])
						{
							 intFlag[i][0] = 0;

							 break;
						}
				 }
			}
	 }
};
