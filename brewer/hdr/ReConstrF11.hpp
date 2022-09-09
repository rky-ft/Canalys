
#ifndef RECONSTRF11_HPP
#define RECONSTRF11_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <TROOT.h>
#include <TTree.h>
#include <TMath.h>

#include "CalibPPAC.hpp"
#include "CalibIC.hpp"
#include "CalibPla.hpp"
#include "Variables.hpp"
#include "Flags.hpp"

class ReConstrF11
{
 public:
	 ReConstrF11();
	 ~ReConstrF11() {};

	 void SetIOTree(TTree *iTree, TTree *oTree);
	 void SetVariable(Variables *vars);
	 void SetFlags(Flags *flags);

	 void Calc();

	 void ReadParameters(std::string paradir, Int_t run);

 private:
	 TTree *itree;
	 TTree *otree;

	 CalibPPAC calibppac;
	 std::vector<CalibPla> calibpla;
	 CalibIC calibic;

	 Int_t ICP;
};

#endif
