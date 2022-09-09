
#ifndef CONSTRF5_HPP
#define CONSTRF5_HPP

#include <iostream>
#include <string>

#include <TROOT.h>
#include <TTree.h>
#include <TMath.h>

#include "TArtCalibPPAC.hh"
#include "TArtCalibPlastic.hh"
#include "TArtCalibFocalPlane.hh"
#include "TArtPPAC.hh"
#include "TArtPlastic.hh"
#include "TArtFocalPlane.hh"

#include "TArrayPPAC.hpp"
#include "TArrayPla.hpp"

class ConstrF5
{
 public:
	 TTree *otree;
	 TArtCalibPPAC *cppac;
	 TArtCalibPlastic *cpla;
	 TArtCalibFocalPlane *cfpl;

	 TArrayPPAC *appac;
	 TArrayPla *apla;

	 ConstrF5()
	 {
	 }
	 virtual ~ConstrF5()
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
	 void SetCalibPlastic(TArtCalibPlastic *c)
	 {
			cpla = c;
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
