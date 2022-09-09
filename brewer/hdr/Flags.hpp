
#ifndef Flags_hpp
#define Flags_hpp

#include <iostream>

#include <TROOT.h>
#include <TTree.h>

class Flags
{
 public:
	 Flags() {};
	 ~Flags() {};
	 void SetTree(TTree *t)
	 {
			tout = t;
	 };
	 void SetFlag(Int_t *f, TString s);
	 void SetFlag(Int_t *f, TString s, Int_t ch, Bool_t skip = false);

	 void SetFlag(TString s);
	 void SetFlag(TString s, Int_t ch, Bool_t skip = false);

	 Int_t GetNumFlag()
	 {
			return (Int_t)intFlag.size();
	 };
	 std::string GetFlagName(Int_t i)
	 {
			return std::string(flag_name[i].Data());
	 };
	 Int_t GetFlagCh(std::string s);

	 Int_t *GetFlag(std::string s);

	 void MakeBranch();
	 void Clear();

	 void Evaluate();

 private:
	 TTree *tout;

	 std::vector<Int_t *> intFlag;

	 std::vector<TString> flag_name;
	 std::vector<Int_t> flag_ch;
	 std::vector<Bool_t> skip_eval;
};

#endif
