
#include "Variables.hpp"

void Variables::SetVariable(Int_t *v, TString s)
{
	 intVar.push_back(v);
	 var_name.push_back(s);
	 var_ch.push_back(1);
	 var_type.push_back(std::string("Int_t"));
};
void Variables::SetVariable(Int_t *v, TString s, Int_t ch)
{
	 intVar.push_back(v);
	 var_name.push_back(s);
	 var_ch.push_back(ch);
	 var_type.push_back(std::string("Int_t"));
};

void Variables::SetVariable(Double_t *v, TString s)
{
	 doubleVar.push_back(v);
	 var_name.push_back(s);
	 var_ch.push_back(1);
	 var_type.push_back(std::string("Double_t"));
};
void Variables::SetVariable(Double_t *v, TString s, Int_t ch)
{
	 doubleVar.push_back(v);
	 var_name.push_back(s);
	 var_ch.push_back(ch);
	 var_type.push_back(std::string("Double_t"));
};

void Variables::SetVariable(ULong64_t *v, TString s)
{
	 ulongVar.push_back(v);
	 var_name.push_back(s);
	 var_ch.push_back(1);
	 var_type.push_back(std::string("ULong64_t"));
};
void Variables::SetVariable(ULong64_t *v, TString s, Int_t ch)
{
	 ulongVar.push_back(v);
	 var_name.push_back(s);
	 var_ch.push_back(ch);
	 var_type.push_back(std::string("ULong64_t"));
};

std::string Variables::GetVarType(std::string s)
{
	 for (Int_t i = 0; i < (Int_t)var_name.size(); i++)
	 {
			if (s.compare(var_name[i].Data()) == 0)
			{
				 return var_type[i];
			}
	 }

	 return std::string("");
};

Int_t *Variables::GetVariableInt(std::string s)
{
	 Int_t i_int = 0;
	 for (Int_t i = 0; i < (Int_t)var_name.size(); i++)
	 {
			if (var_type[i].compare("Int_t") == 0)
			{
				 if (s.compare(var_name[i].Data()) == 0)
				 {
						return intVar[i_int];
				 }

				 i_int++;
			}
	 }

	 return 0;
};

Double_t *Variables::GetVariableDouble(std::string s)
{
	 Int_t i_double = 0;
	 for (Int_t i = 0; i < (Int_t)var_name.size(); i++)
	 {
			if (var_type[i].compare("Double_t") == 0)
			{
				 if (s.compare(var_name[i].Data()) == 0)
				 {
						return doubleVar[i_double];
				 }

				 i_double++;
			}
	 }

	 return 0;
};

ULong64_t *Variables::GetVariableULong64(std::string s)
{
	 Int_t i_ulong = 0;
	 for (Int_t i = 0; i < (Int_t)var_name.size(); i++)
	 {
			if (var_type[i].compare("ULong64_t") == 0)
			{
				 if (s.compare(var_name[i].Data()) == 0)
				 {
						return ulongVar[i_ulong];
				 }

				 i_ulong++;
			}
	 }

	 return 0;
};

void Variables::MakeBranch()
{
	 Int_t i_int = 0, i_double = 0, i_ulong = 0;
	 for (Int_t i = 0; i < (Int_t)var_name.size(); i++)
	 {
			if (var_type[i].compare("Int_t") == 0)
			{
				 if (var_ch[i] == 1)
				 {
						tout->Branch(var_name[i], intVar[i_int], var_name[i] + TString("/I"));
				 }
				 else
				 {
						tout->Branch(var_name[i], intVar[i_int], var_name[i] + Form("[%d]/I", var_ch[i]));
				 }

				 i_int++;
			}
			else if (var_type[i].compare("Double_t") == 0)
			{
				 if (var_ch[i] == 1)
				 {
						tout->Branch(var_name[i], doubleVar[i_double], var_name[i] + TString("/D"));
				 }
				 else
				 {
						tout->Branch(var_name[i], doubleVar[i_double], var_name[i] + Form("[%d]/D", var_ch[i]));
				 }

				 i_double++;
			}
			else if (var_type[i].compare("ULong64_t") == 0)
			{
				 if (var_ch[i] == 1)
				 {
						tout->Branch(var_name[i], ulongVar[i_ulong], var_name[i] + TString("/l"));
				 }
				 else
				 {
						tout->Branch(var_name[i], ulongVar[i_ulong], var_name[i] + Form("[%d]/l", var_ch[i]));
				 }

				 i_ulong++;
			}
	 }
};

void Variables::Clear()
{
	 Int_t i_int = 0, i_double = 0, i_ulong = 0;
	 for (Int_t i = 0; i < (Int_t)var_name.size(); i++)
	 {
			if (var_type[i].compare("Int_t") == 0)
			{
				 if (var_ch[i] == 1)
				 {
						*(intVar[i_int]) = -9999;
				 }
				 else
				 {
						for (Int_t j = 0; j < var_ch[i]; j++)
						{
							 intVar[i_int][j] = -9999;
						}
				 }

				 i_int++;
			}
			else if (var_type[i].compare("Double_t") == 0)
			{
				 if (var_ch[i] == 1)
				 {
						*(doubleVar[i_double]) = -9999;
				 }
				 else
				 {
						for (Int_t j = 0; j < var_ch[i]; j++)
						{
							 doubleVar[i_double][j] = -9999;
						}
				 }

				 i_double++;
			}
			else if (var_type[i].compare("ULong64_t") == 0)
			{
				 if (var_ch[i] == 1)
				 {
						*(ulongVar[i_ulong]) = 0;
				 }
				 else
				 {
						for (Int_t j = 0; j < var_ch[i]; j++)
						{
							 ulongVar[i_ulong][j] = 0;
						}
				 }

				 i_ulong++;
			}
	 }
};
