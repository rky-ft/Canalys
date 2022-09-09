
#ifndef TARRAYPLA_HPP
#define TARRAYPLA_HPP

#include <iostream>
#include <string>
#include <vector>

#include <TROOT.h>
#include <TTree.h>

#include "TArtCalibPlastic.hh"
#include "TArtPlastic.hh"

class TArrayPla
{
 public:
	 TArrayPla() {};
	 ~TArrayPla() {};

	 void SetTree(TTree *t)
	 {
			otree = t;
	 };
	 void SetCalibPlastic(TArtCalibPlastic *c)
	 {
			cpla = c;
	 };

	 void SetPlastic(Char_t *plaName1_xml, Char_t *plaName_toroot);
	 void SetPlastic(Char_t *plaName1_xml, Char_t *plaName2_xml, Char_t *plaName_toroot);

	 void MakeBranch();
	 void Clear();
	 void CopyVal();

 private:
	 TTree *otree;
	 TArtCalibPlastic *cpla;
	 std::vector<std::string> planame1_xml, planame2_xml, planame_toroot, ref_xml;
	 std::vector<Double_t> pla_tl, pla_tr;
	 std::vector<Double_t> pla_tlu, pla_tld, pla_tru, pla_trd;
	 std::vector<Int_t> pla_nhit_tl, pla_nhit_tr;
	 Double_t pla_mul_tl[100][50];
	 Double_t pla_mul_tr[100][50];
	 std::vector<Int_t> pla_ql, pla_qr;
	 std::vector<Int_t> pla_qlu, pla_qld, pla_qru, pla_qrd;
	 std::vector<Double_t> pla_zoffset;
	 std::vector<Bool_t> use_MTDC, use_FourPMTtype;
};

#endif
