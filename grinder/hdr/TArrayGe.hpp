
#ifndef TARRAYGE_HPP
#define TARRAYGE_HPP

#include <iostream>
#include <string>
#include <vector>

#include <TROOT.h>
#include <TTree.h>
#include <TRandom3.h>

#include "TArtCalibGe.hh"
#include "TArtGe.hh"
#include "TArtGePara.hh"

class TArrayGe
{
 public:
	 TArrayGe()
	 {
			ge_ch = 0;
	 };
	 ~TArrayGe() {};

	 void SetTree(TTree *t)
	 {
			otree = t;
	 };
	 void SetCalibGe(TArtCalibGe *c)
	 {
			cge = c;
	 };
	 void SetGe_xml(char *geName_xml);
	 void SetGe_root(char *geName_toroot);

	 void MakeBranch();
	 void Clear();
	 void CopyVal();

 private:
	 TTree *otree;
	 TArtCalibGe *cge;
	 std::vector<std::string> gename_xml;
	 std::string gename_toroot;
	 Int_t ge_tdc[16], ge_adc[16], ge_ch;
	 Double_t ge_t[16], ge_e[16];
	 TRandom3 random;
};

#endif
