
#ifndef Variables_hpp
#define Variables_hpp

#include <TROOT.h>
#include <TTree.h>
#include <iostream>

class Variables
{
 public:
	 Variables() {};
	 ~Variables() {};
	 void SetTree(TTree *t)
	 {
			tout = t;
	 };
	 void SetVariable(Int_t *v, TString s);
	 void SetVariable(Int_t *v, TString s, Int_t ch);
	 void SetVariable(Double_t *v, TString s);
	 void SetVariable(Double_t *v, TString s, Int_t ch);
	 void SetVariable(ULong64_t *v, TString s);
	 void SetVariable(ULong64_t *v, TString s, Int_t ch);

	 std::string GetVarType(std::string s);
	 Int_t *GetVariableInt(std::string s);
	 Double_t *GetVariableDouble(std::string s);
	 ULong64_t *GetVariableULong64(std::string s);

	 void MakeBranch();
	 void Clear();

 private:
	 TTree *tout;

	 std::vector<Int_t *> intVar;
	 std::vector<Double_t *> doubleVar;
	 std::vector<ULong64_t *> ulongVar;

	 std::vector<TString> var_name;
	 std::vector<Int_t> var_ch;
	 std::vector<std::string> var_type;
};

#endif
