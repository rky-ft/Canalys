
#ifndef BREWER_HPP
#define BREWER_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
//#include <sys/time.h>

#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TStyle.h>
#include <TSystem.h>
#include <TMath.h>
#include <TCutG.h>

#include "ReConstrF3.hpp"
#include "ReConstrF5.hpp"
#include "ReConstrF7.hpp"
#include "ReConstrF8.hpp"
#include "ReConstrF9.hpp"
//#include "ReConstrF10.hpp"
#include "ReConstrF11.hpp"

#include "CalcBrho.hpp"
#include "CalcFL.hpp"
#include "CalcBeta.hpp"
#include "CalcAOQ.hpp"
#include "CalcZed.hpp"
#include "CalcZdeg.hpp"
#include "ReadPara.hpp"
#include "Variables.hpp"
#include "Flags.hpp"

#include "GlobalValue.hpp"

class Brewer
{
 public:
	 Brewer() {};
	 ~Brewer() {};

	 void Br(Char_t *rawfileDir, Char_t *rawfileName, Char_t *anafileDir, Char_t *anafileName, Int_t maxEvt, Int_t firstEvt, Int_t runNumber);

 private:
	 TTree *itree;
	 TTree *otree;

	 Int_t RunNumber;

	 Int_t rnum;
	 Double_t tstamp;
	 Int_t tbit;
	 Double_t rf;
	 Int_t id[32];

	 ReConstrF3 calibF3;
	 ReConstrF5 calibF5;
	 ReConstrF7 calibF7;
	 ReConstrF8 calibF8;
	 ReConstrF9 calibF9;
	 //ReConstrF10 calibF10;
	 ReConstrF11 calibF11;

	 std::vector<CalcBrho> calcBrho;
	 std::vector<CalcBeta> calcBeta;
	 std::vector<CalcAOQ> calcAOQ;
	 std::vector<CalcZed> calcZed;
	 std::vector<CalcZdeg> calcZdeg;

	 Variables vars;
	 Flags flags;

	 std::string paradir;

	 Double_t CBrho35;
	 Double_t CBrho57;
	 Double_t CBrho89;
	 Double_t CBrho911;
	 Double_t CBrho811;

	 void Initialization();
	 void Calc();
	 void Clear();

	 void InitBrho();
	 void InitBeta();
	 void InitAOQ();
	 void InitZed();
	 void InitZdeg();

	 void ReadCenterBrho37(std::string filename);
	 void ReadCenterBrho811(std::string filename);
};

#endif
