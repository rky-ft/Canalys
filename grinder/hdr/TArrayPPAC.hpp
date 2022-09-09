
#ifndef TARRAYPPAC_HPP
#define TARRAYPPAC_HPP

#include <iostream>
#include <string>
#include <vector>

#include <TROOT.h>
#include <TTree.h>

#include "TArtCalibPPAC.hh"
#include "TArtPPAC.hh"

class TArrayPPAC
{
 public:
	 TArrayPPAC() {};
	 ~TArrayPPAC() {};
	 void SetTree(TTree *t)
	 {
			otree = t;
	 };
	 void SetCalibPPAC(TArtCalibPPAC *c)
	 {
			cppac = c;
	 };
	 void SetPPAC(Char_t *ppacName_xml, Char_t *ppacName_toroot);
	 void SetPPAC(Char_t *ppacName_xml, Char_t *Ref_xml, Char_t *ppacName_toroot);

	 void MakeBranch();
	 void Clear();
	 void CopyVal();

 private:
	 TTree *otree;
	 TArtCalibPPAC *cppac;
	 std::vector<std::string> ppacname_xml, ppacname_toroot, ref_xml;
	 std::vector<Double_t> ppac_x, ppac_y, ppac_tsumx, ppac_tsumy;
	 std::vector<Double_t> ppac_xzpos, ppac_yzpos, ppac_ta;
};

#endif
