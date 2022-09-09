
#ifndef RECONSTRF7_HPP
#define RECONSTRF7_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <TROOT.h>
#include <TTree.h>
#include <TMath.h>

#include "CalibPPAC.hpp"
#include "CalibPla.hpp"
#include "CalibIC.hpp"
#include "CalibGe.hpp"
#include "Variables.hpp"
#include "Flags.hpp"

class ReConstrF7
{
 public:
	 ReConstrF7();
	 ~ReConstrF7() {};

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
	 CalibGe calibge;
};

#endif
