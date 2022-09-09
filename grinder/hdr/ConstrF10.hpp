
#ifndef CONSTRF10_HPP
#define CONSTRF10_HPP

#include <iostream>
#include <string>

#include <TROOT.h>
#include <TTree.h>
#include <TMath.h>

#include "TArtCalibPPAC.hh"
#include "TArtCalibFocalPlane.hh"
#include "TArtPPAC.hh"
#include "TArtFocalPlane.hh"

#include "TArrayPPAC.hpp"

class ConstrF10
{
 public:
	 TTree *otree;
	 TArtCalibPPAC *cppac;
	 TArtCalibFocalPlane *cfpl;

	 TArrayPPAC *appac;

	 ConstrF10()
	 {
	 }
	 virtual ~ConstrF10()
	 {
	 }
	 void SetTree(TTree *t)
	 {
			otree = t;
	 }
	 void SetCalibPPAC(TArtCalibPPAC *c)
	 {
			cppac = c;
	 }
	 void SetCalibFocalPlane(TArtCalibFocalPlane *c)
	 {
			cfpl = c;
	 }

	 void MakeBranch();
	 void Clear();
	 void CopyVal();
};

#endif
