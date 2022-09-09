
#ifndef CONSTRF9_HPP
#define CONSTRF9_HPP

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

class ConstrF9
{
 public:
	 TTree *otree;
	 TArtCalibPPAC *cppac;
	 TArtCalibFocalPlane *cfpl;

	 TArrayPPAC *appac;

	 ConstrF9()
	 {
	 }
	 virtual ~ConstrF9()
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
