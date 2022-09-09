
#ifndef TARRAYIC_HPP
#define TARRAYIC_HPP

#include <iostream>
#include <string>
#include <vector>

#include <TROOT.h>
#include <TTree.h>

#include "TArtCalibIC.hh"
#include "TArtIC.hh"

class TArrayIC
{
 public:
	 TArrayIC()
	 {
			use_BGtype = false;
	 };
	 ~TArrayIC() {};

	 void SetTree(TTree *t)
	 {
			otree = t;
	 };
	 void SetCalibIC(TArtCalibIC *c)
	 {
			cic = c;
	 };
	 void SetIC(Char_t *icName_xml, Char_t *icName_toroot, Int_t ch);
	 void SetBGtype()
	 {
			use_BGtype = true;
	 };

	 void MakeBranch();
	 void Clear();
	 void CopyVal();

 private:
	 TTree *otree;
	 TArtCalibIC *cic;
	 std::vector<std::string> icname_xml, icname_toroot;
	 std::vector<Int_t> ic_ch;
	 Int_t ic_adc[2][32];
	 std::vector<Double_t> ic_geoave;
	 Bool_t use_BGtype;
};

#endif
