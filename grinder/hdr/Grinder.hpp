
#ifndef GRINDER_HPP
#define GRINDER_HPP

#include <iostream>
#include <string>
#include <time.h>

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TMath.h>
#include <TClonesArray.h>

#include "TArtBigRIPSParameters.hh"
#include "TArtEventStore.hh"
#include "TArtCalibPID.hh"
#include "TArtCalibCoin.hh"
#include "TArtStoreManager.hh"
#include "TArtEventInfo.hh"

#include <ConstrF3.hpp>
#include <ConstrF5.hpp>
#include <ConstrF7.hpp>
#include <ConstrF8.hpp>
#include <ConstrF9.hpp>
#include <ConstrF10.hpp>
#include <ConstrF11.hpp>
#include <SetPara.hpp>

#include "GlobalValue.hpp"

class Grinder
{
 public:
	 TTree *otree;
	 TArtStoreManager *sman;
	 TClonesArray *info_array;
	 TClonesArray *ppac_array;
	 TClonesArray *pla_array;
	 TClonesArray *ic_array;
	 TClonesArray *ge_array;
	 TClonesArray *fpl_array;

	 Int_t rnum;
	 ULong64_t ts;
	 Double_t tstamp;
	 Int_t tbit;
	 Double_t rf;
	 Int_t id[32];

	 ConstrF3 *cf3;
	 ConstrF5 *cf5;
	 ConstrF7 *cf7;
	 ConstrF8 *cf8;
	 ConstrF9 *cf9;
	 ConstrF10 *cf10;
	 ConstrF11 *cf11;

	 //void Initialization();
	 void MakeBranch();
	 void Clear(); // initialize variables to -9999

	 void Gr(Char_t *ridffileDir, Char_t *ridffileName, Char_t *rawfileDir, Char_t *rawfileName, Int_t maxEvt, Int_t firstEvt, Int_t runNumber);

 private:
	 //Bool_t bripsmode;
	 //Bool_t debugmode;

	 void SetTimestamp();
	 void SetTriggerbit();
	 Int_t kbhit(void);
};

#endif
